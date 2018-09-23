LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := uree_mem
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk
LOCAL_SRC_FILES := mem_app.c
LOCAL_MODULE_TAGS := optional
LOCAL_C_INCLUDES += \
    $(call include-path-for, trustzone-uree)

LOCAL_CFLAGS += -Wall -Wno-unused-parameter -Werror

LOCAL_SHARED_LIBRARIES += libtz_uree

include $(MTK_EXECUTABLE)

