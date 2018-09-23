/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 *
 * MediaTek Inc. (C) 2010. All rights reserved.
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

/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2009
*
*  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
*  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
*  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
*  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
*  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
*  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
*  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
*  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
*  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
*  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
*  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
*  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
*  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
*  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
*  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
*
*  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
*  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
*  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
*  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
*
*****************************************************************************/


/*******************************************************************************
 *
 * Filename:
 * ---------
 * AudioCmdHandler.cpp
 *
 * Project:
 * --------
 *   Android
 *
 * Description:
 * ------------
 *   This file implements the  handling about audio command comming from AT Command Service.
 *
 * Author:
 * -------
 *   Donglei Ji (mtk80823)
 *
 *------------------------------------------------------------------------------
 * $Revision: #1 $
 * $Modtime:$
 * $Log:$
 *
 * 06 08 2013 donglei.ji
 * [ALPS00683353] [Need Patch] [Volunteer Patch] DMNR3.0 and VOIP tuning check in
 * .
 *
 * 06 04 2013 donglei.ji
 * [ALPS00683353] [Need Patch] [Volunteer Patch] DMNR3.0 and VOIP tuning check in
 * .
 *
 * 05 24 2013 donglei.ji
 * [ALPS00683353] [Need Patch] [Volunteer Patch] DMNR3.0 and VOIP tuning check in
 * .
 *
 * 05 15 2013 donglei.ji
 * [ALPS00683353] [Need Patch] [Volunteer Patch] DMNR3.0 and VOIP tuning check in
 * .
 *
 * 01 17 2013 donglei.ji
 * [ALPS00425279] [Need Patch] [Volunteer Patch] voice ui and password unlock feature check in
 * .
 *
 * 01 09 2013 donglei.ji
 * [ALPS00438595] [Need Patch] [Volunteer Patch] Audio Tool -  HD Calibration
 * HD Record Calibration.
 *
 * 08 15 2012 donglei.ji
 * [ALPS00337843] [Need Patch] [Volunteer Patch] MM Command Handler JB migration
 * MM Command Handler JB migration.
 *
 * 06 28 2012 donglei.ji
 * [ALPS00308450] [Need Patch] [Volunteer Patch] Audio Taste feature
 * Audio Taste feature.
 *
 * 06 27 2012 donglei.ji
 * [ALPS00307929] [Need Patch] [Volunteer Patch] Audio HQA add I2S output 32 bit test case
 * for MT6577 HQA.
 *
 * 04 27 2012 donglei.ji
 * [ALPS00247341] [Need Patch] [Volunteer Patch] AT Command for Speech Tuning Tool feature
 * add two case:
 * 1. get phone support info
 * 2. read dual mic parameters if phone support dual mic
 *
 * 04 20 2012 donglei.ji
 * [ALPS00272538] [Need Patch] [Volunteer Patch] AT Command for ACF/HCF calibration
 * ACF/HCF calibration feature.
 *
 * 04 12 2012 donglei.ji
 * [ALPS00247341] [Need Patch] [Volunteer Patch] AT Command for Speech Tuning Tool feature
 * Add wide band speech tuning.
 *
 * 03 16 2012 donglei.ji
 * [ALPS00247341] [Need Patch] [Volunteer Patch] AT Command for Speech Tuning Tool feature
 * add speech parameters encode and decode for transfer.
 *
 * 03 09 2012 donglei.ji
 * [ALPS00247341] [Need Patch] [Volunteer Patch] AT Command for Speech Tuning Tool feature
 * add a set parameters setting.
 *
 * 03 06 2012 donglei.ji
 * [ALPS00247341] [Need Patch] [Volunteer Patch] AT Command for Speech Tuning Tool feature
 * AT Command for Speech Tuning tool feature check in.
 *
 * 12 27 2011 donglei.ji
 * [ALPS00107090] [Need Patch] [Volunteer Patch][ICS Migration] MM Command Handler Service Migration
 * MM Command Handler Service check in.
 *
 * 11 21 2011 donglei.ji
 * [ALPS00094843] [Need Patch] [Volunteer Patch] XLOG enhance
 * log enhance -- SXLOG.
 *
 * 07 15 2011 donglei.ji
 * [ALPS00053673] [Need Patch] [Volunteer Patch][Audio HQA]Add Audio HQA test cases
 * check in HQA code.
 *
 * 06 15 2011 donglei.ji
 * [ALPS00053673] [Need Patch] [Volunteer Patch][Audio HQA]Add Audio HQA test cases
 * MM Cmd Handler code check in for MT6575.
 *
 * 05 26 2011 changqing.yan
 * [ALPS00050318] [Need Patch] [Volunteer Patch]Remove fmaudioplayer and matvaudiopath path from mediaplayer.
 * .
 *
 * 05 26 2011 changqing.yan
 * [ALPS00050318] [Need Patch] [Volunteer Patch]Remove fmaudioplayer and matvaudiopath path from mediaplayer.
 * .
 *
 *******************************************************************************/

/*=============================================================================
 *                              Include Files
 *===========================================================================*/
#define MTK_LOG_ENABLE 1
#include <cutils/log.h>
#include <utils/String8.h>
#include <sys/types.h> //for opendir, readdir closdir
#include <dirent.h>    //for opendir, readdir closdir
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

#include <media/AudioSystem.h>
#include <audiocustparam/AudioCustParam.h>
#include <AudioCompensationFilter/AudioCompFltCustParam.h>

#include "AudioCmdHandler.h"

#include <binder/IServiceManager.h>
#include <media/IAudioPolicyService.h>
#include <AudioComponentEngine/MtkAudioLoud.h>
#include "audio_custom_exp.h"
#include "Parameter.h"
#include "AudioToolkit.h"

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "AudioCmdHandler"

#define AUDIO_TEST_ROOT "/sdcard/"
#define RECORD_DIR_UPLINK "/sdcard/Up_link_ADC/"
#define RECORD_DIR_FM "/sdcard/FM_Play_Record/"
#define RECORD_DIR_I2S "/sdcard/I2SRecord/"

#define MAX_FILE_NAME 512
#define TEMP_ARRAY_SIZE 64
#define AUD_TASTE_TUNING_CMD 0x70
#define DEV_NUM 3

#if 0
typedef AUDIO_VOLUME_CUSTOM_STRUCT AUD_VOL_CUSTOM_STRUCT;
#else
typedef AUDIO_VER1_CUSTOM_VOLUME_STRUCT AUD_VOL_CUSTOM_STRUCT;
#endif

#define HD_REC_48K_SUPPORT 0x51

using namespace android;

template <class... T> void unused(T&&...)
{}


static String8 keySetBuffer = String8("SetBuffer=");
static String8 keyGetBuffer = String8("GetBuffer=");
static String8 keySetCmd = String8("SetCmd=");
static String8 keyGetCmd = String8("GetCmd=");
static void print_hex_buffer (size_t len, void* ptr)
{
    char *pp;
    char *tempbuf = NULL;
    int sum;
    int printlen = len;
    if (printlen > 128) {
        ALOGD("%s: Truncate length to 128 byte", __FUNCTION__);
        printlen = 128;
    }

    tempbuf = new char[printlen*16];
    pp = (char*) ptr;
    sum = 0;
    for (int i=0; i<printlen; ++i) {
        sum += sprintf (tempbuf +sum, "0x%02x ", pp[i]);
    }
    ALOGD ("print_hex_buffer: sum=%d, %s", sum, tempbuf);
    delete [] tempbuf;
}

static String8 PrintEncodedString(String8 strKey, size_t len, void *ptr)
{
    String8 returnValue = String8("");
    size_t sz_Needed;
    size_t sz_enc;
    char *buf_enc = NULL;
    bool bPrint = false;

    ALOGD("%s in, len = %d", __FUNCTION__, len);
    print_hex_buffer (len, ptr);

    sz_Needed = Base64_OutputSize(true, len);
    buf_enc = new char[sz_Needed + 1];
    if (buf_enc == NULL) {
        ALOGE("%s(), buf_enc allocate fail", __FUNCTION__);
        return returnValue;
    }
    buf_enc[sz_Needed] = 0;

    sz_enc = Base64_Encode((unsigned char *)ptr, buf_enc, len);

    if (sz_enc != sz_Needed) {
        ALOGE("%s(), Encode Error!!!after encode (%s), len(%d), sz_Needed(%d), sz_enc(%d)",
            __FUNCTION__, buf_enc, len, sz_Needed, sz_enc);
    } else {
        bPrint = true;
        ALOGD("%s(), after encode (%s), len(%d), sz_enc(%d)", __FUNCTION__, buf_enc, len, sz_enc);
    }

    if (bPrint) {
        String8 StrVal = String8(buf_enc, sz_enc);
        returnValue += strKey;
        returnValue += StrVal;
        //returnValue += String8(";");
    }

    delete[] buf_enc;
    return returnValue;
}


static status_t GetDecodedData(String8 strPara, size_t len, void *ptr)
{
    size_t sz_in = strPara.size();
    size_t sz_needed = Base64_OutputSize(false, sz_in);
    size_t sz_dec;
    status_t ret = NO_ERROR;

    if (sz_in <= 0)
        return NO_ERROR;

    ALOGD("%s in, len = %d", __FUNCTION__, len);
    unsigned char *buf_dec = new unsigned char[sz_needed];
    sz_dec = Base64_Decode(strPara.string(), buf_dec, sz_in);

    if (sz_dec > sz_needed || sz_dec <= sz_needed -3) {
        ALOGE("%s(), Decode Error!!!after decode (%s), sz_in(%d), sz_needed(%d), sz_dec(%d)",
            __FUNCTION__, buf_dec, sz_in, sz_needed, sz_dec);
    }  else {
        // sz_needed-3 < sz_dec <= sz_needed
        ALOGD("%s(), after decode, sz_in(%d), sz_dec(%d) len(%d) sizeof(ret)=%d",
            __FUNCTION__, sz_in, sz_dec, len, sizeof(ret));
        print_hex_buffer (sz_dec, buf_dec);
    }

    if( (len == 0) || (len == sz_dec-sizeof(ret)) ) {
       if ( len ) {
           ret = (status_t) *(buf_dec);
           unsigned char *buff = (buf_dec+4);
           memcpy(ptr, buff, len);
       } else {
          const char * IntPtr = (char *)buf_dec;
          ret = atoi(IntPtr);
          ALOGD("%s len = 0 ret(%d)", __FUNCTION__, ret);
       }
    } else {
       ALOGD("%s decoded buffer isn't right format", __FUNCTION__);
    }

    if (buf_dec != NULL) {
        delete[] buf_dec;
    }

    return ret;
}

const char *findFileName(const char *pFilePath, const char *pFileName, char *pFileWholeName)
{
    char *pSearchFileNameSrc = NULL;
    DIR *pSearchPath;
    struct dirent *pFileHandle;

    if ((pSearchPath = opendir(pFilePath)) == NULL)
    {
        ALOGE("open file path: %s error", pFilePath);
        return NULL;
    }

    while ((pFileHandle = readdir(pSearchPath)) != NULL)
    {
        pSearchFileNameSrc = pFileHandle->d_name;
        if (strncmp(pSearchFileNameSrc, pFileName, 2/*strlen(pFileName)*/) == 0)
        {
            ALOGD("Find the file: %s",  pFileHandle->d_name);
            if (pFileWholeName == NULL)
            {
                ALOGE("the pointer pFileWholeName is NULL");
                return NULL;
            }

            strcpy(pFileWholeName, pFileHandle->d_name);
            closedir(pSearchPath);
            return pFileWholeName;
        }
    }

    ALOGE("there are not the file: %s", pFileName);
    return NULL;
}

// AT Command for Speech calibration
static void dataEncode(char *pPara, int length)
{
    char *pParaTemp = pPara + length;
    memcpy((void *)pParaTemp, (void *)pPara, length);

    for (int i = 0; i < length; i++)
    {
        *(pPara + 2 * i) = ((*(pParaTemp + i) >> 4) & 0x0F) | 0x30;
        *(pPara + 2 * i + 1) = (*(pParaTemp + i) & 0x0F) | 0x30;
    }
}

static void dataDecode(char *pPara, int length)
{
    char *pParaTemp = pPara + length;

    for (int i = 0; i < length; i++)
    {
        *(pPara + i) = ((*(pPara + 2 * i) << 4) & 0xF0) | (*(pPara + 2 * i + 1) & 0x0F);
    }

    memset(pParaTemp, 0, length);
}

/*=============================================================================
 *                             Public Function
 *===========================================================================*/

AudioCmdHandler::AudioCmdHandler() :
    m_RecordMaxDur(-1),
    m_RecordChns(1),
    m_RecordSampleRate(8000),
    m_RecordBitsPerSample(16),
    m_fd(-1),
    m_bRecording(false),
    m_bHDRecTunning(false),
    m_RecordAudioSource(Analog_MIC1_Single)
{
    ALOGD("Constructor--AudioCmdHandler::AudioCmdHandler()");
    m_pMediaRecorderListenner = new RecorderListener(this);
	memset((void *)&mDispStru, 0, sizeof(PCDispTotolStru));
	GainInfoFlag = false;
}

AudioCmdHandler::~AudioCmdHandler()
{
    ALOGD("Deconstructor--AudioCmdHandler::AudioCmdHandler()");

    if (m_MediaRecorderClient.get() != NULL)
    {
        m_MediaRecorderClient->release();
    }

}

ACHStatus AudioCmdHandler::setRecorderParam(AudioCmdParam &audioCmdParams)
{
    ALOGD("AudioCmdHandler::setRecorderParam() in");

    if (audioCmdParams.param1 < 0)
    {
        ALOGE("Fail to setRecorderParam: the duration <0");
        return ACHParamError;
    }

    m_RecordMaxDur = audioCmdParams.param1;

    if (audioCmdParams.param2 != 1 && audioCmdParams.param2 != 2)
    {
        ALOGE("Fail to setRecorderParam: the channels is not equal to 1 or 2");
        return ACHParamError;
    }

    m_RecordChns = audioCmdParams.param2;

    if (audioCmdParams.param3 < 8000 || audioCmdParams.param3 > 48000)
    {
        ALOGE("Fail to setRecorderParam: the sample rate is invalid");
        return ACHParamError;
    }

    m_RecordSampleRate = audioCmdParams.param3;

    return ACHSucceeded;
}

ACHStatus AudioCmdHandler::startRecorderFrMIC(AudioCmdParam &audioCmdParams)
{
    ALOGD("AudioCmdHandler::startRecorderFrMIC() in");

    int ret = ACHSucceeded;
    char recordFilepath[MAX_FILE_NAME];
    char recordFileName[TEMP_ARRAY_SIZE];
    char pRecordSrc[TEMP_ARRAY_SIZE];
    AudioSourceType audioSourceType = Analog_MIC1_Single;

    if (audioCmdParams.param1 < 0 || audioCmdParams.param1 > 4)
    {
        return ACHParamError;
    }

    sprintf(pRecordSrc, "HQA_RDMIC_P1=%d", audioCmdParams.param1);
    AudioSystem::setParameters(0, String8(pRecordSrc));
    /*
        switch (audioCmdParams.param1) {
          case 0:
            audioSourceType = Analog_MIC1_Single;
            break;
          case 1:
            audioSourceType = Analog_MIC2_Single;
            break;
          case 3:
            audioSourceType = Analog_MIC_Dual;
            break;
          default:
    //      ALOGE("AudioCmdHandler::startRecorderFrMIC-the audio source type is not supported");
    //      return ACHParamError;
            break;
        }
    */
    if (audioCmdParams.param2 != 0)
    {
        return ACHParamError;
    }

    if (audioCmdParams.param3 < 1 || audioCmdParams.param3 > 999)
    {
        return ACHParamError;
    }

    strcpy(recordFilepath, RECORD_DIR_UPLINK);
    if (access(recordFilepath, F_OK) < 0)
    {
        ALOGE("startRecorderFrMIC() the path %s is not exit", recordFilepath);
        ret = mkdir(recordFilepath, S_IRWXU | S_IRWXG | S_IRWXO);
        if (-1 == ret)
        {
            ALOGE("startRecorderFrMIC() create path %s failed", recordFilepath);
            return ACHFailed;
        }
    }

    sprintf(recordFileName, "%03d.wav", audioCmdParams.param3);
    strcat(recordFilepath, recordFileName);

    ret = startRecorder(recordFilepath, audioSourceType);
    if (ret != ACHSucceeded)
    {
        return ACHFailed;
    }

    return ACHSucceeded;
}

ACHStatus AudioCmdHandler::setMICGain(AudioCmdParam &audioCmdParams)
{
    ALOGD("AudioCmdHandler::setMICGain() in");

    if (audioCmdParams.param1 < 0 || audioCmdParams.param1 > 63)
    {
        return ACHParamError;
    }

    if (audioCmdParams.param2 < 0 || audioCmdParams.param2 > 62)
    {
        return ACHParamError;
    }

    char pPGAGain[TEMP_ARRAY_SIZE];
    sprintf(pPGAGain, "HQA_PGAGAIN_P1=%d", audioCmdParams.param1);
    AudioSystem::setParameters(0, String8(pPGAGain));

    char minPGAGain[TEMP_ARRAY_SIZE];
    sprintf(minPGAGain, "HQA_PGAGAIN_P2=%d", audioCmdParams.param2);
    AudioSystem::setParameters(0, String8(minPGAGain));

    return ACHSucceeded;

}

ACHStatus AudioCmdHandler::startRecorderFrFM(AudioCmdParam &audioCmdParams)
{
    ALOGD("AudioCmdHandler::startRecorderFrFM() in");

    int ret = ACHSucceeded;
    char recordFilepath[MAX_FILE_NAME];
    char recordFileName[TEMP_ARRAY_SIZE];

    if (audioCmdParams.param2 != 0)
    {
        return ACHParamError;
    }

    if (audioCmdParams.param3 < 1 || audioCmdParams.param3 > 999)
    {
        return ACHParamError;
    }

    strcpy(recordFilepath, RECORD_DIR_FM);
    if (access(recordFilepath, F_OK) < 0)
    {
        ALOGE("startRecorderFrI2S() the path %s is not exit", recordFilepath);
        ret = mkdir(recordFilepath, S_IRWXU | S_IRWXG | S_IRWXO);
        if (-1 == ret)
        {
            ALOGE("startRecorderFrI2S() create path %s failed", recordFilepath);
            return ACHFailed;
        }
    }

    sprintf(recordFileName, "%03d.wav", audioCmdParams.param3);
    strcat(recordFilepath, recordFileName);

    ret = startRecorder(recordFilepath, Audio_FM_IN);
    if (ret != ACHSucceeded)
    {
        AudioSystem::setParameters(0, String8("HQA_FMREC_LINE_IN=0"));
        return ACHFailed;
    }

    return ACHSucceeded;
}

ACHStatus AudioCmdHandler::playFM()
{
    ALOGD("AudioCmdHandler::playFM() in");

    AudioSystem::setParameters(0, String8("HQA_FMPLY_LINE_IN=1"));

    return ACHSucceeded;
}

ACHStatus AudioCmdHandler::stopPlayingFM()
{
    ALOGD("AudioCmdHandler::stopPlayingFM() in");

    AudioSystem::setParameters(0, String8("HQA_FMPLY_LINE_IN=0"));

    return ACHSucceeded;
}

ACHStatus AudioCmdHandler::setVDPG(AudioCmdParam &audioCmdParams)
{
    ALOGD("AudioCmdHandler::setVDPG() in");

    if (audioCmdParams.param1 < 0 || audioCmdParams.param1 > 44)
    {
        return ACHParamError;
    }

    if (audioCmdParams.param2 < 0 || audioCmdParams.param2 > 44)
    {
        return ACHParamError;
    }

    if (audioCmdParams.param3 < 0 || audioCmdParams.param3 > 44)
    {
        return ACHParamError;
    }

    char pVDPG1[TEMP_ARRAY_SIZE];
    sprintf(pVDPG1, "HQA_VDPG_P1=%d", audioCmdParams.param1);
    AudioSystem::setParameters(0, String8(pVDPG1));

    char pVDPG2[TEMP_ARRAY_SIZE];
    sprintf(pVDPG2, "HQA_VDPG_P2=%d", audioCmdParams.param2);
    AudioSystem::setParameters(0, String8(pVDPG2));

    char pVDPG3[TEMP_ARRAY_SIZE];
    sprintf(pVDPG3, "HQA_VDPG_P3=%d", audioCmdParams.param3);
    AudioSystem::setParameters(0, String8(pVDPG3));

    return ACHSucceeded;
}

ACHStatus AudioCmdHandler::setAUDLINEPG(AudioCmdParam &audioCmdParams)
{
    ALOGD("AudioCmdHandler::setAUDLINEPG() in");

    if (audioCmdParams.param1 < 0 || audioCmdParams.param1 > 8)
    {
        return ACHParamError;
    }

    char pAUDLINEPG[TEMP_ARRAY_SIZE];
    sprintf(pAUDLINEPG, "HQA_AUDLINEPG_P1=%d", audioCmdParams.param1);
    AudioSystem::setParameters(0, String8(pAUDLINEPG));

    return ACHSucceeded;
}

ACHStatus AudioCmdHandler::setFMorMICVUPG(AudioCmdParam &audioCmdParams, bool bFMGain)
{
    ALOGD("AudioCmdHandler::setFMVUPG() in");

    if (audioCmdParams.param1 < 0 || audioCmdParams.param1 > 63)
    {
        return ACHParamError;
    }

    if (audioCmdParams.param2 < 0 || audioCmdParams.param2 > 63)
    {
        return ACHParamError;
    }

    char pFMorMICVUPG1[TEMP_ARRAY_SIZE];
    char pFMorMICVUPG2[TEMP_ARRAY_SIZE];

    if (bFMGain)
    {
        sprintf(pFMorMICVUPG1, "HQA_FMVUPG_P1=%d", audioCmdParams.param1);
        sprintf(pFMorMICVUPG2, "HQA_FMVUPG_P2=%d", audioCmdParams.param2);
    }
    else
    {
        sprintf(pFMorMICVUPG1, "HQA_MICVUPG_P1=%d", audioCmdParams.param1);
        sprintf(pFMorMICVUPG2, "HQA_MICVUPG_P2=%d", audioCmdParams.param2);
    }

    AudioSystem::setParameters(0, String8(pFMorMICVUPG1));
    AudioSystem::setParameters(0, String8(pFMorMICVUPG2));

    return ACHSucceeded;
}

ACHStatus AudioCmdHandler::startAudioPlayer(AudioCmdParam &audioCmdParams)
{
    ALOGD("AudioCmdHandler::startAudioPlayer() in");

    char filePath[MAX_FILE_NAME];
    char fileName[TEMP_ARRAY_SIZE];
    char fileDir[TEMP_ARRAY_SIZE];
    char fileDirSub[TEMP_ARRAY_SIZE];
    char fileWholeName[TEMP_ARRAY_SIZE];

    strcpy(filePath, AUDIO_TEST_ROOT);
    sprintf(fileName, "%02d", audioCmdParams.param3);
    sprintf(fileDir, "%02d/%02d/", audioCmdParams.param1, audioCmdParams.param2);
    strcat(filePath, fileDir);

    findFileName(filePath, fileName, fileWholeName);
    strcat(filePath, fileWholeName);
    ALOGD("AudioCmdHandler::startAudioPlayer:Audio file is %s", filePath);

    if (m_MediaPlayerClient.get() == NULL)
    {
        m_MediaPlayerClient = new MediaPlayer();
        m_MediaPlayerClient->setListener(this);
    }
    else if (m_MediaPlayerClient->isPlaying())
    {
        m_MediaPlayerClient->stop();
        m_MediaPlayerClient->reset();
    }

	if (m_MediaPlayerClient->setDataSource(NULL, filePath, NULL/* headers*/) != NO_ERROR)
	//if (m_MediaPlayerClient->setDataSource(filePath, NULL/* headers*/) != NO_ERROR)
    {
        m_MediaPlayerClient->reset();
        ALOGE("Fail to load the audio file");
        return ACHLoadFileFailed;
    }

    m_MediaPlayerClient->setAudioStreamType(AUDIO_STREAM_MUSIC);
    if (m_MediaPlayerClient->prepare() != NO_ERROR)
    {
        m_MediaPlayerClient->reset();
        ALOGE("Fail to play the audio file, prepare failed");
        return ACHFailed;
    }

    if (m_MediaPlayerClient->start() != NO_ERROR)
    {
        m_MediaPlayerClient->reset();
        ALOGE("Fail to play the audio file, start failed");
        return ACHFailed;
    }

    if (2 == audioCmdParams.param1)
    {
        AudioSystem::setParameters(0, String8("HQA_MEDPLY_P1=2"));
    }
    else
    {
        AudioSystem::setParameters(0, String8("HQA_MEDPLY_P1=1"));
    }
    ALOGD("AudioCmdHandler::startAudioPlayer() out");
    return ACHSucceeded;
}

ACHStatus AudioCmdHandler::stopAudioPlayer()
{
    ALOGD("AudioCmdHandler::stopAudioPlayer() in");

    if (m_MediaPlayerClient.get() != NULL && m_MediaPlayerClient->isPlaying())
    {
        if (m_MediaPlayerClient->stop() != NO_ERROR)
        {
            ALOGE("Fail to stop playing the audio file");
            return ACHFailed;
        }
        m_MediaPlayerClient->reset();
        return ACHSucceeded;
    }

    return ACHFailed;
}

ACHStatus AudioCmdHandler::startRecorderFrI2S(AudioCmdParam &audioCmdParams)
{
    ALOGD("AudioCmdHandler::startRecorderFrI2S() in");

    int ret = ACHSucceeded;
    char recordFilepath[MAX_FILE_NAME];
    char recordFileName[TEMP_ARRAY_SIZE];

    if (audioCmdParams.param3 < 1 || audioCmdParams.param3 > 99)
    {
        return ACHParamError;
    }

    strcpy(recordFilepath, RECORD_DIR_I2S);
    if (access(recordFilepath, F_OK) < 0)
    {
        ALOGE("startRecorderFrI2S() the path %s is not exit", recordFilepath);
        ret = mkdir(recordFilepath, S_IRWXU | S_IRWXG | S_IRWXO);
        if (-1 == ret)
        {
            ALOGE("startRecorderFrI2S() create path %s failed", recordFilepath);
            return ACHFailed;
        }
    }

    sprintf(recordFileName, "%02d.wav", audioCmdParams.param3);
    strcat(recordFilepath, recordFileName);

    m_RecordSampleRate = audioCmdParams.param4;

    ret = startRecorder(recordFilepath, Audio_I2S_IN);
    if (ret != ACHSucceeded)
    {
        stopFMAudioPlayer();
        AudioSystem::setParameters(0, String8("HQA_I2SREC=0"));
        return ACHFailed;
    }

    return ACHSucceeded;
}

ACHStatus AudioCmdHandler::writeRegister(AudioCmdParam &audioCmdParams)
{
    ALOGD("AudioCmdHandler::writeRegister() in");

    char pRegWrite1[TEMP_ARRAY_SIZE];
    sprintf(pRegWrite1, "HQA_REGWRITE_P1=%x", audioCmdParams.param1);
    AudioSystem::setParameters(0, String8(pRegWrite1));

    char pRegWrite2[TEMP_ARRAY_SIZE];
    sprintf(pRegWrite2, "HQA_REGWRITE_P2=%x", audioCmdParams.param2);
    AudioSystem::setParameters(0, String8(pRegWrite2));

    char pRegWrite3[TEMP_ARRAY_SIZE];
    sprintf(pRegWrite3, "HQA_REGWRITE_P3=%x", audioCmdParams.param3);
    AudioSystem::setParameters(0, String8(pRegWrite3));

    return ACHSucceeded;
}

String8 AudioCmdHandler::readRegister(AudioCmdParam &audioCmdParams)
{
    ALOGD("AudioCmdHandler::readRegister() in");

    char pRegRead[TEMP_ARRAY_SIZE];
    String8 returnValue = String8("");

    sprintf(pRegRead, "HQA_REGREAD_P1=%x,%x", audioCmdParams.param1, audioCmdParams.param2);
    returnValue = AudioSystem::getParameters(0, String8(pRegRead));
    return returnValue;
}

void AudioCmdHandler::notify(int msg, int ext1, int ext2, const Parcel *obj)
{
    ALOGD("AudioCmdHandler received message: msg=%d, ext1=%d, ext2=%d", msg, ext1, ext2);
    obj = NULL;
    switch (msg)
    {
        case MEDIA_PLAYBACK_COMPLETE:
            if (m_MediaPlayerClient.get() != NULL)
            {
                m_MediaPlayerClient->stop();
                m_MediaPlayerClient->reset();
            }

            ALOGD("AudioCmdHandler::notify -- audio playback complete");
            break;
        case MEDIA_ERROR:
            if (m_MediaPlayerClient.get() != NULL)
            {
                m_MediaPlayerClient->reset();
            }

            ALOGE("AudioCmdHandler::notify -- audio playback error, exit");
            break;
        default:
            break;
    }
}

// add for mt6575 HQA
void AudioCmdHandler::setParameters(const String8 &keyValuePaires)
{
    AudioSystem::setParameters(0, keyValuePaires);
}

// add for mt6577 HQA
ACHStatus AudioCmdHandler::SetAudioData(int cmdType, void *ptr, size_t len)
{
    ALOGD("AudioCmdHandler::SetAudioData() cmdType=%d, len=%d", cmdType, len);
    int ret = NO_ERROR;

    ret = SetAudioData(cmdType, len, ptr);

    return ret == NO_ERROR ? ACHSucceeded : ACHFailed;
}

