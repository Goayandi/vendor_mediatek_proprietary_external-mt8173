####################################################################
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := sysenv_test.c

LOCAL_SHARED_LIBRARIES := liblog libsysenv

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../

LOCAL_MODULE := sysenv_test

LOCAL_MULTILIB := 32
LOCAL_MODULE_TAGS := optional
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk

include $(BUILD_EXECUTABLE)

