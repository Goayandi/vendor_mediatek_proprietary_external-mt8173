/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 */
/* MediaTek Inc. (C) 2016. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
 * AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek Software")
 * have been modified by MediaTek Inc. All revisions are subject to any receiver's
 * applicable license agreements with MediaTek Inc.
 */

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <linux/ioctl.h>
#include "sysenv_utils.h"

#if defined(MTK_EMMC_SUPPORT)
#define CLASS_BLKDEV_ROOT    "/sys/class/block/mmcblk0/uevent"
#define CLASS_BLKDEV         "/sys/class/block/mmcblk0p%d/uevent"
#define ENV_BLKDEV_PATH      "/dev/block/mmcblk0p%d"
#define ENV_NAME        "para"
#elif defined(MTK_UFS_BOOTING)
// todo: add ufs device class path
#define CLASS_BLKDEV_ROOT    "/sys/class/block/mmcblk0/uevent"
#define CLASS_BLKDEV         "/sys/class/block/mmcblk0p%d/uevent"
#define ENV_BLKDEV_PATH      "/dev/block/mmcblk0p%d"
#define ENV_NAME        "para"
#else
// todo: add nand device class path
#define CLASS_BLKDEV_ROOT    "/sys/class/block/mmcblk0/uevent"
#define CLASS_BLKDEV         "/sys/class/block/mmcblk0p%d/uevent"
#define ENV_BLKDEV_PATH      "/dev/block/mmcblk0p%d"
#define ENV_NAME        "MISC"
#endif

struct env_struct g_env[SYSENV_AREA_MAX];
static int env_valid[SYSENV_AREA_MAX] = {0};
static char *env_buffer[SYSENV_AREA_MAX];
static int env_init_done[SYSENV_AREA_MAX] = {0};
static char env_path[64];

static char *get_uevent_val(char *buf, const char *target) {
    char *line, *name, *line_ptr, *val_ptr;
    line = strtok_r(buf, "\n", &line_ptr);
    while (line != NULL) {
        name = strtok_r(line, "=", &val_ptr);
        if (name && !strcmp(name, target))
            return val_ptr;
        line = strtok_r(NULL, "\n", &line_ptr);
    }
    return NULL;
}

static int get_partition_count(void)
{
    int i, fd, len, part_cnt;
    char buf[128];
    char *val_ptr;
    fd = open(CLASS_BLKDEV_ROOT, O_RDONLY);
    if (fd < 0) {
        ERR_LOG("open %s fail: %s\n", CLASS_BLKDEV_ROOT, strerror(errno));
        return -1;
    }
    memset(buf, 0, sizeof(buf));
    len = read(fd, buf, sizeof(buf) - 1);
    if (len < 0) {
        ERR_LOG("read fail: %s\n", strerror(errno));
        close(fd);
        return -1;
    }
    buf[len] = 0;
    val_ptr = get_uevent_val(buf, TAG_UEVENT_PART_CNT);
    if (val_ptr == NULL) {
        ERR_LOG("get %s from uevent fail, buf: %s\n", TAG_UEVENT_PART_CNT, buf);
        close(fd);
        return -1;
    }
    close(fd);
    DEBUG_LOG("get_partition_count ret ptr: %s\n", val_ptr);
    return atoi(val_ptr);
}

static int get_partition_path(char* path, int size)
{
    int i, fd, len, part_cnt;
    char buf[128];
    char *name;
    part_cnt = get_partition_count();
    if (part_cnt <= 0) {
        ERR_LOG("get %s from uevent fail\n", TAG_UEVENT_PART_CNT);
        return -1;
    }

    for (i = 1; i <= part_cnt; i++) {
        snprintf(buf, sizeof(buf), CLASS_BLKDEV, i);
        fd = open(buf, O_RDONLY);
        if (fd < 0) {
            ERR_LOG("open %s fail: %s\n", buf, strerror(errno));
            return -1;
        }
        memset(buf, 0, sizeof(buf));
        len = read(fd, buf, sizeof(buf) - 1);
        if (len < 0) {
            ERR_LOG("read fail: %s\n", strerror(errno));
            close(fd);
            return -1;
        }
        buf[len] = 0;
        name = get_uevent_val(buf, TAG_UEVENT_PART_NAME);
        if (name != NULL) {
            if (!strcmp(name, ENV_NAME)) {
                snprintf(path, size, ENV_BLKDEV_PATH, i);
                close(fd);
                break;
            }
        }
        close(fd);
    }
    if (i == part_cnt + 1) {
        ERR_LOG("partition path not found\n");
        return -1;
    } else {
        DEBUG_LOG("partition path = %s\n", path);
        return 0;
    }
}