ACHStatus AudioCmdHandler::DLCustSPHMagiParamToNV(char *pParam)
{
    int write_size = 0;
    int size = 0;

    ALOGD("AudioCmdHandler::DLCustSPHMagiParamToNV() in");
    AUDIO_CUSTOM_MAGI_CONFERENCE_STRUCT *pSPHMagiPara = (AUDIO_CUSTOM_MAGI_CONFERENCE_STRUCT *)malloc(sizeof(AUDIO_CUSTOM_MAGI_CONFERENCE_STRUCT));
    if (pSPHMagiPara == NULL)
    {
        return ACHFailed;
    }
    else if (pParam == NULL)
    {
        free(pSPHMagiPara);
        pSPHMagiPara = NULL;
        return ACHFailed;
    }

    size = GetMagiConSpeechParamFromNVRam(pSPHMagiPara);
    ALOGD("DLCustSPHMagiParamToNV- GetMagiSpeechParamFromNVRam read size=%d", size);
    if (size != sizeof(AUDIO_CUSTOM_MAGI_CONFERENCE_STRUCT))
    {
        ALOGD("DLCustSPHMagiParamToNV Up load from NVRAM fail, structure size=%d,read_size=%d", sizeof(AUDIO_CUSTOM_MAGI_CONFERENCE_STRUCT), size);
        free(pSPHMagiPara);
        pSPHMagiPara = NULL;
        return ACHFailed;
    }

	 size = sizeof(AUDIO_CUSTOM_MAGI_CONFERENCE_STRUCT);
	 dataDecode((char *)pParam, size + sizeof(int));
	 if (*((int *)pParam) != size)
	 {
		 ALOGE("DLCustSPHMagiParamToNV miss data !!, received size = %d", *((int *)pParam));
		 free(pSPHMagiPara);
		 pSPHMagiPara = NULL;
		 return ACHFailed;
	 }
	 memcpy((void *)pSPHMagiPara, pParam + sizeof(int), sizeof(AUDIO_CUSTOM_MAGI_CONFERENCE_STRUCT));

    unsigned short *p = (unsigned short *)pSPHMagiPara;
    for (int i = 0; i < 32 ;  i++)
    {
        SLOGV("MAGI_CONFERENCE_STRUCT[%d] =%hu", i, p[i]);
    }

    write_size = SetMagiConSpeechParamToNVRam(pSPHMagiPara);
    if (write_size != sizeof(AUDIO_CUSTOM_MAGI_CONFERENCE_STRUCT))
    {
        ALOGD("DLCustSPHMagiParamToNV Down load to NVRAM fail, structure size=%d,writed_size=%d", sizeof(AUDIO_CUSTOM_MAGI_CONFERENCE_STRUCT), write_size);
        free(pSPHMagiPara);
        pSPHMagiPara = NULL;
        return ACHFailed;
    }

	AudioSystem::setParameters(0, String8("UpdateMagiConParameters=1"));

    free(pSPHMagiPara);
    pSPHMagiPara = NULL;

    return ACHSucceeded;
}

ACHStatus AudioCmdHandler::ULCustSPHMagiParamFromNV(char *pParam, int *len)
{
    int size = 0;
    int dataLen = 0;

    ALOGD("AudioCmdHandler::ULCustSPHMagiParamFromNV() in");
    if (NULL == pParam)
        return ACHFailed;

    AUDIO_CUSTOM_MAGI_CONFERENCE_STRUCT *pSPHMagiPara = (AUDIO_CUSTOM_MAGI_CONFERENCE_STRUCT *)malloc(sizeof(AUDIO_CUSTOM_MAGI_CONFERENCE_STRUCT));
    if (pSPHMagiPara == NULL)
        return ACHFailed;

    size = GetMagiConSpeechParamFromNVRam(pSPHMagiPara);
    if (size != sizeof(AUDIO_CUSTOM_MAGI_CONFERENCE_STRUCT))
    {
        ALOGD("ULCustSPHMagiParamFromNV Up load from NVRAM fail, structure size=%d,read_size=%d", sizeof(AUDIO_CUSTOM_MAGI_CONFERENCE_STRUCT), size);
        free(pSPHMagiPara);
        return ACHFailed;
    }

    unsigned short *p = (unsigned short *)pSPHMagiPara;
    for (int i = 0; i < 32 ;  i++)
    {
        ALOGD("MAGI_CONFERENCE_STRUCT[%d] =%hu", i, p[i]);
    }

	dataLen = sizeof(AUDIO_CUSTOM_MAGI_CONFERENCE_STRUCT);
	memcpy(pParam + sizeof(int), (void *)pSPHMagiPara, dataLen);
	

    ALOGD("ULCustSPHMagiParamFromNV the data sent to PC is %d", dataLen);
    *((int *)pParam) = dataLen;
    *len = 2 * (dataLen + sizeof(int));

    dataEncode((char *)pParam, dataLen + sizeof(int));

    free(pSPHMagiPara);
    return ACHSucceeded;
}
ACHStatus AudioCmdHandler::DLCustSPHHACParamToNV(char *pParam)
{
    int write_size = 0;
    int size = 0;

    ALOGD("AudioCmdHandler::DLCustSPHHACParamToNV() in");
    AUDIO_CUSTOM_HAC_PARAM_STRUCT *pSPHHACPara = (AUDIO_CUSTOM_HAC_PARAM_STRUCT *)malloc(sizeof(AUDIO_CUSTOM_HAC_PARAM_STRUCT));
    if (pSPHHACPara == NULL)
    {
        return ACHFailed;
    }
    else if (pParam == NULL)
    {
        free(pSPHHACPara);
        pSPHHACPara = NULL;
        return ACHFailed;
    }

    size = GetHACSpeechParamFromNVRam(pSPHHACPara);
    ALOGD("DLCustSPHHACParamToNV- GetHACSpeechParamFromNVRam read size=%d", size);
    if (size != sizeof(AUDIO_CUSTOM_HAC_PARAM_STRUCT))
    {
        ALOGD("DLCustSPHHACParamToNV Up load from NVRAM fail, structure size=%d,read_size=%d", sizeof(AUDIO_CUSTOM_HAC_PARAM_STRUCT), size);
        free(pSPHHACPara);
        pSPHHACPara = NULL;
        return ACHFailed;
    }

	 size = sizeof(AUDIO_CUSTOM_HAC_PARAM_STRUCT);
	 dataDecode((char *)pParam, size + sizeof(int));
	 if (*((int *)pParam) != size)
	 {
		 ALOGE("DLCustSPHHACParamToNV miss data !!, received size = %d", *((int *)pParam));
		 free(pSPHHACPara);
		 pSPHHACPara = NULL;
		 return ACHFailed;
	 }
	 memcpy((void *)pSPHHACPara, pParam + sizeof(int), sizeof(AUDIO_CUSTOM_HAC_PARAM_STRUCT));

    unsigned short *p = (unsigned short *)pSPHHACPara;
    for (int i = 0; i < 32; i++)
    {
        ALOGD("HAC_STRUCT[%d] =%hu", i, p[i]);
    }
    short *ps = (short *)pSPHHACPara;
    for (int i = 0; i < 270;  i++)
    {
        ALOGD("HAC_STRUCT[%d] =%hu", i + 32, ps[i + 32]);
    }

    write_size = SetHACSpeechParamToNVRam(pSPHHACPara);
    if (write_size != sizeof(AUDIO_CUSTOM_HAC_PARAM_STRUCT))
    {
        ALOGD("DLCustSPHHACParamToNV Down load to NVRAM fail, structure size=%d,writed_size=%d", sizeof(AUDIO_CUSTOM_HAC_PARAM_STRUCT), write_size);
        free(pSPHHACPara);
        pSPHHACPara = NULL;
        return ACHFailed;
    }

	AudioSystem::setParameters(0, String8("UpdateHACParameters=1"));

    free(pSPHHACPara);
    pSPHHACPara = NULL;

    return ACHSucceeded;
}

ACHStatus AudioCmdHandler::ULCustSPHHACParamFromNV(char *pParam, int *len)
{
    int size = 0;
    int dataLen = 0;

    ALOGD("AudioCmdHandler::ULCustSPHHACParamFromNV() in");
    if (NULL == pParam)
        return ACHFailed;

    AUDIO_CUSTOM_HAC_PARAM_STRUCT *pSPHHACPara = (AUDIO_CUSTOM_HAC_PARAM_STRUCT *)malloc(sizeof(AUDIO_CUSTOM_HAC_PARAM_STRUCT));
    if (pSPHHACPara == NULL)
        return ACHFailed;

    size = GetHACSpeechParamFromNVRam(pSPHHACPara);
    if (size != sizeof(AUDIO_CUSTOM_HAC_PARAM_STRUCT))
    {
        ALOGD("ULCustSPHHACParamFromNV Up load from NVRAM fail, structure size=%d,read_size=%d", sizeof(AUDIO_CUSTOM_HAC_PARAM_STRUCT), size);
        free(pSPHHACPara);
        return ACHFailed;
    }

    unsigned short *p = (unsigned short *)pSPHHACPara;
    for (int i = 0; i < 32; i++)
    {
        ALOGD("HAC_STRUCT[%d] =%hu", i, p[i]);
    }
    short *ps = (short *)pSPHHACPara;
    for (int i = 0; i < 270;  i++)
    {
        ALOGD("HAC_STRUCT[%d] =%hu", i + 32, ps[i + 32]);
    }


	dataLen = sizeof(AUDIO_CUSTOM_HAC_PARAM_STRUCT);
	memcpy(pParam + sizeof(int), (void *)pSPHHACPara, dataLen);
	

    ALOGD("ULCustSPHHACParamFromNV the data sent to PC is %d", dataLen);
    *((int *)pParam) = dataLen;
    *len = 2 * (dataLen + sizeof(int));

    dataEncode((char *)pParam, dataLen + sizeof(int));

    free(pSPHHACPara);
    return ACHSucceeded;
}
ACHStatus AudioCmdHandler::DLCustSPHLPBKParamToNV(char *pParam)
{
    int write_size = 0;
    int size = 0;

    ALOGD("AudioCmdHandler::DLCustSPHLPBKParamToNV() in");
    if (NULL == pParam)
        return ACHFailed;

    AUDIO_CUSTOM_SPEECH_LPBK_PARAM_STRUCT *pSPHLPBKPara = (AUDIO_CUSTOM_SPEECH_LPBK_PARAM_STRUCT *)malloc(sizeof(AUDIO_CUSTOM_SPEECH_LPBK_PARAM_STRUCT));
    if (pSPHLPBKPara == NULL)
        return ACHFailed;

    size = GetNBSpeechLpbkParamFromNVRam(pSPHLPBKPara);
    ALOGD("DLCustSPHLPBKParamToNV- GetNBSpeechLpbkParamFromNVRam read size=%d", size);
    if (size != sizeof(AUDIO_CUSTOM_SPEECH_LPBK_PARAM_STRUCT))
    {
        ALOGD("DLCustSPHLPBKParamToNV Up load from NVRAM fail, structure size=%d,read_size=%d", sizeof(AUDIO_CUSTOM_SPEECH_LPBK_PARAM_STRUCT), size);
        free(pSPHLPBKPara);
        return ACHFailed;
    }

	 size = sizeof(AUDIO_CUSTOM_SPEECH_LPBK_PARAM_STRUCT);
	 dataDecode((char *)pParam, size + sizeof(int));
	 if (*((int *)pParam) != size)
	 {
		 ALOGE("DLCustSPHHACParamToNV miss data !!, received size = %d", *((int *)pParam));
		 free(pSPHLPBKPara);
		 return ACHFailed;
	 }
	 memcpy((void *)pSPHLPBKPara, pParam + sizeof(int), sizeof(AUDIO_CUSTOM_SPEECH_LPBK_PARAM_STRUCT));

    unsigned short *p = (unsigned short *)pSPHLPBKPara;
    for (int i = 0; i < 48; i++)
    {
        ALOGD("LPBK_STRUCT[%d] =%hu", i, p[i]);
    }

    write_size = SetNBSpeechLpbkParamToNVRam(pSPHLPBKPara);
    if (write_size != sizeof(AUDIO_CUSTOM_SPEECH_LPBK_PARAM_STRUCT))
    {
        ALOGD("DLCustSPHHACParamToNV Down load to NVRAM fail, structure size=%d,writed_size=%d", sizeof(AUDIO_CUSTOM_SPEECH_LPBK_PARAM_STRUCT), write_size);
        free(pSPHLPBKPara);
        return ACHFailed;
    }

	AudioSystem::setParameters(0, String8("UpdateLPBKParameters=1"));

    free(pSPHLPBKPara);
    return ACHSucceeded;
}

ACHStatus AudioCmdHandler::ULCustSPHLPBKParamFromNV(char *pParam, int *len)
{
    int size = 0;
    int dataLen = 0;

    ALOGD("AudioCmdHandler::ULCustSPHLPBKParamFromNV() in");
    if (NULL == pParam)
        return ACHFailed;

    AUDIO_CUSTOM_SPEECH_LPBK_PARAM_STRUCT *pSPHLPBKPara = (AUDIO_CUSTOM_SPEECH_LPBK_PARAM_STRUCT *)malloc(sizeof(AUDIO_CUSTOM_SPEECH_LPBK_PARAM_STRUCT));
    if (pSPHLPBKPara == NULL)
        return ACHFailed;

    size = GetNBSpeechLpbkParamFromNVRam(pSPHLPBKPara);
    if (size != sizeof(AUDIO_CUSTOM_SPEECH_LPBK_PARAM_STRUCT))
    {
        ALOGD("ULCustSPHLPBKParamFromNV Up load from NVRAM fail, structure size=%d,read_size=%d", sizeof(AUDIO_CUSTOM_SPEECH_LPBK_PARAM_STRUCT), size);
        free(pSPHLPBKPara);
        return ACHFailed;
    }
    unsigned short *p = (unsigned short *)pSPHLPBKPara;
    for (int i = 0; i < 48; i++)
    {
        ALOGD("LPBK_STRUCT[%d] =%hu", i, p[i]);
    }

	dataLen = sizeof(AUDIO_CUSTOM_SPEECH_LPBK_PARAM_STRUCT);
	memcpy(pParam + sizeof(int), (void *)pSPHLPBKPara, dataLen);
	

    ALOGD("ULCustSPHLPBKParamFromNV the data sent to PC is %d", dataLen);
    *((int *)pParam) = dataLen;
    *len = 2 * (dataLen + sizeof(int));

    dataEncode((char *)pParam, dataLen + sizeof(int));

    free(pSPHLPBKPara);
    return ACHSucceeded;
}

