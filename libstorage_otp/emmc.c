#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <linux/major.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <fs_mgr.h>
#include <cutils/properties.h>
#include <utils/Log.h>

#include "emmc.h"
#define TAG "[emmc] "

#define OTP_MOUNT_POINT "/otp"
#define FSTAB_PREFIX "/data/nvram/fstab."
#define EMMC_BLOCK_SIZE 512
#define EMMC_SIZE_PATH "/sys/block/mmcblk0/size"
#define WP_GRP_SIZE_PATH "/sys/class/mmc_host/mmc0/mmc0:0001/wp_grp_size"
#define DEVICE_BLOCK_PATH "/dev/block/mmcblk0"
char path_buffer[PATH_MAX] = {0};

static unsigned long long get_storage_size(char * size_path)
{
	FILE *fp;
	unsigned long long size = 0;
	char buffer[256] = {0};

	fp = fopen(size_path, "r");
	if (!fp) {
		OTP_LOG(TAG"Open file failed\n");
		return 0;
	}
	memset(buffer, 0, 256);
	if (fgets(buffer, 256, fp))
		size = strtoul(buffer, NULL, 0);
	fclose(fp);

	return size << 9;
}

static unsigned long long get_wp_grp_size(char* wp_grp_size_path)
{
	FILE *fp;
	unsigned long long size = 0;
	char buffer[256] = {0};

	fp = fopen(wp_grp_size_path, "r");
	if (!fp) {
		OTP_LOG(TAG"Open file failed\n");
		return 0;
	}
	memset(buffer, 0, 256);
	if (fgets(buffer, 256, fp))
		size = strtoul(buffer, NULL, 0) / 512;
	fclose(fp);
	return size;
}

static struct fstab* read_fstab(void)
{
	char fstab_filename[PROPERTY_VALUE_MAX + sizeof(FSTAB_PREFIX)];
	char propbuf[PROPERTY_VALUE_MAX];
	struct fstab *sys_fstab = NULL;

	property_get("ro.hardware", propbuf, "");
	snprintf(fstab_filename, sizeof(fstab_filename), FSTAB_PREFIX"%s", propbuf);
	sys_fstab = fs_mgr_read_fstab(fstab_filename);
	if (!sys_fstab) {
		OTP_LOG(TAG"failed to read %s \n", fstab_filename);
		return NULL;
	}

	return sys_fstab;
}

static char *get_device_path(struct fstab *sys_fstab, const char *mount_point)
{
	struct fstab_rec *rec = NULL;
	char *source = NULL;

	rec = fs_mgr_get_entry_for_mount_point(sys_fstab, mount_point);
	if (!rec) {
		OTP_LOG(TAG"failed to get entry for %s \n", mount_point);
		return NULL;
	}
	source = rec->blk_device;
	return source;
}

static void free_fstab(struct fstab *sys_fstab)
{
	fs_mgr_free_fstab(sys_fstab);
}

static int emmc_read(struct otp *otp_device, char *buffer,
		unsigned long long start, unsigned long long size)
{
	int fd = 0;
	int ret = 0;

	fd = open(otp_device->otp_blk_path, O_RDONLY);
	if (fd < 0) {
		perror(TAG"failed to open \n");
		return -1;
	}
	ret = lseek(fd, start, SEEK_SET);
	OTP_LOG(TAG"set offset is %x\n", ret);
	ret = read(fd, buffer, size);
	if (ret == -1) {
		OTP_LOG(TAG"otp read data error\n");
		return -1;
	}
	close(fd);

	return 0;

}

static unsigned int emmc_write(struct otp *otp_device, char *buffer,
		unsigned long long start, unsigned long long size)
{
	int fd = 0;
	unsigned int ret = 0;

	fd = open(otp_device->otp_blk_path, O_WRONLY);
	if (fd < 0) {
		OTP_LOG(TAG"Open otp block device failed\n");
		return errno;
	}
	lseek(fd, start, SEEK_SET);
	ret = write(fd, buffer, size);
	if (ret != size) {
		OTP_LOG(TAG"otp write data error, write size\n");
		return errno;
	}
	close(fd);

	return size;

}

int emmc_block_read(struct otp *otp_device, char *buffer,
		unsigned long long blk_offset, unsigned long long blknr)
{
	const char *path = DEVICE_BLOCK_PATH;
	struct mmc_ioc_cmd idata;
	int fd;
	int ret;
	unsigned int i;
	char *buf_temp = buffer;

	OTP_LOG(TAG"%s\n", __func__);
	if (!buffer || !otp_device) {
		OTP_LOG("NULL parameter!\n");
		return -EINVAL;
	}

	fd = open(path, O_RDONLY);
	if (fd < 0) {
		OTP_LOG("failed to open %s\n", path);
		return errno;
	}
	for (i= 0; i < blknr; i++) {
		memset(&idata, 0, sizeof(idata));
		idata.opcode = MMC_READ_SINGLE_BLOCK;
		idata.arg = blk_offset + i;
		idata.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_ADTC;
		idata.blocks = 1;
		idata.blksz = 512;
		idata.write_flag = 0;
		mmc_ioc_cmd_set_data(idata, buf_temp);
		ret = ioctl(fd, MMC_IOC_CMD, &idata);
		if (ret) {
			OTP_LOG(TAG"%s: ioctl MMC_READ_SINGLE_BLOCK error %d\n", path, ret);
			return ret;
		}
		buf_temp += 512;
	}

	close(fd);

	return ret;
}

