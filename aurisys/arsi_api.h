/**
 ******************************************************************************
 * @file    arsi_api.h
 * @author  MTK audio driver team
 * @version V0.10
 * @date    07-September-2015
 * @brief   Aurisys: Auris System
 *          ARSI: AuRisys Software Interface
 *          The standard interface for the integration of processing SWIPs
 ******************************************************************************
 */

#ifndef MTK_ARSI_API_H
#define MTK_ARSI_API_H

#include <stdint.h>


#define MAKE_ARSI_API_VERSION(major, minor) (((uint8_t)(major)) << 8 | ((uint8_t)(minor)))
#define ARSI_API_VERSION MAKE_ARSI_API_VERSION(0, 10)


/*==============================================================================
 *                     typedefs
 *============================================================================*/

typedef enum {
    LIB_UNSUPPORTED  = -1,
    LIB_OK           =  0,
    LIB_ERROR        =  1,
    LIB_NULL_POINTER =  2,
} lib_status_t;


typedef enum {
    TASK_SCENE_PHONE_CALL,
    TASK_SCENE_VOW,
    TASK_SCENE_PLAYBACK_MP3,
    TASK_SCENE_VOICE_ULTRASOUND,
    TASK_SCENE_RECORD,
    TASK_SCENE_VOIP,
    TASK_SCENE_SPEAKER_PROTECTION,
} task_scene_t;


typedef enum {
    TASK_DEVICE_IN_NONE             = 0,
    TASK_DEVICE_IN_PHONE_MIC        = (1 << 0),
    TASK_DEVICE_IN_HEADSET_MIC      = (1 << 1),
    TASK_DEVICE_IN_BLUETOOTH_MIC    = (1 << 2),
} task_device_in_t;


typedef enum {
    TASK_DEVICE_OUT_NONE        = 0,
    TASK_DEVICE_OUT_RECEIVER    = (1 << 0),
    TASK_DEVICE_OUT_SPEAKER     = (1 << 1),
    TASK_DEVICE_OUT_HEADPHONE   = (1 << 2),
    TASK_DEVICE_OUT_BLUETOOTH   = (1 << 3),
} task_device_out_t;


typedef enum {
    BIT_FORMAT_S16_LE = 0,  /* 16-bit signed pcm (2-bytes per channel) */
    BIT_FORMAT_S24_LE,      /* 24-bit signed pcm (4-bytes per channel) */
    BIT_FORMAT_S32_LE,      /* 32-bit signed pcm (4-bytes per channel) */
} bit_format_t;


typedef struct stream_info_t {
    uint16_t device;                /* task_device_in_t OR task_device_out_t */
    uint16_t device_extra_info;     /* reserve */
    uint32_t sample_rate_in;        /* 8000, 16000, 24000, 32000, ... */
    uint32_t sample_rate_out;       /* 8000, 16000, 24000, 32000, ... */
    uint8_t  bit_format_in;         /* bit_format_t */
    uint8_t  bit_format_out;        /* bit_format_t */
    uint8_t  num_channels_in;       /* 1, 2, 3, 4 */
    uint8_t  num_channels_out;      /* 1, 2, 3, 4 */
    int16_t  analog_gain;           /* The unit is 0.25 dB. Ex. 0x0020 = +8.0dB */
    int16_t  digital_gain;          /* The unit is 0.25 dB. Ex. 0xFFFC = -1.0dB */
} stream_info_t;


/** debug log function pointer */
typedef void (*debug_log_fp_t)(const char *message, ...);


typedef struct arsi_task_config_t {
    uint16_t api_version;           /* ex, 0x0120 => ver 1.32 */
    uint16_t vendor_id;             /* ex, 0x0E8D */
    uint8_t  task_scene;            /* task_scene_t */
    uint16_t frame_size_ms;         /* ex, 20ms */
    debug_log_fp_t debug_log;

    stream_info_t stream_uplink;    /* for record & phone call */
    stream_info_t stream_downlink;  /* for playback & phone call */
    union {
        stream_info_t stream_echo_ref;  /* for record & phone call */
        stream_info_t stream_dl_fbk;    /* for playback only */
    };
} arsi_task_config_t;


