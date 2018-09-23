#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <log/log.h>
#include <sys/types.h>
#include <unistd.h>

#include <mrdump_user.h>
#include <mrdump_user_private.h>

static bool mrdump_dramlog_dump(char *buf, int *wp)
{
	if(buf == NULL || wp == NULL)
		return false;

	memset(buf, 0, MRDUMP_DRAM_KLOG_SIZE);

	struct partinfo partinfo;
	if (expdb_open(&partinfo) >= 0) {
		if (lseek64(partinfo.fd, partinfo.size - MRDUMP_OFFSET + MRDUMP_DRAM_KLOG_OFFSET, SEEK_SET) < 0) {
			ALOGE("%s: Can't seek part fd %d\n", __func__, partinfo.fd);
			close(partinfo.fd);
			return false;
		}

		*wp = read(partinfo.fd, buf, MRDUMP_DRAM_KLOG_SIZE);
		if (*wp != MRDUMP_DRAM_KLOG_SIZE) {
			ALOGE("%s: Can't read part fd %d\n", __func__, partinfo.fd);
			close(partinfo.fd);
			return false;
		}
		close(partinfo.fd);

		unsigned int *dram_klog_magic = buf;
		if (*dram_klog_magic != MRDUMP_DRAM_KLOG_MAGIC) {
			ALOGE("%s: dram klog magic mismatched, fd %d\n", __func__, partinfo.fd);
			return false;
		}

		return true;
	}
	return false;
}

bool mrdump_dramlog_get(void **data, int *len)
{
	*len = 0;
	*data = malloc(MRDUMP_DRAM_KLOG_SIZE);
	if (*data == NULL)
		return false;

	if (!mrdump_dramlog_dump(*data, len)) {
		*len = 0;
		return false;
	}

	return true;
}

void mrdump_dramlog_put(void **data)
{
	free(*data);
}
