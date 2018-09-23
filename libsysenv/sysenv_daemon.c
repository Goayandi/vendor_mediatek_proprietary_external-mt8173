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
#include <stdlib.h>
#include <malloc.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include <errno.h>
#include <linux/ioctl.h>
#include <fcntl.h>
#include "sysenv_utils.h"

#define MAX_PAYLOAD CFG_ENV_SIZE

int send_kernel_env(int sock_fd, char *data, int len)
{
    struct sockaddr_nl dst_addr;
    struct nlmsghdr *nlh = NULL;
    struct iovec iov;
    struct msghdr msg;

    memset(&msg,0,sizeof(msg));
    memset(&dst_addr, 0, sizeof(dst_addr));
    dst_addr.nl_family = AF_NETLINK;
    dst_addr.nl_pid = 0; /* For Linux Kernel */
    dst_addr.nl_groups = 0; /* unicast */

    nlh=(struct nlmsghdr *)malloc(NLMSG_SPACE(MAX_PAYLOAD));
    if (nlh == NULL) {
        ERR_LOG("allocate %d buffer fail!\n", NLMSG_SPACE(MAX_PAYLOAD));
        close(sock_fd);
        return -1;
    }

    /* Fill the netlink message header */
    nlh->nlmsg_len = NLMSG_SPACE(MAX_PAYLOAD);
    nlh->nlmsg_pid = getpid(); /* self pid */
    nlh->nlmsg_flags = 0;
    /* Fill in the netlink message payload */
    snprintf(NLMSG_DATA(nlh), MAX_PAYLOAD, "%s", data);

    iov.iov_base = (void *)nlh;
    iov.iov_len = nlh->nlmsg_len;
    msg.msg_name = (void *)&dst_addr;
    msg.msg_namelen = sizeof(dst_addr);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;

    DEBUG_LOG("Sending message to kernel %s\n", NLMSG_DATA(nlh));

    len = sendmsg(sock_fd, &msg, 0);
    if (len < 0) {
        ERR_LOG("send message by socket fail: %s\n", strerror(errno));
        close(sock_fd);
        return -1;
    }
    return len;
}

int init_kernel_socket()
{
    struct sockaddr_nl src_addr;
    int fd = socket(PF_NETLINK, SOCK_RAW,NETLINK_USERSOCK);
    if (fd < 0) {
        ERR_LOG("create socket fail: %s\n", strerror(errno));
        return -1;
    }
    memset(&src_addr, 0, sizeof(src_addr));
    src_addr.nl_family = AF_NETLINK;
    src_addr.nl_pid = getpid();
    src_addr.nl_groups = 0; /* not in mcast groups */
    if (bind(fd, (struct sockaddr*)&src_addr,sizeof(src_addr)) < 0) {
        ERR_LOG("bind socket %d fail: %s\n", fd, strerror(errno));
        close(fd);
        return -1;
    }
    return fd;
}

int init_kernel_sysenv(void)
{
    int fd, ret = 0;
    struct env_ioctl en_ctl;
    char *line, *data, *p;

    fd = open("/proc/lk_env", O_RDWR);
    if (fd < 0) {
        ERR_LOG("open lk_env fail: %s\n", strerror(errno));
        return -1;
    }
    memset(&en_ctl,0x00,sizeof(struct env_ioctl));

    /* set sysenv to kernel */
    data = sysenv_get_all(SYSENV_RW_AREA);
    if (data) {
        line = strtok_r(data, "\n", &p);
        while (line != NULL) {
            en_ctl.name = strtok_r(line, "=", &en_ctl.value);
            if (en_ctl.name == NULL)
                break;
            en_ctl.name_len = strlen(en_ctl.name) + 1;
            en_ctl.value_len = strlen(en_ctl.value) + 1;
            DEBUG_LOG("ioctl set kernel sysenv %s=%s\n", en_ctl.name, en_ctl.value);
            if (ioctl(fd, ENV_USER_INIT, &en_ctl) < 0)
                ERR_LOG("ioctl ENV_WRITE fail: %s\n", strerror(errno));
            line = strtok_r(NULL, "\n", &p);
        }
        free(data);
    }

    /* set sysenv daemon pid to kernel */
    if (asprintf(&en_ctl.name, "user_daemon") < 0) {
        ERR_LOG("asprintf fail: %s\n", strerror(errno));
        close(fd);
        return -1;
    }
    en_ctl.name_len = strlen(en_ctl.name) + 1;
    if (asprintf(&en_ctl.value, "%d", getpid()) < 0) {
        ERR_LOG("asprintf fail: %s\n", strerror(errno));
        close(fd);
        free(en_ctl.name);
        return -1;
    }
    en_ctl.value_len = strlen(en_ctl.value) + 1;
    if (ioctl(fd, ENV_SET_PID, &en_ctl) < 0) {
        ERR_LOG("ioctl ENV_SET_PID fail: %s\n", strerror(errno));
        ret = -1;
    }

    free(en_ctl.name);
    free(en_ctl.value);
    close(fd);
    return ret;
}