// add for speech parameters calibration-2/6/2012
ACHStatus AudioCmdHandler::DLCustSPHParamToNV(char *pParam, int block)
{
    int write_size = 0;
    int size = 0;

    ALOGD("AudioCmdHandler::DLCustSPHParamToNV() in");
    AUD_SPH_PARAM_STRUCT *pCustomPara = NULL;
	AUD_SPH_AFTER_FOUR_MODE_PARAM_STRUCT *pFourModeCustomPara = NULL;
    AUDIO_PARAM_MED_STRUCT *pSPHMedPara = (AUDIO_PARAM_MED_STRUCT *)malloc(sizeof(AUDIO_PARAM_MED_STRUCT));
    if (pSPHMedPara == NULL)
    {
        return ACHFailed;
    }
    else if (pParam == NULL)
    {
        free(pSPHMedPara);
        pSPHMedPara = NULL;
        return ACHFailed;
    }

    size = GetMedParamFromNV(pSPHMedPara);
    ALOGD("DLCustSPHParamToNV- GetMedParamFromNV read size=%d", size);
    if (size != sizeof(AUDIO_PARAM_MED_STRUCT))
    {
        ALOGD("DLCustSPHParamToNV Up load from NVRAM fail, structure size=%d,read_size=%d", sizeof(AUDIO_PARAM_MED_STRUCT), size);
        free(pSPHMedPara);
        pSPHMedPara = NULL;
        return ACHFailed;
    }

    if (block == 0)
    {
        pCustomPara = (AUD_SPH_PARAM_STRUCT *)(pParam + sizeof(int));
        AUDIO_CUSTOM_PARAM_STRUCT *pSPHPara = (AUDIO_CUSTOM_PARAM_STRUCT *)malloc(sizeof(AUDIO_CUSTOM_PARAM_STRUCT));
        if (pSPHPara == NULL)
        {
            free(pSPHMedPara);
            pSPHMedPara = NULL;
            return ACHFailed;
        }

        ALOGD("DLCustSPHParamToNV customer size=%d,sph_param size=%d", size , sizeof(AUDIO_CUSTOM_PARAM_STRUCT));
        size = GetNBSpeechParamFromNVRam(pSPHPara);
        if (size != sizeof(AUDIO_CUSTOM_PARAM_STRUCT))
        {
            ALOGD("DLCustSPHParamToNV Up load from NVRAM fail, structure size=%d,read_size=%d", sizeof(AUDIO_CUSTOM_PARAM_STRUCT), size);
            free(pSPHPara);
            pSPHPara = NULL;
            free(pSPHMedPara);
            pSPHMedPara = NULL;
            return ACHFailed;
        }

        size = sizeof(pCustomPara->sph_com_param) + sizeof(pCustomPara->sph_mode_param) + sizeof(pCustomPara->sph_in_fir) + sizeof(pCustomPara->sph_out_fir);
        dataDecode((char *)pParam, size + sizeof(int));
        if (*((int *)pParam) != size)
        {
            ALOGE("DLCustSPHParamToNV miss data !!");
            free(pSPHPara);
            pSPHPara = NULL;
            free(pSPHMedPara);
            pSPHMedPara = NULL;
            return ACHFailed;
        }

        for (int i = 0; i < FIR_NUM_NB ;  i++)
        {
            SLOGV("Received FIR Coefs sph_out_fir[0][%d]=%d", i, pCustomPara->sph_out_fir[0][i]);
        }

        for (int i = 0; i < FIR_NUM_NB ;  i++)
        {
            SLOGV("Speech Out FIR Coefs ori sph_out_fir[0][%d]=%d", i, pSPHPara->sph_out_fir[0][i]);
        }

        ALOGD("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        ALOGD("Speech Param uSupportVM_ori = %d", pSPHPara->uSupportVM);
        ALOGD("Speech Param uAutoVM_ori = %d", pSPHPara->uAutoVM);
        ALOGD("Speech Param uMicbiasVolt_ori = %d", pSPHPara->uMicbiasVolt);

        for (int i = 0; i < SPH_ENHANCE_PARAM_NUM ;  i++)
        {
            SLOGV("Received speech mode parameters ori sph_mode_param[0][%d]=%d", i, pCustomPara->sph_mode_param[0][i]);
        }

        for (int i = 0; i < SPH_ENHANCE_PARAM_NUM ;  i++)
        {
            SLOGV("Speech mode parameters ori speech_mode_para[0][%d]=%d", i, pSPHPara->speech_mode_para[0][i]);
        }

        memcpy((void *)pSPHPara->speech_common_para, (void *)pCustomPara->sph_com_param, sizeof(pCustomPara->sph_com_param));
        memcpy((void *)pSPHPara->speech_mode_para, (void *)pCustomPara->sph_mode_param, sizeof(pCustomPara->sph_mode_param));
        memcpy((void *)pSPHPara->sph_in_fir, (void *)pCustomPara->sph_in_fir, sizeof(pCustomPara->sph_in_fir));
        memcpy((void *)pSPHPara->sph_out_fir, (void *)pCustomPara->sph_out_fir, sizeof(pCustomPara->sph_out_fir));

        memcpy((void *)pSPHMedPara->speech_mode_para, (void *)pCustomPara->sph_mode_param, sizeof(pCustomPara->sph_mode_param));
        memcpy((void *)pSPHMedPara->speech_input_FIR_coeffs, (void *)pCustomPara->sph_in_fir, sizeof(pCustomPara->sph_in_fir));

        for (int i = 0; i < FIR_NUM_NB ;  i++)
        {
            SLOGV("Speech Out FIR Coefs new sph_out_fir[0][%d]=%d", i, pSPHPara->sph_out_fir[0][i]);
        }

        SLOGV("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        SLOGV("Speech Param uSupportVM_new = %d", pSPHPara->uSupportVM);
        SLOGV("Speech Param uAutoVM_new = %d", pSPHPara->uAutoVM);
        SLOGV("Speech Param uMicbiasVolt_new = %d", pSPHPara->uMicbiasVolt);

        for (int i = 0; i < SPH_ENHANCE_PARAM_NUM ;  i++)
        {
            SLOGV("Speech mode parameters new speech_mode_para[0][%d]=%d", i, pSPHPara->speech_mode_para[0][i]);
        }

        write_size = SetNBSpeechParamToNVRam(pSPHPara);
        if (write_size != sizeof(AUDIO_CUSTOM_PARAM_STRUCT))
        {
            ALOGD("DLCustSPHParamToNV Down load to NVRAM fail, structure size=%d,writed_size=%d", sizeof(AUDIO_CUSTOM_PARAM_STRUCT), write_size);
            free(pSPHPara);
            pSPHPara = NULL;
            free(pSPHMedPara);
            pSPHMedPara = NULL;
            return ACHFailed;
        }

        free(pSPHPara);
        pSPHPara = NULL;
    }
    else if (block == 1)
    {
        size = 2 * sizeof(pCustomPara->sph_output_FIR_coeffs[0]);
        dataDecode((char *)pParam, size + sizeof(int));

        if (*((int *)pParam) != size)
        {
            ALOGE("DLCustSPHParamToNV miss data !! block = %d, received size = %d", block, *((int *)pParam));
            free(pSPHMedPara);
            pSPHMedPara = NULL;
            return ACHFailed;
        }

        for (int i = 0; i < SPH_MODE_NUM ;  i++)
        {
            SLOGV("selected Speech Out FIR index ori select_FIR_output_index[%d]=%d", i, pSPHMedPara->select_FIR_output_index[i]);
        }

        for (int i = 0; i < SPH_MODE_NUM; i++)
        {
            for (int j = 0; j < SPH_ENHANCE_PARAM_NUM; j++)
            {
                SLOGV("MED Speech Out FIR index ori speech_output_FIR_coeffs[%d][0][%d]=%d", i, j, pSPHMedPara->speech_output_FIR_coeffs[i][0][j]);
            }
        }

        memcpy((void *)pSPHMedPara->speech_output_FIR_coeffs, pParam + sizeof(int), size);
    }
    else if(block == 2)
    {
        size = 2 * sizeof(pCustomPara->sph_output_FIR_coeffs[0]) + sizeof(pCustomPara->selected_FIR_output_index);
        dataDecode((char *)pParam, size + sizeof(int));

        if (*((int *)pParam) != size)
        {
            ALOGE("DLCustSPHParamToNV miss data !! block = %d, received size = %d", block, *((int *)pParam));
            free(pSPHMedPara);
            pSPHMedPara = NULL;
            return ACHFailed;
        }

        // to solve coverity 115203
        //memcpy((void *)pSPHMedPara->speech_output_FIR_coeffs[2], pParam + sizeof(int), 2 * sizeof(pCustomPara->sph_output_FIR_coeffs[0]));
        //size = 2 * sizeof(pCustomPara->sph_output_FIR_coeffs[0]) + sizeof(int);
        //memcpy((void *)pSPHMedPara->select_FIR_output_index, pParam + size, sizeof(pCustomPara->selected_FIR_output_index));

        struct DLcustIn {
            int size;
            short speech_output_FIR_coeffs[2][FIR_INDEX_NUM][FIR_NUM_NB]; //[2][6][45];
            short selected_FIR_output_index[SPH_MODE_NUM]; //[4];
        };

        struct DLcustIn *pIn = (struct DLcustIn*) pParam;
        for (int i = 0; i < 2 ;  i++)
            memcpy(pSPHMedPara->speech_output_FIR_coeffs[2+i], pIn->speech_output_FIR_coeffs[i], sizeof(pIn->speech_output_FIR_coeffs[0]));
        memcpy(pSPHMedPara->select_FIR_output_index, pIn->selected_FIR_output_index, sizeof(pIn->selected_FIR_output_index));

        for (int i = 0; i < SPH_MODE_NUM ;  i++)
        {
            SLOGV("selected Speech Out FIR index new select_FIR_output_index[%d]=%d", i, pSPHMedPara->select_FIR_output_index[i]);
        }

        for (int i = 0; i < SPH_MODE_NUM; i++)
        {
            for (int j = 0; j < SPH_ENHANCE_PARAM_NUM; j++)
            {
                SLOGV("MED Speech Out FIR index new speech_output_FIR_coeffs[%d][0][%d]=%d", i, j, pSPHMedPara->speech_output_FIR_coeffs[i][0][j]);
            }
        }

#ifndef MTK_AUDIO_BT_NREC_WO_ENH_MODE
        AudioSystem::setParameters(0, String8("UpdateSpeechParameter=0"));
#endif
    }
	else if(block == 3) 
	{
		 pFourModeCustomPara = (AUD_SPH_AFTER_FOUR_MODE_PARAM_STRUCT *)(pParam + sizeof(int));
		 AUDIO_CUSTOM_PARAM_STRUCT *pSPHPara = (AUDIO_CUSTOM_PARAM_STRUCT *)malloc(sizeof(AUDIO_CUSTOM_PARAM_STRUCT));
		 if (pSPHPara == NULL)
		 {
			 free(pSPHMedPara);
			 pSPHMedPara = NULL;
			 return ACHFailed;
		 }
		
		 ALOGD("DLCustSPHParamToNV customer size=%d,sph_param size=%d", size , sizeof(AUDIO_CUSTOM_PARAM_STRUCT));
		 size = GetNBSpeechParamFromNVRam(pSPHPara);
		 if (size != sizeof(AUDIO_CUSTOM_PARAM_STRUCT))
		 {
			 ALOGD("DLCustSPHParamToNV Up load from NVRAM fail, structure size=%d,read_size=%d", sizeof(AUDIO_CUSTOM_PARAM_STRUCT), size);
			 free(pSPHPara);
			 pSPHPara = NULL;
			 free(pSPHMedPara);
			 pSPHMedPara = NULL;
			 return ACHFailed;
		 }
		
		 size = sizeof(pFourModeCustomPara->nb_dl_sph_mode_param) * 2;
		 dataDecode((char *)pParam, size + sizeof(int));
		 if (*((int *)pParam) != size)
		 {
			 ALOGE("DLCustSPHParamToNV miss data !!");
			 free(pSPHPara);
			 pSPHPara = NULL;
			 free(pSPHMedPara);
			 pSPHMedPara = NULL;
			 return ACHFailed;
		 }
		
		 for (int i = 0; i < SPH_MODE_NUM*SPH_ENHANCE_PARAM_NUM ;  i++)
		 {
			 ALOGD("AUD_SPH_AFTER_FOUR_MODE_PARAM_STRUCT[%d]=%d", i, *((unsigned short *)pFourModeCustomPara + i));
		 }
		
		 for(int i = 0; i < SPH_MODE_NUM; i++)
		 {
			for(int j = 0; j < SPH_ENHANCE_PARAM_NUM; j++)
				{
					pSPHPara->speech_mode_para[4+i][j] =  pFourModeCustomPara->nb_dl_sph_mode_param[i][j];
				}
		 }
		
		 write_size = SetNBSpeechParamToNVRam(pSPHPara);
		 if (write_size != sizeof(AUDIO_CUSTOM_PARAM_STRUCT))
		 {
			 ALOGD("DLCustSPHParamToNV Down load to NVRAM fail, structure size=%d,writed_size=%d", sizeof(AUDIO_CUSTOM_PARAM_STRUCT), write_size);
			 free(pSPHPara);
			 pSPHPara = NULL;
			 free(pSPHMedPara);
			 pSPHMedPara = NULL;
			 return ACHFailed;
		 }

		AudioSystem::setParameters(0, String8("UpdateSpeechParameter=0"));
		 free(pSPHPara);
		 pSPHPara = NULL;
	}

    write_size = SetMedParamToNV(pSPHMedPara);
    if (write_size != sizeof(AUDIO_PARAM_MED_STRUCT))
    {
        ALOGD("DLCustSPHParamToNV Down load to NVRAM fail, structure size=%d,writed_size=%d", sizeof(AUDIO_PARAM_MED_STRUCT), write_size);
        free(pSPHMedPara);
        pSPHMedPara = NULL;
        return ACHFailed;
    }

    free(pSPHMedPara);
    pSPHMedPara = NULL;

    return ACHSucceeded;
}

ACHStatus AudioCmdHandler::ULCustSPHParamFromNV(char *pParam, int *len, int block)
{
    int size = 0;
    int dataLen = 0;

    ALOGD("AudioCmdHandler::ULCustSPHParamFromNV() in");
    if (NULL == pParam)
        return ACHFailed;

    AUDIO_CUSTOM_PARAM_STRUCT *pSPHPara = (AUDIO_CUSTOM_PARAM_STRUCT *)malloc(sizeof(AUDIO_CUSTOM_PARAM_STRUCT));
    if (NULL == pSPHPara)
        return ACHFailed;

    AUDIO_PARAM_MED_STRUCT *pSPHMedPara = (AUDIO_PARAM_MED_STRUCT *)malloc(sizeof(AUDIO_PARAM_MED_STRUCT));
    if (pSPHMedPara == NULL) {
        free(pSPHPara);
        return ACHFailed;
    }

    size = GetNBSpeechParamFromNVRam(pSPHPara);
    if (size != sizeof(AUDIO_CUSTOM_PARAM_STRUCT))
    {
        ALOGD("ULCustSPHParamFromNV Up load from NVRAM fail, structure size=%d,read_size=%d", sizeof(AUDIO_CUSTOM_PARAM_STRUCT), size);
        free(pSPHPara);
        free(pSPHMedPara);
        return ACHFailed;
    }

    size = GetMedParamFromNV(pSPHMedPara);
    if (size != sizeof(AUDIO_PARAM_MED_STRUCT))
    {
        ALOGD("ULCustSPHParamFromNV Up load from NVRAM fail, structure size=%d,read_size=%d", sizeof(AUDIO_PARAM_MED_STRUCT), size);
        free(pSPHPara);
        free(pSPHMedPara);
        return ACHFailed;
    }

    for (int i = 0; i < FIR_NUM_NB ;  i++)
    {
        SLOGV("Speech Out FIR Coefs ori sph_out_fir[0][%d]=%d", i, pSPHPara->sph_out_fir[0][i]);
    }

    SLOGV("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    SLOGV("Speech Param uSupportVM_ori = %d", pSPHPara->uSupportVM);
    SLOGV("Speech Param uAutoVM_ori = %d", pSPHPara->uAutoVM);
    SLOGV("Speech Param uMicbiasVolt_ori = %d", pSPHPara->uMicbiasVolt);

    for (int i = 0; i < SPH_ENHANCE_PARAM_NUM ;  i++)
    {
        SLOGV("Speech mode parameters ori speech_mode_para[0][%d]=%d", i, pSPHPara->speech_mode_para[0][i]);
    }

    for (int i = 0; i < 8 ;  i++)
    {
        SLOGV("selected Speech Out FIR index ori select_FIR_output_index[%d]=%d", i, pSPHMedPara->select_FIR_output_index[i]);
    }

    for (int i = 0; i < 5 ;  i++)
    {
        SLOGV("MED Speech Out FIR index ori speech_output_FIR_coeffs[1][0][%d]=%d", i, pSPHMedPara->speech_output_FIR_coeffs[1][0][i]);
    }

    if (block == 0)
    {
        dataLen = sizeof(AUDIO_CUSTOM_PARAM_STRUCT);
        memcpy(pParam + sizeof(int), (void *)pSPHPara, dataLen);
    }
    else if (block == 1)
    {
        dataLen = sizeof(pSPHMedPara->speech_input_FIR_coeffs);
        memcpy(pParam + sizeof(int), (void *)pSPHMedPara->speech_input_FIR_coeffs, dataLen);
    }
    else if (block == 2 || block == 3)
    {
        dataLen = 3 * sizeof(pSPHMedPara->speech_output_FIR_coeffs[0]);
        memcpy(pParam + sizeof(int), (void *)pSPHMedPara->speech_output_FIR_coeffs[3 * block - 6], dataLen);
    }
    else
    {
        dataLen = 2 * sizeof(pSPHMedPara->speech_output_FIR_coeffs[0]) + sizeof(pSPHMedPara->speech_mode_para);
        dataLen += sizeof(pSPHMedPara->select_FIR_intput_index) + sizeof(pSPHMedPara->select_FIR_output_index);

        // For coverity
        //memcpy(pParam + sizeof(int), (void *)pSPHMedPara->speech_output_FIR_coeffs[6], dataLen);

        char *pTemp = (char*)(pParam + sizeof(int));
        size_t tempsize = 2 * sizeof(pSPHMedPara->speech_output_FIR_coeffs[0]);
        memcpy (pTemp, (void *)pSPHMedPara->speech_output_FIR_coeffs[6], tempsize);

        pTemp += tempsize;
        tempsize =  sizeof(pSPHMedPara->select_FIR_output_index);
        memcpy (pTemp, (void *)pSPHMedPara->select_FIR_output_index, tempsize);

        pTemp += tempsize;
        tempsize =  sizeof(pSPHMedPara->select_FIR_intput_index);
        memcpy (pTemp, (void *)pSPHMedPara->select_FIR_intput_index, tempsize);

        pTemp += tempsize;
        tempsize =  sizeof(pSPHMedPara->speech_mode_para);
        memcpy (pTemp, (void *)pSPHMedPara->speech_mode_para, tempsize);
    }

    ALOGD("ULCustSPHParamFromNV the data sent to PC is %d", dataLen);

    *((int *)pParam) = dataLen;
    *len = 2 * (dataLen + sizeof(int));

    dataEncode((char *)pParam, dataLen + sizeof(int));

    free(pSPHPara);
    free(pSPHMedPara);
    return ACHSucceeded;
}

ACHStatus AudioCmdHandler::DLCustSPHVolumeParamToNV(char *pParam)
{
    int write_size = 0;
    int size = 0;
    int dataLen = 0;

    ALOGD("AudioCmdHandler::DLCustSPHVolumeParamToNV() in");
    if (NULL == pParam)
        return ACHFailed;

    AUD_VOL_CUSTOM_STRUCT *pSPHVolPara = (AUD_VOL_CUSTOM_STRUCT *)malloc(sizeof(AUD_VOL_CUSTOM_STRUCT));
    if (pSPHVolPara == NULL)
        return ACHFailed;

    dataDecode((char *)pParam, sizeof(AUD_VOL_CUSTOM_STRUCT) + sizeof(int));
    dataLen = *((int *)pParam);
    if (dataLen != sizeof(AUD_VOL_CUSTOM_STRUCT))
    {
        ALOGE("DLCustSPHVolumeParamToNV miss data !!");
        free(pSPHVolPara);
        return ACHFailed;
    }

    AUD_VOL_CUSTOM_STRUCT *pCustomPara = (AUD_VOL_CUSTOM_STRUCT *)(pParam + sizeof(int));

#if 0
    size = GetAudioCustomParamFromNV(pSPHVolPara);
#else
    size = GetVolumeVer1ParamFromNV(pSPHVolPara);
#endif
    if (size != sizeof(AUD_VOL_CUSTOM_STRUCT))
    {
        ALOGD("DLCustSPHVolumeParamToNV Up load from NVRAM fail, structure size=%d,read_size=%d", sizeof(AUD_VOL_CUSTOM_STRUCT), size);
        free(pSPHVolPara);
        return ACHFailed;
    }
#if 0
    SLOGV("~~~~~~~~~~~~~~~~DL mic volume~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    for (int i = 0; i < MAX_VOL_CATE; i++)
    {
        for (int j = 0; j < CUSTOM_VOL_STEP; j++)
        {
            SLOGV("ori data - mic volume audiovolume_mic[%d][%d] = %d", i, j, pSPHVolPara->audiovolume_mic[i][j]);
        }
    }
    SLOGV("~~~~~~~~~~~~~~~~DL sid volume~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    for (int i = 0; i < MAX_VOL_CATE; i++)
    {
        for (int j = 0; j < CUSTOM_VOL_STEP; j++)
        {
            SLOGV("ori data - sid volume audiovolume_sid[%d][%d]=%d", i, j, pSPHVolPara->audiovolume_sid[i][j]);
        }
    }
    SLOGV("~~~~~~~~~~~~~~~~DL sph volume~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    for (int i = 0; i < MAX_VOL_CATE; i++)
    {
        for (int j = 0; j < CUSTOM_VOL_STEP; j++)
        {
            SLOGV("ori data - sph volume audiovolume_sph[%d][%d]=%d", i, j, pSPHVolPara->audiovolume_sph[i][j]);
        }
    }
#else
    SLOGV("~~~~~~~~~~~~~~~~DL ring volume~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    for (int i = 0; i < NUM_OF_VOL_MODE; i++)
    {
        for (int j = 0; j < AUDIO_MAX_VOLUME_STEP; j++)
        {
            SLOGV("ori data - ring volume audiovolume_ring[%d][%d]=%d", i, j, pSPHVolPara->audiovolume_ring[i][j]);
        }
    }

    SLOGV("~~~~~~~~~~~~~~~~DL sph volume~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    for (int i = 0; i < NUM_OF_VOL_MODE; i++)
    {
        for (int j = 0; j < AUDIO_MAX_VOLUME_STEP; j++)
        {
            SLOGV("ori data - mic volume audiovolume_sph[%d][%d] = %d", i, j, pSPHVolPara->audiovolume_sph[i][j]);
        }
    }

    SLOGV("~~~~~~~~~~~~~~~~audio volume level~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    for (int i = 0; i < VER1_NUM_OF_VOL_TYPE; i++)
    {
        SLOGV("ori data - audio volume level audiovolume_level[%d] = %d", i, pSPHVolPara->audiovolume_level[i]);
    }
#endif

    memcpy((void *)pSPHVolPara, (void *)pCustomPara, sizeof(AUD_VOL_CUSTOM_STRUCT));

#if 0
    SLOGV("~~~~~~~~~~~~~~~~mic volume~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    for (int i = 0; i < MAX_VOL_CATE; i++)
    {
        for (int j = 0; j < CUSTOM_VOL_STEP; j++)
        {
            SLOGV("new data - mic volume audiovolume_mic[%d][%d]=%d", i, j, pSPHVolPara->audiovolume_mic[i][j]);
        }
    }
    SLOGV("~~~~~~~~~~~~~~~~sid volume~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    for (int i = 0; i < MAX_VOL_CATE; i++)
    {
        for (int j = 0; j < CUSTOM_VOL_STEP; j++)
        {
            SLOGV("new data - sid volume audiovolume_sid[%d][%d]=%d", i, j, pSPHVolPara->audiovolume_sid[i][j]);
        }
    }
    SLOGV("~~~~~~~~~~~~~~~~sph volume~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    for (int i = 0; i < MAX_VOL_CATE; i++)
    {
        for (int j = 0; j < CUSTOM_VOL_STEP; j++)
        {
            SLOGV("new data - sph volume audiovolume_sph[%d][%d]=%d", i, j, pSPHVolPara->audiovolume_sph[i][j]);
        }
    }

    write_size = SetAudioCustomParamToNV(pSPHVolPara);
#else
    SLOGV("~~~~~~~~~~~~~~~~DL ring volume~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    for (int i = 0; i < NUM_OF_VOL_MODE; i++)
    {
        for (int j = 0; j < AUDIO_MAX_VOLUME_STEP; j++)
        {
            SLOGV("new data - ring volume audiovolume_ring[%d][%d]=%d", i, j, pSPHVolPara->audiovolume_ring[i][j]);
        }
    }
    SLOGV("~~~~~~~~~~~~~~~~DL sph volume~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    for (int i = 0; i < NUM_OF_VOL_MODE; i++)
    {
        for (int j = 0; j < AUDIO_MAX_VOLUME_STEP; j++)
        {
            SLOGV("new data - sph volume audiovolume_sph[%d][%d]=%d", i, j, pSPHVolPara->audiovolume_sph[i][j]);
        }
    }
    SLOGV("~~~~~~~~~~~~~~~~audio volume level~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    for (int i = 0; i < NUM_OF_VOL_MODE; i++)
    {
        SLOGV("new data - audio volume level audiovolume_level[%d]=%d", i, pSPHVolPara->audiovolume_level[i]);
    }

    write_size = SetVolumeVer1ParamToNV(pSPHVolPara);
#endif

    if (write_size != sizeof(AUD_VOL_CUSTOM_STRUCT))
    {
        ALOGD("DLCustSPHVolumeParamToNV Down load to NVRAM fail, structure size=%d,writed_size=%d", sizeof(AUD_VOL_CUSTOM_STRUCT), write_size);
        free(pSPHVolPara);
        return ACHFailed;
    }

    free(pSPHVolPara);
    pSPHVolPara = NULL;

    int volumeIndex[DEV_NUM][AUDIO_STREAM_PUBLIC_CNT];
    for (int i = 0; i < AUDIO_STREAM_PUBLIC_CNT; i++)
    {
        // get volue for different devices, 0:receiver; 1:speaker; 2:headset;
        AudioSystem::getStreamVolumeIndex((audio_stream_type_t)i, &volumeIndex[0][i], AUDIO_DEVICE_OUT_EARPIECE);
        AudioSystem::getStreamVolumeIndex((audio_stream_type_t)i, &volumeIndex[1][i], AUDIO_DEVICE_OUT_SPEAKER);
        AudioSystem::getStreamVolumeIndex((audio_stream_type_t)i, &volumeIndex[2][i], AUDIO_DEVICE_OUT_WIRED_HEADSET);
    }

#ifdef MTK_AUDIO
#ifndef MTK_BASIC_PACKAGE
    const sp<IAudioPolicyService> &aps = AudioSystem::get_audio_policy_service();
    if (aps == 0) { return ACHFailed; }
    aps->SetPolicyManagerParameters(LOAD_VOLUME_POLICY, 0, 0, 0);
#endif
#endif
    AudioSystem::setParameters(0, String8("UpdateSphVolumeParameter=0"));
    for (int i = 0; i < AUDIO_STREAM_PUBLIC_CNT; i++)
    {
        AudioSystem::setStreamVolumeIndex((audio_stream_type_t)i, volumeIndex[0][i], AUDIO_DEVICE_OUT_EARPIECE);
        AudioSystem::setStreamVolumeIndex((audio_stream_type_t)i, volumeIndex[1][i], AUDIO_DEVICE_OUT_SPEAKER);
        AudioSystem::setStreamVolumeIndex((audio_stream_type_t)i, volumeIndex[2][i], AUDIO_DEVICE_OUT_WIRED_HEADSET);
    }

    return ACHSucceeded;

}

ACHStatus AudioCmdHandler::RealTimeSetVolume(int iStreamType, int VolumeIndex,int iDeviceType)
{
   AudioSystem::setStreamVolumeIndex((audio_stream_type_t)iStreamType,VolumeIndex, iDeviceType);
   return ACHSucceeded;
}


ACHStatus AudioCmdHandler::ULCustSPHVolumeParamFromNV(char *pParam, int *len)
{
    int size = 0;

    ALOGD("AudioCmdHandler::ULCustSPHVolumeParamFromNV() in");
    if (NULL == pParam)
        return ACHFailed;

    AUD_VOL_CUSTOM_STRUCT *pSPHVolPara = (AUD_VOL_CUSTOM_STRUCT *)malloc(sizeof(AUD_VOL_CUSTOM_STRUCT));
    if (pSPHVolPara == NULL)
        return ACHFailed;

    *len = 2 * (sizeof(AUD_VOL_CUSTOM_STRUCT) + sizeof(int));

#if 0
    size = GetAudioCustomParamFromNV(pSPHVolPara);
#else
    size = GetVolumeVer1ParamFromNV(pSPHVolPara);
#endif

    if (size != sizeof(AUD_VOL_CUSTOM_STRUCT))
    {
        ALOGD("ULCustSPHVolumeParamFromNV Up load from NVRAM fail, structure size=%d,read_size=%d", sizeof(AUD_VOL_CUSTOM_STRUCT), size);
        free(pSPHVolPara);
        pSPHVolPara = NULL;
        return ACHFailed;
    }

#if 0
    SLOGV("~~~~~~~~~~~~~~~~UL mic volume~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    for (int i = 0; i < MAX_VOL_CATE; i++)
    {
        for (int j = 0; j < CUSTOM_VOL_STEP ; j++)
        {
            SLOGV("ori data - mic volume audiovolume_mic[%d][%d]=%d", i, j, pSPHVolPara->audiovolume_mic[i][j]);
        }
    }
    SLOGV("~~~~~~~~~~~~~~~~UL sid volume~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    for (int i = 0; i < MAX_VOL_CATE; i++)
    {
        for (int j = 0; j < CUSTOM_VOL_STEP; j++)
        {
            SLOGV("ori data - sid volume audiovolume_sid[%d][%d]=%d", i, j, pSPHVolPara->audiovolume_sid[i][j]);
        }
    }
    SLOGV("~~~~~~~~~~~~~~~~UL sph volume~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    for (int i = 0; i < MAX_VOL_CATE; i++)
    {
        for (int j = 0; j < CUSTOM_VOL_STEP; j++)
        {
            SLOGV("ori data - sph volume audiovolume_sph[%d][%d]=%d", i, j, pSPHVolPara->audiovolume_sph[i][j]);
        }
    }
#else
    SLOGV("~~~~~~~~~~~~~~~~UL ring volume~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    for (int i = 0; i < NUM_OF_VOL_MODE; i++)
    {
        for (int j = 0; j < AUDIO_MAX_VOLUME_STEP; j++)
        {
            SLOGV("ori data - ring volume audiovolume_ring[%d][%d]=%d", i, j, pSPHVolPara->audiovolume_ring[i][j]);
        }
    }

    SLOGV("~~~~~~~~~~~~~~~~UL sph volume~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    for (int i = 0; i < NUM_OF_VOL_MODE; i++)
    {
        for (int j = 0; j < AUDIO_MAX_VOLUME_STEP; j++)
        {
            SLOGV("ori data - mic volume audiovolume_sph[%d][%d] = %d", i, j, pSPHVolPara->audiovolume_sph[i][j]);
        }
    }

    SLOGV("~~~~~~~~~~~~~~~~audio volume level~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    for (int i = 0; i < VER1_NUM_OF_VOL_TYPE; i++)
    {
        SLOGV("ori data - audio volume level audiovolume_level[%d] = %d", i, pSPHVolPara->audiovolume_level[i]);
    }
#endif

    *((int *)pParam) = sizeof(AUD_VOL_CUSTOM_STRUCT);
    AUD_VOL_CUSTOM_STRUCT *pCustomPara = (AUD_VOL_CUSTOM_STRUCT *)(pParam + sizeof(int));

    memcpy((void *)pCustomPara, (void *)pSPHVolPara, sizeof(AUD_VOL_CUSTOM_STRUCT));
    dataEncode((char *)pParam, sizeof(AUD_VOL_CUSTOM_STRUCT) + sizeof(int));

    free(pSPHVolPara);
    pSPHVolPara = NULL;
    return ACHSucceeded;
}

ACHStatus AudioCmdHandler::DLCustSPHWBParamToNV(char *pParam, int block)
{
    int write_size = 0;
    int size = 0;
    int dataLen = 0;

    ALOGD("AudioCmdHandler::DLCustSPHWBParamToNV() in");
#ifdef MTK_WB_SPEECH_SUPPORT
    AUD_SPH_WB_PARAM_STRUCT *pCustomPara = NULL;
	AUD_SPH_AFTER_FOUR_MODE_PARAM_STRUCT *pFourCustomPara = NULL;
    AUDIO_CUSTOM_WB_PARAM_STRUCT *pSPHWBPara = (AUDIO_CUSTOM_WB_PARAM_STRUCT *)malloc(sizeof(AUDIO_CUSTOM_WB_PARAM_STRUCT));
    if (pSPHWBPara == NULL)
    {
        return ACHFailed;
    }

    ALOGD("DLCustSPHWBParamToNV ,wb sph param size=%d", sizeof(AUDIO_CUSTOM_WB_PARAM_STRUCT));
    size = GetWBSpeechParamFromNVRam(pSPHWBPara);
    if (size != sizeof(AUDIO_CUSTOM_WB_PARAM_STRUCT))
    {
        ALOGD("DLCustSPHWBParamToNV Up load from NVRAM fail, structure size=%d,read_size=%d", sizeof(AUDIO_CUSTOM_WB_PARAM_STRUCT), size);
        free(pSPHWBPara);
        pSPHWBPara = NULL;
        return ACHFailed;
    }

    if (block == 0)
    {
        size = sizeof(pCustomPara->sph_mode_wb_param) + sizeof(pCustomPara->sph_wb_in_fir);
        dataDecode((char *)pParam, size + sizeof(int));

        dataLen = *((int *)pParam);
        pCustomPara = (AUD_SPH_WB_PARAM_STRUCT *)(pParam + sizeof(int));

        if (dataLen != size)
        {
            ALOGE("DLCustSPHWBParamToNV data miss !!");
            free(pSPHWBPara);
            pSPHWBPara = NULL;
            return ACHFailed;
        }

        for (int i = 0; i < SPH_ENHANCE_PARAM_NUM ; i++)
        {
            SLOGV("Received speech mode parameters sph_mode_wb_param[0][%d]=%d", i, pCustomPara->sph_mode_wb_param[0][i]);
        }

        for (int i = 0; i < FIR_NUM_NB; i++)
        {
            SLOGV("Received WB FIR Coefs sph_wb_in_fir[0][%d]=%d", i, pCustomPara->sph_wb_in_fir[0][i]);
        }

        memcpy((void *)pSPHWBPara->speech_mode_wb_para, (void *)pCustomPara->sph_mode_wb_param, sizeof(pCustomPara->sph_mode_wb_param));
        memcpy((void *)pSPHWBPara->sph_wb_in_fir, (void *)pCustomPara->sph_wb_in_fir, sizeof(pCustomPara->sph_wb_in_fir));

        for (int i = 0; i < SPH_ENHANCE_PARAM_NUM ;  i++)
        {
            SLOGV("WB speech mode parameters new=%d", pSPHWBPara->speech_mode_wb_para[0][i]);
        }

        for (int i = 0; i < FIR_NUM_NB ;  i++)
        {
            SLOGV("WB speech in FIR Coefs new=%d", pSPHWBPara->sph_wb_in_fir[0][i]);
        }

        write_size = SetWBSpeechParamToNVRam(pSPHWBPara);
        if (write_size != sizeof(AUDIO_CUSTOM_WB_PARAM_STRUCT))
        {
            ALOGD("DLCustSPHWBParamToNV Down load to NVRAM fail, structure size=%d,writed_size=%d", sizeof(AUDIO_CUSTOM_WB_PARAM_STRUCT), write_size);
            free(pSPHWBPara);
            pSPHWBPara = NULL;
            return ACHFailed;
        }
    }
    else if(block == 1)
    {
        dataDecode((char *)pParam, sizeof(pCustomPara->sph_wb_out_fir) + sizeof(int));

        dataLen = *((int *)pParam);
        if (dataLen != sizeof(pCustomPara->sph_wb_out_fir))
        {
            ALOGE("DLCustSPHWBParamToNV data miss !!");
            free(pSPHWBPara);
            pSPHWBPara = NULL;
            return ACHFailed;
        }

        for (int i = 0; i < FIR_NUM_NB ;  i++)
        {
            SLOGV("WB speech out FIR Coefs ori=%d", pSPHWBPara->sph_wb_out_fir[0][i]);
        }

        memcpy((void *)pSPHWBPara->sph_wb_out_fir, pParam + sizeof(int), sizeof(pSPHWBPara->sph_wb_out_fir));

        for (int i = 0; i < FIR_NUM_NB ;  i++)
        {
            SLOGV("WB speech out FIR Coefs new=%d", pSPHWBPara->sph_wb_out_fir[0][i]);
        }

        write_size = SetWBSpeechParamToNVRam(pSPHWBPara);
        if (write_size != sizeof(AUDIO_CUSTOM_WB_PARAM_STRUCT))
        {
            ALOGD("DLCustSPHWBParamToNV Down load to NVRAM fail, structure size=%d,writed_size=%d", sizeof(AUDIO_CUSTOM_WB_PARAM_STRUCT), write_size);
            free(pSPHWBPara);
            pSPHWBPara = NULL;
            return ACHFailed;
        }

#ifndef MTK_AUDIO_BT_NREC_WO_ENH_MODE
		AudioSystem::setParameters(0, String8("UpdateSpeechParameter=1"));
#endif
    }
	else if(block == 2) 
	{
        size = sizeof(AUD_SPH_AFTER_FOUR_MODE_PARAM_STRUCT);
        dataDecode((char *)pParam, size + sizeof(int));

        dataLen = *((int *)pParam);
        pFourCustomPara = (AUD_SPH_AFTER_FOUR_MODE_PARAM_STRUCT *)(pParam + sizeof(int));

        if (dataLen != size)
        {
            ALOGE("DLCustSPHWBParamToNV data miss !!");
            free(pSPHWBPara);
            pSPHWBPara = NULL;
            return ACHFailed;
        }

		for (int i = 0; i < SPH_MODE_NUM*SPH_ENHANCE_PARAM_NUM ;  i++)
		{
			ALOGD("AUD_SPH_AFTER_FOUR_MODE_PARAM_STRUCT[%d]=%d", i, *((unsigned short *)pFourCustomPara + i));
		}
		
		for(int i = 0; i < SPH_MODE_NUM; i++)
		{
		   for(int j = 0; j < SPH_ENHANCE_PARAM_NUM; j++)
			   {
				   pSPHWBPara->speech_mode_wb_para[4+i][j] =  pFourCustomPara->wb_ul_dl_sph_mode_param[i][j];
			   }
		}

        write_size = SetWBSpeechParamToNVRam(pSPHWBPara);
        if (write_size != sizeof(AUDIO_CUSTOM_WB_PARAM_STRUCT))
        {
            ALOGD("DLCustSPHWBParamToNV Down load to NVRAM fail, structure size=%d,writed_size=%d", sizeof(AUDIO_CUSTOM_WB_PARAM_STRUCT), write_size);
            free(pSPHWBPara);
            pSPHWBPara = NULL;
            return ACHFailed;
        }
		
		AudioSystem::setParameters(0, String8("UpdateSpeechParameter=1"));
	}

    free(pSPHWBPara);
    pSPHWBPara = NULL;
#else
	return ACHFailed;
#endif

    return ACHSucceeded;
}

ACHStatus AudioCmdHandler::ULCustSPHWBParamFromNV(char *pParam, int *len, int block)
{
    int size = 0;

    ALOGD("AudioCmdHandler::ULCustSPHWBParamFromNV() in");
#ifdef MTK_WB_SPEECH_SUPPORT
    AUD_SPH_WB_PARAM_STRUCT *pCustomPara = (AUD_SPH_WB_PARAM_STRUCT *)(pParam + sizeof(int));
	AUD_SPH_AFTER_FOUR_MODE_PARAM_STRUCT *pFourCustomPara = (AUD_SPH_AFTER_FOUR_MODE_PARAM_STRUCT *)(pParam + sizeof(int));
    AUDIO_CUSTOM_WB_PARAM_STRUCT *pSPHWBPara = (AUDIO_CUSTOM_WB_PARAM_STRUCT *)malloc(sizeof(AUDIO_CUSTOM_WB_PARAM_STRUCT));

    if (pSPHWBPara == NULL)
    {
        return ACHFailed;
    }

    size = GetWBSpeechParamFromNVRam(pSPHWBPara);
    if (size != sizeof(AUDIO_CUSTOM_WB_PARAM_STRUCT))
    {
        ALOGD("ULCustSPHWBParamFromNV Up load from NVRAM fail, structure size=%d,read_size=%d", sizeof(AUDIO_CUSTOM_WB_PARAM_STRUCT), size);
        free(pSPHWBPara);
        pSPHWBPara = NULL;
        return ACHFailed;
    }

    if (block == 0)
    {
        *len = 2 * (sizeof(pCustomPara->sph_mode_wb_param) + sizeof(pCustomPara->sph_wb_in_fir) + sizeof(int));
        *((int *)pParam) = sizeof(pCustomPara->sph_mode_wb_param) + sizeof(pCustomPara->sph_wb_in_fir);

        for (int i = 0; i < FIR_NUM_NB ; i++)
        {
            SLOGV("Speech In FIR Coefs ori=%d", pSPHWBPara->sph_wb_in_fir[0][i]);
        }

        for (int i = 0; i < SPH_ENHANCE_PARAM_NUM ; i++)
        {
            SLOGV("Speech mode parameters ori=%d", pSPHWBPara->speech_mode_wb_para[0][i]);
        }

        memcpy((void *)pCustomPara->sph_mode_wb_param, (void *)pSPHWBPara->speech_mode_wb_para, sizeof(pCustomPara->sph_mode_wb_param));
        memcpy((void *)pCustomPara->sph_wb_in_fir, (void *)pSPHWBPara->sph_wb_in_fir, sizeof(pCustomPara->sph_wb_in_fir));

        dataEncode((char *)pParam, (*len) / 2);
    }
    else if (block == 1)
    {
        *len = 2 * (sizeof(pCustomPara->sph_wb_out_fir) + sizeof(int));
        *((int *)pParam) = sizeof(pCustomPara->sph_wb_out_fir);

        for (int i = 0; i < FIR_NUM_NB ; i++)
        {
            SLOGV("Speech Out FIR Coefs ori=%d", pSPHWBPara->sph_wb_out_fir[0][i]);
        }

        memcpy((void *)pCustomPara, (void *)pSPHWBPara->sph_wb_out_fir, sizeof(pCustomPara->sph_wb_out_fir));

        dataEncode((char *)pParam, (*len) / 2);
    }
	else if(block == 2) 
	{
        *len = 2 * (sizeof(AUD_SPH_AFTER_FOUR_MODE_PARAM_STRUCT) + sizeof(int));
        *((int *)pParam) = sizeof(AUD_SPH_AFTER_FOUR_MODE_PARAM_STRUCT);

		for (int i = 0; i < SPH_MODE_NUM*SPH_ENHANCE_PARAM_NUM ;  i++)
		{
			ALOGD("AUD_SPH_AFTER_FOUR_MODE_PARAM_STRUCT[%d]=%d", i, *((unsigned short *)pFourCustomPara + i));
		}

		for(int i = 0; i < SPH_MODE_NUM; i++)
		{
		   for(int j = 0; j < SPH_ENHANCE_PARAM_NUM; j++)
			   {
				   pFourCustomPara->wb_ul_dl_sph_mode_param[i][j] =  pSPHWBPara->speech_mode_wb_para[4+i][j];
			   }
		}
		
        dataEncode((char *)pParam, (*len) / 2);
	}

    free(pSPHWBPara);
    pSPHWBPara = NULL;
#else
	return ACHFailed;
#endif

    return ACHSucceeded;
}

ACHStatus AudioCmdHandler::DLCustHFPParamToNV(char *pParam)
{
    int write_size = 0;
    int size = 0;

    ALOGD("AudioCmdHandler::DLCustHFPParamToNV() in");
    AUDIO_HFP_PARAM_STRUCT *pHFPPara = (AUDIO_HFP_PARAM_STRUCT *)malloc(sizeof(AUDIO_HFP_PARAM_STRUCT));
    if (pHFPPara == NULL)
    {
        return ACHFailed;
    }
    else if (pParam == NULL)
    {
        free(pHFPPara);
        pHFPPara = NULL;
        return ACHFailed;
    }

    size = GetAudioHFPParamFromNV(pHFPPara);
    ALOGD("DLCustHFPParamToNV- GetAudioHFPParamFromNV read size=%d", size);
    if (size != sizeof(AUDIO_HFP_PARAM_STRUCT))
    {
        ALOGD("DLCustHFPParamToNV Up load from NVRAM fail, structure size=%d,read_size=%d", sizeof(AUDIO_HFP_PARAM_STRUCT), size);
        free(pHFPPara);
        pHFPPara = NULL;
        return ACHFailed;
    }

	 size = sizeof(AUDIO_HFP_PARAM_STRUCT);
	 dataDecode((char *)pParam, size + sizeof(int));
	 if (*((int *)pParam) != size)
	 {
		 ALOGE("DLCustHFPParamToNV miss data !!, received size = %d", *((int *)pParam));
		 free(pHFPPara);
		 pHFPPara = NULL;
		 return ACHFailed;
	 }
	 memcpy((void *)pHFPPara, pParam + sizeof(int), sizeof(AUDIO_HFP_PARAM_STRUCT));

    unsigned short *p = (unsigned short *)pHFPPara;
    for (int i = 0; i < 48; i++)
    {
        ALOGD("LPBK_STRUCT[%d] =%hu", i, p[i]);
    }

    write_size = SetAudioHFPParamToNV(pHFPPara);
    if (write_size != sizeof(AUDIO_HFP_PARAM_STRUCT))
    {
        ALOGD("DLCustHFPParamToNV Down load to NVRAM fail, structure size=%d,writed_size=%d", sizeof(AUDIO_HFP_PARAM_STRUCT), write_size);
        free(pHFPPara);
        pHFPPara = NULL;
        return ACHFailed;
    }

	AudioSystem::setParameters(0, String8("UpdateHFPParameters=1"));

    free(pHFPPara);
    pHFPPara = NULL;

    return ACHSucceeded;
}

ACHStatus AudioCmdHandler::ULCustHFPParamFromNV(char *pParam, int *len)
{
    int size = 0;
    int dataLen = 0;

    ALOGD("AudioCmdHandler::ULCustHFPParamFromNV() in");
    if (NULL == pParam)
        return ACHFailed;

    AUDIO_HFP_PARAM_STRUCT *pHFPPara = (AUDIO_HFP_PARAM_STRUCT *)malloc(sizeof(AUDIO_HFP_PARAM_STRUCT));
    if (pHFPPara == NULL)
        return ACHFailed;

    size = GetAudioHFPParamFromNV(pHFPPara);
    if (size != sizeof(AUDIO_HFP_PARAM_STRUCT))
    {
        ALOGD("ULCustHFPParamFromNV Up load from NVRAM fail, structure size=%d,read_size=%d", sizeof(AUDIO_HFP_PARAM_STRUCT), size);
        free(pHFPPara);
        return ACHFailed;
    }
    unsigned short *p = (unsigned short *)pHFPPara;
    for (int i = 0; i < 48; i++)
    {
        ALOGD("LPBK_STRUCT[%d] =%hu", i, p[i]);
    }

	dataLen = sizeof(AUDIO_HFP_PARAM_STRUCT);
	memcpy(pParam + sizeof(int), (void *)pHFPPara, dataLen);
	

    ALOGD("ULCustHFPParamFromNV the data sent to PC is %d", dataLen);
    *((int *)pParam) = dataLen;
    *len = 2 * (dataLen + sizeof(int));

    dataEncode((char *)pParam, dataLen + sizeof(int));

    free(pHFPPara);
    return ACHSucceeded;
}

#if 0
ACHStatus AudioCmdHandler::DLCustACFParamToNV(char *pParam)
{
    int write_size = 0;
    int size = 0;
    int dataLen = 0;

    ALOGD("AudioCmdHandler::DLCustACFParamToNV() in");

    AUDIO_ACF_CUSTOM_PARAM_STRUCT *pCustomPara = NULL;
    AUDIO_ACF_CUSTOM_PARAM_STRUCT *pACFPara = (AUDIO_ACF_CUSTOM_PARAM_STRUCT *)malloc(sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT));
    if (pACFPara == NULL)
    {
        return ACHFailed;
    }

    ALOGD("DLCustACFParamToNV ,acf param size=%d", sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT));
    size = getAudioCompFltCustParamFromStorage(AUDIO_COMP_FLT_AUDIO, pACFPara);
    if (size != sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT))
    {
        ALOGD("DLCustACFParamToNV Up load from NVRAM fail, structure size=%d,read_size=%d", sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT), size);
        free(pACFPara);
        pACFPara = NULL;
        return ACHFailed;
    }

    size = sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT) + sizeof(int);
    dataDecode((char *)pParam, size);

    dataLen = *((int *)pParam);
    pCustomPara = (AUDIO_ACF_CUSTOM_PARAM_STRUCT *)(pParam + sizeof(int));

    if (dataLen != sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT))
    {
        ALOGE("DLCustACFParamToNV data miss !!");
        free(pACFPara);
        pACFPara = NULL;
        return ACHFailed;
    }
#if defined(MTK_AUDIO_BLOUD_CUSTOMPARAMETER_V5)
    for (int i = 0; i < 5; i++)
    {
        SLOGV("Received  - loudness hsf coeffs bes_loudness_hsf_coeff[0][0][%d] = %d", i, pCustomPara->bes_loudness_hsf_coeff[0][0][i]);
    }

    for (int i = 0; i < 3; i++)
    {
        SLOGV("Received - loudness bpf coeffs bes_loudness_bpf_coeff[0][0][%d]=%d", i, pCustomPara->bes_loudness_bpf_coeff[0][0][i]);
    }

    for (int i = 0; i < 3; i++)
    {
        SLOGV("Received - loudness lpf coeffs bes_loudness_lpf_coeff[0][%d]=%d", i, pCustomPara->bes_loudness_lpf_coeff[0][i]);
    }

    ALOGD("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    ALOGD("Received - ACF Param bes_loudness_WS_Gain_Max = %d", pCustomPara->bes_loudness_WS_Gain_Max);
    ALOGD("Received - ACF Param bes_loudness_WS_Gain_Min = %d", pCustomPara->bes_loudness_WS_Gain_Min);
    ALOGD("Received - ACF Param bes_loudness_Filter_First = %d", pCustomPara->bes_loudness_Filter_First);
    ALOGD("Received - ACF Param bes_loudness_Sep_LR_Filter = %d", pCustomPara->bes_loudness_Sep_LR_Filter);

    ALOGD("Received - ACF Param bes_loudness_Num_Bands = %d", pCustomPara->bes_loudness_Num_Bands);
    ALOGD("Received - ACF Param bes_loudness_Flt_Bank_Order = %d", pCustomPara->bes_loudness_Flt_Bank_Order);
    ALOGD("Received - ACF Param bes_loudness_DRC_Delay = %d", pCustomPara->bes_loudness_DRC_Delay);
    ALOGD("Received - ACF Param bes_loudness_Lim_Th = %d", pCustomPara->bes_loudness_Lim_Th);
    ALOGD("Received - ACF Param bes_loudness_Lim_Gn = %d", pCustomPara->bes_loudness_Lim_Gn);
    ALOGD("Received - ACF Param bes_loudness_Lim_Const = %d", pCustomPara->bes_loudness_Lim_Const);
    ALOGD("Received - ACF Param bes_loudness_Lim_Delay = %d", pCustomPara->bes_loudness_Lim_Delay);

#elif defined(MTK_AUDIO_BLOUD_CUSTOMPARAMETER_V4)
    for (int i = 0; i < 5; i++)
    {
        SLOGV("Received  - loudness hsf coeffs bes_loudness_hsf_coeff[0][0][%d] = %d", i, pCustomPara->bes_loudness_hsf_coeff[0][0][i]);
    }

    for (int i = 0; i < 3; i++)
    {
        SLOGV("Received - loudness bpf coeffs bes_loudness_bpf_coeff[0][0][%d]=%d", i, pCustomPara->bes_loudness_bpf_coeff[0][0][i]);
    }

    for (int i = 0; i < 3; i++)
    {
        SLOGV("Received - loudness lpf coeffs bes_loudness_lpf_coeff[0][%d]=%d", i, pCustomPara->bes_loudness_lpf_coeff[0][i]);
    }

    ALOGD("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    ALOGD("Received - ACF Param bes_loudness_WS_Gain_Max = %d", pCustomPara->bes_loudness_WS_Gain_Max);
    ALOGD("Received - ACF Param bes_loudness_WS_Gain_Min = %d", pCustomPara->bes_loudness_WS_Gain_Min);
    ALOGD("Received - ACF Param bes_loudness_Filter_First = %d", pCustomPara->bes_loudness_Filter_First);
    ALOGD("Received - ACF Param bes_loudness_Att_Time = %d", pCustomPara->bes_loudness_Att_Time);
    ALOGD("Received - ACF Param bes_loudness_Rel_Time = %d", pCustomPara->bes_loudness_Rel_Time);

    for (int i = 0; i < 5; i++)
    {
        SLOGV("Received - gain map in bes_loudness_Gain_Map_In[%d]=%d", i, pCustomPara->bes_loudness_Gain_Map_In[i]);
    }

    for (int i = 0; i < 5; i++)
    {
        SLOGV("Received - gain map out bes_loudness_Gain_Map_Out[%d]=%d", i, pCustomPara->bes_loudness_Gain_Map_Out[i]);
    }
#else
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 4 ; j++)
        {
            SLOGV("Received  - loudness hsf coeffs bes_loudness_hsf_coeff[%d][%d] = %d", i, j, pCustomPara->bes_loudness_hsf_coeff[i][j]);
        }
    }

    for (int i = 0; i < 3; i++)
    {
        SLOGV("Received - loudness bpf coeffs bes_loudness_bpf_coeff[0][0][%d]=%d", i, pCustomPara->bes_loudness_bpf_coeff[0][0][i]);
    }

    ALOGD("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    ALOGD("Received - ACF Param bes_loudness_DRC_Forget_Table[0][0] = %d", pCustomPara->bes_loudness_DRC_Forget_Table[0][0]);
    ALOGD("Received - ACF Param bes_loudness_WS_Gain_Max = %d", pCustomPara->bes_loudness_WS_Gain_Max);
    ALOGD("Received - ACF Param bes_loudness_WS_Gain_Min = %d", pCustomPara->bes_loudness_WS_Gain_Min);
    ALOGD("Received - ACF Param bes_loudness_Filter_First = %d", pCustomPara->bes_loudness_Filter_First);
    ALOGD("Received - ACF Param bes_loudness_Filter_First = %d", pCustomPara->bes_loudness_Filter_First);
    for (int i = 0; i < 5; i++)
    {
        SLOGV("Received - gain map in bes_loudness_Gain_Map_In[%d]=%d", i, pCustomPara->bes_loudness_Gain_Map_In[i]);
    }

    for (int i = 0; i < 5; i++)
    {
        SLOGV("Received - gain map out bes_loudness_Gain_Map_Out[%d]=%d", i, pCustomPara->bes_loudness_Gain_Map_Out[i]);
    }
#endif

    memcpy((void *)pACFPara, (void *)pCustomPara, sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT));

    write_size = setAudioCompFltCustParamToStorage(AUDIO_COMP_FLT_AUDIO, pACFPara);
    if (write_size != sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT))
    {
        ALOGD("DLCustACFParamToNV Down load to NVRAM fail, structure size=%d,writed_size=%d", sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT), write_size);
        free(pACFPara);
        pACFPara = NULL;
        return ACHFailed;
    }

    AudioSystem::setParameters(0, String8("UpdateACFHCFParameters=0"));

    free(pACFPara);
    pACFPara = NULL;
    return ACHSucceeded;
}

ACHStatus AudioCmdHandler::ULCustACFParamFromNV(char *pParam, int *len)
{
    int size = 0;

    ALOGD("AudioCmdHandler::ULCustACFParamFromNV() in");

    AUDIO_ACF_CUSTOM_PARAM_STRUCT *pCustomPara = NULL;
    AUDIO_ACF_CUSTOM_PARAM_STRUCT *pACFPara = (AUDIO_ACF_CUSTOM_PARAM_STRUCT *)malloc(sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT));
    if (pACFPara == NULL)
    {
        return ACHFailed;
    }

    ALOGD("ULCustACFParamFromNV ,acf param size=%d", sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT));
    size = getAudioCompFltCustParamFromStorage(AUDIO_COMP_FLT_AUDIO, pACFPara);
    if (size != sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT))
    {
        ALOGD("ULCustACFParamFromNV Up load from NVRAM fail, structure size=%d,read_size=%d", sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT), size);
        free(pACFPara);
        pACFPara = NULL;
        return ACHFailed;
    }
#if defined(MTK_AUDIO_BLOUD_CUSTOMPARAMETER_V5)
        for (int i = 0; i < 5; i++)
        {
            SLOGV("Ori  - loudness hsf coeffs bes_loudness_hsf_coeff[0][0][%d] = %d", i, pACFPara->bes_loudness_hsf_coeff[0][0][i]);
        }
    
        for (int i = 0; i < 3; i++)
        {
            SLOGV("Ori - loudness bpf coeffs bes_loudness_bpf_coeff[0][0][%d]=%d", i, pACFPara->bes_loudness_bpf_coeff[0][0][i]);
        }
    
        for (int i = 0; i < 3; i++)
        {
            SLOGV("Ori - loudness lpf coeffs bes_loudness_lpf_coeff[0][%d]=%d", i, pACFPara->bes_loudness_lpf_coeff[0][i]);
        }
    
        ALOGD("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        ALOGD("Ori - ACF Param bes_loudness_WS_Gain_Max = %d", pACFPara->bes_loudness_WS_Gain_Max);
        ALOGD("Ori - ACF Param bes_loudness_WS_Gain_Min = %d", pACFPara->bes_loudness_WS_Gain_Min);
        ALOGD("Ori - ACF Param bes_loudness_Filter_First = %d", pACFPara->bes_loudness_Filter_First);
        ALOGD("Ori - ACF Param bes_loudness_Sep_LR_Filter = %d", pACFPara->bes_loudness_Sep_LR_Filter);
    
        ALOGD("Ori - ACF Param bes_loudness_Num_Bands = %d", pACFPara->bes_loudness_Num_Bands);
        ALOGD("Ori - ACF Param bes_loudness_Flt_Bank_Order = %d", pACFPara->bes_loudness_Flt_Bank_Order);
        ALOGD("Ori - ACF Param bes_loudness_DRC_Delay = %d", pACFPara->bes_loudness_DRC_Delay);
        ALOGD("Ori - ACF Param bes_loudness_Lim_Th = %d", pACFPara->bes_loudness_Lim_Th);
        ALOGD("Ori - ACF Param bes_loudness_Lim_Gn = %d", pACFPara->bes_loudness_Lim_Gn);
        ALOGD("Ori - ACF Param bes_loudness_Lim_Const = %d", pACFPara->bes_loudness_Lim_Const);
        ALOGD("Ori - ACF Param bes_loudness_Lim_Delay = %d", pACFPara->bes_loudness_Lim_Delay);
    
    
#elif defined(MTK_AUDIO_BLOUD_CUSTOMPARAMETER_V4)
    for (int i = 0; i < 5; i++)
    {
        SLOGV("Ori  - loudness hsf coeffs bes_loudness_hsf_coeff[0][0][%d] = %d", i, pACFPara->bes_loudness_hsf_coeff[0][0][i]);
    }

    for (int i = 0; i < 3; i++)
    {
        SLOGV("Ori - loudness bpf coeffs bes_loudness_bpf_coeff[0][0][%d]=%d", i, pACFPara->bes_loudness_bpf_coeff[0][0][i]);
    }

    for (int i = 0; i < 3; i++)
    {
        SLOGV("Ori - loudness lpf coeffs bes_loudness_lpf_coeff[0][%d]=%d", i, pACFPara->bes_loudness_lpf_coeff[0][i]);
    }

    ALOGD("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    ALOGD("Ori - ACF Param bes_loudness_WS_Gain_Max = %d", pACFPara->bes_loudness_WS_Gain_Max);
    ALOGD("Ori - ACF Param bes_loudness_WS_Gain_Min = %d", pACFPara->bes_loudness_WS_Gain_Min);
    ALOGD("Ori - ACF Param bes_loudness_Filter_First = %d", pACFPara->bes_loudness_Filter_First);
    ALOGD("Ori - ACF Param bes_loudness_Att_Time = %d", pACFPara->bes_loudness_Att_Time);
    ALOGD("Ori - ACF Param bes_loudness_Rel_Time = %d", pACFPara->bes_loudness_Rel_Time);

    for (int i = 0; i < 5; i++)
    {
        SLOGV("Ori - gain map in bes_loudness_Gain_Map_In[%d]=%d", i, pACFPara->bes_loudness_Gain_Map_In[i]);
    }

    for (int i = 0; i < 5; i++)
    {
        SLOGV("Ori - gain map out bes_loudness_Gain_Map_Out[%d]=%d", i, pACFPara->bes_loudness_Gain_Map_Out[i]);
    }
#else
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 4 ; j++)
        {
            SLOGV("Ori  - loudness hsf coeffs bes_loudness_hsf_coeff[%d][%d] = %d", i, j, pACFPara->bes_loudness_hsf_coeff[i][j]);
        }
    }

    for (int i = 0; i < 3; i++)
    {
        SLOGV("Ori - loudness bpf coeffs bes_loudness_bpf_coeff[0][0][%d]=%d", i, pACFPara->bes_loudness_bpf_coeff[0][0][i]);
    }

    ALOGD("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    ALOGD("Ori - ACF Param bes_loudness_DRC_Forget_Table[0][0] = %d", pACFPara->bes_loudness_DRC_Forget_Table[0][0]);
    ALOGD("Ori - ACF Param bes_loudness_WS_Gain_Max = %d", pACFPara->bes_loudness_WS_Gain_Max);
    ALOGD("Ori - ACF Param bes_loudness_WS_Gain_Min = %d", pACFPara->bes_loudness_WS_Gain_Min);
    ALOGD("Ori - ACF Param bes_loudness_Filter_First = %d", pACFPara->bes_loudness_Filter_First);
    ALOGD("Ori - ACF Param bes_loudness_Filter_First = %d", pACFPara->bes_loudness_Filter_First);
    for (int i = 0; i < 5; i++)
    {
        SLOGV("Ori - gain map in bes_loudness_Gain_Map_In[%d]=%d", i, pACFPara->bes_loudness_Gain_Map_In[i]);
    }

    for (int i = 0; i < 5; i++)
    {
        SLOGV("Ori - gain map out bes_loudness_Gain_Map_Out[%d]=%d", i, pACFPara->bes_loudness_Gain_Map_Out[i]);
    }
#endif

    *((int *)pParam) = sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT);
    pCustomPara = (AUDIO_ACF_CUSTOM_PARAM_STRUCT *)(pParam + sizeof(int));

    memcpy((void *)pCustomPara, (void *)pACFPara, sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT));

    dataEncode((char *)pParam, sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT) + sizeof(int));
    *len = 2 * (sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT) + sizeof(int));

    free(pACFPara);
    pACFPara = NULL;
    return ACHSucceeded;
}
#else
const char* strFLTID[]={"ACF","HCF","ACF-SUB","Music-DRC","RingTone-DRC"};
AudioCompFltType_t AudioCompFltType_tMapID[]={AUDIO_COMP_FLT_AUDIO,AUDIO_COMP_FLT_HEADPHONE,AUDIO_COMP_FLT_AUDIO_SUB,AUDIO_COMP_FLT_DRC_FOR_MUSIC,AUDIO_COMP_FLT_DRC_FOR_RINGTONE};
const char* strUpdateFLTID[]={"UpdateACFHCFParameters=0","UpdateACFHCFParameters=1","UpdateACFHCFParameters=2","UpdateACFHCFParameters=3","UpdateACFHCFParameters=4"};


ACHStatus AudioCmdHandler::DLCustAudioFLTParamToNV(char *pParam,AudioFltTunningType eFLTID)
{
    int write_size = 0;
    int size = 0;
    int dataLen = 0;
    int dFLTID = (int)eFLTID;

    if (eFLTID>=AUDIO_FLT_MAX)
    {
        ALOGD("AudioCmdHandler DLCustAudioFLTParamToNV() FilterID too big ..[%d]",dFLTID);
        return ACHFailed;
    }

    ALOGD("AudioCmdHandler::DLCustAudioFLTParamToNV() in FilterID = %s",strFLTID[dFLTID]);

    AUDIO_ACF_CUSTOM_PARAM_STRUCT *pCustomPara = NULL;
    AUDIO_ACF_CUSTOM_PARAM_STRUCT *pACFPara = (AUDIO_ACF_CUSTOM_PARAM_STRUCT *)malloc(sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT));
    if (pACFPara == NULL)
    {
        return ACHFailed;
    }

    ALOGD("DLCustAudioFLTParamToNV ,acf param size=%d", sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT));
    size = getAudioCompFltCustParamFromStorage(AudioCompFltType_tMapID[(int)dFLTID], pACFPara);
    if (size != sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT))
    {
        ALOGD("DLCustAudioFLTParamToNV Up load from NVRAM fail, structure size=%d,read_size=%d", sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT), size);
        free(pACFPara);
        pACFPara = NULL;
        return ACHFailed;
    }

    size = sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT) + sizeof(int);
    dataDecode((char *)pParam, size);

    dataLen = *((int *)pParam);
    pCustomPara = (AUDIO_ACF_CUSTOM_PARAM_STRUCT *)(pParam + sizeof(int));

    if (dataLen != sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT))
    {
        ALOGE("DLCustAudioFLTParamToNV data miss !!");
        free(pACFPara);
        pACFPara = NULL;
        return ACHFailed;
    }
#if defined(MTK_AUDIO_BLOUD_CUSTOMPARAMETER_V5)
    int dRev;
    dRev = MtkAudioLoud::getBesSoundVer();
    if (pCustomPara->SWIPRev!=dRev)
    {
       SLOGV("Don't Modify SWIP Rev. [0x%x] To [0x%x] (SWIPRev Setting Fail)",dRev,pCustomPara->SWIPRev);
       pCustomPara->SWIPRev = dRev;
    }

    SLOGV("Received - bes_loudness_L_hpf_fc [%d]",pCustomPara->bes_loudness_f_param.V5F.bes_loudness_L_hpf_fc);
    SLOGV("Received - bes_loudness_L_hpf_order [%d]",pCustomPara->bes_loudness_f_param.V5F.bes_loudness_L_hpf_order);
    SLOGV("Received - bes_loudness_L_lpf_fc [%d]",pCustomPara->bes_loudness_f_param.V5F.bes_loudness_L_lpf_fc);
    SLOGV("Received - bes_loudness_L_lpf_order [%d]",pCustomPara->bes_loudness_f_param.V5F.bes_loudness_L_lpf_order);
    for (int i = 0; i < 8; i++)
    {
        SLOGV("Received  - loudness bpf coeffs bes_loudness_L_bpf_fc[%d] = %d", i, pCustomPara->bes_loudness_f_param.V5F.bes_loudness_L_bpf_fc[i]);
    }

    for (int i = 0; i < 8; i++)
    {
        SLOGV("Received - loudness bpf coeffs bes_loudness_L_bpf_bw[%d]=%d", i, pCustomPara->bes_loudness_f_param.V5F.bes_loudness_L_bpf_bw[i]);
    }

    for (int i = 0; i < 8; i++)
    {
        SLOGV("Received - loudness bps coeffs bes_loudness_L_bpf_gain[%d]=%d", i, pCustomPara->bes_loudness_f_param.V5F.bes_loudness_L_bpf_gain[i]);
    }

    SLOGV("Received - bes_loudness_R_hpf_fc [%d]",pCustomPara->bes_loudness_f_param.V5F.bes_loudness_R_hpf_fc);
    SLOGV("Received - bes_loudness_R_hpf_order [%d]",pCustomPara->bes_loudness_f_param.V5F.bes_loudness_R_hpf_order);
    SLOGV("Received - bes_loudness_R_lpf_fc [%d]",pCustomPara->bes_loudness_f_param.V5F.bes_loudness_R_lpf_fc);
    SLOGV("Received - bes_loudness_R_lpf_order [%d]",pCustomPara->bes_loudness_f_param.V5F.bes_loudness_R_lpf_order);
    for (int i = 0; i < 8; i++)
    {
        SLOGV("Received  - loudness bpf coeffs bes_loudness_R_bpf_fc[%d] = %d", i, pCustomPara->bes_loudness_f_param.V5F.bes_loudness_R_bpf_fc[i]);
    }

    for (int i = 0; i < 8; i++)
    {
        SLOGV("Received - loudness bpf coeffs bes_loudness_R_bpf_bw[%d]=%d", i, pCustomPara->bes_loudness_f_param.V5F.bes_loudness_R_bpf_bw[i]);
    }

    for (int i = 0; i < 8; i++)
    {
        SLOGV("Received - loudness bps coeffs bes_loudness_R_bpf_gain[%d]=%d", i, pCustomPara->bes_loudness_f_param.V5F.bes_loudness_R_bpf_gain[i]);
    }


    ALOGD("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    ALOGD("Received - AudioFLT Param bes_loudness_Sep_LR_Filter = %d", pCustomPara->bes_loudness_Sep_LR_Filter);
    ALOGD("Received - AudioFLT Param bes_loudness_WS_Gain_Max = %d", pCustomPara->bes_loudness_WS_Gain_Max);
    ALOGD("Received - AudioFLT Param bes_loudness_WS_Gain_Min = %d", pCustomPara->bes_loudness_WS_Gain_Min);

    ALOGD("Received - AudioFLT Param bes_loudness_Filter_First = %d", pCustomPara->bes_loudness_Filter_First);

    ALOGD("Received - AudioFLT Param bes_loudness_Num_Bands = %d", pCustomPara->bes_loudness_Num_Bands);
    ALOGD("Received - AudioFLT Param bes_loudness_Flt_Bank_Order = %d", pCustomPara->bes_loudness_Flt_Bank_Order);

    ALOGD("Received - AudioFLT Param DRC_Delay = %d", pCustomPara->DRC_Delay);
    ALOGD("Received - AudioFLT Param Lim_Th = %d", pCustomPara->Lim_Th);
    ALOGD("Received - AudioFLT Param Lim_Gn = %d", pCustomPara->Lim_Gn);
    ALOGD("Received - AudioFLT Param Lim_Const = %d", pCustomPara->Lim_Const);
    ALOGD("Received - AudioFLT Param Lim_Delay = %d", pCustomPara->Lim_Delay);  

#elif defined(MTK_AUDIO_BLOUD_CUSTOMPARAMETER_V4)
    for (int i = 0; i < 5; i++)
    {
        SLOGV("Received  - loudness hsf coeffs bes_loudness_hsf_coeff[0][0][%d] = %d", i, pCustomPara->bes_loudness_hsf_coeff[0][0][i]);
    }

    for (int i = 0; i < 3; i++)
    {
        SLOGV("Received - loudness bpf coeffs bes_loudness_bpf_coeff[0][0][%d]=%d", i, pCustomPara->bes_loudness_bpf_coeff[0][0][i]);
    }

    for (int i = 0; i < 3; i++)
    {
        SLOGV("Received - loudness lpf coeffs bes_loudness_lpf_coeff[0][%d]=%d", i, pCustomPara->bes_loudness_lpf_coeff[0][i]);
    }

    ALOGD("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    ALOGD("Received - AudioFLT Param bes_loudness_WS_Gain_Max = %d", pCustomPara->bes_loudness_WS_Gain_Max);
    ALOGD("Received - AudioFLT Param bes_loudness_WS_Gain_Min = %d", pCustomPara->bes_loudness_WS_Gain_Min);
    ALOGD("Received - AudioFLT Param bes_loudness_Filter_First = %d", pCustomPara->bes_loudness_Filter_First);
    ALOGD("Received - AudioFLT Param bes_loudness_Att_Time = %d", pCustomPara->bes_loudness_Att_Time);
    ALOGD("Received - AudioFLT Param bes_loudness_Rel_Time = %d", pCustomPara->bes_loudness_Rel_Time);

    for (int i = 0; i < 5; i++)
    {
        SLOGV("Received - gain map in bes_loudness_Gain_Map_In[%d]=%d", i, pCustomPara->bes_loudness_Gain_Map_In[i]);
    }

    for (int i = 0; i < 5; i++)
    {
        SLOGV("Received - gain map out bes_loudness_Gain_Map_Out[%d]=%d", i, pCustomPara->bes_loudness_Gain_Map_Out[i]);
    }
#else
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 4 ; j++)
        {
            SLOGV("Received  - loudness hsf coeffs bes_loudness_hsf_coeff[%d][%d] = %d", i, j, pCustomPara->bes_loudness_hsf_coeff[i][j]);
        }
    }

    for (int i = 0; i < 3; i++)
    {
        SLOGV("Received - loudness bpf coeffs bes_loudness_bpf_coeff[0][0][%d]=%d", i, pCustomPara->bes_loudness_bpf_coeff[0][0][i]);
    }

    ALOGD("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    ALOGD("Received - AudioFLT Param bes_loudness_DRC_Forget_Table[0][0] = %d", pCustomPara->bes_loudness_DRC_Forget_Table[0][0]);
    ALOGD("Received - AudioFLT Param bes_loudness_WS_Gain_Max = %d", pCustomPara->bes_loudness_WS_Gain_Max);
    ALOGD("Received - AudioFLT Param bes_loudness_WS_Gain_Min = %d", pCustomPara->bes_loudness_WS_Gain_Min);
    ALOGD("Received - AudioFLT Param bes_loudness_Filter_First = %d", pCustomPara->bes_loudness_Filter_First);
    ALOGD("Received - AudioFLT Param bes_loudness_Filter_First = %d", pCustomPara->bes_loudness_Filter_First);
    for (int i = 0; i < 5; i++)
    {
        SLOGV("Received - gain map in bes_loudness_Gain_Map_In[%d]=%d", i, pCustomPara->bes_loudness_Gain_Map_In[i]);
    }

    for (int i = 0; i < 5; i++)
    {
        SLOGV("Received - gain map out bes_loudness_Gain_Map_Out[%d]=%d", i, pCustomPara->bes_loudness_Gain_Map_Out[i]);
    }
#endif

    memcpy((void *)pACFPara, (void *)pCustomPara, sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT));

    write_size = setAudioCompFltCustParamToStorage(AudioCompFltType_tMapID[dFLTID], pACFPara);
    if (write_size != sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT))
    {
        ALOGD("DLCustAudioFLTParamToNV Down load to NVRAM fail, structure size=%d,writed_size=%d", sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT), write_size);
        free(pACFPara);
        pACFPara = NULL;
        return ACHFailed;
    }

    AudioSystem::setParameters(0, String8(strUpdateFLTID[dFLTID]/*"UpdateACFHCFParameters=0"*/));

    free(pACFPara);
    pACFPara = NULL;
    return ACHSucceeded;
}
ACHStatus AudioCmdHandler::ULCustAudioFLTParamFromNV(char *pParam, int *len,AudioFltTunningType eFLTID)
{
    int size = 0;
    int dFLTID = (int)eFLTID;

    if (eFLTID>=AUDIO_FLT_MAX)
    {
        ALOGD("AudioCmdHandler ULCustAudioFLTParamFromNV() FilterID too big ..[%d]",dFLTID);
        return ACHFailed;
    }

    ALOGD("AudioCmdHandler::ULCustAudioFLTParamFromNV() in FilterID = %s",strFLTID[dFLTID]);

    AUDIO_ACF_CUSTOM_PARAM_STRUCT *pCustomPara = NULL;
    AUDIO_ACF_CUSTOM_PARAM_STRUCT *pACFPara = (AUDIO_ACF_CUSTOM_PARAM_STRUCT *)malloc(sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT));
    if (pACFPara == NULL)
    {
        return ACHFailed;
    }

    ALOGD("ULCustAudioFLTParamFromNV ,acf param size=%d", sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT));
    size = getAudioCompFltCustParamFromStorage(AudioCompFltType_tMapID[dFLTID], pACFPara);
    if (size != sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT))
    {
        ALOGD("ULCustAudioFLTParamFromNV Up load from NVRAM fail, structure size=%d,read_size=%d", sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT), size);
        free(pACFPara);
        pACFPara = NULL;
        return ACHFailed;
    }
