LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	mrdump_plat_debug.c \
	mrdump_status.c

LOCAL_MODULE := libmrdump
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk
LOCAL_MODULE_TAGS := optional
LOCAL_SHARED_LIBRARIES = liblog

include $(MTK_SHARED_LIBRARY)


include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	mrdump_tool.c

LOCAL_MODULE := mrdump_tool
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk
LOCAL_MODULE_TAGS := eng userdebug
LOCAL_SHARED_LIBRARIES = libmrdump liblog

include $(MTK_EXECUTABLE)

