#if !defined(__MRDUMP_USER_PRIVATE_H__)
#define __MRDUMP_USER_PRIVATE_H__

#include <stdbool.h>
#include <stdint.h>

/* DRAM KLOG at MRDUMP area of expdb, offset from bottom = 3145728 - 16384 = 3129344 */
#define MRDUMP_OFFSET 3145728
#define MRDUMP_DRAM_KLOG_OFFSET 16384
#define MRDUMP_DRAM_KLOG_SIZE 8192
#define MRDUMP_DRAM_KLOG_MAGIC 0x19870611

struct partinfo {
    int fd;
    uint64_t size;
    uint32_t blksize;
};

int expdb_open(struct partinfo *partinfo);

#endif
