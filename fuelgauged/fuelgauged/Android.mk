LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
				  fgauge_main.cpp \
				  fg_log.cpp 

LOCAL_CFLAGS += $(MTK_CDEFS)

LOCAL_SHARED_LIBRARIES := libcutils libutils libdl

LOCAL_MODULE:= fuelgauged
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk
#bobule workaround pdk build error, needing review
LOCAL_MULTILIB := 32
LOCAL_PRELINK_MODULE := false
include $(MTK_EXECUTABLE)