static void show_env(int area)
{
    char *buffer, *line, *p;
    if (area >= 0 && area < SYSENV_AREA_MAX) {
        buffer = g_env[area].env_data;
        line = strtok_r(buffer, "\n", &p);
        while (line != NULL) {
            printf("%s\n", line);
            line = strtok_r(NULL, "\n", &p);
        }
    }
}

static int write_env_area(char *env_buf, int area)
{
    unsigned int i, checksum = 0;
    int result = 0;
    int ret = 0;
    int fd;
    off_t offset = 0;
    char env_sig[8];
    if (area >= SYSENV_AREA_MAX) {
        ERR_LOG("Invalid sysenv area %d\n", area);
        return -1;
    }
    memset(env_sig, 0, sizeof(env_sig));
    memcpy(env_sig, ENV_SIG, strlen(ENV_SIG));
    memcpy(env_buf, env_sig, sizeof(g_env[area].sig_head));
    memcpy(env_buf + CFG_ENV_SIG_1_OFFSET, env_sig, sizeof(g_env[area].sig_tail));

    for (i = 0; i < CFG_ENV_DATA_SIZE; i++)
        checksum += *(env_buf + CFG_ENV_DATA_OFFSET + i);
    *((int *)env_buf + CFG_ENV_CHECKSUM_OFFSET / 4) = checksum;
    fd = open(env_path, O_RDWR);
    if (fd < 0) {
        ERR_LOG("open %s fail: %s\n", env_path, strerror(errno));
        return -1;
    }
    if (area == SYSENV_RW_AREA)
        offset = CFG_ENV_RW_OFFSET;
    else
        offset = CFG_ENV_RO_OFFSET;
    DEBUG_LOG("seek to %lx", offset);
    if (lseek(fd, offset, SEEK_SET) != offset)
        ERR_LOG("seek to %ld fail: %s\n", offset, strerror(errno));
    ret = write(fd, (char *)env_buf, CFG_ENV_SIZE);
    if (ret < 0) {
        ERR_LOG("write env fail: %s\n", strerror(errno));
        result = -1;
    }
    DEBUG_LOG("write %x data size %d\n", (unsigned int) env_buf, ret);
    if (fsync(fd) < 0)
        WARN_LOG("write env sync fail: %s\n", strerror(errno));
    close(fd);
    return result;
}

static int read_env_area(char *env_buf, int area)
{
    int result = 0;
    int ret = 0;
    int fd;
    off_t offset = 0;

    fd = open(env_path, O_RDONLY);
    if (fd < 0) {
        ERR_LOG("open %s fail: %s\n", env_path, strerror(errno));
        return -1;
    }
    if (area == SYSENV_RW_AREA)
        offset = CFG_ENV_RW_OFFSET;
    else
        offset = CFG_ENV_RO_OFFSET;
    if (lseek(fd, offset, SEEK_SET) != offset)
        ERR_LOG("seek to %ld fail!\n", offset);
    ret = read(fd, (char *)env_buf, CFG_ENV_SIZE);
    if (ret < 0) {
        ERR_LOG("read env fail: %s\n", strerror(errno));
        result = -1;
    }
    DEBUG_LOG("read %d data from %lx to %x\n", ret, offset, (unsigned int) env_buf);
    close(fd);
    return result;
}

static char env_get_char(int index, int area)
{
    if (area < 0 || area >= SYSENV_AREA_MAX)
        area = 0;
    return *(g_env[area].env_data + index);
}

static char *env_get_addr(int index, int area)
{
    if (area < 0 || area >= SYSENV_AREA_MAX)
        area = 0;
    return g_env[area].env_data + index;

}

static int envmatch(char *s1, int i2, int area)
{
    while (*s1 == env_get_char(i2++, area)) {
        if (*s1++ == '=')
            return i2;
    }
    if (*s1 == '\0' && env_get_char(i2 - 1, area) == '=')
        return i2;
    return -1;
}

static char *findenv(const char *name, int area)
{
    int i, nxt, val;

    for (i = 0; env_get_char(i, area) != '\0'; i = nxt + 1) {
        for (nxt = i; env_get_char(nxt, area) != '\0'; ++nxt) {
            if (nxt >= CFG_ENV_SIZE)
                return NULL;
        }
        val = envmatch((char *)name, i, area);
        if (val < 0)
            continue;
        return (char *)env_get_addr(val, area);
    }
    return NULL;
}