static int emmc_block_write(struct otp *otp_device, char *buffer,
		unsigned long long blk_offset, unsigned long long blknr)
{
	const char *path = DEVICE_BLOCK_PATH;
	struct mmc_ioc_cmd idata;
	int fd;
	int ret;
	unsigned int i;
	char *buf_temp = buffer;

	OTP_LOG(TAG"%s\n", __func__);
	if (!buffer || !otp_device) {
		OTP_LOG("NULL parameter!\n");
		return -EINVAL;
	}

	fd = open(path, O_RDWR);
	if (fd < 0) {
		OTP_LOG("failed to open %s\n", path);
		return errno;
	}
	for (i= 0; i < blknr; i++) {
		memset(&idata, 0, sizeof(idata));
		idata.opcode = MMC_WRITE_BLOCK;
		idata.arg = blk_offset + i;
		idata.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_ADTC;
		idata.blocks = 1;
		idata.blksz = 512;
		idata.write_flag = 1;
		mmc_ioc_cmd_set_data(idata, buf_temp);
		ret = ioctl(fd, MMC_IOC_CMD, &idata);
		if (ret) {
			OTP_LOG(TAG"ioctl MMC_WRITE_BLOCK error %d\n", ret);
			return ret;
		}
		buf_temp += 512;
	}
	close(fd);

	return ret;
}



static int emmc_set_usr_wp(unsigned char wp)
{
	const char *path = DEVICE_BLOCK_PATH;
	struct mmc_ioc_cmd idata;
	int fd;
	int ret;

	fd = open(path, O_RDWR);
	if (fd < 0) {
		OTP_LOG(TAG"failed to open %s\n", path);
		return errno;
	}
	memset(&idata, 0, sizeof(idata));
	idata.opcode = MMC_SWITCH;
	idata.arg = (MMC_SWITCH_MODE_WRITE_BYTE << 24) |
		(EXT_CSD_USR_WP << 16) |
		(wp << 8) |
		EXT_CSD_CMD_SET_NORMAL;
	idata.flags = MMC_RSP_SPI_R1B | MMC_RSP_R1B | MMC_CMD_AC;
	idata.write_flag = 1;
	ret = ioctl(fd, MMC_IOC_CMD, &idata);

	close(fd);
	return ret;
}

/* Usually, the blknr should set to 0, Per the Spec, this command sets
 * the write protection bit of the addressed group. in general, the write
 * protect group is very big(eg, 512KB or 4MB), set any block will do write
 * protect for the group totally.
 */