#if defined(MTK_AUDIO_BLOUD_CUSTOMPARAMETER_V5)
        pACFPara->SWIPRev = MtkAudioLoud::getBesSoundVer();
        SLOGV("Ori - SWIPRev [0x%x]",pACFPara->SWIPRev);
        SLOGV("Ori - bes_loudness_L_hpf_fc [%d]",pACFPara->bes_loudness_f_param.V5F.bes_loudness_L_hpf_fc);
        SLOGV("Ori - bes_loudness_L_hpf_order [%d]",pACFPara->bes_loudness_f_param.V5F.bes_loudness_L_hpf_order);
        SLOGV("Ori - bes_loudness_L_lpf_fc [%d]",pACFPara->bes_loudness_f_param.V5F.bes_loudness_L_lpf_fc);
        SLOGV("Ori - bes_loudness_L_lpf_order [%d]",pACFPara->bes_loudness_f_param.V5F.bes_loudness_L_lpf_order);
        for (int i = 0; i < 8; i++)
        {
            SLOGV("Ori  - loudness bpf coeffs bes_loudness_L_bpf_fc[%d] = %d", i, pACFPara->bes_loudness_f_param.V5F.bes_loudness_L_bpf_fc[i]);
        }
    
        for (int i = 0; i < 8; i++)
        {
            SLOGV("Ori - loudness bpf coeffs bes_loudness_L_bpf_bw[%d]=%d", i, pACFPara->bes_loudness_f_param.V5F.bes_loudness_L_bpf_bw[i]);
        }
    
        for (int i = 0; i < 8; i++)
        {
            SLOGV("Ori - loudness bps coeffs bes_loudness_L_bpf_gain[%d]=%d", i, pACFPara->bes_loudness_f_param.V5F.bes_loudness_L_bpf_gain[i]);
        }
        
        SLOGV("Ori - bes_loudness_R_hpf_fc [%d]",pACFPara->bes_loudness_f_param.V5F.bes_loudness_R_hpf_fc);
        SLOGV("Ori - bes_loudness_R_hpf_order [%d]",pACFPara->bes_loudness_f_param.V5F.bes_loudness_R_hpf_order);
        SLOGV("Ori - bes_loudness_R_lpf_fc [%d]",pACFPara->bes_loudness_f_param.V5F.bes_loudness_R_lpf_fc);
        SLOGV("Ori - bes_loudness_R_lpf_order [%d]",pACFPara->bes_loudness_f_param.V5F.bes_loudness_R_lpf_order);
        for (int i = 0; i < 8; i++)
        {
            SLOGV("Ori  - loudness bpf coeffs bes_loudness_R_bpf_fc[%d] = %d", i, pACFPara->bes_loudness_f_param.V5F.bes_loudness_R_bpf_fc[i]);
        }
    
        for (int i = 0; i < 8; i++)
        {
            SLOGV("Ori - loudness bpf coeffs bes_loudness_R_bpf_bw[%d]=%d", i, pACFPara->bes_loudness_f_param.V5F.bes_loudness_R_bpf_bw[i]);
        }
    
        for (int i = 0; i < 8; i++)
        {
            SLOGV("Ori - loudness bps coeffs bes_loudness_R_bpf_gain[%d]=%d", i, pACFPara->bes_loudness_f_param.V5F.bes_loudness_R_bpf_gain[i]);
        }

    
        ALOGD("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        ALOGD("Ori - AudioFLT Param bes_loudness_Sep_LR_Filter = %d", pACFPara->bes_loudness_Sep_LR_Filter);
        ALOGD("Ori - AudioFLT Param bes_loudness_WS_Gain_Max = %d", pACFPara->bes_loudness_WS_Gain_Max);
        ALOGD("Ori - AudioFLT Param bes_loudness_WS_Gain_Min = %d", pACFPara->bes_loudness_WS_Gain_Min);
        
        ALOGD("Ori - AudioFLT Param bes_loudness_Filter_First = %d", pACFPara->bes_loudness_Filter_First);
    
        ALOGD("Ori - AudioFLT Param bes_loudness_Num_Bands = %d", pACFPara->bes_loudness_Num_Bands);
        ALOGD("Ori - AudioFLT Param bes_loudness_Flt_Bank_Order = %d", pACFPara->bes_loudness_Flt_Bank_Order);

        ALOGD("Ori - AudioFLT Param DRC_Delay = %d", pACFPara->DRC_Delay);
        ALOGD("Ori - AudioFLT Param Lim_Th = %d", pACFPara->Lim_Th);
        ALOGD("Ori - AudioFLT Param Lim_Gn = %d", pACFPara->Lim_Gn);
        ALOGD("Ori - AudioFLT Param Lim_Const = %d", pACFPara->Lim_Const);
        ALOGD("Ori - AudioFLT Param Lim_Delay = %d", pACFPara->Lim_Delay);
    
    
#elif defined(MTK_AUDIO_BLOUD_CUSTOMPARAMETER_V4)
    for (int i = 0; i < 5; i++)
    {
        SLOGV("Ori  - loudness hsf coeffs bes_loudness_hsf_coeff[0][0][%d] = %d", i, pACFPara->bes_loudness_hsf_coeff[0][0][i]);
    }

    for (int i = 0; i < 3; i++)
    {
        SLOGV("Ori - loudness bpf coeffs bes_loudness_bpf_coeff[0][0][%d]=%d", i, pACFPara->bes_loudness_bpf_coeff[0][0][i]);
    }

    for (int i = 0; i < 3; i++)
    {
        SLOGV("Ori - loudness lpf coeffs bes_loudness_lpf_coeff[0][%d]=%d", i, pACFPara->bes_loudness_lpf_coeff[0][i]);
    }

    ALOGD("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    ALOGD("Ori - AudioFLT Param bes_loudness_WS_Gain_Max = %d", pACFPara->bes_loudness_WS_Gain_Max);
    ALOGD("Ori - AudioFLT Param bes_loudness_WS_Gain_Min = %d", pACFPara->bes_loudness_WS_Gain_Min);
    ALOGD("Ori - AudioFLT Param bes_loudness_Filter_First = %d", pACFPara->bes_loudness_Filter_First);
    ALOGD("Ori - AudioFLT Param bes_loudness_Att_Time = %d", pACFPara->bes_loudness_Att_Time);
    ALOGD("Ori - AudioFLT Param bes_loudness_Rel_Time = %d", pACFPara->bes_loudness_Rel_Time);

    for (int i = 0; i < 5; i++)
    {
        SLOGV("Ori - gain map in bes_loudness_Gain_Map_In[%d]=%d", i, pACFPara->bes_loudness_Gain_Map_In[i]);
    }

    for (int i = 0; i < 5; i++)
    {
        SLOGV("Ori - gain map out bes_loudness_Gain_Map_Out[%d]=%d", i, pACFPara->bes_loudness_Gain_Map_Out[i]);
    }
#else
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 4 ; j++)
        {
            SLOGV("Ori  - loudness hsf coeffs bes_loudness_hsf_coeff[%d][%d] = %d", i, j, pACFPara->bes_loudness_hsf_coeff[i][j]);
        }
    }

    for (int i = 0; i < 3; i++)
    {
        SLOGV("Ori - loudness bpf coeffs bes_loudness_bpf_coeff[0][0][%d]=%d", i, pACFPara->bes_loudness_bpf_coeff[0][0][i]);
    }

    ALOGD("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    ALOGD("Ori - AudioFLT Param bes_loudness_DRC_Forget_Table[0][0] = %d", pACFPara->bes_loudness_DRC_Forget_Table[0][0]);
    ALOGD("Ori - AudioFLT Param bes_loudness_WS_Gain_Max = %d", pACFPara->bes_loudness_WS_Gain_Max);
    ALOGD("Ori - AudioFLT Param bes_loudness_WS_Gain_Min = %d", pACFPara->bes_loudness_WS_Gain_Min);
    ALOGD("Ori - AudioFLT Param bes_loudness_Filter_First = %d", pACFPara->bes_loudness_Filter_First);
    ALOGD("Ori - AudioFLT Param bes_loudness_Filter_First = %d", pACFPara->bes_loudness_Filter_First);
    for (int i = 0; i < 5; i++)
    {
        SLOGV("Ori - gain map in bes_loudness_Gain_Map_In[%d]=%d", i, pACFPara->bes_loudness_Gain_Map_In[i]);
    }

    for (int i = 0; i < 5; i++)
    {
        SLOGV("Ori - gain map out bes_loudness_Gain_Map_Out[%d]=%d", i, pACFPara->bes_loudness_Gain_Map_Out[i]);
    }
#endif

    *((int *)pParam) = sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT);
    pCustomPara = (AUDIO_ACF_CUSTOM_PARAM_STRUCT *)(pParam + sizeof(int));

    memcpy((void *)pCustomPara, (void *)pACFPara, sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT));

    dataEncode((char *)pParam, sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT) + sizeof(int));
    *len = 2 * (sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT) + sizeof(int));

    free(pACFPara);
    pACFPara = NULL;
    return ACHSucceeded;
}
#endif
ACHStatus AudioCmdHandler::findACFFO(unsigned short cmdType, char *pParam, int *len)
{
	ACHStatus ret = ACHFailed;
	status_t ret1 = BAD_VALUE;
	int initVal = -1;
	int* pfo_value = &initVal;

	if(cmdType == 0 || cmdType == 1)
	{
		ret1 = SetAudioCommand(AUDIO_ACF_FO, cmdType);
		ALOGW ("AtCmd_SetAudioCommand ret1 =%d ", ret1);
		if(ret1 == NO_ERROR || ret1 == -38) //-38 Workaround for Audioflinger
			ret = ACHSucceeded;
	}
	else if(cmdType == 2)
	{
		if(NULL == len)
			return ret;

		ret1 = GetAudioCommand(AUDIO_ACF_FO, pfo_value);
		if(ret1 != NO_ERROR)
			return ACHFailed;
		else
			ALOGD("findACFFO, Test");

		ALOGD("findACFFO, fo_value is %d", *pfo_value);
		memcpy(pParam+sizeof(int), (void *)pfo_value, 4);

		*((int *)pParam) = 4;
		*len = 2*(4 + sizeof(int));
		
		dataEncode((char *)pParam, 4+sizeof(int));
	}
	return ret;
}