static int get_env_valid_length(int area)
{
    unsigned int len = 0;
    if (area < 0 || area >= SYSENV_AREA_MAX)
        area = 0;
    if (!env_valid[area])
        return 0;
    for (len = 0; len < CFG_ENV_DATA_SIZE; len++) {
        if (g_env[area].env_data[len] == '\0' && g_env[area].env_data[len + 1] == '\0')
            break;
    }
    return len;
}

static void get_env_info(int area)
{
    int ret, i;
    int checksum = 0;

    DEBUG_LOG("initialize\n");

    if (!env_init_done[area]) {
        ret = get_partition_path(env_path, sizeof(env_path));
        if (ret < 0) {
            ERR_LOG("get_partition_path fail\n");
            return;
        }
        if (env_buffer[area] == NULL) {
            env_buffer[area] = malloc(CFG_ENV_SIZE);
            ERR_LOG("env_buffer[%d] : %x\n", area, (unsigned int) env_buffer[area]);
            if (!env_buffer[area]) {
                ERR_LOG("allocate %d of env buffer fail!\n", CFG_ENV_SIZE);
                return;
            }
            g_env[area].env_data = env_buffer[area] + CFG_ENV_DATA_OFFSET;
        }
    }

    ret = read_env_area(env_buffer[area], area);
    if (ret < 0) {
        ERR_LOG("read_env_area fail\n");
        free(env_buffer[area]);
        return;
    }

    memcpy(g_env[area].sig_head, env_buffer[area], sizeof(g_env[area].sig_head));
    memcpy(g_env[area].sig_tail, env_buffer[area] + CFG_ENV_SIG_1_OFFSET, sizeof(g_env[area].sig_tail));

    if (!strcmp(g_env[area].sig_head, ENV_SIG) && !strcmp(g_env[area].sig_tail, ENV_SIG)) {
        g_env[area].checksum = *((int *)env_buffer[area] + CFG_ENV_CHECKSUM_OFFSET / 4);
        for (i = 0; i < (int) CFG_ENV_DATA_SIZE; i++)
            checksum += g_env[area].env_data[i];
        if (checksum != g_env[area].checksum) {
            ERR_LOG("checksum mismatch\n");
            env_valid[area] = 0;
        } else {
            DEBUG_LOG("ENV initialize success\n");
            env_valid[area] = 1;
        }
    } else {
        WARN_LOG("Incorrect sig, probably sysenv is still empty\n");
        env_valid[area] = 0;
    }
    if (!env_valid[area])
        memset(env_buffer[area], 0x00, CFG_ENV_SIZE);

    env_init_done[area] = 1;
    return;
}


static void env_uninit(void)
{
    int i;
    for (i = 0; i < SYSENV_AREA_MAX; i++) {
        if (env_init_done[i] == 0) {
            DEBUG_LOG("not initialized before\n");
            continue; 
        }
        DEBUG_LOG("uninit\n");
        if (env_buffer[i])
            free(env_buffer[i]);
        env_init_done[i] = 0;
    }
}

char* sysenv_get_all(int area)
{
    char *ptr, *p, *env_ret, *env_ptr;
    int err = 0;
    ssize_t len = 0;
    int env_valid_length = 0;
    char buf[128];
    int i, nxt, offset = 0;

    get_env_info(area);

    if (!env_valid[area]) {
        DEBUG_LOG("sysenv is empty now\n");
        return NULL;
    }
    env_valid_length = get_env_valid_length(area);
    DEBUG_LOG("valid length of area %d is %d\n", area, env_valid_length);

    env_ret = malloc(env_valid_length + 2); // last \n + \0
    if (env_ret == NULL) {
        ERR_LOG("allocate %d buffer fail!\n", env_valid_length + 2);
        return NULL;
    }
    memset(env_ret, 0, env_valid_length + 2);
    env_ptr = env_ret;

    for (i = 0; env_get_char(i, area) != '\0'; i = nxt + 1) {
        for (nxt = i; env_get_char(nxt, area) != '\0'; ++nxt) {
            if (nxt >= (int)CFG_ENV_DATA_SIZE) {
                break;
            }
        }
        memset(buf, 0, sizeof(buf));
        if (nxt - i > (int)sizeof(buf) - 1) {
            WARN_LOG("item larger than buffer (size: %d, buf: %d)\n", nxt-i, (int)sizeof(buf));
        } else {
            if (offset + nxt - i > env_valid_length) {
                ERR_LOG("out of buffer, offset:%d, len:%d, buffer_len:%d\n", offset, nxt-i, env_valid_length);
                break;
            }
            DEBUG_LOG("offset:%d, len:%d, buffer_len:%d\n", offset, nxt-i, env_valid_length);
            memcpy(env_ret + offset, g_env[area].env_data + i, nxt - i);
            env_ret[offset + nxt - i] = '\n';
            offset = offset + nxt - i + 1;
        }
    }
    return env_ret;
}

