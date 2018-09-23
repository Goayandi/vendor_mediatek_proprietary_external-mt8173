LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := md_ctrl.cpp

LOCAL_C_INCLUDES := system/core/logwrapper/include

$(warning CUSTOM_MODEM: $(CUSTOM_MODEM))
ifneq (,$(strip $(CUSTOM_MODEM)))
LOCAL_CFLAGS += -DCUSTOM_MODEM
endif

LOCAL_MODULE := md_ctrl
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk
LOCAL_SHARED_LIBRARIES := liblogwrap liblog libcutils

include $(MTK_EXECUTABLE)