static int emmc_set_write_protect(unsigned int blknr)
{
	const char *path = DEVICE_BLOCK_PATH;
	struct mmc_ioc_cmd idata;
	int fd;
	int ret = 0;

	fd = open(path, O_RDWR);
	if (fd < 0) {
		OTP_LOG(TAG"failed to open %s\n", path);
		return errno;
	}
	memset(&idata, 0, sizeof(idata));
	idata.opcode = MMC_SET_WRITE_PROT;
	idata.arg = blknr;
	idata.flags = MMC_RSP_SPI_R1B | MMC_RSP_R1B | MMC_CMD_AC;
	idata.write_flag = 1;
	ret = ioctl(fd, MMC_IOC_CMD, &idata);

	close(fd);
	return ret;
}
static int emmc_clear_write_protect(unsigned int blknr)
{
	const char *path = DEVICE_BLOCK_PATH;
	struct mmc_ioc_cmd idata;
	int fd;
	int ret = 0;

	fd = open(path, O_RDWR);
	if (fd < 0) {
		OTP_LOG(TAG"failed to open %s\n", path);
		return errno;
	}
	memset(&idata, 0, sizeof(idata));
	idata.opcode = MMC_CLR_WRITE_PROT;
	idata.arg = blknr;
	idata.flags = MMC_RSP_SPI_R1B | MMC_RSP_R1B | MMC_CMD_AC;
	idata.write_flag = 1;
	ret = ioctl(fd, MMC_IOC_CMD, &idata);

	close(fd);
	return ret;
}
static int emmc_get_write_protect_status(unsigned int blknr, unsigned int *wp_status)
{
	const char *path = DEVICE_BLOCK_PATH;
	struct mmc_ioc_cmd idata;
	int fd;
	int ret = 0;
	unsigned int status;

	fd = open(path, O_RDWR);
	if (fd < 0) {
		OTP_LOG(TAG"failed to open %s\n", path);
		return errno;
	}
	memset(&idata, 0, sizeof(idata));
	idata.opcode = MMC_SEND_WRITE_PROT;
	idata.arg = blknr;
	idata.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_ADTC;
	idata.blocks = 1;
	idata.blksz = 4;
	idata.write_flag = 0;
	mmc_ioc_cmd_set_data(idata, &status);
	ret = ioctl(fd, MMC_IOC_CMD, &idata);
	if (ret) {
		OTP_LOG(TAG"ioctl MMC_SEND_WRITE_PROT error %d\n", ret);
		return -1;
	}
	*wp_status = (status >> 24) & 0x01;

	close(fd);
	return ret;
}
static int emmc_get_write_protect_type(unsigned int blknr, unsigned int *wp_type)
{
	const char *path = DEVICE_BLOCK_PATH;
	struct mmc_ioc_cmd idata;
	int fd;
	int ret = 0;
	unsigned int type[2];

	fd = open(path, O_RDWR);
	if (fd < 0) {
		OTP_LOG(TAG"failed to open %s\n", path);
		return errno;
	}
	memset(&idata, 0, sizeof(idata));
	idata.opcode = MMC_SEND_WRITE_PROT_TYPE;
	idata.arg = blknr;
	idata.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_ADTC;
	idata.blocks = 1;
	idata.blksz = 8;
	idata.write_flag = 0;
	mmc_ioc_cmd_set_data(idata, type);
	ret = ioctl(fd, MMC_IOC_CMD, &idata);
	if (ret) {
		OTP_LOG(TAG"ioctl MMC_SEND_WRITE_PROT_TYPE error %d\n", ret);
		return -1;
	}
	*wp_type = (type[1] >> 24) & 0x03;
	close(fd);
	return ret;
}
int emmc_otp_lock(struct otp *otp_device, unsigned int type, unsigned long long start_block,
		unsigned long long group_count, unsigned long long wp_grp_size)
{
	unsigned int i;
	int ret = 0;

	if (!otp_device) {
		OTP_LOG("NULL parameter!\n");
		return -EINVAL;
	}

	switch (type) {
	case WP_TEMPORARY:
		OTP_LOG(TAG"Tpye is WP_TEMPORARY\n");
		break;
	case WP_POWER_ON:
		OTP_LOG(TAG"Tpye is WP_POWER_ON\n");
		ret = emmc_set_usr_wp(EXT_CSD_USR_WP_EN_PWR_WP);
		if (ret) {
			OTP_LOG(TAG"%s error\n", __func__);
			return -EINVAL;
		}
		break;
	case WP_PERMANENT:
		OTP_LOG(TAG"Tpye is WP_PERMANENT\n");
		//ret = emmc_set_usr_wp(EXT_CSD_USR_WP_EN_PERM_WP);
		if (ret) {
			OTP_LOG(TAG"%s error\n", __func__);
			return -EINVAL;
		}
		break;
	default:
		OTP_LOG(TAG"wp type is invalid\n");
 		break;
	}
	for (i = 0; i < group_count; i++) {
		ret = emmc_set_write_protect(start_block + (i * wp_grp_size));
		OTP_LOG(TAG"set WP at %llx\n", start_block + (i * wp_grp_size));
		if (ret) {
			OTP_LOG(TAG"%s error\n", __func__);
			return -EINVAL;
		}
	}
	return 0;
}
int emmc_otp_unlock(struct otp *otp_device, unsigned long long start_block,
		unsigned long long group_count, unsigned long long wp_grp_size)
{
	unsigned int i;
	int ret = 0;

	if (!otp_device) {
		OTP_LOG("NULL parameter!\n");
		return -EINVAL;
	}

	for (i = 0; i < group_count; i++) {
		ret = emmc_clear_write_protect(start_block + (i * wp_grp_size));
		OTP_LOG(TAG"clear WP at %llx\n", start_block + (i * wp_grp_size));
		if (ret) {
			OTP_LOG(TAG"%s error\n", __func__);
			return -EINVAL;
		}
	}
	return 0;
}
int emmc_otp_get_status(struct otp *otp_device, unsigned long long start_block,
		unsigned long long group_count,
		unsigned int *status, unsigned int *type)
{
	unsigned int wp_status = 0;
	unsigned int wp_type[2] = {0, 0};
	int ret = 0;

	if (!otp_device) {
		OTP_LOG("NULL parameter!\n");
		return -EINVAL;
	}

	if (group_count > 32) {
		OTP_LOG(TAG"%s group_count must < 32\n", __func__);
		return -EINVAL;
	}
	ret = emmc_get_write_protect_status(start_block, &wp_status);

	if (!ret)
		OTP_LOG(TAG"Address 0x%llx WP status is 0x%x\n", start_block, wp_status);
	else
		return -EINVAL;
	ret = emmc_get_write_protect_type(start_block, wp_type);
	if (!ret)
		OTP_LOG(TAG"Address 0x%llx WP type is 0x%.8x %.8x\n", start_block,
				wp_type[0], wp_type[1]);
	else
		return -EINVAL;

	*status = wp_status;
	*type = wp_type[0];
	return 0;
}