typedef struct data_buf_t {
    uint32_t memory_size;        /* buffer size (memory) */
    uint32_t data_size;          /* 0 <= data_size <= memory_size */
    void    *p_buffer;           /* memory address */
} data_buf_t;


typedef struct audio_buf_t {
    data_buf_t pcm_data;           /* PCM data */
    uint32_t   sample_rate;        /* 8000, 16000, 24000, 32000, ... */
    uint8_t    bit_format;         /* bit_format_t */
    uint8_t    num_channels;       /* 1, 2, 3, 4 */
} audio_buf_t;


typedef struct string_buf_t {
    uint32_t memory_size;        /* 0 <= string_size < memory_size */
    uint32_t string_size;        /* string_size = strlen(p_string); */
    char    *p_string;
} string_buf_t;



typedef enum {
    PHONE_CALL_BAND_08K = 0,
    PHONE_CALL_BAND_16K = 1,
} call_band_t;


typedef enum {
    PHONE_CALL_NET_2G = 0,
    PHONE_CALL_NET_3G = 1,
    PHONE_CALL_NET_4G = 2,
} call_net_t;


typedef struct extra_call_arg_t {
    uint8_t call_band_type;   /* call_band_t */
    uint8_t call_net_type;    /* call_net_t */
} extra_call_arg_t;


/*==============================================================================
 *                     APIs
 *============================================================================*/

/**
 ******************************************************************************
 *  @brief Query the size of the working buffer
 *
 *  @param p_arsi_task_config the task configure
 *  @param p_working_buf_size the working buffer size.
 *
 *  @return lib_status_t
 ******************************************************************************
 */
lib_status_t arsi_query_working_buf_size(
    const arsi_task_config_t *p_arsi_task_config,
    uint32_t                 *p_working_buf_size);


/**
 ******************************************************************************
 *  @brief Create handler and initialize it
 *
 *  @param p_arsi_task_config the task configure
 *  @param p_param_buf the enhancement parameters and lib related configure settings
 *  @param p_working_buf the allocated buffer and the size is from arsi_create_handler()
 *  @param pp_handler the handler of speech enhancement
 *
 *  @return lib_status_t
 ******************************************************************************
 */
lib_status_t arsi_create_handler(
    const arsi_task_config_t *p_arsi_task_config,
    const data_buf_t         *p_param_buf,
    data_buf_t               *p_working_buf,
    void                    **pp_handler);


/**
 ******************************************************************************
 *  @brief Processing microphone/uplink data
 *
 *  @param p_ul_buf_in the microphone/uplink data to be processed
 *         buffer arrangement: chunks of audio destined for different channels
               => mic1(1 frame sz) + ... + micN (1 frame sz)
 *  @param p_ul_buf_out the processed microphone/uplink data
 *  @param p_aec_buf_in the AEC reference data
 *  @param delay_ms the delay time(ms) for AEC
 *  @param p_handler the handler of speech enhancement
 *  @param arg reserved field
 *
 *  @return lib_status_t
 ******************************************************************************
 */
lib_status_t arsi_process_ul_buf(
    audio_buf_t    *p_ul_buf_in,
    audio_buf_t    *p_ul_buf_out,
    audio_buf_t    *p_aec_buf_in,
    const uint32_t  delay_ms,
    void           *p_handler,
    void           *arg);


/**
 ******************************************************************************
 *  @brief Processing playback/downlink data
 *
 *  @param p_dl_buf_in the playback/downlink data to be Processed
 *  @param p_dl_buf_out the processed playback/downlink data
 *  @param p_handler the handler of speech enhancement
 *  @param arg reserved field
 *
 *  @return lib_status_t
 ******************************************************************************
 */
lib_status_t arsi_process_dl_buf(
    audio_buf_t    *p_dl_buf_in,
    audio_buf_t    *p_dl_buf_out,
    void           *p_handler,
    void           *arg);


