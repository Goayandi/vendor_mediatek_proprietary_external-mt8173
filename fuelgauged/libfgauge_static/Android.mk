LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := libfgauge_static
LOCAL_MODULE_CLASS := STATIC_LIBRARIES
LOCAL_MODULE_OWNER := mtk
LOCAL_SRC_FILES_arm := libfgauge.a
LOCAL_MULTILIB := 32
LOCAL_MODULE_SUFFIX := .a
include $(BUILD_PREBUILT)