#if 0
ACHStatus AudioCmdHandler::DLCustHCFParamToNV(char *pParam)
{
    int write_size = 0;
    int size = 0;
    int dataLen = 0;

    ALOGD("AudioCmdHandler::DLCustHCFParamToNV() in");

    AUDIO_ACF_CUSTOM_PARAM_STRUCT *pCustomPara = NULL;
    AUDIO_ACF_CUSTOM_PARAM_STRUCT *pHCFPara = (AUDIO_ACF_CUSTOM_PARAM_STRUCT *)malloc(sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT));
    if (pHCFPara == NULL)
    {
        return ACHFailed;
    }

    ALOGD("DLCustHCFParamToNV ,acf param size=%d", sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT));
    size = getAudioCompFltCustParamFromStorage(AUDIO_COMP_FLT_HEADPHONE, pHCFPara);
    if (size != sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT))
    {
        ALOGD("DLCustHCFParamToNV Up load from NVRAM fail, structure size=%d,read_size=%d", sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT), size);
        free(pHCFPara);
        pHCFPara = NULL;
        return ACHFailed;
    }

    size = sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT) + sizeof(int);
    dataDecode((char *)pParam, size);

    dataLen = *((int *)pParam);
    pCustomPara = (AUDIO_ACF_CUSTOM_PARAM_STRUCT *)(pParam + sizeof(int));

    if (dataLen != sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT))
    {
        ALOGE("DLCustHCFParamToNV data miss !!");
        free(pHCFPara);
        pHCFPara = NULL;
        return ACHFailed;
    }

#if defined(MTK_AUDIO_BLOUD_CUSTOMPARAMETER_V5)
    for (int i = 0; i < 5; i++)
    {
        SLOGV("Received  - loudness hsf coeffs bes_loudness_hsf_coeff[0][0][%d] = %d", i, pCustomPara->bes_loudness_hsf_coeff[0][0][i]);
    }

    for (int i = 0; i < 3; i++)
    {
        SLOGV("Received - loudness bpf coeffs bes_loudness_bpf_coeff[0][0][%d]=%d", i, pCustomPara->bes_loudness_bpf_coeff[0][0][i]);
    }

    for (int i = 0; i < 3; i++)
    {
        SLOGV("Received - loudness lpf coeffs bes_loudness_lpf_coeff[0][%d]=%d", i, pCustomPara->bes_loudness_lpf_coeff[0][i]);
    }

    ALOGD("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    ALOGD("Received - HCF Param bes_loudness_WS_Gain_Max = %d", pCustomPara->bes_loudness_WS_Gain_Max);
    ALOGD("Received - HCF Param bes_loudness_WS_Gain_Min = %d", pCustomPara->bes_loudness_WS_Gain_Min);
    ALOGD("Received - HCF Param bes_loudness_Filter_First = %d", pCustomPara->bes_loudness_Filter_First);
    ALOGD("Received - HCF Param bes_loudness_Sep_LR_Filter = %d", pCustomPara->bes_loudness_Sep_LR_Filter);

    ALOGD("Received - HCF Param bes_loudness_Num_Bands = %d", pCustomPara->bes_loudness_Num_Bands);
    ALOGD("Received - HCF Param bes_loudness_Flt_Bank_Order = %d", pCustomPara->bes_loudness_Flt_Bank_Order);
    ALOGD("Received - HCF Param bes_loudness_DRC_Delay = %d", pCustomPara->bes_loudness_DRC_Delay);
    ALOGD("Received - HCF Param bes_loudness_Lim_Th = %d", pCustomPara->bes_loudness_Lim_Th);
    ALOGD("Received - HCF Param bes_loudness_Lim_Gn = %d", pCustomPara->bes_loudness_Lim_Gn);
    ALOGD("Received - HCF Param bes_loudness_Lim_Const = %d", pCustomPara->bes_loudness_Lim_Const);
    ALOGD("Received - HCF Param bes_loudness_Lim_Delay = %d", pCustomPara->bes_loudness_Lim_Delay);

#elif defined(MTK_AUDIO_BLOUD_CUSTOMPARAMETER_V4)      
    for (int i = 0; i < 5; i++)
    {
        SLOGV("Received  - loudness hsf coeffs bes_loudness_hsf_coeff[0][0][%d] = %d", i, pCustomPara->bes_loudness_hsf_coeff[0][0][i]);
    }

    for (int i = 0; i < 3; i++)
    {
        SLOGV("Received - loudness bpf coeffs bes_loudness_bpf_coeff[0][0][%d]=%d", i, pCustomPara->bes_loudness_bpf_coeff[0][0][i]);
    }

    for (int i = 0; i < 3; i++)
    {
        SLOGV("Received - loudness lpf coeffs bes_loudness_lpf_coeff[0][%d]=%d", i, pCustomPara->bes_loudness_lpf_coeff[0][i]);
    }

    ALOGD("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    ALOGD("Received - HCF Param bes_loudness_WS_Gain_Max = %d", pCustomPara->bes_loudness_WS_Gain_Max);
    ALOGD("Received - HCF Param bes_loudness_WS_Gain_Min = %d", pCustomPara->bes_loudness_WS_Gain_Min);
    ALOGD("Received - HCF Param bes_loudness_Filter_First = %d", pCustomPara->bes_loudness_Filter_First);
    ALOGD("Received - HCF Param bes_loudness_Att_Time = %d", pCustomPara->bes_loudness_Att_Time);
    ALOGD("Received - HCF Param bes_loudness_Rel_Time = %d", pCustomPara->bes_loudness_Rel_Time);

    for (int i = 0; i < 5; i++)
    {
        SLOGV("Received - gain map in bes_loudness_Gain_Map_In[%d]=%d", i, pCustomPara->bes_loudness_Gain_Map_In[i]);
    }

    for (int i = 0; i < 5; i++)
    {
        SLOGV("Received - gain map out bes_loudness_Gain_Map_Out[%d]=%d", i, pCustomPara->bes_loudness_Gain_Map_Out[i]);
    }
#else
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 4 ; j++)
        {
            SLOGV("Received  - loudness hsf coeffs bes_loudness_hsf_coeff[%d][%d] = %d", i, j, pCustomPara->bes_loudness_hsf_coeff[i][j]);
        }
    }

    for (int i = 0; i < 3; i++)
    {
        SLOGV("Received - loudness bpf coeffs bes_loudness_bpf_coeff[0][0][%d]=%d", i, pCustomPara->bes_loudness_bpf_coeff[0][0][i]);
    }

    SLOGV("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    SLOGV("Received - HCF Param bes_loudness_DRC_Forget_Table[0][0] = %d", pCustomPara->bes_loudness_DRC_Forget_Table[0][0]);
    SLOGV("Received - HCF Param bes_loudness_WS_Gain_Max = %d", pCustomPara->bes_loudness_WS_Gain_Max);
    SLOGV("Received - HCF Param bes_loudness_WS_Gain_Min = %d", pCustomPara->bes_loudness_WS_Gain_Min);
    SLOGV("Received - HCF Param bes_loudness_Filter_First = %d", pCustomPara->bes_loudness_Filter_First);
    SLOGV("Received - HCF Param bes_loudness_Filter_First = %d", pCustomPara->bes_loudness_Filter_First);
    for (int i = 0; i < 5; i++)
    {
        SLOGV("Received - gain map in bes_loudness_Gain_Map_In[%d]=%d", i, pCustomPara->bes_loudness_Gain_Map_In[i]);
    }

    for (int i = 0; i < 5; i++)
    {
        SLOGV("Received - gain map out bes_loudness_Gain_Map_Out[%d]=%d", i, pCustomPara->bes_loudness_Gain_Map_Out[i]);
    }
#endif
    memcpy((void *)pHCFPara, (void *)pCustomPara, sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT));

    write_size = setAudioCompFltCustParamToStorage(AUDIO_COMP_FLT_HEADPHONE, pHCFPara);
    if (write_size != sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT))
    {
        ALOGD("DLCustHCFParamToNV Down load to NVRAM fail, structure size=%d,writed_size=%d", sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT), write_size);
        free(pHCFPara);
        pHCFPara = NULL;
        return ACHFailed;
    }

    AudioSystem::setParameters(0, String8("UpdateACFHCFParameters=1"));

    free(pHCFPara);
    pHCFPara = NULL;
    return ACHSucceeded;
}

ACHStatus AudioCmdHandler::ULCustHCFParamFromNV(char *pParam, int *len)
{
    int size = 0;

    ALOGD("AudioCmdHandler::ULCustHCFParamFromNV() in");

    AUDIO_ACF_CUSTOM_PARAM_STRUCT *pCustomPara = NULL;
    AUDIO_ACF_CUSTOM_PARAM_STRUCT *pHCFPara = (AUDIO_ACF_CUSTOM_PARAM_STRUCT *)malloc(sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT));
    if (pHCFPara == NULL)
    {
        return ACHFailed;
    }

    ALOGD("ULCustHCFParamFromNV ,acf param size=%d", sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT));
    size = getAudioCompFltCustParamFromStorage(AUDIO_COMP_FLT_HEADPHONE, pHCFPara);
    if (size != sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT))
    {
        ALOGD("ULCustHCFParamFromNV Up load from NVRAM fail, structure size=%d,read_size=%d", sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT), size);
        free(pHCFPara);
        pHCFPara = NULL;
        return ACHFailed;
    }
#if defined(MTK_AUDIO_BLOUD_CUSTOMPARAMETER_V5)
            for (int i = 0; i < 5; i++)
            {
                SLOGV("Ori  - loudness hsf coeffs bes_loudness_hsf_coeff[0][0][%d] = %d", i, pHCFPara->bes_loudness_hsf_coeff[0][0][i]);
            }
        
            for (int i = 0; i < 3; i++)
            {
                SLOGV("Ori - loudness bpf coeffs bes_loudness_bpf_coeff[0][0][%d]=%d", i, pHCFPara->bes_loudness_bpf_coeff[0][0][i]);
            }
        
            for (int i = 0; i < 3; i++)
            {
                SLOGV("Ori - loudness lpf coeffs bes_loudness_lpf_coeff[0][%d]=%d", i, pHCFPara->bes_loudness_lpf_coeff[0][i]);
            }
        
            ALOGD("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            ALOGD("Ori - HCF Param bes_loudness_WS_Gain_Max = %d", pHCFPara->bes_loudness_WS_Gain_Max);
            ALOGD("Ori - HCF Param bes_loudness_WS_Gain_Min = %d", pHCFPara->bes_loudness_WS_Gain_Min);
            ALOGD("Ori - HCF Param bes_loudness_Filter_First = %d", pHCFPara->bes_loudness_Filter_First);
            ALOGD("Ori - HCF Param bes_loudness_Sep_LR_Filter = %d", pHCFPara->bes_loudness_Sep_LR_Filter);
        
            ALOGD("Ori - HCF Param bes_loudness_Num_Bands = %d", pHCFPara->bes_loudness_Num_Bands);
            ALOGD("Ori - HCF Param bes_loudness_Flt_Bank_Order = %d", pHCFPara->bes_loudness_Flt_Bank_Order);
            ALOGD("Ori - HCF Param bes_loudness_DRC_Delay = %d", pHCFPara->bes_loudness_DRC_Delay);
            ALOGD("Ori - HCF Param bes_loudness_Lim_Th = %d", pHCFPara->bes_loudness_Lim_Th);
            ALOGD("Ori - HCF Param bes_loudness_Lim_Gn = %d", pHCFPara->bes_loudness_Lim_Gn);
            ALOGD("Ori - HCF Param bes_loudness_Lim_Const = %d", pHCFPara->bes_loudness_Lim_Const);
            ALOGD("Ori - HCF Param bes_loudness_Lim_Delay = %d", pHCFPara->bes_loudness_Lim_Delay);

#elif defined(MTK_AUDIO_BLOUD_CUSTOMPARAMETER_V4)  

    for (int i = 0; i < 5; i++)
    {
        SLOGV("Ori  - loudness hsf coeffs bes_loudness_hsf_coeff[0][0][%d] = %d", i, pHCFPara->bes_loudness_hsf_coeff[0][0][i]);
    }

    for (int i = 0; i < 3; i++)
    {
        SLOGV("Ori - loudness bpf coeffs bes_loudness_bpf_coeff[0][0][%d]=%d", i, pHCFPara->bes_loudness_bpf_coeff[0][0][i]);
    }

    for (int i = 0; i < 3; i++)
    {
        SLOGV("Ori - loudness lpf coeffs bes_loudness_lpf_coeff[0][%d]=%d", i, pHCFPara->bes_loudness_lpf_coeff[0][i]);
    }

    ALOGD("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    ALOGD("Ori - HCF Param bes_loudness_WS_Gain_Max = %d", pHCFPara->bes_loudness_WS_Gain_Max);
    ALOGD("Ori - HCF Param bes_loudness_WS_Gain_Min = %d", pHCFPara->bes_loudness_WS_Gain_Min);
    ALOGD("Ori - HCF Param bes_loudness_Filter_First = %d", pHCFPara->bes_loudness_Filter_First);
    ALOGD("Ori - HCF Param bes_loudness_Att_Time = %d", pHCFPara->bes_loudness_Att_Time);
    ALOGD("Ori - HCF Param bes_loudness_Rel_Time = %d", pHCFPara->bes_loudness_Rel_Time);

    for (int i = 0; i < 5; i++)
    {
        SLOGV("Ori - gain map in bes_loudness_Gain_Map_In[%d]=%d", i, pHCFPara->bes_loudness_Gain_Map_In[i]);
    }

    for (int i = 0; i < 5; i++)
    {
        SLOGV("Ori - gain map out bes_loudness_Gain_Map_Out[%d]=%d", i, pHCFPara->bes_loudness_Gain_Map_Out[i]);
    }
#else
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 4 ; j++)
        {
            SLOGV("Ori  - loudness hsf coeffs bes_loudness_hsf_coeff[%d][%d] = %d", i, j, pHCFPara->bes_loudness_hsf_coeff[i][j]);
        }
    }

    for (int i = 0; i < 3; i++)
    {
        SLOGV("Ori - loudness bpf coeffs bes_loudness_bpf_coeff[0][0][%d]=%d", i, pHCFPara->bes_loudness_bpf_coeff[0][0][i]);
    }

    SLOGV("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    SLOGV("Ori - HCF Param bes_loudness_DRC_Forget_Table[0][0] = %d", pHCFPara->bes_loudness_DRC_Forget_Table[0][0]);
    SLOGV("Ori - HCF Param bes_loudness_WS_Gain_Max = %d", pHCFPara->bes_loudness_WS_Gain_Max);
    SLOGV("Ori - HCF Param bes_loudness_WS_Gain_Min = %d", pHCFPara->bes_loudness_WS_Gain_Min);
    SLOGV("Ori - HCF Param bes_loudness_Filter_First = %d", pHCFPara->bes_loudness_Filter_First);
    SLOGV("Ori - HCF Param bes_loudness_Filter_First = %d", pHCFPara->bes_loudness_Filter_First);
    for (int i = 0; i < 5; i++)
    {
        SLOGV("Ori - gain map in bes_loudness_Gain_Map_In[%d]=%d", i, pHCFPara->bes_loudness_Gain_Map_In[i]);
    }

    for (int i = 0; i < 5; i++)
    {
        SLOGV("Ori - gain map out bes_loudness_Gain_Map_Out[%d]=%d", i, pHCFPara->bes_loudness_Gain_Map_Out[i]);
    }
#endif
    *((int *)pParam) = sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT);
    pCustomPara = (AUDIO_ACF_CUSTOM_PARAM_STRUCT *)(pParam + sizeof(int));

    memcpy((void *)pCustomPara, (void *)pHCFPara, sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT));

    dataEncode((char *)pParam, sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT) + sizeof(int));
    *len = 2 * (sizeof(AUDIO_ACF_CUSTOM_PARAM_STRUCT) + sizeof(int));

    free(pHCFPara);
    pHCFPara = NULL;
    return ACHSucceeded;
}
#endif

ACHStatus AudioCmdHandler::AudioTasteRunning(unsigned short cmdType, char *pParam)
{
    ALOGD("AudioCmdHandler::AudioTasteRunning() in");

    int size = 0;
    int dataLen = 0;
    status_t ret = NO_ERROR;
    AUD_TASTE_PARAM_STRUCT sAudioTAsteParam;;
    memset (&sAudioTAsteParam, 0, sizeof(AUD_TASTE_PARAM_STRUCT));

    if (cmdType)
    {
        size = sizeof(AUD_TASTE_PARAM_STRUCT) + sizeof(int);
        dataDecode((char *)pParam, size);

        dataLen = *((int *)pParam);
        size = 5 * sizeof(unsigned short) + strlen((char *)(pParam + 7 * sizeof(unsigned short))) + 1;
        ALOGD("AudioTasteRunning() received data size is dataLen=%d, ori size is %d", dataLen, size);
        if (dataLen != size || (size > (5 * (int)sizeof(unsigned short) + MAX_FILE_NAME_LEN)))
        {
            ALOGE("AudioTasteRunning data miss !! dataLen=%d, size=%d", dataLen, size);
            return ACHFailed;
        }
        sAudioTAsteParam.cmdType = cmdType;
        memcpy((void *)&sAudioTAsteParam.selected_fir_index, pParam + sizeof(int), size);

        ALOGD("AudioTasteRunning - cmd type=%d, mode=%d, wb_mode=%d", cmdType, sAudioTAsteParam.phone_mode, sAudioTAsteParam.wb_mode);
        ALOGD("AudioTasteRunning - index=%d, dl DG gain=%d, dl PGA=%d", sAudioTAsteParam.selected_fir_index, sAudioTAsteParam.dlDGGain, sAudioTAsteParam.dlPGA);
        ALOGD("AudioTasteRunning - file name: %s", sAudioTAsteParam.audio_file);
        ret = SetAudioData(AUD_TASTE_TUNING_CMD, sizeof(AUD_TASTE_PARAM_STRUCT), (void *)&sAudioTAsteParam);
        ALOGD("SetAudioData = %d",ret);
        if (ret != NO_ERROR)
        {
            return ACHFailed;
        }
    }
    else
    {
        sAudioTAsteParam.cmdType = 0;
        ret = SetAudioData(AUD_TASTE_TUNING_CMD, sizeof(AUD_TASTE_PARAM_STRUCT), (void *)&sAudioTAsteParam);
        ALOGD("SetAudioData = %d",ret);
        if (ret != NO_ERROR)
        {
            return ACHFailed;
        }
    }

    return ACHSucceeded;
}


