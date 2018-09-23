#ifndef __TRUSTZONE_TA_PLAYREADY__
#define __TRUSTZONE_TA_PLAYREADY__


#define TZ_TA_PLAYREADY_UUID         "b25bf100-d276-11e2-8b8b-0800200c9a66"
#define TZCMD_SECURETIME_GET_CURRENT_COUNTER            0x00000000  // used for getting encrypted prtime struct to save file when shutdown and suspend or after THREAD_SAVEFILE_VALUE second
#define TZ_TA_SECURETIME_UUID         "b25bf100-d276-11e2-9c9c-9c9c9c9c9c9c"



#if 1 //// playready 25
#define TZCMD_PLAYREADY_HALBASE 0x00000000


#define TZCTL_TEE_Wrapped_OEM_HAL_IsHalDevCertValidationSupported           ((UINT32)0x6380)
#define TZCTL_TEE_Wrapped_OEM_HAL_IsHalDevCertValidationUnsupported           ((UINT32)0x6381)
#define TZCTL_TEE_Wrapped_Oem_Hal_AllocateRegister         ((UINT32)0x6382)
#define TZCTL_TEE_Wrapped_Oem_Hal_FreeRegister          ((UINT32)0x6383)
#define TZCTL_TEE_Wrapped_Oem_Hal_RegisterCount         ((UINT32)0x6384)
#define TZCTL_TEE_Wrapped_Oem_Hal_GetPreloadedIndex         ((UINT32)0x6385)
#define TZCTL_TEE_Wrapped_Oem_Hal_Initialize          ((UINT32)0x6386)
#define TZCTL_TEE_Wrapped_Oem_Hal_Deinitialize          ((UINT32)0x6387)
#define TZCTL_TEE_Wrapped_Oem_Hal_VerifyMessageSignature          ((UINT32)0x6388)
#define TZCTL_TEE_Wrapped_Oem_Hal_CreateMessageSignature          ((UINT32)0x6389)
#define TZCTL_TEE_Wrapped_Oem_Hal_VerifyOMAC1Signature           ((UINT32)0x638A)
#define TZCTL_TEE_Wrapped_Oem_Hal_CreateOMAC1Signature           ((UINT32)0x638B)
#define TZCTL_TEE_Wrapped_Oem_Hal_EncryptDataBlock         ((UINT32)0x638C)
#define TZCTL_TEE_Wrapped_Oem_Hal_IsDevelopmentPlatform          ((UINT32)0x638D)
#define TZCTL_TEE_Wrapped_Oem_Hal_UnwrapKey        ((UINT32)0x638E)
#define TZCTL_TEE_Wrapped_Oem_Hal_WrapKey          ((UINT32)0x638F)
#define TZCTL_TEE_Wrapped_Oem_Hal_GenerateKey          ((UINT32)0x6390)
#define TZCTL_TEE_Wrapped_Oem_Hal_DecryptContent           ((UINT32)0x6391)
#define TZCTL_TEE_Wrapped_Oem_Hal_DecryptContentOpaque           ((UINT32)0x6392)
#define TZCTL_TEE_Wrapped_Oem_Hal_CreateSampleEncryptionContext          ((UINT32)0x6393)
#define TZCTL_TEE_Wrapped_Oem_Hal_EncryptSampleData           ((UINT32)0x6394)
#define TZCTL_TEE_Wrapped_Oem_Hal_QuerySampleMetadata           ((UINT32)0x6395)
#define TZCTL_TEE_Wrapped_Oem_Hal_DestroySampleEncryptionContext          ((UINT32)0x6396)
#define TZCTL_TEE_Wrapped_Oem_Hal_LoadPlayReadyRevocationInfo           ((UINT32)0x6397)
#define TZCTL_TEE_Wrapped_Oem_Hal_LoadPlayReadyCrl          ((UINT32)0x6398)
#define TZCTL_TEE_Wrapped_Oem_Hal_SetPrivDat          ((UINT32)0x6399)
#define TZCTL_TEE_Wrapped_Oem_Hal_SetZGPrivDat          ((UINT32)0x639a)
#define TZCTL_TEE_Wrapped_Wrapped_Get_EncryptionType     ((UINT32)0x639b)
#define TZCTL_TEE_Wrapped_Wrapped_Get_KeyDataType          ((UINT32)0x639c)