/**
 ******************************************************************************
 *  @brief deinitialize handler and destroy it (no need to free the working buffer)
 *
 *  @param p_handler the handler of speech enhancement
 *
 *  @return lib_status_t
 ******************************************************************************
 */
lib_status_t arsi_destroy_handler(void *p_handler);


/**
 ******************************************************************************
 *  @brief Update task device info
 *
 *  @param p_arsi_task_config the task configure
 *  @param p_param_buf the enhancement parameters and lib related configure settings
 *  @param p_handler the handler of speech enhancement
 *
 *  @return lib_status_t
 ******************************************************************************
 */
lib_status_t arsi_update_device(
    const arsi_task_config_t *p_arsi_task_config,
    const data_buf_t         *p_param_buf,
    void                     *p_handler);


/**
 ******************************************************************************
 *  @brief Update speech enhancement parameters
 *
 *  @param p_arsi_task_config the task configure
 *  @param p_param_buf the enhancement parameters and lib related configure settings
 *  @param p_handler the handler of speech enhancement
 *
 *  @return lib_status_t
 ******************************************************************************
 */
lib_status_t arsi_update_param(
    const arsi_task_config_t *p_arsi_task_config,
    const data_buf_t         *p_param_buf,
    void                     *p_handler);


/**
 ******************************************************************************
 *  @brief Query the buffer size to keep speech enhancement parameters(single mode)
 *         Implemented in HAL, but not in OpenDSP.
 *
 *  @param p_arsi_task_config the task configure
 *  @param platform_name the platform name by "adb shell getprop ro.product.model"
 *  @param param_file_path the speech enhancement param file (fullset)
 *  @param enhancement_mode the speech enhancement mode by apk
 *  @param p_param_buf_size need how much memory size to keep the enhancement
           parameters for the specific device/mode.
 *
 *  @return lib_status_t
 ******************************************************************************
 */
lib_status_t arsi_query_param_buf_size(
    const arsi_task_config_t *p_arsi_task_config,
    const string_buf_t       *platform_name,
    const string_buf_t       *param_file_path,
    const int                 enhancement_mode,
    uint32_t                 *p_param_buf_size);


/**
 ******************************************************************************
 *  @brief Parsing param file to get parameters into p_param_buf(single mode)
 *         Implemented in HAL, but not in OpenDSP.
 *
 *  @param p_arsi_task_config the task configure
 *  @param platform_name the platform name by "adb shell getprop ro.product.model"
 *  @param param_file_path the speech enhancement param file (fullset)
 *  @param enhancement_mode the speech enhancement mode by apk
 *         TODO: add setParameters example here
 *  @param p_param_buf the enhancement parameters for the specific device/mode.
 *
 *  @return lib_status_t
 ******************************************************************************
 */
lib_status_t arsi_parsing_param_file(
    const arsi_task_config_t *p_arsi_task_config,
    const string_buf_t       *platform_name,
    const string_buf_t       *param_file_path,
    const int                 enhancement_mode,
    data_buf_t               *p_param_buf);


/**
 ******************************************************************************
 *  @brief Set value at a specified address
 *
 *  @param addr the specified address
 *  @param value the value to be assigned at the specified address
 *  @param p_handler the handler of speech enhancement
 *
 *  @return lib_status_t
 ******************************************************************************
 */
lib_status_t arsi_set_addr_value(
    const uint32_t addr,
    const uint32_t value,
    void          *p_handler);


/**
 ******************************************************************************
 *  @brief Get value from the specified address
 *
 *  @param addr the specified address
 *  @param p_value the value at the specified address
 *  @param p_handler the handler of speech enhancement
 *
 *  @return lib_status_t
 ******************************************************************************
 */
lib_status_t arsi_get_addr_value(
    const uint32_t addr,
    uint32_t      *p_value,
    void          *p_handler);


/**
 ******************************************************************************
 *  @brief set key_value string to library
 *
 *  @param key_value_pair the "key=value" string
 *  @param p_handler the handler of speech enhancement
 *
 *  @return lib_status_t
 ******************************************************************************
 */
lib_status_t arsi_set_key_value_pair(
    const string_buf_t *key_value_pair,
    void               *p_handler);