static const char *sysenv_get_with_area(const char *name, int area)
{
    DEBUG_LOG("get env name=%s\n", name);

    get_env_info(area);

    if (!env_valid[area])
        return NULL;
    return findenv(name, area);
}

const char *sysenv_get(const char *name)
{
    return sysenv_get_with_area(name, SYSENV_RW_AREA);
}

const char *sysenv_get_static(const char *name)
{
    return sysenv_get_with_area(name, SYSENV_RO_AREA);
}

int sysenv_set_in_user(const char *name, const char *value, int area)
{
    int len;
    int oldval = -1;
    char *env, *nxt = NULL;
    int ret = 0;
    char *env_data = NULL;

    DEBUG_LOG("area: %d, name: %s, value: %s\n", area, name, value);

    if (area >= SYSENV_AREA_MAX) {
        ERR_LOG("Invalid sysenv area %d\n", area);
        return -1;
    }

    get_env_info(area);

    env_data = g_env[area].env_data;
    if (!env_buffer[area])
        return -1;
    if (!env_valid[area]) {
        env = env_data;
        goto add;
    }
/* find match name and return the val header pointer*/
    for (env = env_data; *env; env = nxt + 1) {
        for (nxt = env; *nxt; ++nxt)
            ;
        oldval = envmatch((char *)name, env - env_data, area);
        if (oldval >= 0)
            break;
    }           /* end find */
    if (oldval > 0) {
        if (*++nxt == '\0') {
            if (env > env_data)
                env--;
             else
                *env = '\0';
        } else {
            for (;;) {
                *env = *nxt++;
                if (((*env == '\0') && (*nxt == '\0')) || (nxt - env_data >= (int)CFG_ENV_DATA_SIZE))
                    break;
                ++env;
            }
        }
        *++env = '\0';
    }

    for (env = env_data; *env || *(env + 1); ++env)
        ;
    if (env > env_data)
        ++env;
add:
    if (*value == '\0') {
        DEBUG_LOG("clear env name=%s\n", name);
        goto write_env;
    }

    len = strlen(name) + 1; // =
    len += strlen(value) + 1; // \0
    if (len > (&env_data[CFG_ENV_DATA_SIZE] - env)) {
        ERR_LOG("env data overflow, %s deleted\n", name);
        return -1;
    }
    while ((*env = *name++) != '\0')
        env++;
    *env = '=';
    while ((*++env = *value++) != '\0')
        ;
write_env:
/* end is marked with double '\0' */
    *++env = '\0';
    memset(env, 0x00, CFG_ENV_DATA_SIZE - (env - env_data));

    ret = write_env_area(env_buffer[area], area);
    if (ret < 0) {
        ERR_LOG("error: write env area fail\n");
        memset(env_buffer[area], 0x00, CFG_ENV_SIZE);
        return -1;
    }
    env_valid[area] = 1;
    return 0;
}

int sysenv_set(const char *name, const char *value)
{
    int fd;
    int ret = 0;
    struct env_ioctl en_ctl;

    memset(&en_ctl,0x00,sizeof(struct env_ioctl));
    fd = open("/proc/lk_env",O_RDWR);
    if (fd < 0) {
        ERR_LOG("open /proc/lk_env fail\n");
        return -1;
    }

    en_ctl.name = strdup(name);
    en_ctl.value = strdup(value);
    en_ctl.name_len = strlen(name)+1;
    en_ctl.value_len = strlen(value)+1;
    if (ioctl(fd,ENV_WRITE,&en_ctl) < 0) {
        ERR_LOG("ioctl ENV_WRITE fail: %s\n", strerror(errno));
        ret = -1;
    }
    free(en_ctl.name);
    free(en_ctl.value);
    close(fd);
    return ret;
}

/* This API is "only" used for meta tool now to write static data which will not change during runtime.
 * The real "read-only" might be taken by power on write protect in the future.
 */
int sysenv_set_static(const char *name, const char *value)
{
    return sysenv_set_in_user(name, value, SYSENV_RO_AREA);
}
