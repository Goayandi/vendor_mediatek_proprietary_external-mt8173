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
#include <fcntl.h>
#include <errno.h>
#include <linux/ioctl.h>
#include "sysenv_utils.h"

int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("%s argv incorrect, usage: %s [read name | write name value | all]\n", argv[0]);
        return -1;
    }
    if (!strcmp(argv[1], "write_rw")) {
        if (argc != 4) {
            printf("write argv incorrect\n");
            return -1;
        }
        if (sysenv_set_in_user(argv[2], argv[3], SYSENV_RW_AREA) < 0)
            printf("write sysenv fail\n");
    } else if (!strcmp(argv[1], "write_ro")) {
        if (argc != 4) {
            printf("write argv incorrect\n");
            return -1;
        }
        if (sysenv_set_in_user(argv[2], argv[3], SYSENV_RO_AREA) < 0)
            printf("write sysenv fail\n");
    } if (!strcmp(argv[1], "delete_rw")) {
        if (argc != 3) {
            printf("delete argv incorrect\n");
            return -1;
        }
        if (sysenv_set_in_user(argv[2], "", SYSENV_RW_AREA) < 0)
            printf("write sysenv fail\n");
    } else if (!strcmp(argv[1], "delete_ro")) {
        if (argc != 3) {
            printf("delete argv incorrect\n");
            return -1;
        }
        if (sysenv_set_in_user(argv[2], "", SYSENV_RO_AREA) < 0)
            printf("write sysenv fail\n");
    } else if (!strcmp(argv[1], "read_rw")) {
        if (argc != 3) {
            printf("%s read argv incorrect\n", LOG_TAG);
            return -1;
        }
        const char* val = sysenv_get(argv[2]);
        if (val)
            printf("%s=%s\n", argv[2], val);
        else
            printf("%s not found\n", argv[2]);
    } else if (!strcmp(argv[1], "read_ro")) {
        if (argc != 3) {
            printf("read argv incorrect\n");
            return -1;
        }
        const char* val = sysenv_get_static(argv[2]);
        if (val)
            printf("%s=%s\n", argv[2], val);
        else
            printf("%s not found\n", argv[2]);
    } else if (!strcmp(argv[1], "all_rw")) {
        char *data = sysenv_get_all(SYSENV_RW_AREA);
        if (data) {
            printf("%s\n", data);
            free(data);
        }
    } else if (!strcmp(argv[1], "all_ro")) {
        char *data = sysenv_get_all(SYSENV_RO_AREA);
        if (data) {
            printf("%s\n", data);
            free(data);
        }
    }

    return 0;
}
