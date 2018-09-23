LOCAL_PATH := $(call my-dir)


include $(CLEAR_VARS)
LOCAL_MULTILIB := 32
LOCAL_MODULE_TAGS := optional
LOCAL_SRC_FILES := thermal_manager.c
LOCAL_SHARED_LIBRARIES := libdl libcutils
LOCAL_MODULE := thermal_manager
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk
include $(MTK_EXECUTABLE)




include $(CLEAR_VARS)
LOCAL_MODULE:= libmtcloader
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_SRC_FILES_arm := libmtcloader.so

#bobule workaround pdk build error, needing review
LOCAL_MULTILIB := 32
LOCAL_MODULE_SUFFIX := .so

include $(BUILD_PREBUILT)