int storage_init(struct otp *otp_device)
{
	FILE *fp = NULL;
	unsigned long long storage_size = 0;
	unsigned long long otp_start = 0;
	unsigned long long otp_size = 0;
	unsigned long long wp_grp_size = 0;
	char buffer[256] = {0};
	char otp_start_path[128] = {0};
	char otp_size_path[128] = {0};
	char otp_block_name[128] = {0};
	char *otp_block_link_path = NULL;
	struct fstab *sys_fstab = NULL;
	int ret = 0;

	otp_device->block_read = emmc_block_read;
	otp_device->block_write = emmc_block_write;
	otp_device->lock = emmc_otp_lock;
	otp_device->unlock = emmc_otp_unlock;
	otp_device->get_status = emmc_otp_get_status;

	//otp_device->read = emmc_read;
	//otp_device->write = emmc_write;

	/* get emmc otp partition block device name */
	sys_fstab = read_fstab();
	otp_block_link_path = get_device_path(sys_fstab, OTP_MOUNT_POINT);
	if (otp_block_link_path == NULL) {
		OTP_LOG(TAG"get otp partition block device path failed\n");
		return -EINVAL;
	}
	ret = readlink(otp_block_link_path, otp_device->otp_blk_path, PATH_MAX);
	free_fstab(sys_fstab);

	storage_size = get_storage_size(EMMC_SIZE_PATH);
	if (storage_size == 0) {
		OTP_LOG(TAG"get_storage_size failed\n");
		return -EINVAL;
	}

	wp_grp_size = get_wp_grp_size(WP_GRP_SIZE_PATH);
	if (!wp_grp_size) {
		OTP_LOG(TAG"get_wp_grp_size failed\n");
		return -EINVAL;
	}

	memset(path_buffer, 0, PATH_MAX);

	sscanf(otp_device->otp_blk_path, "/dev/block/%s", otp_block_name);

	snprintf(path_buffer, PATH_MAX, "/sys/block/mmcblk0/%s", otp_block_name);

	strncpy(otp_start_path, path_buffer, 128);
	strncpy(otp_size_path, path_buffer, 128);
	strcat(otp_start_path, "/start");
	strcat(otp_size_path, "/size");

	OTP_LOG(TAG"Device info: block device path: %s. sysfs start path: %s\n",
		   otp_device->otp_blk_path,
 		   otp_start_path);

	memset(buffer, 0, sizeof(buffer));
	fp = fopen(otp_start_path, "r");
	if (!fp) {
		OTP_LOG(TAG"Open file failed\n");
		return errno;
	}
	if (fgets(buffer, sizeof(buffer), fp))
		otp_start = strtoul(buffer, NULL, 0);
	fclose(fp);
	memset(buffer, 0, sizeof(buffer));
	fp = fopen(otp_size_path, "r");
	if (!fp) {
		OTP_LOG(TAG"Open file failed\n");
		return errno;
	}
	if (fgets(buffer, sizeof(buffer), fp)) {
		otp_size = strtoul(buffer, NULL, 0);
	} else {
		OTP_LOG(TAG"get otp size fialed \n");
		fclose(fp);
		return errno;
	}
	fclose(fp);

	otp_device->total_size = storage_size;
	otp_device->wp_grp_size = wp_grp_size;

	if (otp_start % wp_grp_size) {
		otp_device->otp_start = otp_start + (wp_grp_size - otp_start % wp_grp_size);
		if (otp_device->otp_start > (otp_start + otp_size)) {
			OTP_LOG(TAG"Invalid otp partition, otp_start: 0x%llx, size: 0x%llx\n",
					otp_start, otp_size);
			return -EINVAL;
		} else {
			otp_device->otp_size = otp_size;
		}
	}
	otp_device->partition_start = otp_start;

	/* transfer from block to byte */
	otp_device->blk_sz = EMMC_BLOCK_SIZE;

	otp_device->total_size *= otp_device->blk_sz;
	otp_device->wp_grp_size *= otp_device->blk_sz;
	otp_device->partition_start *= otp_device->blk_sz;


	otp_device->otp_start *= otp_device->blk_sz;
	otp_device->otp_size *= otp_device->blk_sz;

	return 0;
}