/**
 ******************************************************************************
 *  @brief get key_value string from library
 *
 *  @param key_value_pair there is only "key" when input,
           and then library need rewrite "key=value" to key_value_pair
 *  @param p_handler the handler of speech enhancement
 *
 *  @return lib_status_t
 ******************************************************************************
 */
lib_status_t arsi_get_key_value_pair(
    string_buf_t *key_value_pair,
    void         *p_handler);


/**
 ******************************************************************************
 *  @brief set uplink digital gain
 *
 *  @param ul_analog_gain_ref_only uplink PGA gain. For reference only.
 *              The unit is 0.25 dB.
 *              value: 0x0000 => 0.0dB, 0xFFFC = -1.0dB, 0x0020 = +8.0dB
 *  @param ul_digital_gain uplink gain.
 *              The unit is 0.25 dB.
 *              So gain value [0, 120] => 0 to 30dB
 *  @param p_handler the handler of speech enhancement
 *
 *  @return lib_status_t
 ******************************************************************************
 */
lib_status_t arsi_set_ul_digital_gain(
    const int16_t ul_analog_gain_ref_only,
    const int16_t ul_digital_gain,
    void         *p_handler);


/**
 ******************************************************************************
 *  @brief set downlink digital gain
 *
 *  @param dl_analog_gain_ref_only downlink PGA gain. For reference only.
 *              The unit is 0.25 dB.
 *              value: 0x0000 => 0.0dB, 0xFFFC = -1.0dB, 0x0020 = +8.0dB
 *  @param dl_digital_gain downlink gain.
                The unit is 0.25 dB.
 *              So gain value [-256, 0] => -64 to 0 dB
 *  @param p_handler the handler of speech enhancement
 *
 *  @return lib_status_t
 ******************************************************************************
 */
lib_status_t arsi_set_dl_digital_gain(
    const int16_t dl_analog_gain_ref_only,
    const int16_t dl_digital_gain,
    void         *p_handler);


/**
 ******************************************************************************
 *  @brief mute/unmute uplink
 *
 *  @param b_mute_on mute uplink or not.
 *             - true: mute
 *             - false: unmute(default state)
 *  @param p_handler the handler of speech enhancement
 *
 *  @return lib_status_t
 ******************************************************************************
 */
lib_status_t arsi_set_ul_mute(const uint8_t b_mute_on, void *p_handler);


/**
 ******************************************************************************
 *  @brief mute/unmute downlink
 *
 *  @param b_mute_on mute downlink or not.
 *             - true: mute
 *             - false: unmute(default state)
 *  @param p_handler the handler of speech enhancement
 *
 *  @return lib_status_t
 ******************************************************************************
 */
lib_status_t arsi_set_dl_mute(const uint8_t b_mute_on, void *p_handler);


/**
 ******************************************************************************
 *  @brief enable/disable uplink enhancement function
 *
 *  @param b_enhance_on enable uplink speech enhancement or not.
 *             true: enable(default state)
 *             false: disable
 *  @param p_handler the handler of speech enhancement
 *
 *  @return lib_status_t
 ******************************************************************************
 */
lib_status_t arsi_set_ul_enhance(const uint8_t b_enhance_on, void *p_handler);


/**
 ******************************************************************************
 *  @brief enable/disable downlink enhancement function
 *
 *  @param b_enhance_on enable downlink speech enhancement or not.
 *             - true: enable(default state)
 *             - false: disable
 *  @param p_handler the handler of speech enhancement
 *
 *  @return lib_status_t
 ******************************************************************************
 */
lib_status_t arsi_set_dl_enhance(const uint8_t b_enhance_on, void *p_handler);


/**
 ******************************************************************************
 *  @brief set debug log print callback function
 *
 *  @param debug_log log print function pointer
 *
 *  @param p_handler the handler of speech enhancement
 *
 *  @return lib_status_t
 ******************************************************************************
 */
lib_status_t arsi_set_debug_log_fp(const debug_log_fp_t debug_log,
                                   void *p_handler);


#endif // end of MTK_ARSI_API_H