static void showAll(void)
{
    char *line;
    char *data = sysenv_get_all(SYSENV_RW_AREA);
    if (data == NULL) {
        DEBUG_LOG("no valid data\n");
        return;
    }
    DEBUG_LOG("all env data: \n");
    line = strtok(data, "\n");
    while (line != NULL) {
        DEBUG_LOG("%s\n", line);
        line = strtok(NULL, "\n");
    }
    free(data);
}

extern int sysenv_set_in_user(const char *name, const char *value, int area);
int parseMsg(char *msg)
{
    char *tag = NULL, *name = NULL, *value = NULL, *p;
    int ret = 0;

    DEBUG_LOG("Received message payload %s", msg);
    tag = strtok_r(msg, " ", &value);
    if (!tag) {
        ERR_LOG("Incorrect tag format %s\n", msg);
        return -1;
    }
    if (!strcmp(tag, TAG_SET_ENV)) {
        name = strtok_r(NULL, "=", &value);
        if (!name || !value)
            ERR_LOG("Incorrect parameter format %s\n", msg);
        else
            ret = sysenv_set_in_user(name, value, SYSENV_RW_AREA);
    } else if (!strcmp(tag, TAG_SHOW_ALL)) {
        showAll();
    }
    return ret;
}

int main(void)
{
    struct sockaddr_nl dst_addr;
    struct nlmsghdr *nlh = NULL;
    struct iovec iov;
    int sock_fd, len;
    struct msghdr msg;

    memset(&msg,0,sizeof(msg));

    init_kernel_sysenv();

    sock_fd = init_kernel_socket();
    if (sock_fd < 0)
        return -1;

    memset(&dst_addr, 0, sizeof(dst_addr));
    dst_addr.nl_family = AF_NETLINK;
    dst_addr.nl_pid = 0; /* For Linux Kernel */
    dst_addr.nl_groups = 0; /* unicast */

    nlh=(struct nlmsghdr *)malloc(NLMSG_SPACE(MAX_PAYLOAD));
    if (nlh == NULL) {
        ERR_LOG("allocate %d buffer fail!\n", NLMSG_SPACE(MAX_PAYLOAD));
        close(sock_fd);
        return -1;
    }

    nlh->nlmsg_len = NLMSG_SPACE(MAX_PAYLOAD);
    nlh->nlmsg_pid = getpid(); /* self pid */
    nlh->nlmsg_flags = 0;

    iov.iov_base = (void *)nlh;
    iov.iov_len = nlh->nlmsg_len;
    msg.msg_name = (void *)&dst_addr;
    msg.msg_namelen = sizeof(dst_addr);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;

    DEBUG_LOG("Waiting for sysenv message from kernel\n");
    while (1) {
        /* Read message from kernel */
        DEBUG_LOG("Waiting for sysenv message from kernel\n");
        len = recvmsg(sock_fd, &msg, 0);
        if (len < 0) {
            ERR_LOG("receive message from socket fail: %s\n", strerror(errno));
            close(sock_fd);
            return -1;
        }
        parseMsg(NLMSG_DATA(msg.msg_iov->iov_base));
    }
    close(sock_fd);

    return 0;
}