#define TZCTL_TEE_PLAYREADY_SECURESTOP_INITSS                         ((UINT32)0x6360)
#define TZCTL_TEE_PLAYREADY_SECURESTOP_GETSESSION                        ((UINT32)0x6361)
#define TZCTL_TEE_PLAYREADY_SECURESTOP_GETSESSIONBYKID                        ((UINT32)0x6362)
#define TZCTL_TEE_PLAYREADY_SECURESTOP_ADDSESSION                        ((UINT32)0x6363)
#define TZCTL_TEE_PLAYREADY_SECURESTOP_CANCELSESSION                        ((UINT32)0x6364)
#define TZCTL_TEE_PLAYREADY_SECURESTOP_BINDLICENSE                        ((UINT32)0x6365)
#define TZCTL_TEE_PLAYREADY_SECURESTOP_BINDSESSION                        ((UINT32)0x6366)
#define TZCTL_TEE_PLAYREADY_SECURESTOP_REMOVESESSION                        ((UINT32)0x6367)
#define TZCTL_TEE_PLAYREADY_SECURESTOP_RESETSESSION                        ((UINT32)0x6368)
#define TZCTL_TEE_PLAYREADY_SECURESTOP_WRITE_SECURESTOP                        ((UINT32)0x6369)
#define TZCTL_TEE_PLAYREADY_SECURESTOP_INIT_SECURESTOPS                        ((UINT32)0x636a)
#define TZCTL_TEE_PLAYREADY_SECURESTOP_GET_SECURESTOPS                        ((UINT32)0x636b)
#define TZCTL_TEE_PLAYREADY_SECURESTOP_GET_SECURESTOP_IDS                        ((UINT32)0x636c)
#define TZCTL_TEE_PLAYREADY_SECURESTOP_GET_SECURESTOP                        ((UINT32)0x636d)
#define TZCTL_TEE_PLAYREADY_SECURESTOP_UPDATE_SECURESTOP                        ((UINT32)0x636e)
#define TZCTL_TEE_PLAYREADY_SECURESTOP_COMMIT_SECURESTOP                        ((UINT32)0x636f)
#define TZCTL_TEE_PLAYREADY_SECURESTOP_RESET_SECURESTOPS                        ((UINT32)0x6370)

#endif

#define PLAYREADY_PROVISIONED_CERT  1
#define PLAYREADY_PROVISIONED_KEY 2
#define PLAYREADY_PROVISIONED_CLEAR_KEY  3  // for debug
#define PLAYREADY_PROVISIONED_NEED_CERT  4  // for debug


#define TZ_DRM_UI64EQL   1
#define TZ_DRM_UI64LES    2

#define TZ_TOKEN_TOKEN    1
#define TZ_TOKEN_VALUE     2
#define TZ_VALUE_TOKEN     3

#define SUPPORT_MULTIPLE_INSTANCE 1

#define C_SECONDS_IN_ROLLBACK_GRACE_PERIOD 30

/* Data Structure for Playready TA */
/* You should define data structure used both in REE/TEE here
     N/A for Playready TA */

/* Command for Playready TA */
#define TZCMD_PLAYREADY_BASE                             0x00000000
#define TZCMD_PLAYREADY_PROVISIONED_DATA_GET             0x00000001
#define TZCMD_PLAYREADY_ECCP256_KEYPAIR_GEN              0x00000002
#define TZCMD_PLAYREADY_ECCP256_KEY_SET                  0x00000003
#define TZCMD_PLAYREADY_ECDSAP256_SIGN                   0x00000004
#define TZCMD_PLAYREADY_ECCP256_DECRYPT                  0x00000005
#define TZCMD_PLAYREADY_OMAC1_KEY_SET                    0x00000006
#define TZCMD_PLAYREADY_OMAC1_VERIFY                     0x00000007
#define TZCMD_PLAYREADY_OMAC1_SIGN                       0x00000008
#define TZCMD_PLAYREADY_COPYBYTE                         0x00000009
#define TZCMD_PLAYREADY_CONTENTKEY_AESCTR_SET            0x0000000a
#define TZCMD_PLAYREADY_CONTENT_AESCTR_DECRYPT           0x0000000b
#define TZCMD_PLAYREADY_AESECB_KEY_SET                   0x0000000c
#define TZCMD_PLAYREADY_AESECB_ENCRYPT                   0x0000000d
#define TZCMD_PLAYREADY_AESECB_DECRYPT                   0x0000000e
#define TZCMD_PLAYREADY_GET_KFKEY                        0x0000000f
#define TZCMD_PLAYREADY_AESCBC_KEY_SET                   0x00000010
#define TZCMD_PLAYREADY_AESCBC_ENCRYPT                   0x00000011
#define TZCMD_PLAYREADY_AESCBC_DECRYPT                   0x00000012
#define TZCMD_PLAYREADY_HANDLE_CONTENT_AESCTR_DECRYPT    0x00000013
#define TZCMD_PLAYREADY_KEYFILE_DECRYPT                  0x00000014
#define TZCMD_PLAYREADY_KEYFILE_ENCRYPT                  0x00000015
#define TZCMD_PLAYREADY_TOKENTIME_COMPARE          0x00000016
#define TZCMD_PLAYREADY_TOKENTIME_UPDATE                 0x00000017
#define TZCMD_PLAYREADY_MACHINEDATETIME_CHECK            0x00000019
#define TZCMD_PLAYREADY_GET_HWID            0x00000020
#define TZCMD_PLAYREADY_COPY_TO_SECURE_BUFFER            0x00000021


