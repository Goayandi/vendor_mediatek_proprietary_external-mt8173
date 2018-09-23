#!/usr/bin/env python

#
# Copyright (C) 2015 MediaTek Inc. All rights reserved.
# Tristan Shieh <tristan.shieh@mediatek.com>
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.
#

import os
import struct
import sys

def read(path):
        with open(path, "rb") as f:
                return f.read()

def write(path, data):
        with open(path, "wb") as f:
                f.write(data)

def padding(data, size, pattern = '\0'):
        return data + pattern * (size - len(data))

LK_MEM_ADDRs = {'8135': 0x81e00000,
                '8127': 0x81e00000,
                '6595': 0x41e00000,
                '8173': 0x41e00000,
                '2701': 0x81e00000,
                '7623': 0x81e00000,
                '8163': 0x41e00000}

BOOTARG_OFFSET = 0x80

boot_args = {
        '8135': struct.pack("26I",
        0x504c504c, 0x00000063, 0x00000000, 0x11009000,
        0x000e1000, 0x00500a01, 0x00000001, 0x34000000,
        0x10240d40, 0x02101010, 0x000a8200, 0x00000000,
        0x00000000, 0x00000000, 0x00000231, 0x00000000,
        0x00000000, 0x00000000, 0x822041c1, 0x51200655,
        0x92124805, 0x18420000, 0x3a00a284, 0xc0444890,
        0x1980a991, 0x04000099),

        '8127': struct.pack("27I",
        0x504C504C, 0x00000063, 0x00000000, 0x11002000,
        0x000E1000, 0x00000301, 0x00000001, 0x37C00000,
        0x00000000, 0x00000000, 0x00000000, 0x00000003,
        0x00000000, 0x00000000, 0x00002116, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0xAFB50204, 0x00000000,
        0x00000000, 0x00000000, 0x00008127),

        '6595': struct.pack("26I",
        0x504c504c, 0x00000063, 0x00000000, 0x11002000,
        0x000e1000, 0xEBFE0101, 0x00000001, 0x80000000,
        0x00000000, 0xE59304C0, 0xE3500000, 0x00000000,
        0x00000000, 0x00000000, 0x00000231, 0x00000000,
        0x00000000, 0x00000000, 0x822041c1, 0x51200655,
        0x92124805, 0x18420000, 0x40079a84, 0xE1A09000,
        0x00000000, 0x00000000),

        '8173': struct.pack("44I",
        0x504C504C, 0x00000063, 0x00000000, 0x11002000,
        0x000E1000, 0x00000301, 0x00000001, 0x7F800000,
        0x00000000, 0x00000000, 0x00000000, 0x00000001,
        0x00000000, 0x00000000, 0x000014E7, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x40079A84, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x001997C0, 0x00000000,
        0x00000007, 0x00000005, 0x0012C000, 0x00004000,
        0xBF800000, 0x00000000, 0x00800000, 0x00000000),

        '2701': struct.pack("27I",
        0x504C504C, 0x00000063, 0x00000000, 0x11002000,
        0x000E1000, 0x00000F01, 0x00000001, 0x38E00000,
        0x080DE16C, 0x35040640, 0x08443804, 0x00000000,
        0x00000000, 0x00000000, 0x0000025E, 0x0A1B7166,
        0x91C08166, 0xD20B0FA3, 0xC86B7442, 0x02069291,
        0x6025E020, 0x20E02706, 0xAFB50204, 0xFF980529,
        0x00000000, 0x00000000, 0x00008590),

        '7623': struct.pack("27I",
        0x504C504C, 0x00000063, 0x00000000, 0x11004000,
        0x000E1000, 0xFFFC4201, 0x00000001, 0x3FE00000,
        0xDFF4FFBF, 0xFE7FFFFF, 0xDFEFFFFF, 0x00000000,
        0x00000000, 0x00000000, 0x000011FD, 0xFFFDB7FE,
        0xF1FF2FFF, 0xFFFFFFAF, 0xFFF29FFF, 0xBF7BDE7F,
        0x3FFD997F, 0xFFEFFFBF, 0xAFB50204, 0xFECF3FFF,
        0x00000000, 0x00000000, 0x00008590),

        '8163': struct.pack("88I",
        0x504C504C, 0x00000063, 0x00000000, 0x11002000,
        0x000E1000, 0xFFFF0301, 0x00000001, 0x3FC00000,
        0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
        0x00000001, 0x00000000, 0x40000000, 0x00000000,
        0x3FC00000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000001, 0xFFFFFFFF,
        0x40000000, 0x00000000, 0x40000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x7FC00000, 0x00000000, 0x00400000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x0000E4DC,
        0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
        0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x42058A04,
        0xFFFFFFFF, 0x00000000, 0x00000000, 0x00178980,
        0x11003000, 0x00000000, 0x00000006, 0x00000004,
        0x0012C000, 0x00004000, 0x2E312E30, 0x25003030)}

def main(argv):
        lk = read(argv[2])

        print("CHIP_ID: %s" % argv[1])
        boot_arg = boot_args[argv[1]]
        LK_MEM_ADDR = LK_MEM_ADDRs[argv[1]]

        lk_wrapper = struct.pack("21I",
					#LK_WRAPPER:
         0xe1a0000f, 			#   0:	mov     r0, pc
         0xe2400008, 			#   4:	sub     r0, r0, #8
         0xe59f1030, 			#   8:	ldr     r1, [pc, #48]   ; 40 <COPY+0x1c>
         0xe0800001, 			#   c:	add     r0, r0, r1
         0xe59f102c, 			#  10:	ldr     r1, [pc, #44]   ; 44 <COPY+0x20>
         0xe59f202c, 			#  14:	ldr     r2, [pc, #44]   ; 48 <COPY+0x24>
         0xe0812002, 			#  18:	add     r2, r1, r2
         0xe59f3028, 			#  1c:	ldr     r3, [pc, #40]   ; 4c <COPY+0x28>
         0xe0822003, 			#  20:	add     r2, r2, r3
					#COPY:
         0xe1510002, 			#  24:	cmp     r1, r2
         0x34903004, 			#  28:	ldrcc   r3, [r0], #4
         0x34813004, 			#  2c:	strcc   r3, [r1], #4
         0x3afffffb, 			#  30:	bcc     24 <COPY>
         0xe59f4008, 			#  34:	ldr     r4, [pc, #8]    ; 44 <COPY+0x20>
         0xe59f5008, 			#  38:	ldr     r5, [pc, #8]    ; 48 <COPY+0x24>
         0xe59ff00c, 			#  3c:	ldr     pc, [pc, #12]   ; 50 <COPY+0x2c>
         BOOTARG_OFFSET,		#  40:	BOOTARG_OFFSET  .word   0x11111111
         LK_MEM_ADDR - len(boot_arg),	#  44:	BOOTARG_ADDR    .word   0x22222222
         len(boot_arg),			#  48:	BOOTARG_SIZE    .word   0x33333333
         len(lk),			#  4c:	LK_SIZE         .word   0x44444444
         LK_MEM_ADDR			#  50:	LK_ADDR         .word   0x55555555
        )

        o = padding(lk_wrapper, BOOTARG_OFFSET, '\0') + boot_arg + lk
        # padding to even-sized output
        write(argv[3], padding(o, len(o)+len(o)%2, '\0'))


if __name__ == "__main__":
        main(sys.argv)