ACHStatus AudioCmdHandler::DLCustDualMicParamToNV(char *pParam, int block)
{
    // block = 0: for ABF_para[NUM_ABF_PARAM + NUM_ABFWB_PARAM]
    // block = 1: for remains
    ALOGD("AudioCmdHandler::DLCustDualMicParamToNV() in");
    int size = 0;
    int dataLen = 0;

    if (NULL == pParam)
        return ACHFailed;

#ifdef MTK_DUAL_MIC_SUPPORT
    AUDIO_CUSTOM_EXTRA_PARAM_STRUCT *pDualMicPara = (AUDIO_CUSTOM_EXTRA_PARAM_STRUCT *)malloc(sizeof(AUDIO_CUSTOM_EXTRA_PARAM_STRUCT));
    if (pDualMicPara == NULL)
        return ACHFailed;

    ALOGD("DLCustDualMicParamToNV ,dual mic param size=%d", sizeof(AUDIO_CUSTOM_EXTRA_PARAM_STRUCT));
    size = GetDualMicSpeechParamFromNVRam(pDualMicPara);
    if (size != sizeof(AUDIO_CUSTOM_EXTRA_PARAM_STRUCT))
    {
        ALOGD("DLCustDualMicParamToNV Upload from NVRAM fail, structure size=%d,read_size=%d", sizeof(AUDIO_CUSTOM_EXTRA_PARAM_STRUCT), size);
        if (pDualMicPara) { free(pDualMicPara); }
        pDualMicPara = NULL;
        return ACHFailed;
    }

    if (block == 0)
    {
        size = sizeof(pDualMicPara->ABF_para);
        dataDecode((char *)pParam, size + sizeof(int));

        dataLen = *((int *)pParam);
        if (dataLen != size)
        {
            ALOGE("DLCustDualMicParamToNV ABF_para data miss !! dataLen=%d, size=%d", dataLen, size);
            if (pDualMicPara) { free(pDualMicPara); }
            return ACHFailed;
        }

        memcpy((void *)pDualMicPara->ABF_para, (void*)(pParam + sizeof(int)), size);

        for (int i = 0; i < NUM_ABF_PARAM + NUM_ABFWB_PARAM; i++)
        {
            SLOGV("Dual Mic parameters ABF[%d]=%d", i, pDualMicPara->ABF_para[i]);
        }
    }
    else if (block == 1)
    {
#ifdef MTK_HANDSFREE_DMNR_SUPPORT
        size = sizeof(AUDIO_CUSTOM_EXTRA_PARAM_STRUCT) - sizeof(pDualMicPara->ABF_para) + sizeof(int);
        dataDecode((char *)pParam, size);

        dataLen = *((int *)pParam);
        size -= sizeof(int);
        if (dataLen != size)
        {
            ALOGE("DLCustDualMicParamToNV ABF_para data miss !! dataLen=%d, size=%d", dataLen, size);
            if (pDualMicPara) { free(pDualMicPara); }
            return ACHFailed;
        }

        // For coverity, copy field by field
        //memcpy((void *)pDualMicPara->ABF_para_LoudSPK, pParam + sizeof(int), size);
        char *pTemp = pParam + sizeof(int);
        size_t tempsize = sizeof(pDualMicPara->ABF_para_LoudSPK);
        memcpy ((void *)pDualMicPara->ABF_para_LoudSPK, pTemp, tempsize);

        pTemp += tempsize;
        tempsize = sizeof (pDualMicPara->ABF_para_VR);
        memcpy ((void *)pDualMicPara->ABF_para_VR, pTemp, tempsize);

        pTemp += tempsize;
        tempsize = sizeof (pDualMicPara->ABF_para_VOIP);
        memcpy ((void *)pDualMicPara->ABF_para_VOIP, pTemp, tempsize);

        pTemp += tempsize;
        tempsize = sizeof (pDualMicPara->ABF_para_VOIP_LoudSPK);
        memcpy ((void *)pDualMicPara->ABF_para_VOIP_LoudSPK, pTemp, tempsize);

        for (int i = 0; i < NUM_ABF_PARAM + NUM_ABFWB_PARAM; i++)
        {
            SLOGV("Dual Mic parameters ABF_para_LoudSPK[%d]=%d", i, pDualMicPara->ABF_para_LoudSPK[i]);
        }

        for (int i = 0; i < NUM_ABFWB_PARAM; i++)
        {
            SLOGV("Dual Mic parameters ABF_para_VR[%d]=%d", i, pDualMicPara->ABF_para_VR[i]);
        }

        for (int i = 0; i < NUM_ABFWB_PARAM; i++)
        {
            SLOGV("Dual Mic parameters ABF_para_VOIP[%d]=%d", i, pDualMicPara->ABF_para_VOIP[i]);
        }

        for (int i = 0; i < NUM_ABFWB_PARAM; i++)
        {
            SLOGV("Dual Mic parameters ABF_para_VOIP_LoudSPK[%d]=%d", i, pDualMicPara->ABF_para_VOIP_LoudSPK[i]);
        }
#else
        SLOGW("do not support DMNR3.0, block:%d", block);
        if (pDualMicPara) { free(pDualMicPara); }
        pDualMicPara = NULL;
        return ACHFailed;
#endif
    }
    else
    {
        SLOGW("command parameters error block:%d", block);
        if (pDualMicPara) { free(pDualMicPara); }
        pDualMicPara = NULL;
        return ACHFailed;
    }

    size = SetDualMicSpeechParamToNVRam(pDualMicPara);
    if (size != sizeof(AUDIO_CUSTOM_EXTRA_PARAM_STRUCT))
    {
        ALOGD("DLCustDualMicParamToNV down load to NVRAM fail, structure size=%d,write_size=%d", sizeof(AUDIO_CUSTOM_EXTRA_PARAM_STRUCT), size);
        if (pDualMicPara) { free(pDualMicPara); }
        pDualMicPara = NULL;
        return ACHFailed;
    }
    AudioSystem::setParameters(0, String8("UpdateDualMicParameters=1"));
    AudioSystem::setParameters(0, String8("UpdateBesRecordParameters=1"));

    if (pDualMicPara) { free(pDualMicPara); }
    return ACHSucceeded;
#else
    unused(block);
    return ACHFailed;
#endif
}

ACHStatus AudioCmdHandler::ULCustDualMicParamFromNV(char *pParam, int *len, int block)
{
    ALOGD("AudioCmdHandler::ULCustDualMicParamFromNV() in");
    int size = 0;

    AUDIO_CUSTOM_EXTRA_PARAM_STRUCT *pDualMicPara = (AUDIO_CUSTOM_EXTRA_PARAM_STRUCT *)malloc(sizeof(AUDIO_CUSTOM_EXTRA_PARAM_STRUCT));
    if (pDualMicPara == NULL || pParam == NULL)
    {
        if (pDualMicPara != NULL)
        {
            free(pDualMicPara);
        }
        return ACHFailed;
    }

    ALOGD("dual mic param size=%d", sizeof(AUDIO_CUSTOM_EXTRA_PARAM_STRUCT));
    size = GetDualMicSpeechParamFromNVRam(pDualMicPara);
    if (size != sizeof(AUDIO_CUSTOM_EXTRA_PARAM_STRUCT))
    {
        ALOGD("Up load from NVRAM fail, structure size=%d,read_size=%d", sizeof(AUDIO_CUSTOM_EXTRA_PARAM_STRUCT), size);
        free(pDualMicPara);
        pDualMicPara = NULL;
        return ACHFailed;
    }

    if (block == 0)
    {
        for (int i = 0; i < NUM_ABF_PARAM + NUM_ABFWB_PARAM; i++)
        {
            SLOGV("Dual Mic parameters ABF[%d]=%d", i, pDualMicPara->ABF_para[i]);
        }

        *((int *)pParam) = sizeof(pDualMicPara->ABF_para);
        memcpy(pParam + sizeof(int), (void *)pDualMicPara->ABF_para, sizeof(pDualMicPara->ABF_para));

        dataEncode((char *)pParam, sizeof(pDualMicPara->ABF_para) + sizeof(int));
        *len = 2 * (sizeof(pDualMicPara->ABF_para) + sizeof(int));
    }
    else if (block == 1)
    {
#ifdef MTK_HANDSFREE_DMNR_SUPPORT
        for (int i = 0; i < NUM_ABF_PARAM + NUM_ABFWB_PARAM; i++)
        {
            SLOGV("Dual Mic parameters ABF_para_LoudSPK[%d]=%d", i, pDualMicPara->ABF_para_LoudSPK[i]);
        }

        for (int i = 0; i < NUM_ABFWB_PARAM; i++)
        {
            SLOGV("Dual Mic parameters ABF_para_VR[%d]=%d", i, pDualMicPara->ABF_para_VR[i]);
        }

        for (int i = 0; i < NUM_ABFWB_PARAM; i++)
        {
            SLOGV("Dual Mic parameters ABF_para_VOIP[%d]=%d", i, pDualMicPara->ABF_para_VOIP[i]);
        }

        for (int i = 0; i < NUM_ABFWB_PARAM; i++)
        {
            SLOGV("Dual Mic parameters ABF_para_VOIP_LoudSPK[%d]=%d", i, pDualMicPara->ABF_para_VOIP_LoudSPK[i]);
        }

        size = sizeof(AUDIO_CUSTOM_EXTRA_PARAM_STRUCT) - sizeof(pDualMicPara->ABF_para);
        *((int *)pParam) = size;

        // to make coverity happy, dont copy across array's boundary.
        // we need all fields from AUDIO_CUSTOM_EXTRA_PARAM_STRUCT except ABF_para
        //memcpy(pParam + sizeof(int), (void *)pDualMicPara->ABF_para_LoudSPK, size);

        char *pTemp = (char*)pParam + sizeof(int);
        size_t tempsize = sizeof (pDualMicPara->ABF_para_LoudSPK);
        memcpy (pTemp, pDualMicPara->ABF_para_LoudSPK, tempsize);

        pTemp += tempsize;
        tempsize = sizeof (pDualMicPara->ABF_para_VR);
        memcpy (pTemp, pDualMicPara->ABF_para_VR, tempsize);

        pTemp += tempsize;
        tempsize = sizeof (pDualMicPara->ABF_para_VOIP);
        memcpy (pTemp, pDualMicPara->ABF_para_VOIP, tempsize);

        pTemp += tempsize;
        tempsize = sizeof (pDualMicPara->ABF_para_VOIP_LoudSPK);
        memcpy (pTemp, pDualMicPara->ABF_para_VOIP_LoudSPK, tempsize);


        dataEncode((char *)pParam, size + sizeof(int));
        *len = 2 * (size + sizeof(int));
#else
        SLOGW("do not support DMNR3.0, block:%d", block);
        if (pDualMicPara) { free(pDualMicPara); }
        pDualMicPara = NULL;
        return ACHFailed;
#endif
    }
    else
    {
        SLOGW("command parameters error block:%d", block);
        if (pDualMicPara) { free(pDualMicPara); }
        pDualMicPara = NULL;
        return ACHFailed;
    }

    if (pDualMicPara) { free(pDualMicPara); }
    pDualMicPara = NULL;
    return ACHSucceeded;
}

//for DMNR tuning
ACHStatus AudioCmdHandler::AudioDMNRTuning(unsigned short cmdType, bool bWB, char *pParam)
{
    ALOGD("AudioCmdHandler::AudioDMNRTuning() in, cmdType = %d", cmdType);
#if defined(MTK_DUAL_MIC_SUPPORT) || defined(MTK_AUDIO_HD_REC_SUPPORT)
    int size = 0;
    int dataLen = 0;
    char keyInputFileName[MAX_FILE_NAME_LEN];
    char keyOutputFileName[MAX_FILE_NAME_LEN];
    char keyCmdType[MAX_FILE_NAME_LEN];
    DMNRTuningFileName *pFileName = NULL;

    switch (cmdType)
    {
        case DUAL_MIC_REC_PLAY_STOP:
            sprintf(keyCmdType, "DUAL_MIC_REC_PLAY=%d", cmdType);
            AudioSystem::setParameters(0, String8(keyCmdType));
            break;
        case DUAL_MIC_REC:
        case DUAL_MIC_REC_HF:
        {
            size = MAX_FILE_NAME_LEN + sizeof(int);
            dataDecode((char *)pParam, size);

            dataLen = *((int *)pParam);
            size = strlen((char *)(pParam + sizeof(int))) + 1;
            if (dataLen != size)
            {
                ALOGE("AudioDMNRTuning data miss !! dataLen=%d, size=%d", dataLen, size);
                return ACHFailed;
            }

            cmdType = bWB ? (cmdType | 0x10) : (cmdType);
            sprintf(keyCmdType, "DUAL_MIC_REC_PLAY=%d", cmdType);
            sprintf(keyOutputFileName, "DUAL_MIC_OUT_FILE_NAME=%s", (char *)(pParam + sizeof(int)));

            AudioSystem::setParameters(0, String8(keyOutputFileName));
            AudioSystem::setParameters(0, String8(keyCmdType));
            break;
        }
        case DUAL_MIC_REC_PLAY:
        case DUAL_MIC_REC_PLAY_HS:
        case DUAL_MIC_REC_PLAY_HF:
        case DUAL_MIC_REC_PLAY_HS_HF:
        {
            size = 2 * MAX_FILE_NAME_LEN + sizeof(int);
            dataDecode((char *)pParam, size);

            dataLen = *((int *)pParam);
            pFileName = (DMNRTuningFileName *)(pParam + sizeof(int));
            size = strlen(pFileName->input_file) + strlen(pFileName->output_file) + 2;
            if (dataLen != size)
            {
                ALOGE("AudioDMNRTuning data miss !! dataLen=%d, size=%d", dataLen, size);
                return ACHFailed;
            }

            cmdType = bWB ? (cmdType | 0x10) : (cmdType);
            sprintf(keyCmdType, "DUAL_MIC_REC_PLAY=%d", cmdType);
            sprintf(keyInputFileName, "DUAL_MIC_IN_FILE_NAME=%s", pFileName->input_file);
            sprintf(keyOutputFileName, "DUAL_MIC_OUT_FILE_NAME=%s", pFileName->output_file);

            AudioSystem::setParameters(0, String8(keyInputFileName));
            AudioSystem::setParameters(0, String8(keyOutputFileName));
            AudioSystem::setParameters(0, String8(keyCmdType));
            break;
        }
        default:
            ALOGD("AudioCmdHandler::AudioDMNRTuning() cmdType error, cmdType=%d", cmdType);
            return ACHFailed;
            break;
    }

    return ACHSucceeded;
#else
    return ACHFailed;
#endif
}

ACHStatus AudioCmdHandler::getDMNRGain(unsigned short cmdType, char *pParam, int *len)
{
    ALOGD("AudioCmdHandler::getDMNRGain() in");
    unsigned short gain = 0;
    char gainStr[MAX_FILE_NAME_LEN];
    char *pParamValue = NULL;
    char *pParamName = NULL;
    String8 mValue;

    if (cmdType < 0 || cmdType >= DUAL_MIC_GAIN_CNT)
    {
        return ACHFailed;
    }

    sprintf(gainStr, "DUAL_MIC_GET_GAIN=%d", cmdType);
    mValue = AudioSystem::getParameters(0, String8(gainStr));

    ALOGD("getDMNRGain the parameters is %s", mValue.string());
    strcpy(gainStr, mValue.string());
    pParamValue = gainStr;
    pParamName = strsep(&pParamValue, "=");
    if (NULL == pParamName || NULL == pParamValue)
    {
        return ACHFailed;
    }

    gain = atoi(pParamValue);
    ALOGD("getDMNRGain ori str:%s, new: %s, gain=%d", gainStr, pParamName, gain);

    *((int *)pParam) = sizeof(unsigned short);
    *((unsigned short *)(pParam + sizeof(int))) = gain;

    dataEncode((char *)pParam, sizeof(unsigned short) + sizeof(int));
    *len = 2 * (sizeof(unsigned short) + sizeof(int));

    return ACHSucceeded;
}

ACHStatus AudioCmdHandler::setDMNRGain(unsigned short cmdType, unsigned short gain)
{
    ALOGD("AudioCmdHandler::setDMNRGain() in");
    ALOGD("setDMNRGain() cmd type=%d, gain=%d", cmdType, gain);
    char gainStr[MAX_FILE_NAME_LEN];

    if (cmdType < 0 || cmdType >= DUAL_MIC_GAIN_CNT)
    {
        return ACHFailed;
    }

    switch (cmdType)
    {
        case DUAL_MIC_UL_GAIN:
            sprintf(gainStr, "DUAL_MIC_SET_UL_GAIN=%d", gain);
            break;
        case DUAL_MIC_DL_GAIN:
            sprintf(gainStr, "DUAL_MIC_SET_DL_GAIN=%d", gain);
            break;
        case DUAL_MIC_HSDL_GAIN:
            sprintf(gainStr, "DUAL_MIC_SET_HSDL_GAIN=%d", gain);
            break;
        case DUAL_MIC_UL_GAIN_HF:
            sprintf(gainStr, "DUAL_MIC_SET_UL_GAIN_HF=%d", gain);
            break;
        default:
            break;
    }

    AudioSystem::setParameters(0, String8(gainStr));
    return ACHSucceeded;
}

#ifdef MTK_AUDIO_GAIN_TABLE
void AudioCmdHandler::printGainInfo(PCDispTotolStru *dispStru, int block)
{
	if(block == 1)
	{
		ALOGD("PCDispTotolStru->itemNum: 0x%x", dispStru->itemNum);
		for(int i=0; i<16; i++)
		{
			ALOGD("PCDispTotolStru->DispItem[%d].strType is %s", i, dispStru->DispItem[i].strType);
			ALOGD("PCDispTotolStru->DispItem[%d].level is 0x%x", i, dispStru->DispItem[i].level);
			ALOGD("PCDispTotolStru->DispItem[%d].subItemNum is 0x%x", i, dispStru->DispItem[i].subItemNum);
			for(int j=0; j<MAX_SUB_ITEM_NUM; j++)
			{
				ALOGD("PCDispTotolStru->DispItem[%d].subItem[%d].outputDevice is %s", i, j, dispStru->DispItem[i].subItem[j].outputDevice);
				ALOGD("PCDispTotolStru->DispItem[%d].subItem[%d].AnalogPoint is 0x%x", i, j, dispStru->DispItem[i].subItem[j].AnalogPoint);
			}
		}
	}
	else if(block == 2)
	{
		ALOGD("Disp Info For Mic");
		ALOGD("dispStru->DispMic.strType: %s", dispStru->DispMic.strType);
		ALOGD("dispStru->DispMic.subItem: 0x%x", dispStru->DispMic.subItemNum);
		for(int j=0; j<24; j++)
		{
			ALOGD("dispStru->DispMic.subItem[j]:%s", dispStru->DispMic.subItem[j]);
		}
		
		ALOGD("dispStru->gainRangeNum: 0x%x", dispStru->gainRangeNum);
		for(int k=0; k<MAX_GAIN_POINT_NUM; k++)
		{
			ALOGD("Audio Buffer Gain/Voice Buffer Gain/Mic Gain/Ext AMP1 Gain/Ext AMP2 Gain/Ext AMP3 Gain/Ext AMP4 Gain/Side Tone Gain");
			ALOGD("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d", dispStru->gainRange[k][0], dispStru->gainRange[k][1], dispStru->gainRange[k][2], dispStru->gainRange[k][3],
			dispStru->gainRange[k][4], dispStru->gainRange[k][5], dispStru->gainRange[k][6], dispStru->gainRange[k][7], dispStru->gainRange[k][8], dispStru->gainRange[k][9], dispStru->gainRange[k][10], dispStru->gainRange[k][11], 
			dispStru->gainRange[k][12], dispStru->gainRange[k][13], dispStru->gainRange[k][14], dispStru->gainRange[k][15], dispStru->gainRange[k][16], dispStru->gainRange[k][17], dispStru->gainRange[k][18], dispStru->gainRange[k][19],
			dispStru->gainRange[k][20], dispStru->gainRange[k][21], dispStru->gainRange[k][22], dispStru->gainRange[k][23], dispStru->gainRange[k][24], dispStru->gainRange[k][25], dispStru->gainRange[k][26], dispStru->gainRange[k][27],
			dispStru->gainRange[k][28], dispStru->gainRange[k][29], dispStru->gainRange[k][30], dispStru->gainRange[k][31]);		
		}
	}



}
void AudioCmdHandler::printCustGainTable(AUDIO_GAIN_TABLE_STRUCT *gainTable, int block)
{
	int i=0, j=0;
	ALOGD("OutputDevice: GAIN_OUTPUT_EARPIECE,GAIN_OUTPUT_HEADSET,GAIN_OUTPUT_SPEAKER,GAIN_OUTPUT_DOCK");

	if(block == 1)
	{
		for(i=0; i<12; i++)
		{
			STREAM_GAIN *ptr = (STREAM_GAIN *)((char *)gainTable + i*sizeof(STREAM_GAIN));
			for(j=0; j<3; j++)
			{
				ALOGD("Digtal Gain: 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x", 
					ptr->stream[j].digital[0], ptr->stream[j].digital[1], ptr->stream[j].digital[2], ptr->stream[j].digital[3], ptr->stream[j].digital[4], ptr->stream[j].digital[5], 
					ptr->stream[j].digital[6], ptr->stream[j].digital[7], ptr->stream[j].digital[8], ptr->stream[j].digital[9], ptr->stream[j].digital[10], ptr->stream[j].digital[11],
					ptr->stream[j].digital[12], ptr->stream[j].digital[13], ptr->stream[j].digital[14], ptr->stream[j].digital[15], ptr->stream[j].digital[16], ptr->stream[j].digital[17]);
				ALOGD("Analog Gain: 0x%x", ptr->stream[j].analog);
				ALOGD("Amp Gain: 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x", 
				ptr->stream[j].amp[0], ptr->stream[j].amp[1], ptr->stream[j].amp[2], ptr->stream[j].amp[3], ptr->stream[j].amp[4], ptr->stream[j].amp[5], 
				ptr->stream[j].amp[6], ptr->stream[j].amp[7], ptr->stream[j].amp[8], ptr->stream[j].amp[9]);
			}

			ALOGD("");
			ALOGD("********************************************************************************************************");
			ALOGD("");
		}
	}
	else if(block == 2)
	{
		ALOGD("OutputDevice: GAIN_OUTPUT_EARPIECE,GAIN_OUTPUT_HEADSET,GAIN_OUTPUT_SPEAKER,GAIN_OUTPUT_DOCK, and Every Gain Step");
		for(i=0; i<4; i++)
		{
			for(j=0; j<18; j++)
			{
				ALOGD("SpeechWB Digtal Gain: 0x%x", gainTable->speechWB.speech[i][j].digital);
				ALOGD("SpeechWB Analog Gain: 0x%x", gainTable->speechWB.speech[i][j].analog);
				ALOGD("Amp Gain: 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x", 
				gainTable->speechWB.speech[i][j].amp[0], gainTable->speechWB.speech[i][j].amp[1], gainTable->speechWB.speech[i][j].amp[2], gainTable->speechWB.speech[i][j].amp[3], gainTable->speechWB.speech[i][j].amp[4], gainTable->speechWB.speech[i][j].amp[5], 
				gainTable->speechWB.speech[i][j].amp[6], gainTable->speechWB.speech[i][j].amp[7], gainTable->speechWB.speech[i][j].amp[8], gainTable->speechWB.speech[i][j].amp[9]);
			}
		}

		ALOGD("stream Type is sideToneWB");
		ALOGD("sideToneWB Gain: 0x%x, 0x%x, 0x%x, 0x%x", gainTable->sideToneWB.sidetone[0], gainTable->sideToneWB.sidetone[1], gainTable->sideToneWB.sidetone[2], gainTable->sideToneWB.sidetone[3]);

		ALOGD("stream Type is mic");
		ALOGD("mic Gain: 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x", 
			gainTable->mic.mic[0].digital, gainTable->mic.mic[1].digital, gainTable->mic.mic[2].digital, gainTable->mic.mic[3].digital, gainTable->mic.mic[4].digital, gainTable->mic.mic[5].digital, 
			gainTable->mic.mic[6].digital, gainTable->mic.mic[7].digital, gainTable->mic.mic[8].digital, gainTable->mic.mic[9].digital, gainTable->mic.mic[10].digital, gainTable->mic.mic[11].digital,
			gainTable->mic.mic[12].digital, gainTable->mic.mic[13].digital, gainTable->mic.mic[14].digital, gainTable->mic.mic[15].digital, gainTable->mic.mic[16].digital, gainTable->mic.mic[17].digital, 
			gainTable->mic.mic[18].digital, gainTable->mic.mic[19].digital, gainTable->mic.mic[20].digital, gainTable->mic.mic[21].digital, gainTable->mic.mic[22].digital, gainTable->mic.mic[23].digital);
	}
}

ACHStatus AudioCmdHandler::getGainInfoForDisp(char *pParam, int *len, int block)
{
    ALOGD("getGainInfoForDisp() in, pParam is 0x%x", (int)pParam);

    if (pParam == NULL)
    {
        return ACHFailed;
    }

	//TBD:get PCDispTotolStru from Audio HAL
	if(GainInfoFlag == false)
	{
		ALOGD("GainInfoFlag == false, Start to get GainInfo");
        status_t ret = GetAudioData(AUDIO_GET_LGE_DISP, sizeof(PCDispTotolStru), (void *)&mDispStru);
		if(ret != NO_ERROR)
		{
			ALOGE("read PCDispTotolStru error");
			return ACHFailed;
		}
	}

    int size = 0;
    char *pGainInfoCustomParam = pParam + sizeof(int);
    char *pGainInfoCustomParamBegain = pGainInfoCustomParam;
    PCDispTotolStru *pGainInfoParam = (PCDispTotolStru *)malloc(sizeof(PCDispTotolStru));
	memcpy((void *)pGainInfoParam, (void *)&mDispStru, sizeof(PCDispTotolStru));

	printGainInfo((PCDispTotolStru *)pGainInfoParam, block);
	
	if(block == 0)
	{
		ALOGD("Get all PCDispTotolStru Structure");
		//TBD
	}
	else if(block == 1)  
	{
		ALOGD("First get GainInfo for PC UI display");
		GainInfoFlag = true;
	
		ALOGD("Get itemNum and 20 DispItems");
		memcpy(pGainInfoCustomParam, (void *)&(pGainInfoParam->itemNum), sizeof(pGainInfoParam->itemNum));
		pGainInfoCustomParam += sizeof(pGainInfoParam->itemNum);
		for(int i=0; i<MAX_ITEM_NUM; i++)
		{
			memcpy(pGainInfoCustomParam, (void *)&(pGainInfoParam->DispItem[i]), sizeof(pGainInfoParam->DispItem[i]));
			pGainInfoCustomParam += sizeof(pGainInfoParam->DispItem[i]);
		}

		size = (int)pGainInfoCustomParam - (int)pGainInfoCustomParamBegain;
	}
	else if(block == 2)
	{
		ALOGD("Get Mic Structure and gainRange");
		
		memcpy(pGainInfoCustomParam, (void *)&(pGainInfoParam->DispMic), sizeof(pGainInfoParam->DispMic));
		pGainInfoCustomParam += sizeof(pGainInfoParam->DispMic);

		memcpy(pGainInfoCustomParam, (void *)&(pGainInfoParam->gainRangeNum), sizeof(pGainInfoParam->gainRangeNum));
		pGainInfoCustomParam += sizeof(pGainInfoParam->gainRangeNum);

		memcpy(pGainInfoCustomParam, (void *)pGainInfoParam->gainRange, MAX_GAIN_POINT_NUM*32);
		pGainInfoCustomParam += MAX_GAIN_POINT_NUM*32;

		size = (int)pGainInfoCustomParam - (int)pGainInfoCustomParamBegain;

		ALOGD("get GainInfo for PC UI display Done");
		GainInfoFlag = false;
	}
	else if(block == 3)
	{
/*
		ALOGD("Pass next 4 DispItems and Analog Gain Range");
		for(int i=0; i<4; i++)
		{
			memcpy(pGainInfoCustomParam, (void *)&(pGainInfoParam->DispItem[i+12]), sizeof(pGainInfoParam->DispItem[i+12]));
			pGainInfoCustomParam += sizeof(pGainInfoParam->DispItem[i+12]);
		}
		ALOGD("sizeof(pGainInfoParam->gainRange) is %d", sizeof(pGainInfoParam->gainRange));
//		memcpy(pGainInfoCustomParam, (void *)pGainInfoParam->gainRange, sizeof(pGainInfoParam->gainRange));
//		pGainInfoCustomParam += sizeof(pGainInfoParam->gainRange);
		memcpy(pGainInfoCustomParam, (void *)pGainInfoParam->gainRange, 8*32);
		pGainInfoCustomParam += 8*32;

		size = (int)pGainInfoCustomParam - (int)pGainInfoCustomParamBegain;
*/
	}
	else
	{
		ALOGE("The value of block: %d is invailed", block);
		return ACHFailed;
	}

    *((int *)pParam) = size;

    dataEncode((char *)pParam, size + sizeof(int));
	ALOGD("size is %d", size);
    *len = 2 * (size + sizeof(int));

	
    if (pGainInfoParam) { free(pGainInfoParam); }
    pGainInfoParam = NULL;

	ALOGD("getGainInfoForDisp() out, size is %d, len is %d", size, *len);
    return ACHSucceeded;
}

