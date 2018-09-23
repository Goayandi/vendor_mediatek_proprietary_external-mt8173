/* MediaTek Inc. (C) 2016. All rights reserved.
 *
 * Copyright Statement:
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein is
 * confidential and proprietary to MediaTek Inc. and/or its licensors. Without
 * the prior written permission of MediaTek inc. and/or its licensors, any
 * reproduction, modification, use or disclosure of MediaTek Software, and
 * information contained herein, in whole or in part, shall be strictly
 * prohibited.
 */

/*
* Description:
*   This file implements Mtk Audio Loudness Header
*/
#ifndef __MTK_AUDIO_LOUDNESS_EXP_H__
#define __MTK_AUDIO_LOUDNESS_EXP_H__

#include <utils/threads.h>
#include "MtkAudioComponent.h"
extern "C" {
#include "BesLoudness_HD_exp.h"
}
#include "CFG_AUDIO_File.h"

typedef struct _AUDIO_ACF_CUSTOM_PARAM_STRUCT_FILTER_PARAM {
    unsigned int bes_loudness_hsf_coeff[2][9][5];       // Compensation Filter HSF coeffs    [9][4]->[2][9][5]
    unsigned int bes_loudness_bpf_coeff[8][6][3];       // Compensation Filter BPF coeffs    [4][6][3]->[6][6][3]->[8][6][3]
    unsigned int bes_loudness_lpf_coeff[6][3];

} AUDIO_ACF_CUSTOM_PARAM_STRUCT_FILTER_PARAM;

namespace android {

class MtkAudioCustParamCache {
public:
    MtkAudioCustParamCache();
    ~MtkAudioCustParamCache();
    static MtkAudioCustParamCache *getInstance(void);
    ACE_ERRID loadParameter(uint32_t FilterType, AUDIO_ACF_CUSTOM_PARAM_STRUCT *AudioParam);
    ACE_ERRID saveParameter(uint32_t FilterType, AUDIO_ACF_CUSTOM_PARAM_STRUCT *AudioParam);
private:
    uint32_t mFilterType;
    AUDIO_ACF_CUSTOM_PARAM_STRUCT mAudioParam;
    Mutex mLock;
    static MtkAudioCustParamCache *mAudioCustParamCache;
};

class MtkAudioLoud : public MtkAudioLoudBase {
public:
    MtkAudioLoud();
    MtkAudioLoud(uint32_t eFLTtype);
    virtual ACE_ERRID setParameter(uint32_t paramID, void *param);
    virtual ACE_ERRID getParameter(uint32_t paramID, void *param);
    virtual ACE_ERRID open(void);
    virtual ACE_ERRID close(void);
    virtual ACE_ERRID resetBuffer(void);
    virtual ACE_ERRID change2ByPass(void);
    virtual ACE_ERRID change2Normal(void);
    virtual ACE_ERRID process(void *pInputBuffer,   /* Input, pointer to input buffer */
                              uint32_t *InputSampleCount,        /* Input, length(byte) of input buffer */
                              /* Output, length(byte) left in the input buffer after conversion */
                              void *pOutputBuffer,               /* Input, pointer to output buffer */
                              uint32_t *OutputSampleCount);      /* Input, length(byte) of output buffer */
    /* Output, output data length(byte) */
    virtual ACE_ERRID setWorkMode(uint32_t chNum, uint32_t smpRate, uint32_t workMode, bool bRampUpEnable);
    virtual ACE_ERRID setOutputGain(int32_t gain, uint32_t ramp_sample_cnt);
    virtual ACE_ERRID setNotchFilterParam(uint32_t fc, uint32_t bw, int32_t th);
    virtual bool isZeroCoeffFilter(void);
    static int getBesSoundVer(void);
    virtual ~MtkAudioLoud();
private:
    void init();
    void useDefaultFullband(BLOUD_HD_InitParam *pInitParam);
    void useNoiseFilter(BLOUD_HD_InitParam *pInitParam);
    void copyParam(void);
    void copyParamSub(void);
    int getBesLoudSamplingRateIndex(unsigned int sampling_rate);
    int convertBesLoudCoeffV4ToV5(unsigned int sampling_rate, AUDIO_ACF_CUSTOM_PARAM_STRUCT_FILTER_PARAM *p_V4, BLOUD_HD_FilterCoef *p_V5);
    ACE_STATE mState;
    uint32_t mPcmFormat;
    uint32_t mFilterType;
    uint32_t mWorkMode;
    uint32_t mTempBufSize; // in byte
    uint32_t mInternalBufSize; // in byte
    uint32_t mTempBufSize_cache; // in byte
    uint32_t mInternalBufSize_cache; // in byte
    BLOUD_HD_InitParam mInitParam;    // loudness param
    BS_HD_Handle mBloudHandle;
    char *mpTempBuf;
    char *mpInternalBuf;
    AUDIO_ACF_CUSTOM_PARAM_STRUCT mAudioParam;
    Mutex mLock;
    bool mIsSepLR_Filter;
    BLOUD_HD_IIR_Design_Param mParamFormatUse;
    AUDIO_ACF_CUSTOM_PARAM_STRUCT_FILTER_PARAM mV4ToV5Use;
    bool mIsZeroCoeff;
    static int mMusicCount;
    static int mMaxMusicCount;
    int mNoiseFilter;
    static bool mAudioCompFltXmlRegCallback;
};

}; // namespace android

#endif // __MTK_AUDIO_LOUDNESS_EXP_H__