// SUPPORT_PLAYREADY_SECURE_CLOCK
#define TZ_SECURETIME_BIRTHDATE 1392967151
#define TZCMD_PLAYREADY_GET_CURRENT_COUNTER            0x00000030  // used for getting encrypted prtime struct to save file when shutdown and suspend or after THREAD_SAVEFILE_VALUE second
#define TZCMD_PLAYREADY_SET_CURRENT_COUNTER            0x00000031  //  used for set new playready time using the current rtc counter and encrypted saved prtime struct when resume and bootup
#define TZCMD_PLAYREADY_INC_CURRENT_COUNTER            0x00000032  //  used for increase current counter at least PR_TIME_INC_COUNTER secs and no more than PR_TIME_MAX_COUNTER_OFFSET secs
#define TZCMD_PLAYREADY_SET_CURRENT_PRTIME            0x00000033   // used for network time-sync module to sync pr_time
#define PR_TIME_INC_COUNTER 10
#define PR_TIME_MAX_COUNTER_OFFSET 15

#define PR_TIME_FILE_BASE        50000
#define PR_TIME_FILE_ERROR_SIGN  (PR_TIME_FILE_BASE + 1)
#define PR_TIME_FILE_OK_SIGN   (PR_TIME_FILE_BASE + 2)
#define NO_SECURETD_FILE        (PR_TIME_FILE_BASE + 3)
#define PR_TIME_ERROR_SETPRTIME   (PR_TIME_FILE_BASE + 4)

typedef struct _TZ_JG_SECURECLOCK_INFO{
unsigned long long hwcounter;
unsigned long long pr_time;
char signature[8];
}TZ_JG_SECURECLOCK_INFO;

struct TM_PR {
   int     tm_sec;         /* seconds */
   int     tm_min;         /* minutes */
   int     tm_hour;        /* hours */
   int     tm_mday;        /* day of the month */
   int     tm_mon;         /* month */
   int     tm_year;        /* year */
   int     tm_wday;        /* day of the week */
   int     tm_yday;        /* day in the year */
   int     tm_isdst;       /* daylight saving time */

   long int tm_gmtoff;     /* Seconds east of UTC.  */
   const char *tm_zone;    /* Timezone abbreviation.  */

};

//end of SUPPORT_PLAYREADY_SECURE_CLOCK

typedef struct PLAYREADY_IVDATA {
    unsigned long long qwInitializationVector;
    unsigned long long qwBlockOffset;
    unsigned long  bByteOffset;
} PLAYREADY_IVDATA;


typedef struct TZ_PLAYREADY_ENCINFO{
    char                                        role[100];
    unsigned int                         dataSize;                  //total enc buffer size
    unsigned int                         segNum;                  //trunk number
    PLAYREADY_IVDATA          iv[10];                      //IV data for each trunk
    unsigned int                         offset[10];               //pointer to an integer array, each element describe clear data size
    unsigned int                         length[10];              //pointer to an integer array, each element describe enc data size
    unsigned int                      dstHandle;              //true : dstData is a handle; false : dstData is a buffer;
}TZ_PLAYREADY_ENCINFO ;

#ifdef SUPPORT_MULTIPLE_INSTANCE
#ifndef DRM_AES_KEYSIZE_128
#define DRM_AES_KEYSIZE_128 ( 16 ) /* Size ( in bytes ) of a 128 bit key */
#endif

/* Now at least two or more process will use ta_playready.c at same time , drm server and media server */
#define MAX_AESECB_KEYS_INSTANCE   4
#define MAX_OMAC1_KEYS_INSTANCE   4

typedef struct TZ_PLAYREADY_AESECB_KEYS{
    uint32_t handle;   // tee session handle
    char aesecbKey[DRM_AES_KEYSIZE_128];
    uint32_t bProtect;
    uint32_t bInUse;
}TZ_PLAYREADY_AESECB_KEYS;

typedef struct TZ_PLAYREADY_OMAC1_KEYS{
    uint32_t handle;   // tee session handle
    char omac1Key[DRM_AES_KEYSIZE_128];
    uint32_t bProtect;
    uint32_t bInUse;
}TZ_PLAYREADY_OMAC1_KEYS;

#endif

#endif /* __TRUSTZONE_TA_PLAYREADY__ */