ACHStatus AudioCmdHandler::ULCustGainParamFromNV(char *pParam, int *len, int block)
{

	ALOGD("ULCustGainParamFromNV() in");
    if (pParam == NULL)
    {
        return ACHFailed;
    }

    int size = 0;
    char *pGainTableCustomParam = pParam + sizeof(int);
    char *pGainTableCustomParamBegain = pGainTableCustomParam;
    AUDIO_GAIN_TABLE_STRUCT *pGainTableParam = (AUDIO_GAIN_TABLE_STRUCT *)malloc(sizeof(AUDIO_GAIN_TABLE_STRUCT));

    ALOGD("ULCustGainParamFromNV ,LGE Gain Table size=%d", sizeof(AUDIO_GAIN_TABLE_STRUCT));
    size = GetAudioGainTableParamFromNV(pGainTableParam);  //TBD
    if (size != sizeof(AUDIO_GAIN_TABLE_STRUCT))
    {
        ALOGD("ULCustGainParamFromNV Up load from NVRAM fail, structure size=%d,read_size=%d", sizeof(AUDIO_GAIN_TABLE_STRUCT), size);
        if (pGainTableParam) { free(pGainTableParam); }
        pGainTableParam = NULL;
        return ACHFailed;
    }
	printCustGainTable(pGainTableParam, block);

	if(block ==0)
	{
		ALOGD("Get all AUDIO_GAIN_TABLE_STRUCT Structure");
		//TBD
	}
	else if(block == 1)
	{
		ALOGD("Get 12 streamType items");
		memcpy(pGainTableCustomParam, (void *)pGainTableParam, 12*sizeof(pGainTableParam->voiceCall));
		pGainTableCustomParam += 12*sizeof(pGainTableParam->voiceCall);

		size = (int)pGainTableCustomParam - (int)pGainTableCustomParamBegain;
	}
	else if(block == 2)
	{
		ALOGD("Get Speech/SideTone/Mic items");

		memcpy(pGainTableCustomParam, (void *)&(pGainTableParam->speechNB), sizeof(pGainTableParam->speechNB));
		pGainTableCustomParam += sizeof(pGainTableParam->speechNB);
		memcpy(pGainTableCustomParam, (void *)&(pGainTableParam->speechWB), sizeof(pGainTableParam->speechWB));
		pGainTableCustomParam += sizeof(pGainTableParam->speechWB);
		memcpy(pGainTableCustomParam, (void *)&(pGainTableParam->sideToneNB), sizeof(pGainTableParam->sideToneNB));
		pGainTableCustomParam += sizeof(pGainTableParam->sideToneNB);
		memcpy(pGainTableCustomParam, (void *)&(pGainTableParam->sideToneWB), sizeof(pGainTableParam->sideToneWB));
		pGainTableCustomParam += sizeof(pGainTableParam->sideToneWB);
		memcpy(pGainTableCustomParam, (void *)&(pGainTableParam->mic), sizeof(pGainTableParam->mic));
		pGainTableCustomParam += sizeof(pGainTableParam->mic);

		size = (int)pGainTableCustomParam - (int)pGainTableCustomParamBegain;
	}
	else
	{
		ALOGE("The value of block: %d is invailed", block);
		return ACHFailed;
	}

	*((int *)pParam) = size;

	dataEncode((char *)pParam, size + sizeof(int));
	*len = 2 * (size + sizeof(int));


	if (pGainTableParam) { free(pGainTableParam); }
	pGainTableParam = NULL;

	ALOGD("ULCustGainParamFromNV() out, size is %d, len is %d", size, *len);
	return ACHSucceeded;
}

ACHStatus AudioCmdHandler::DLCustGainParamToNV(char *pParam, int block)
{
	ALOGD("AudioCmdHandler::DLCustGainParamToNV() in");
	int size = 0;
	int dataLen = 0;

	AUDIO_GAIN_TABLE_STRUCT *pGainTableParam = (AUDIO_GAIN_TABLE_STRUCT *)malloc(sizeof(AUDIO_GAIN_TABLE_STRUCT));
	if (pGainTableParam == NULL || pParam == NULL)
	{
		if (pGainTableParam) { free(pGainTableParam); }
		return ACHFailed;
	}

	ALOGD("DLCustGainParamToNV ,LGE Gain Table size=%d", sizeof(AUDIO_GAIN_TABLE_STRUCT));
	size = GetAudioGainTableParamFromNV(pGainTableParam);  //TBD
	if (size != sizeof(AUDIO_GAIN_TABLE_STRUCT))
	{
		ALOGD("DLCustGainParamToNV Upload from NVRAM fail, structure size=%d,read_size=%d", sizeof(AUDIO_GAIN_TABLE_STRUCT), size);
		if (pGainTableParam) { free(pGainTableParam); }
		pGainTableParam = NULL;
		return ACHFailed;
	}
//	printCustGainTable(pGainTableParam, block);

	if(block == 0)
	{
		ALOGD("Get all AUDIO_GAIN_TABLE_STRUCT Structure");
		//TBD
	}
	else if(block == 1)
	{
		ALOGD("Set 12 stream items");
        size = 12 * sizeof(pGainTableParam->voiceCall) + sizeof(int);
        dataDecode((char *)pParam, size);

        dataLen = *((int *)pParam);
        size -= sizeof(int);
        if (dataLen != size)
        {
            ALOGE("DLCustGainParamToNV 12 streamType data miss !! dataLen=%d, size=%d", dataLen, size);
            if (pGainTableParam) { free(pGainTableParam); }
            return ACHFailed;
        }

		memcpy((void *)pGainTableParam, pParam + sizeof(int), size);
	}
	else if(block == 2)
	{
		ALOGD("Set Speech/SideTone/Mic items");
        size = 2*sizeof(pGainTableParam->speechNB) + 2*sizeof(pGainTableParam->sideToneNB) + sizeof(pGainTableParam->mic) + sizeof(int);
        dataDecode((char *)pParam, size);

        dataLen = *((int *)pParam);
        size -= sizeof(int);
        if (dataLen != size)
        {
            ALOGE("DLCustGainParamToNV  Speech/SideTone/Mic items data miss !! dataLen=%d, size=%d", dataLen, size);
            if (pGainTableParam) { free(pGainTableParam); }
            return ACHFailed;
        }

		memcpy((void *)((char *)pGainTableParam + 12*sizeof(pGainTableParam->voiceCall)), pParam + sizeof(int), size);
	}
	else
	{
		ALOGE("The value of block: %d is invailed", block);
		return ACHFailed;		
	}

	printCustGainTable(pGainTableParam, block);
    size = SetAudioGainTableParamToNV(pGainTableParam);  //TBD
    if (size != sizeof(AUDIO_GAIN_TABLE_STRUCT))
    {
        ALOGD("DLCustDualMicParamToNV down load to NVRAM fail, structure size=%d,write_size=%d", sizeof(AUDIO_GAIN_TABLE_STRUCT), size);
        if (pGainTableParam) { free(pGainTableParam); }
        pGainTableParam = NULL;
        return ACHFailed;
    }


    int volumeIndex[DEV_NUM][AUDIO_STREAM_PUBLIC_CNT];
    for (int i = 0; i < AUDIO_STREAM_PUBLIC_CNT; i++)
    {
        // get volue for different devices, 0:receiver; 1:speaker; 2:headset;
        AudioSystem::getStreamVolumeIndex((audio_stream_type_t)i, &volumeIndex[0][i], AUDIO_DEVICE_OUT_EARPIECE);
        AudioSystem::getStreamVolumeIndex((audio_stream_type_t)i, &volumeIndex[1][i], AUDIO_DEVICE_OUT_SPEAKER);
        AudioSystem::getStreamVolumeIndex((audio_stream_type_t)i, &volumeIndex[2][i], AUDIO_DEVICE_OUT_WIRED_HEADSET);
    }
#ifdef MTK_AUDIO
#ifndef MTK_BASIC_PACKAGE
    const sp<IAudioPolicyService> &aps = AudioSystem::get_audio_policy_service();
    if (aps == 0) { return ACHFailed; }
    	aps->SetPolicyManagerParameters(LOAD_VOLUME_POLICY, 0, 0, 0);
#endif
#endif
    AudioSystem::setParameters(0, String8("UpdateHALCustGainTable=0"));
    for (int i = 0; i < AUDIO_STREAM_PUBLIC_CNT; i++)
    {
        AudioSystem::setStreamVolumeIndex((audio_stream_type_t)i, volumeIndex[0][i], AUDIO_DEVICE_OUT_EARPIECE);
        AudioSystem::setStreamVolumeIndex((audio_stream_type_t)i, volumeIndex[1][i], AUDIO_DEVICE_OUT_SPEAKER);
        AudioSystem::setStreamVolumeIndex((audio_stream_type_t)i, volumeIndex[2][i], AUDIO_DEVICE_OUT_WIRED_HEADSET);
    }
	AudioSystem::setParameters(0, String8("UpdateMicGain=0"));

	ALOGD("DLCustGainParamToNV() out");
	return ACHSucceeded;
}

ACHStatus AudioCmdHandler::getBtNrecInfoForDisp(char *pParam, int *len)
{
    ALOGD("getBtNrecInfoForDisp() in, pParam is 0x%x", (int)pParam);
    if (pParam == NULL)
    {
        return ACHFailed;
    }

	//TBD:get PCDispTotolStru from Audio HAL
    status_t ret = GetAudioData(AUDIO_GET_BT_NREC_DISP, sizeof(PCDispItem), (void *)&mBtNrecDispItem);
	if(ret != NO_ERROR)
	{
		ALOGE("read PCDispTotolStru error");
		return ACHFailed;
	}

    int size = 0;
    void *pGainInfoCustomParam = (void *)((char *)pParam + sizeof(int));
	ALOGD("Get 1 DispItems");
	memcpy(pGainInfoCustomParam, (void *)&mBtNrecDispItem, sizeof(PCDispItem));
	size = sizeof(PCDispItem);

    *((int *)pParam) = size;
    dataEncode((char *)pParam, size + sizeof(int));
	ALOGD("size is %d", size);
    *len = 2 * (size + sizeof(int));

	ALOGD("getBtNrecInfoForDisp() out, size is %d, len is %d", size, *len);
    return ACHSucceeded;
}

ACHStatus AudioCmdHandler::DLCustBtNrecParamToNV(char * pParam)
{
    int write_size = 0;
    int size = 0;

    ALOGD("AudioCmdHandler::DLCustBtNrecParamToNV() in");
    AUDIO_BT_GAIN_STRUCT *pBTGainPara = (AUDIO_BT_GAIN_STRUCT *)malloc(sizeof(AUDIO_BT_GAIN_STRUCT));
    if (pBTGainPara == NULL)
    {
        return ACHFailed;
    }
    else if (pParam == NULL)
    {
        free(pBTGainPara);
        pBTGainPara = NULL;
        return ACHFailed;
    }

    size = GetAudioBTGainParamFromNV(pBTGainPara);
    ALOGD("DLCustBtNrecParamToNV- GetAudioBTGainParamFromNV read size=%d", size);
    if (size != sizeof(AUDIO_BT_GAIN_STRUCT))
    {
        ALOGD("DLCustBtNrecParamToNV Up load from NVRAM fail, structure size=%d,read_size=%d", sizeof(AUDIO_BT_GAIN_STRUCT), size);
        free(pBTGainPara);
        pBTGainPara = NULL;
        return ACHFailed;
    }

//Print
	 STREAM_GAIN *ptr = (STREAM_GAIN *)(&(pBTGainPara->blueToothNrec));
	 for(int j=0; j<3; j++)
	 {
		 ALOGD("Digtal Gain: 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x", 
			 ptr->stream[j].digital[0], ptr->stream[j].digital[1], ptr->stream[j].digital[2], ptr->stream[j].digital[3], ptr->stream[j].digital[4], ptr->stream[j].digital[5], 
			 ptr->stream[j].digital[6], ptr->stream[j].digital[7], ptr->stream[j].digital[8], ptr->stream[j].digital[9], ptr->stream[j].digital[10], ptr->stream[j].digital[11],
			 ptr->stream[j].digital[12], ptr->stream[j].digital[13], ptr->stream[j].digital[14], ptr->stream[j].digital[15], ptr->stream[j].digital[16], ptr->stream[j].digital[17]);
		 ALOGD("Analog Gain: 0x%x", ptr->stream[j].analog);
		 ALOGD("Amp Gain: 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x", 
		 ptr->stream[j].amp[0], ptr->stream[j].amp[1], ptr->stream[j].amp[2], ptr->stream[j].amp[3], ptr->stream[j].amp[4], ptr->stream[j].amp[5], 
		 ptr->stream[j].amp[6], ptr->stream[j].amp[7], ptr->stream[j].amp[8], ptr->stream[j].amp[9]);
	 }

	 size = sizeof(AUDIO_BT_GAIN_STRUCT);
	 dataDecode((char *)pParam, size + sizeof(int));
	 if (*((int *)pParam) != size)
	 {
		 ALOGE("DLCustBtNrecParamToNV miss data !!, received size = %d", *((int *)pParam));
		 free(pBTGainPara);
		 pBTGainPara = NULL;
		 return ACHFailed;
	 }
	 memcpy((void *)pBTGainPara, pParam + sizeof(int), sizeof(AUDIO_BT_GAIN_STRUCT));


    write_size = SetAudioBTGainParamToNV(pBTGainPara);
    if (write_size != sizeof(AUDIO_BT_GAIN_STRUCT))
    {
        ALOGD("DLCustSPHHACParamToNV Down load to NVRAM fail, structure size=%d,writed_size=%d", sizeof(AUDIO_BT_GAIN_STRUCT), write_size);
        free(pBTGainPara);
        pBTGainPara = NULL;
        return ACHFailed;
    }

	AudioSystem::setParameters(0, String8("UpdateBTParameters=1"));

    free(pBTGainPara);
    pBTGainPara = NULL;

    return ACHSucceeded;
}

ACHStatus AudioCmdHandler::ULCustBtNrecParamFromNV(char * pParam,int * len)
{
    int size = 0;
    int dataLen = 0;

    ALOGD("AudioCmdHandler::ULCustBTNRECParamFromNV() in");
    AUDIO_BT_GAIN_STRUCT *pBTGainPara = (AUDIO_BT_GAIN_STRUCT *)malloc(sizeof(AUDIO_BT_GAIN_STRUCT));
    if (pBTGainPara == NULL || pParam == NULL)
    {
        return ACHFailed;
    }

    size = GetAudioBTGainParamFromNV(pBTGainPara);
    if (size != sizeof(AUDIO_BT_GAIN_STRUCT))
    {
        ALOGD("ULCustBTNRECParamFromNV Up load from NVRAM fail, structure size=%d,read_size=%d", sizeof(AUDIO_BT_GAIN_STRUCT), size);
        free(pBTGainPara);
        pBTGainPara = NULL;
        return ACHFailed;
    }
//Print
	 STREAM_GAIN *ptr = (STREAM_GAIN *)(&(pBTGainPara->blueToothNrec));
	 for(int j=0; j<3; j++)
	 {
		 ALOGD("Digtal Gain: 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x", 
			 ptr->stream[j].digital[0], ptr->stream[j].digital[1], ptr->stream[j].digital[2], ptr->stream[j].digital[3], ptr->stream[j].digital[4], ptr->stream[j].digital[5], 
			 ptr->stream[j].digital[6], ptr->stream[j].digital[7], ptr->stream[j].digital[8], ptr->stream[j].digital[9], ptr->stream[j].digital[10], ptr->stream[j].digital[11],
			 ptr->stream[j].digital[12], ptr->stream[j].digital[13], ptr->stream[j].digital[14], ptr->stream[j].digital[15], ptr->stream[j].digital[16], ptr->stream[j].digital[17]);
		 ALOGD("Analog Gain: 0x%x", ptr->stream[j].analog);
		 ALOGD("Amp Gain: 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x", 
		 ptr->stream[j].amp[0], ptr->stream[j].amp[1], ptr->stream[j].amp[2], ptr->stream[j].amp[3], ptr->stream[j].amp[4], ptr->stream[j].amp[5], 
		 ptr->stream[j].amp[6], ptr->stream[j].amp[7], ptr->stream[j].amp[8], ptr->stream[j].amp[9]);
	 }

	dataLen = sizeof(AUDIO_BT_GAIN_STRUCT);
	memcpy(pParam + sizeof(int), (void *)pBTGainPara, dataLen);
	

    ALOGD("ULCustBTNRECParamFromNV the data sent to PC is %d", dataLen);
    *((int *)pParam) = dataLen;
    *len = 2 * (dataLen + sizeof(int));

    dataEncode((char *)pParam, dataLen + sizeof(int));

    free(pBTGainPara);
    pBTGainPara = NULL;
	
    return ACHSucceeded;
}

#endif

ACHStatus AudioCmdHandler::DLCustHDRecParamToNV(char *pParam, int block)
{
    ALOGD("DLCustHDRecParamToNV() in");

    if (pParam == NULL)
    {
        return ACHFailed;
    }

#if defined(MTK_AUDIO_HD_REC_SUPPORT)
    int size = 0;
    int dataLen = 0;
    AUDIO_HD_RECORD_PARAM_STRUCT *pHDRecParam = (AUDIO_HD_RECORD_PARAM_STRUCT *)malloc(sizeof(AUDIO_HD_RECORD_PARAM_STRUCT));
    if (NULL == pHDRecParam)
        return ACHFailed;

    size = GetHdRecordParamFromNV(pHDRecParam);
    if (size != sizeof(AUDIO_HD_RECORD_PARAM_STRUCT))
    {
        ALOGD("DLCustHDRecParamToNV Up load from NVRAM fail, structure size=%d,read_size=%d", sizeof(AUDIO_HD_RECORD_PARAM_STRUCT), size);
        free(pHDRecParam);
        return ACHFailed;
    }

    if (block == 0)
    {
        size = 2 * sizeof(pHDRecParam->hd_rec_mode_num) + sizeof(pHDRecParam->hd_rec_speech_mode_para);
        dataDecode((char *)pParam, size + sizeof(int));
        dataLen = *((int *)pParam);
        if (dataLen != size)
        {
            ALOGE("DLCustHDRecParamToNV part1 data miss !! dataLen=%d, size=%d", dataLen, size);
            free(pHDRecParam);
            return ACHFailed;
        }

        memcpy((void *)(&pHDRecParam->hd_rec_mode_num), pParam + sizeof(int), size);

        ALOGD("HD Record parameters part 1 ~~~~~~~~~~~~~~~~");
    }
    else if (block == 1)
    {
        ALOGD("HD Record parameters part 2 ~~~~~~~~~~~~~~~~");
#if 0
        size = sizeof(AUDIO_HD_RECORD_PARAM_STRUCT) - 2 * sizeof(pHDRecParam->hd_rec_mode_num) - sizeof(pHDRecParam->hd_rec_speech_mode_para);
#else
        size = sizeof(pHDRecParam->hd_rec_fir) / 2;
#endif

        dataDecode((char *)pParam, size + sizeof(int));
        dataLen = *((int *)pParam);
        if (dataLen != size)
        {
            ALOGE("DLCustHDRecParamToNV part2 data miss !! dataLen=%d, size=%d", dataLen, size);
            free(pHDRecParam);
            return ACHFailed;
        }

        memcpy((void *)pHDRecParam->hd_rec_fir, pParam + sizeof(int), size);
    }
    else if (block == 2)
    {
        ALOGD("HD Record parameters part 3 ~~~~~~~~~~~~~~~~");
        size = sizeof(AUDIO_HD_RECORD_PARAM_STRUCT) - 2 * sizeof(pHDRecParam->hd_rec_mode_num) - sizeof(pHDRecParam->hd_rec_speech_mode_para) - sizeof(pHDRecParam->hd_rec_fir) / 2;

        dataDecode((char *)pParam, size + sizeof(int));
        dataLen = *((int *)pParam);
        if (dataLen != size)
        {
            ALOGE("DLCustHDRecParamToNV part2 data miss !! dataLen=%d, size=%d", dataLen, size);
            free(pHDRecParam);
            return ACHFailed;
        }

        // Fix coverity 115584 and 115202
        //memcpy((void *)pHDRecParam->hd_rec_fir[SPC_MAX_NUM_RECORD_INPUT_FIR / 2], pParam + sizeof(int), size);

        struct HDRecIn {
            int size;
            short hd_rec_fir[SPC_MAX_NUM_RECORD_INPUT_FIR / 2][WB_FIR_NUM];
            unsigned short hd_rec_map_to_fir_for_ch1[SPC_MAX_NUM_RECORD_SPH_MODE];
            unsigned short hd_rec_map_to_fir_for_ch2[SPC_MAX_NUM_RECORD_SPH_MODE];
            unsigned char hd_rec_map_to_dev_mode[SPC_MAX_NUM_RECORD_SPH_MODE];
            unsigned char hd_rec_map_to_input_src[SPC_MAX_NUM_RECORD_SPH_MODE];
            unsigned char hd_rec_map_to_stereo_flag[SPC_MAX_NUM_RECORD_SPH_MODE];
        };
        struct HDRecIn *pIn = (struct HDRecIn *)pParam;
        for (int i = 0; i < SPC_MAX_NUM_RECORD_INPUT_FIR / 2; i++)
            memcpy(pHDRecParam->hd_rec_fir[SPC_MAX_NUM_RECORD_INPUT_FIR / 2 + i], pIn->hd_rec_fir[i], sizeof(pIn->hd_rec_fir[0]));
        memcpy(pHDRecParam->hd_rec_map_to_fir_for_ch1, pIn->hd_rec_map_to_fir_for_ch1, sizeof(pIn->hd_rec_map_to_fir_for_ch1));
        memcpy(pHDRecParam->hd_rec_map_to_fir_for_ch2, pIn->hd_rec_map_to_fir_for_ch2, sizeof(pIn->hd_rec_map_to_fir_for_ch2));
        memcpy(pHDRecParam->hd_rec_map_to_dev_mode, pIn->hd_rec_map_to_dev_mode, sizeof(pIn->hd_rec_map_to_dev_mode));
        memcpy(pHDRecParam->hd_rec_map_to_input_src, pIn->hd_rec_map_to_input_src, sizeof(pIn->hd_rec_map_to_input_src));
        memcpy(pHDRecParam->hd_rec_map_to_stereo_flag, pIn->hd_rec_map_to_stereo_flag, sizeof(pIn->hd_rec_map_to_stereo_flag));
    }

    size = SetHdRecordParamToNV(pHDRecParam);
    if (size != sizeof(AUDIO_HD_RECORD_PARAM_STRUCT))
    {
        ALOGD("DLCustHDRecParamToNV down load to NVRAM fail, structure size=%d,read_size=%d", sizeof(AUDIO_HD_RECORD_PARAM_STRUCT), size);
        free(pHDRecParam);
        return ACHFailed;
    }

    ALOGD("HD Record Parameters ~~~~~~~~~~~~~~~~");
    ALOGD("mode num=%d, fir num=%d", pHDRecParam->hd_rec_mode_num, pHDRecParam->hd_rec_fir_num);
    ALOGD("speenc mode hd_rec_speech_mode_para[0][0]=%d, hd_rec_speech_mode_para[end][end]=%d", pHDRecParam->hd_rec_speech_mode_para[0][0], pHDRecParam->hd_rec_speech_mode_para[SPC_MAX_NUM_RECORD_SPH_MODE - 1][SPEECH_PARA_NUM - 1]);
    ALOGD("speenc fir hd_rec_fir[0][0]=%d, hd_rec_fir[end][end]=%d", pHDRecParam->hd_rec_fir[0][0], pHDRecParam->hd_rec_fir[SPC_MAX_NUM_RECORD_INPUT_FIR - 1][WB_FIR_NUM - 1]);

    for (int i = 0; i < SPC_MAX_NUM_RECORD_SPH_MODE; i++)
    {
        ALOGD("hd_rec_map_to_fir_for_ch1[%d]=%d", i, pHDRecParam->hd_rec_map_to_fir_for_ch1[i]);
        ALOGD("hd_rec_map_to_fir_for_ch2[%d]=%d", i, pHDRecParam->hd_rec_map_to_fir_for_ch2[i]);
        ALOGD("hd_rec_map_to_dev_mode[%d]=%d", i, pHDRecParam->hd_rec_map_to_dev_mode[i]);
        ALOGD("hd_rec_map_to_input_src[%d]=%d", i, pHDRecParam->hd_rec_map_to_input_src[i]);
        ALOGD("hd_rec_map_to_stereo_flag[%d]=%d", i, pHDRecParam->hd_rec_map_to_stereo_flag[i]);
    }

    AudioSystem::setParameters(0, String8("UpdateBesRecordParameters=1"));
    free(pHDRecParam);
    return ACHSucceeded;
#else
    SLOGW("DLCustHDRecParamToNV-do not support HD record!!");
    return ACHFailed;
#endif
}


ACHStatus AudioCmdHandler::ULCustHDRecParamFromNV(char *pParam, int *len, int block)
{
    ALOGD("ULCustHDRecParamFromNV() in");

    if (pParam == NULL)
    {
        return ACHFailed;
    }

#if defined(MTK_AUDIO_HD_REC_SUPPORT)
    int size = 0;
    AUDIO_HD_RECORD_PARAM_STRUCT *pHDRecCustParam = (AUDIO_HD_RECORD_PARAM_STRUCT *)(pParam + sizeof(int));
    AUDIO_HD_RECORD_PARAM_STRUCT *pHDRecParam = (AUDIO_HD_RECORD_PARAM_STRUCT *)malloc(sizeof(AUDIO_HD_RECORD_PARAM_STRUCT));

    ALOGD("ULCustHDRecParamFromNV ,HD record parameters size=%d", sizeof(AUDIO_HD_RECORD_PARAM_STRUCT));
    size = GetHdRecordParamFromNV(pHDRecParam);
    if (size != sizeof(AUDIO_HD_RECORD_PARAM_STRUCT))
    {
        ALOGD("ULCustHDRecParamFromNV Up load from NVRAM fail, structure size=%d,read_size=%d", sizeof(AUDIO_HD_RECORD_PARAM_STRUCT), size);
        if (pHDRecParam) { free(pHDRecParam); }
        pHDRecParam = NULL;
        return ACHFailed;
    }

    if (block == 0)
    {
        pHDRecCustParam->hd_rec_mode_num = pHDRecParam->hd_rec_mode_num;
        pHDRecCustParam->hd_rec_fir_num  = pHDRecParam->hd_rec_fir_num;
        memcpy((void *)pHDRecCustParam->hd_rec_speech_mode_para, (void *)pHDRecParam->hd_rec_speech_mode_para, sizeof(pHDRecParam->hd_rec_speech_mode_para));

        size = 2 * sizeof(pHDRecParam->hd_rec_mode_num) + sizeof(pHDRecParam->hd_rec_speech_mode_para);

        ALOGD("HD Record parameters part 1 ~~~~~~~~~~~~~~~~");
        ALOGD("audio record mode num=%d, fir num=%d", pHDRecCustParam->hd_rec_mode_num, pHDRecCustParam->hd_rec_fir_num);
        for (int i = 0; i < SPC_MAX_NUM_RECORD_SPH_MODE; i++)
        {
            for (int j = 0; j < SPEECH_PARA_NUM; j++)
            {
                ALOGD("HD record speech mode parameters[%d][%d]=%d", i, j, pHDRecCustParam->hd_rec_speech_mode_para[i][j]);
            }
        }
    }
    else if (block == 1)
    {
        ALOGD("HD Record parameters part 2 ~~~~~~~~~~~~~~~~");
#if 0
        size = sizeof(AUDIO_HD_RECORD_PARAM_STRUCT) - 2 * sizeof(pHDRecParam->hd_rec_mode_num) - sizeof(pHDRecParam->hd_rec_speech_mode_para);
#else
        size = sizeof(pHDRecParam->hd_rec_fir) / 2;
#endif
        memcpy(pParam + sizeof(int), (void *)pHDRecParam->hd_rec_fir, size);
    }
    else if (block == 2)
    {
        ALOGD("HD Record parameters part 3 ~~~~~~~~~~~~~~~~");
        // Original code as follow, but to make coverity happy, we will copy per field.
        //size = sizeof(AUDIO_HD_RECORD_PARAM_STRUCT) - 2 * sizeof(pHDRecParam->hd_rec_mode_num) - sizeof(pHDRecParam->hd_rec_speech_mode_para) - sizeof(pHDRecParam->hd_rec_fir) / 2;
        //memcpy(pParam + sizeof(int), (void *)pHDRecParam->hd_rec_fir[SPC_MAX_NUM_RECORD_INPUT_FIR / 2], size);

        size = 0;
        // copy half of hd_rec_fir
        char *pTemp = pParam + sizeof(int);
        size_t tempsize = sizeof(pHDRecParam->hd_rec_fir) / 2;
        memcpy (pTemp, pHDRecParam->hd_rec_fir[SPC_MAX_NUM_RECORD_INPUT_FIR / 2], tempsize);
        size += tempsize;

        pTemp += tempsize;
        tempsize = sizeof (pHDRecParam->hd_rec_map_to_fir_for_ch1);
        memcpy (pTemp, pHDRecParam->hd_rec_map_to_fir_for_ch1, tempsize);
        size += tempsize;

        pTemp += tempsize;
        tempsize = sizeof (pHDRecParam->hd_rec_map_to_fir_for_ch2);
        memcpy (pTemp, pHDRecParam->hd_rec_map_to_fir_for_ch2, tempsize);
        size += tempsize;

        pTemp += tempsize;
        tempsize = sizeof (pHDRecParam->hd_rec_map_to_dev_mode);
        memcpy (pTemp, pHDRecParam->hd_rec_map_to_dev_mode, tempsize);
        size += tempsize;

        pTemp += tempsize;
        tempsize = sizeof (pHDRecParam->hd_rec_map_to_input_src);
        memcpy (pTemp, pHDRecParam->hd_rec_map_to_input_src, tempsize);
        size += tempsize;

        pTemp += tempsize;
        tempsize = sizeof (pHDRecParam->hd_rec_map_to_stereo_flag);
        memcpy (pTemp, pHDRecParam->hd_rec_map_to_stereo_flag, tempsize);
        size += tempsize;
        ALOGD("HD Record parameters part 3 return size = %d", size);
    }
    else
    {
        size = 0;
    }

    *((int *)pParam) = size;

    dataEncode((char *)pParam, size + sizeof(int));
    *len = 2 * (size + sizeof(int));

    if (pHDRecParam) { free(pHDRecParam); }
    pHDRecParam = NULL;
    return ACHSucceeded;
#else
    SLOGW("ULCustHDRecParamFromNV-do not support HD record!!");
    return ACHFailed;
#endif
}

ACHStatus AudioCmdHandler::DLCustHDRecSceTableToNV(char *pParam)
{
    ALOGD("DLCustHDRecSceTableToNV() in");

    if (pParam == NULL)
    {
        return ACHFailed;
    }

#if defined(MTK_AUDIO_HD_REC_SUPPORT)
    int size = 0;
    int dataLen = 0;

    ALOGD("DLCustHDRecSceTableToNV ,HD record scene table size=%d", sizeof(AUDIO_HD_RECORD_SCENE_TABLE_STRUCT));
    size = sizeof(AUDIO_HD_RECORD_SCENE_TABLE_STRUCT) + sizeof(int);
    dataDecode((char *)pParam, size);

    dataLen = *((int *)pParam);
    if (dataLen != sizeof(AUDIO_HD_RECORD_SCENE_TABLE_STRUCT))
    {
        ALOGE("DLCustHDRecSceTableToNV data miss !! dataLen=%d, size=%d", dataLen, sizeof(AUDIO_HD_RECORD_SCENE_TABLE_STRUCT));
        return ACHFailed;
    }

    AUDIO_HD_RECORD_SCENE_TABLE_STRUCT *pHDRecPara = (AUDIO_HD_RECORD_SCENE_TABLE_STRUCT *)(pParam + sizeof(int));
    size = SetHdRecordSceneTableToNV(pHDRecPara);
    if (size != sizeof(AUDIO_HD_RECORD_SCENE_TABLE_STRUCT))
    {
        ALOGD("DLCustHDRecSceTableToNV down load to NVRAM fail, structure size=%d,write_size=%d", sizeof(AUDIO_HD_RECORD_SCENE_TABLE_STRUCT), size);
        return ACHFailed;
    }

    ALOGD("HD Record Scene Table ~~~~~~~~~~~~~~~~");
    ALOGD("audio record scene num=%d, video record scene num=%d", pHDRecPara->num_voice_rec_scenes, pHDRecPara->num_video_rec_scenes);
    for (int i = 0; i < MAX_HD_REC_SCENES; i++)
    {
        for (int j = 0; j < NUM_HD_REC_DEVICE_SOURCE; j++)
        {
            SLOGV("scene_table[%d][%d]=%d", i, j, pHDRecPara->scene_table[i][j]);
        }
    }

    AudioSystem::setParameters(0, String8("UpdateBesRecordParameters=1"));
    return ACHSucceeded;
#else
    SLOGW("DLCustHDRecSceTableToNV-do not support HD record!!");
    return ACHFailed;
#endif
}

ACHStatus AudioCmdHandler::ULCustHDRecSceTableFromNV(char *pParam, int *len)
{
    ALOGD("ULCustHDRecSceTableFromNV() in");

    if (pParam == NULL)
    {
        return ACHFailed;
    }

#if defined(MTK_AUDIO_HD_REC_SUPPORT)
    int size = 0;
    AUDIO_HD_RECORD_SCENE_TABLE_STRUCT *pHDRecPara = (AUDIO_HD_RECORD_SCENE_TABLE_STRUCT *)(pParam + sizeof(int));

    ALOGD("ULCustHDRecSceTableFromNV ,HD record scene table size=%d", sizeof(AUDIO_HD_RECORD_SCENE_TABLE_STRUCT));
    size = GetHdRecordSceneTableFromNV(pHDRecPara);
    if (size != sizeof(AUDIO_HD_RECORD_SCENE_TABLE_STRUCT))
    {
        ALOGD("ULCustHDRecSceTableFromNV Up load from NVRAM fail, structure size=%d,read_size=%d", sizeof(AUDIO_HD_RECORD_SCENE_TABLE_STRUCT), size);
        return ACHFailed;
    }

    ALOGD("HD Record Scene Table ~~~~~~~~~~~~~~~~");
    ALOGD("audio record scene num=%d, video record scene num=%d", pHDRecPara->num_voice_rec_scenes, pHDRecPara->num_video_rec_scenes);
    for (int i = 0; i < MAX_HD_REC_SCENES; i++)
    {
        for (int j = 0; j < NUM_HD_REC_DEVICE_SOURCE; j++)
        {
            SLOGV("scene_table[%d][%d]=%d", i, j, pHDRecPara->scene_table[i][j]);
        }
    }

    *((int *)pParam) = sizeof(AUDIO_HD_RECORD_SCENE_TABLE_STRUCT);

    dataEncode((char *)pParam, sizeof(AUDIO_HD_RECORD_SCENE_TABLE_STRUCT) + sizeof(int));
    *len = 2 * (sizeof(AUDIO_HD_RECORD_SCENE_TABLE_STRUCT) + sizeof(int));

    return ACHSucceeded;
#else
    SLOGW("ULCustHDRecSceTableFromNV-do not support HD record!!");
    return ACHFailed;
#endif
}

ACHStatus AudioCmdHandler::DLCustHDRecHSParamToNV(char *pParam)
{
    ALOGD("DLCustHDRecHSParamToNV() in +");
//#if defined(MTK_AUDIO_HD_REC_SUPPORT)

    if (pParam == NULL)
    {
        return ACHFailed;
    }
#if 0
    int size = 0;
    int dataLen = 0;

    ALOGD("DLCustHDRecHSParamToNV ,48k HD record parameters size=%d", sizeof(AUDIO_HD_RECORD_48K_PARAM_STRUCT));
    size = sizeof(AUDIO_HD_RECORD_48K_PARAM_STRUCT) + sizeof(int);
    dataDecode((char *)pParam, size);

    dataLen = *((int *)pParam);
    if (dataLen != sizeof(AUDIO_HD_RECORD_48K_PARAM_STRUCT))
    {
        ALOGE("DLCustHDRecHSParamToNV data miss !! dataLen=%d, size=%d", dataLen, sizeof(AUDIO_HD_RECORD_48K_PARAM_STRUCT));
        return ACHFailed;
    }

    AUDIO_HD_RECORD_48K_PARAM_STRUCT *pHDRecPara = (AUDIO_HD_RECORD_48K_PARAM_STRUCT *)(pParam + sizeof(int));
    size = SetHdRecord48kParamToNV(pHDRecPara);
    if (size != sizeof(AUDIO_HD_RECORD_48K_PARAM_STRUCT))
    {
        ALOGD("DLCustHDRecHSParamToNV down load to NVRAM fail, structure size=%d,write_size=%d", sizeof(AUDIO_HD_RECORD_48K_PARAM_STRUCT), size);
        return ACHFailed;
    }

    for (int i = 0; i < SPC_MAX_NUM_48K_RECORD_INPUT_FIR; i++)
    {
        for (int j = 0; j < WB_FIR_NUM; j++)
        {
            SLOGV("48k sample rate parameters hd_rec_fir[%d][%d]=%d", i, j, pHDRecPara->hd_rec_fir[i][j]);
        }
    }

    return ACHSucceeded;
#else
    SLOGW("DLCustHDRecHSParamToNV-do not support HD record!!");
    return ACHFailed;
#endif
}

ACHStatus AudioCmdHandler::ULCustHDRecHSParamFromNV(char *pParam, int *len)
{
    ALOGD("ULCustHDRecHSParamFromNV() in +");
//#if defined(MTK_AUDIO_HD_REC_SUPPORT)

    if (pParam == NULL)
    {
        return ACHFailed;
    }
#if 0
    int size = 0;
    AUDIO_HD_RECORD_48K_PARAM_STRUCT *pHDRecPara = (AUDIO_HD_RECORD_48K_PARAM_STRUCT *)(pParam + sizeof(int));

    ALOGD("ULCustHDRecHSParamFromNV ,HD record scene table size=%d", sizeof(AUDIO_HD_RECORD_48K_PARAM_STRUCT));
    size = GetHdRecord48kParamFromNV(pHDRecPara);
    if (size != sizeof(AUDIO_HD_RECORD_48K_PARAM_STRUCT))
    {
        ALOGD("ULCustHDRecHSParamFromNV Up load from NVRAM fail, structure size=%d,read_size=%d", sizeof(AUDIO_HD_RECORD_48K_PARAM_STRUCT), size);
        return ACHFailed;
    }

    for (int i = 0; i < SPC_MAX_NUM_48K_RECORD_INPUT_FIR; i++)
    {
        for (int j = 0; j < WB_FIR_NUM; j++)
        {
            SLOGV("48k sample rate parameters hd_rec_fir[%d][%d]=%d", i, j, pHDRecPara->hd_rec_fir[i][j]);
        }
    }

    *((int *)pParam) = sizeof(AUDIO_HD_RECORD_48K_PARAM_STRUCT);

    dataEncode((char *)pParam, sizeof(AUDIO_HD_RECORD_48K_PARAM_STRUCT) + sizeof(int));
    *len = 2 * (sizeof(AUDIO_HD_RECORD_48K_PARAM_STRUCT) + sizeof(int));

    return ACHSucceeded;
#else
    *len = 0;
    SLOGW("ULCustHDRecHSParamFromNV-do not support HD record!!");
    return ACHFailed;
#endif
}

ACHStatus AudioCmdHandler::HDRecording(int enable, char *pParam)
{
    ALOGD("HDRecording() in +");
    int dataLen = 0;
    ACHStatus ret = ACHSucceeded;
    int size = MAX_FILE_NAME_LEN + sizeof(int);
    char outputFileName[MAX_FILE_NAME_LEN];
    String8 mValue;

    if (enable)
    {
        dataDecode((char *)pParam, size);
        dataLen = *((int *)pParam);
        size = strlen((char *)(pParam + sizeof(int))) + 1;
        if (dataLen != size)
        {
            ALOGE("HDRecording data miss !! dataLen=%d, size=%d", dataLen, size);
            return ACHFailed;
        }

        sprintf(outputFileName, "HDRecVMFileName=%s", (char *)(pParam + sizeof(int)));
        AudioSystem::setParameters(0, String8(outputFileName));
        ALOGD("HDRecording output file name:%s", outputFileName);

        enableHALHDRecTunning(true);

        ret = startRecorder("/sdcard/HDRecordTemp.3gpp", AUDIO_SOURCE_MIC);
        if (ret != ACHSucceeded)
        {
            enableHALHDRecTunning(false);
        }
    }
    else
    {
        enableHALHDRecTunning(false);
        ret = stopRecorder();
    }

    return ret;
}

ACHStatus AudioCmdHandler::getPhoneSupportInfo(unsigned int *supportInfo)
{
    ALOGD("AudioCmdHandler::getPhoneSupportInfo() in");
    *supportInfo = (unsigned int)QueryFeatureSupportInfo();

    ALOGD("AudioCmdHandler::getPhoneSupportInfo() supportInfo=0x%x", *supportInfo);
    return ACHSucceeded;
}

void AudioCmdHandler::enableHALHDRecTunning(bool enbale)
{
    ALOGD("enableHALHDRecTunning in");
    if (enbale)
    {
        AudioSystem::setParameters(0, String8("HDRecTunningEnable=1"));
        m_bHDRecTunning = true;
    }
    else if (m_bHDRecTunning)
    {
        AudioSystem::setParameters(0, String8("HDRecTunningEnable=0"));
        m_bHDRecTunning = false;
    }
}

ACHStatus AudioCmdHandler::DLCustVOIPParamToNV(char *pParam)
{
    ALOGD("DLCustVOIPParamToNV in");

    if (pParam == NULL)
    {
        return ACHFailed;
    }

    int size = 0;
    int dataLen = 0;
    uint32_t supportInfo = QueryFeatureSupportInfo();

    if (supportInfo & 0x40)
    {
        ALOGD("DLCustVOIPParamToNV ,VOIP parameters size=%d", sizeof(AUDIO_VOIP_PARAM_STRUCT));
        size = sizeof(AUDIO_VOIP_PARAM_STRUCT) + sizeof(int);
        dataDecode((char *)pParam, size);

        dataLen = *((int *)pParam);
        if (dataLen != sizeof(AUDIO_VOIP_PARAM_STRUCT))
        {
            ALOGE("DLCustVOIPParamToNV data miss !! dataLen=%d, size=%d", dataLen, sizeof(AUDIO_VOIP_PARAM_STRUCT));
            return ACHFailed;
        }

        AUDIO_VOIP_PARAM_STRUCT *pVOIPPara = (AUDIO_VOIP_PARAM_STRUCT *)(pParam + sizeof(int));
        size = SetAudioVoIPParamToNV(pVOIPPara);
        if (size != sizeof(AUDIO_VOIP_PARAM_STRUCT))
        {
            ALOGD("DLCustVOIPParamToNV down load to NVRAM fail, structure size=%d,write_size=%d", sizeof(AUDIO_VOIP_PARAM_STRUCT), size);
            return ACHFailed;
        }

        for (int i = 0; i < SPEECH_COMMON_NUM; i++)
        {
            SLOGV("VOIP parameters speech_common_para[%d]=%d", i, pVOIPPara->speech_common_para[i]);
        }

        for (int i = 0; i < VOIP_INDEX_NUM; i++)
        {
            for (int j = 0; j < SPEECH_PARA_NUM; j++)
            {
                SLOGV("VOIP parameters speech_mode_para[%d][%d]=%d", i, j, pVOIPPara->speech_mode_para[i][j]);
            }
        }

        for (int i = 0; i < WB_FIR_NUM; i++)
        {
            SLOGV("VOIP parameters in_fir[0][%d]=%d", i, pVOIPPara->in_fir[0][i]);
            SLOGV("VOIP parameters out_fir[0][%d]=%d", i, pVOIPPara->out_fir[0][i]);
        }

        AudioSystem::setParameters(0, String8("UpdateBesRecordParameters=1"));
    }
    else
    {
        SLOGW("DLCustVOIPParamToNV - do not support VOIP enhance!!");
        return ACHFailed;
    }
    return ACHSucceeded;
}

ACHStatus AudioCmdHandler::ULCustVOIPParamFromNV(char *pParam, int *len)
{
    ALOGD("ULCustVOIPParamFromNV in");

    if (pParam == NULL)
    {
        return ACHFailed;
    }

    uint32_t supportInfo = QueryFeatureSupportInfo();

    if (supportInfo & 0x40)
    {
        int size = 0;
        AUDIO_VOIP_PARAM_STRUCT *pVOIPPara = (AUDIO_VOIP_PARAM_STRUCT *)(pParam + sizeof(int));

        ALOGD("ULCustVOIPParamFromNV ,VOIP parameters size=%d", sizeof(AUDIO_VOIP_PARAM_STRUCT));
        size = GetAudioVoIPParamFromNV(pVOIPPara);
        if (size != sizeof(AUDIO_VOIP_PARAM_STRUCT))
        {
            ALOGD("ULCustVOIPParamFromNV Up load from NVRAM fail, structure size=%d,read_size=%d", sizeof(AUDIO_VOIP_PARAM_STRUCT), size);
            return ACHFailed;
        }

        for (int i = 0; i < SPEECH_COMMON_NUM; i++)
        {
            SLOGV("VOIP parameters speech_common_para[%d]=%d", i, pVOIPPara->speech_common_para[i]);
        }

        for (int i = 0; i < VOIP_INDEX_NUM; i++)
        {
            for (int j = 0; j < SPEECH_PARA_NUM; j++)
            {
                SLOGV("VOIP parameters speech_mode_para[%d][%d]=%d", i, j, pVOIPPara->speech_mode_para[i][j]);
            }
        }

        for (int i = 0; i < WB_FIR_NUM; i++)
        {
            SLOGV("VOIP parameters in_fir[0][%d]=%d", i, pVOIPPara->in_fir[0][i]);
            SLOGV("VOIP parameters out_fir[0][%d]=%d", i, pVOIPPara->out_fir[0][i]);
        }

        *((int *)pParam) = sizeof(AUDIO_VOIP_PARAM_STRUCT);

        dataEncode((char *)pParam, sizeof(AUDIO_VOIP_PARAM_STRUCT) + sizeof(int));
        *len = 2 * (sizeof(AUDIO_VOIP_PARAM_STRUCT) + sizeof(int));
    }
    else
    {
        SLOGW("ULCustVOIPParamFromNV - do not support VOIP enhance!!");
        return ACHFailed;
    }
    
    return ACHSucceeded;
}

ACHStatus AudioCmdHandler::startRecorder(const char *filePath, int recordAudioSource)
{
    ALOGD("AudioCmdHandler::startRecorder() in");
    int ret = OK;

    if (m_MediaRecorderClient.get() == NULL)
    {
    	ALOGD("new MediaRecorder()");
        m_MediaRecorderClient = new MediaRecorder(String16());
		ALOGD("m_MediaRecorderClient.get() is: 0x%p", (void*)m_MediaRecorderClient.get());
        if (m_pMediaRecorderListenner != NULL)
        {
            m_MediaRecorderClient->setListener(m_pMediaRecorderListenner);
        }
    }
    else if (isRecording())
    {
        stopRecorder();
    }

    ret = m_MediaRecorderClient->setAudioSource(recordAudioSource);
    if (ret != OK)
    {
        m_MediaRecorderClient->reset();
        ALOGE("AudioCmdHandler::startRecorder-Fail to setAudioSource");
        return ACHFailed;
    }

    ret = m_MediaRecorderClient->setOutputFormat(OUTPUT_FORMAT_THREE_GPP);
    if (ret != OK)
    {
        m_MediaRecorderClient->reset();
        ALOGE("AudioCmdHandler::startRecorder-Fail to setOutputFormat");
        return ACHFailed;
    }

    ret = m_MediaRecorderClient->setAudioEncoder(AUDIO_ENCODER_AAC);
    if (ret != OK)
    {
        m_MediaRecorderClient->reset();
        ALOGE("AudioCmdHandler::startRecorder-Fail to setAudioEncoder");
        return ACHFailed;
    }

    //  ret = m_MediaRecorderClient->setOutputFile(filePath);   //for opencore
    ALOGD("AudioCmdHandler::filePath=%s", filePath);
    m_fd = open(filePath, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);
    if (m_fd == -1)
    {
        m_MediaRecorderClient->reset();
        ALOGE("AudioCmdHandler::Create file failed  errno = %d, m_fd =%d", errno, m_fd);
        return ACHFailed;
    }

    ret = m_MediaRecorderClient->setOutputFile(m_fd, 0, 0);
    if (ret != OK)
    {
        m_MediaRecorderClient->reset();
        close(m_fd);
        ALOGE("AudioCmdHandler::startRecorder-Fail to setOutputFile");
        return ACHFailed;
    }

    if (recordAudioSource == Audio_I2S_IN)
    {
        AudioSystem::setParameters(0, String8("HQA_I2SREC=1"));
        ret = m_MediaRecorderClient->setParameters(String8("audio-param-number-of-channels=2"));
        if (ret != OK)
        {
            m_MediaRecorderClient->reset();
            close(m_fd);
            ALOGE("AudioCmdHandler::startRecorder-Fail to set audio-param-number-of-channels");
            return ACHFailed;
        }
    }
    else
    {
        char param1[TEMP_ARRAY_SIZE];
        sprintf(param1, "max-duration=%d", m_RecordMaxDur);
        ret = m_MediaRecorderClient->setParameters(String8(param1));
        if (ret != OK)
        {
            m_MediaRecorderClient->reset();
            close(m_fd);
            ALOGE("AudioCmdHandler::startRecorder-Fail to set max-duration");
            return ACHFailed;
        }

        char param2[TEMP_ARRAY_SIZE];
        sprintf(param2, "audio-param-number-of-channels=%d", m_RecordChns);
        ret = m_MediaRecorderClient->setParameters(String8(param2));
        if (ret != OK)
        {
            m_MediaRecorderClient->reset();
            close(m_fd);
            ALOGE("AudioCmdHandler::startRecorder-Fail to set audio-param-number-of-channels");
            return ACHFailed;
        }

        if (recordAudioSource == Audio_FM_IN)
        {
            AudioSystem::setParameters(0, String8("HQA_FMREC_LINE_IN=1"));
        }
    }

    char param4[TEMP_ARRAY_SIZE];
    sprintf(param4, "audio-param-sampling-rate=%d", m_RecordSampleRate);
    ret = m_MediaRecorderClient->setParameters(String8(param4));
    if (ret != OK)
    {
        m_MediaRecorderClient->reset();
        close(m_fd);
        ALOGE("AudioCmdHandler::startRecorder-Fail to set audio-param-sampling-rate");
        return ACHFailed;
    }

    ret = m_MediaRecorderClient->prepare();
    if (ret != OK)
    {
        m_MediaRecorderClient->reset();
        close(m_fd);
        ALOGE("AudioCmdHandler::startRecorder-Fail to prepare");
        return ACHFailed;
    }

    ret = m_MediaRecorderClient->start();
    if (ret != OK)
    {
        m_MediaRecorderClient->reset();
        close(m_fd);
        ALOGE("AudioCmdHandler::startRecorder-Fail to start");
        return ACHFailed;
    }

    if (recordAudioSource == Audio_I2S_IN)
    {
        ret = startFMAudioPlayer();
        if (ret != ACHSucceeded)
        {
            m_MediaRecorderClient->reset();
            close(m_fd);
            ALOGE("AudioCmdHandler::startRecorder-Fail to startFMAudioPlayer");
            return ACHFailed;
        }
    }

    m_bRecording = true;
    m_RecordAudioSource = (AudioSourceType)recordAudioSource;
    return ACHSucceeded;

}

ACHStatus AudioCmdHandler::stopRecorder()
{
    ALOGD("AudioCmdHandler::stopRecorder() in");

    int ret = OK;
    if (m_MediaRecorderClient.get() == NULL)
    {
        ALOGE("AudioCmdHandler::stopRecorder-have not start recording");
        return ACHFailed;
    }

    if (!isRecording())
    {
        return ACHFailed;
    }

    if (m_RecordAudioSource == Audio_I2S_IN)
    {
        stopFMAudioPlayer();
    }

    //  ret = m_MediaRecorderClient->stop();
    //  if (ret!=OK && ret!=INVALID_OPERATION)
    //      ALOGE("AudioCmdHandler::stopRecorder-fail to stop recorder");

    m_MediaRecorderClient->reset();
    if (m_RecordAudioSource == Audio_I2S_IN)
    {
        AudioSystem::setParameters(0, String8("HQA_I2SREC=0"));
    }
    else if (m_RecordAudioSource == Audio_FM_IN)
    {
        AudioSystem::setParameters(0, String8("HQA_FMREC_LINE_IN=0"));
    }

    m_bRecording = false;
    close(m_fd);
    return ACHSucceeded;
}

ACHStatus AudioCmdHandler::startFMAudioPlayer()
{
    ALOGD("AudioCmdHandler::startFMAudioPlayer() in");

    if (m_FMMediaPlayerClient.get() == NULL)
    {
        m_FMMediaPlayerClient = new MediaPlayer();
    }
    else if (m_FMMediaPlayerClient->isPlaying())
    {
        m_FMMediaPlayerClient->stop();
        m_FMMediaPlayerClient->reset();
    }

	if (m_FMMediaPlayerClient->setDataSource(NULL,"MEDIATEK://MEDIAPLAYER_PLAYERTYPE_FM", 0) != NO_ERROR)
	//if (m_FMMediaPlayerClient->setDataSource("MEDIATEK://MEDIAPLAYER_PLAYERTYPE_FM", 0) != NO_ERROR)
    {
        m_FMMediaPlayerClient->reset();
        ALOGE("AudioCmdHandler::startFMAudioPlayer-fail to create FM Audio player");
        return ACHFailed;
    }

    //    m_MediaPlayerClient->setAudioStreamType(AUDIO_STREAM_MUSIC);
    if (m_FMMediaPlayerClient->prepare() != NO_ERROR)
    {
        m_FMMediaPlayerClient->reset();
        ALOGE("AudioCmdHandler::startFMAudioPlayer-fail to play I2S data, FMAudioPlayer prepare failed");
        return ACHFailed;
    }

    if (m_FMMediaPlayerClient->start() != NO_ERROR)
    {
        m_FMMediaPlayerClient->reset();
        ALOGE("AudioCmdHandler::startFMAudioPlayer-fail to play I2S data, FMAudioPlayer start failed");
        return ACHFailed;
    }

    return ACHSucceeded;
}


ACHStatus AudioCmdHandler::stopFMAudioPlayer()
{
    ALOGD("AudioCmdHandler::stopAudioPlayer() in");

    if (m_FMMediaPlayerClient.get() != NULL && m_FMMediaPlayerClient->isPlaying())
    {
        if (m_FMMediaPlayerClient->stop() != NO_ERROR)
        {
            ALOGE("AudioCmdHandler::stopFMAudioPlayer-fail to stop playing I2S data");
            return ACHFailed;
        }
        m_FMMediaPlayerClient->reset();
        return ACHSucceeded;
    }

    ALOGE("AudioCmdHandler::stopFMAudioPlayer-fail to stop playing I2S data");
    return ACHFailed;
}

status_t AudioCmdHandler::SetAudioCommand(int par1,int par2)
{
    int iPara[2];
    iPara[0] = par1;
    iPara[1] = par2;

    String8 strPara = PrintEncodedString(keySetCmd, sizeof(iPara), iPara);
    int ret = AudioSystem::setParameters(0, strPara);
    if (ret == OK || ret == -38)
        return NO_ERROR;
    else
        return ret;
}

status_t AudioCmdHandler::GetAudioCommand(int par1, int *par2)
{
    String8 returnValue;
    char cmd[8];

    sprintf (cmd, "%d", par1);
    returnValue = AudioSystem::getParameters(0, keyGetCmd + String8(cmd));
    *par2 = atoi (returnValue.string() + keyGetCmd.size());
    ALOGD("%s: returnValue: %s, *par2 = %d", __FUNCTION__, returnValue.string(), *par2);
    return NO_ERROR;
}

status_t AudioCmdHandler::SetAudioData(int par1, size_t len, void *ptr)
{
    ALOGD ("%s in: par1 = %d, len = %d", __FUNCTION__, par1, len);
    size_t sz_in = (sizeof(par1) + sizeof(len) + len);

    unsigned char *buf = new unsigned char[sz_in];
    if (NULL == buf) {
        ALOGE ("Fail to allocate memory !!");
        return NO_MEMORY;
    }
    int *iBuf = (int*)buf;
    *iBuf = par1;
    *(iBuf+1) = len;

    unsigned char *cptr;
    cptr = buf + sizeof(par1) + sizeof(len);
    memcpy(cptr, ptr, len);

    String8 strPara = PrintEncodedString(keySetBuffer, sz_in, buf);
    ALOGD ("%s: strPara = %s", __FUNCTION__, strPara.string());

    delete[] buf;
    int ret = AudioSystem::setParameters(0, strPara);
    ALOGD ("%s: AudioSystem::setParameters ret = %d", __FUNCTION__, ret);
    if (ret == OK || ret == -38)
        return NO_ERROR;
    else
        return ret;
}

status_t AudioCmdHandler::GetAudioData(int par1,size_t len,void *ptr)
{
    int iPara[2];
    iPara[0] = par1;
    iPara[1] = len;

    String8 strPara = PrintEncodedString(keyGetBuffer, sizeof(iPara), iPara);
    String8 returnValue = AudioSystem::getParameters(0, strPara);
    ALOGD ("%s  AudioSystem::getParameters(%s) returnValue = %s",
        __FUNCTION__, strPara.string(), returnValue.string());

    String8 newval; //remove "GetBuffer="
    newval.appendFormat("%s", returnValue.string()+keyGetBuffer.size());
    ALOGD ("%s(), newval = %s", __FUNCTION__, newval.string());

    return GetDecodedData(newval, len, ptr);
}

//*****************Media Record Listener*********************//
RecorderListener::RecorderListener(AudioCmdHandler *pListener) :
    m_pListener(pListener)
{
}

void RecorderListener::notify(int msg, int ext1, int ext2)
{
    ALOGD("AudioCmdHandler::RecorderListener::notify-received message: msg=%d, ext1=%d, ext2=%d", msg, ext1, ext2);
    switch (msg)
    {
        case MEDIA_RECORDER_EVENT_INFO:
            switch (ext1)
            {
                case MEDIA_RECORDER_INFO_MAX_DURATION_REACHED:
                    if (m_pListener != NULL)
                    {
                        m_pListener->enableHALHDRecTunning(false);
                        m_pListener->stopRecorder();
                    }
                    break;
                default:
                    break;
            }
            break;
        case MEDIA_RECORDER_EVENT_ERROR:
            if (m_pListener != NULL)
            {
                m_pListener->enableHALHDRecTunning(false);
                m_pListener->stopRecorder();
            }
            break;
        default:
            break;
    }
}
