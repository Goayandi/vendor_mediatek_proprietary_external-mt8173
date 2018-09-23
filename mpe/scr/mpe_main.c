/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2008
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
***************************************************************/
#ifndef MPE_MAIN_C
#define MPE_MAIN_C

#ifdef __cplusplus
  extern "C" {
#endif

/*****************************************************************************
 * Include
 *****************************************************************************/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <pthread.h>
#include <signal.h>
#include <stdarg.h>
#include <utils/Log.h> // For Debug
#include <cutils/sockets.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <errno.h>
#include <cutils/properties.h>
#include <private/android_filesystem_config.h>
#include "mpe_sys_common.h"
#include "mpe_API.h"
#include "mpe_PDR.h"
#include "SensorListener_API.h"

/*****************************************************************************
 * Define
 *****************************************************************************/
#ifdef DEBUG_LOG

#ifdef LOG_TAG
#undef LOG_TAG
#endif

#define LOG_TAG "MPE_MA"
#define LOG_EN

#ifdef LOG_EN
#define FLPE(...)       MPE_sys_dbg(MPE_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define FLPD(...)       MPE_sys_dbg(MPE_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define FLPW(...)       MPE_sys_dbg(MPE_LOG_WARN, LOG_TAG, __VA_ARGS__)
#else
#define FLPD(...)
#define FLPW(...)
#define FLPE(...)
#endif

#endif

#define BATCH_LOCAL_SIZE 100
#define sensor_axis 3
#define GYRO_RATE 10
#define ACC_RATE 10
#define MAG_RATE 10
#define EPOLL_NUM 1
#define ERR_REMOTE_HANGUP   0x0F01
#define ERR_MNL_DIED        0x0F02
#define DEFAULT_LEAP_SEC    17
#define SDCARD_SWITCH_PROP  "persist.mtklog.log2sd.path"
#define PATH_INTERNAL       "internal_sd"
#define PATH_EXTERNAL       "external_sd"
#define PATH_DEFAULT        "/mnt/sdcard/"
#define PATH_EX             "/mnt/sdcard2/"
#define PATH_SUFFIX         "mtklog/gpsdbglog"
#define LOG_FILE            "/data/misc/"
#define MPEMNL_COMM_SOCK_PATH   "/data/mtk_flp_server"

//socket connecting mnl & mpe
#define MPEMNL_UDP_CLI_PATH    "/data/mpe_mnl/mnl2mpe"
#define MPEMNL_UDP_SRV_PATH    "/data/mpe_mnl/mpe2mnl"

//socket connecting flp_sensor & mpe
#define MPEFLPSENSOR_UDP_CLI_PATH    "/data/mpe_flp/flpsensor2mpe"
#define MPEFLPSENSOR_UDP_SRV_PATH    "/data/mpe_flp/mpe2flpsensor"

//Exception trigger
//#define TRIGGER_AEE

//fifo function
//#define MPE_FIFO_ENABLE

#if 0
//socket connecting flp_gnss & mpe
#define MPEFLPGNSS_UDP_CLI_PATH    "/data/mpe_flp/flpgnss2mpe"
#define MPEFLPGNSS_UDP_SRV_PATH    "/data/mpe_flp/mpe2flpgnss"
#endif

/*****************************************************************************
 * GLobal Variable
 *****************************************************************************/
extern MPE_TASK_T   gMPETasks[MPE_TASKID_END];
static struct sockaddr_un sock_mpemnl_cli_addr;
static struct sockaddr_un sock_mpeflpsensor_cli_addr;
static struct sockaddr_un sock_mpemnl_srv_addr;
static struct sockaddr_un sock_mpeflpsensor_srv_addr;
static volatile int g_ThreadExitMPE = FALSE;
static volatile int g_ThreadExitSocket = FALSE;
static volatile BL SE_listener_mode = MPE_ERROR_MODE;
static BL current_run_mode = -1;
static int mpe_mnl_socket_fd = -1;
static int mpe_mnl_socket_server_fd = -1;
static int mpe_flp_sensor_socket_fd = -1;
static int mpe_flp_sensor_socket_server_fd = -1;
BL isInit = FALSE;
BL isUninit_SE = FALSE;
int isRunning_source = 0;
MNL_location_input_t mnl_in;
mtk_int32 leap_sec = 17;

//Mtklogger function
char mpe_debuglog_file_name[MPE_DEBUG_LOG_FILE_NAME_MAX_LEN];

//fifo function
#ifdef MPE_FIFO_ENABLE
int client_to_server;
char *myfifo = "/data/mnlmpe_server_fifo";
char *myfifo2 = "/data/mnlmpe_client_fifo";
static volatile int pipe_close = 0;
#endif

//PDR/ADR result
float abs_height = 0, rel_height = 0;
volatile mtk_int32 dr_status = 0;
mtk_int32 dr_flag = 0;
mtk_int32 pdr_global[3] = {0};
int sensor_delta = 0;
int64_t last_ttick = 0;

#ifdef TRIGGER_AEE
mtk_uint32 aee_run_cnt = 0;
#endif

#ifdef MPE_BACKGROUND_MONITOR
mtk_uint32 static_count = 0, mpe_run_cnt = 0, monitor_period = 0;
extern double global_time;
extern mtk_uint8 monitor_state;
#endif

//check for baro validity
extern BL isfirst_baro;

/*****************************************************************************
 * Functions
 *****************************************************************************/
extern int update_activity_monitor(IMU* pImu);
extern int MPE_API_position_update_dr(IMU *pImu, int* disp_cm, int dt_us, int *adr, MNL_location_input_t *gps_input);
int MPE_sensor_cb(IMU* data, mtk_uint16 len);
void mpe_mnl_out_set(MNL_location_input_t *mnl_in,MNL_location_output_t *mnl_out );
void check_pipe_handler( int signum );
#ifdef MPE_BACKGROUND_MONITOR
void MPE_run_statistic(MPE_MONITORING_CONV mode);
#endif

/*****************************************************************************
* FUNCTION
*  thread_main_MPE
* DESCRIPTION
*   Main thread of MPE, process REQ & RES to/from socket
* PARAMETERS:
* RETURNS
*****************************************************************************/
void thread_main_MPE(void) {
    BL ret;
    mtk_int32 ret1 = MPE_SUCCESS;
    mtk_uint16 SE_data_cnt = 0;
    int log_rec = 0, rec_loc =0;
    MPE_MSG *msg = NULL, *msg1 = NULL, *msg2 = NULL;
    mtk_int32 run_source = 0, SE_run_rate = 0, gps_sec = 0;
    int MPE_op_mode = 0;
    FLP_location_input_t flp_in = {{0}};
    MNL_location_output_t mnl_out = {{0}};
    FLP_location_output_t flp_out = {{0}};
    IMU* SE_data = NULL;
    float lla_in_acc = 0;

    FLPD("Start of MPE main thread");

    //variables initialization
    memset(&flp_in, 0, sizeof(FLP_location_input_t));
    memset(&mnl_out, 0, sizeof(MNL_location_output_t));
    memset(&flp_out, 0, sizeof(FLP_location_output_t));
    memset(&mnl_in, 0 , sizeof(MNL_location_input_t));

#ifdef MPE_FIFO_ENABLE
    signal(SIGPIPE, check_pipe_handler);
    //client_to_server = open(myfifo, O_WRONLY);
#endif

    while( !g_ThreadExitMPE )
    {
        //recv msg
        ret1 = MPE_sys_msg_recv(MPE_TASKID_MAIN, &msg);
        msg1 = NULL; //reset msg1 content for each run

        if (MPE_NO_MSG_RECEIVED == ret1) {
            FLPD("no msg received");
        } else if (MPE_SUCCESS == ret1) {
            if(msg == NULL) {
                FLPD("msg null \n");
            } else {
                //Debug code, disable SE
                if( msg->type == CMD_START_MPE_REQ ) {
#if 0
                    if(isRunning_source == 0) {
                        MPE_run_statistic(MPE_TIMEOUT_CONV);
                    } else {
                        MPE_run_statistic(MPE_NORMAL_CONV);
                    }
#endif

                    memcpy( &run_source,((mtk_int8 *)msg) + sizeof(MPE_MSG), sizeof(mtk_int32) );
                    memcpy( &SE_run_rate,((mtk_int8 *)msg) + sizeof(MPE_MSG) + sizeof(mtk_int32), sizeof(mtk_int32) );
                    memcpy( &gps_sec,((mtk_int8 *)msg) + sizeof(MPE_MSG)+ 2*sizeof(mtk_int32), sizeof(mtk_int32) );
                    memcpy( &leap_sec,((mtk_int8 *)msg) + sizeof(MPE_MSG) + 3*sizeof(mtk_int32), sizeof(mtk_int32) );
                    FLPD("run rate =%ld, source =%ld, gps_sec =%ld, leap_sec=%ld\n", SE_run_rate,run_source, gps_sec, leap_sec);

                    //send response to client for successful startup
                    msg1 = MPE_Mem_Alloc( (mtk_uint16)(sizeof(MPE_MSG)) );
                    if(msg1 != NULL) {
                        msg1->length = 0;
                        msg1->type = CMD_START_MPE_RES;
                        MPE_sys_socket_send( mpe_mnl_socket_server_fd, msg1,sock_mpemnl_srv_addr );
                        MPE_mem_free(msg1);
                    }
#ifdef MPE_FIFO_ENABLE
                    //reset pipe
                    pipe_close = 0;
                    if( client_to_server == -1) {
                        client_to_server = open(myfifo, O_WRONLY);
                        FLPD("reopen client_to_server 1, %d \n", client_to_server);
                    }
#endif
                    SE_set_gpstime(gps_sec, leap_sec);

                    if(!isInit) {
                        //run setting
                        sensor_delta = 0;
                        SE_listener_mode = SE_sensor_run(MPE_LOC_SOURCE_GNSS);
                        isRunning_source |= run_source;
                        FLPD("SE run = %d, rate =%d", SE_listener_mode, SE_run_rate);

                        if(SE_listener_mode == MPE_RUNTIME_MODE) {//isInit is false for other mode since selistener will not be deinit automatically
                            //Init SensorExplorer+ ksensor lib
                            isInit = TRUE;
                        }
                        //send response to client for successful startup
                        msg1 = MPE_Mem_Alloc( (mtk_uint16)(sizeof(MPE_MSG)) );
                        if(msg1 != NULL) {
                            msg1->length = 0;
                            msg1->type = CMD_START_MPE_RES;
                            MPE_sys_socket_send( mpe_mnl_socket_server_fd, msg1,sock_mpemnl_srv_addr );
                            MPE_mem_free(msg1);
                        }
                    } else {
                        if( !(isRunning_source & run_source)) {//record initialization from multiple sources
                            isRunning_source |= run_source;
                        }
                        FLPD("SE continue run= %d",run_source);
                        SE_MPE_client(MPE_LOC_SOURCE_GNSS, MPE_SET_MODE);

                        //send response to client for successful startup
                        msg1 = MPE_Mem_Alloc( (mtk_uint16)(sizeof(MPE_MSG)) );
                        if(msg1 != NULL) {
                            msg1->length = 0;
                            msg1->type = CMD_START_MPE_RES;
                            MPE_sys_socket_send( mpe_mnl_socket_server_fd, msg1,sock_mpemnl_srv_addr );
                            MPE_mem_free(msg1);
                        }
                    }
                } else if( msg->type == CMD_STOP_MPE_REQ ) {
                    memcpy( &run_source,((mtk_int8 *)msg) +sizeof(MPE_MSG), sizeof(mtk_int32) );
                    FLPD("trigger uninit se, %ld %d", run_source, isRunning_source);

                    isRunning_source &= (~MPE_LOC_SOURCE_GNSS); // remove current client
                    SE_MPE_client(MPE_LOC_SOURCE_GNSS, MPE_RESET_MODE);
                    dr_flag = -1;

#ifdef MPE_FIFO_ENABLE
                    if(client_to_server != -1) {
                        FLPD("close client_to_server %d \n",client_to_server);
                        close(client_to_server);
                        client_to_server = -1;
                    }
#endif
                    //stop ADR
                    if(isRunning_source == 0) {
                        //Stop MPE kernel if both FLP/MNL are inactive
                        isInit = FALSE;
                        last_ttick = 0;
                        ret = SE_sensor_stop(); //full stop ==1, partial stop ==0
                        MPE_Msg_Ring_Buf_Init((MPE_TASKID_E)MPE_TASKID_MAIN);
                        FLPD("SE stop = %d", ret);
                        SE_listener_mode = MPE_ERROR_MODE; //reset listener mode to enable first ADR flag can be sent to mnld upon next startup
                    }
                    //send response to client for successful stop
                    if(!isUninit_SE) { //return RES if uninit not triggered by SE
                        msg1 = MPE_Mem_Alloc( (mtk_uint16)(sizeof(MPE_MSG)) );
                        if(msg1 != NULL) {
                            msg1->length = 0;
                            msg1->type = CMD_STOP_MPE_RES;
                            FLPD("uninit se type, source %d\n",run_source);
                            MPE_sys_socket_send( mpe_mnl_socket_server_fd, msg1,sock_mpemnl_srv_addr );
                            MPE_mem_free(msg1);
                        }
                    } else {
                        isUninit_SE = FALSE;
                        FLPD("uninit se type automatically \n");
                    }
                } else if( msg->type == CMD_SET_MPE_MODE ) {
#ifdef MPE_BACKGROUND_MONITOR
                    //MNL request for background monitor value
                    if(isRunning_source == 0) {
                        MPE_run_statistic(MPE_TIMEOUT_CONV);
                    } else {
                        MPE_run_statistic(MPE_NORMAL_CONV);
                    }

                    //Deinit monitoring if not yet timeout
                    if(isRunning_source & MPE_LOC_SOURCE_GNSS) {
                        isRunning_source &= (~MPE_LOC_SOURCE_GNSS); // remove current client
                        SE_MPE_client(MPE_LOC_SOURCE_GNSS, MPE_RESET_MODE);
                    }
                    dr_flag = -1;

                    //stop ADR
                    if(isRunning_source == 0) {
                        //Stop MPE kernel if both FLP/MNL are inactive
                        isInit = FALSE;
                        ret = SE_sensor_stop(); //full stop ==1, partial stop ==0
                        MPE_Msg_Ring_Buf_Init((MPE_TASKID_E)MPE_TASKID_MAIN);
                        FLPD("SE stop = %d", ret);
                        SE_listener_mode = MPE_ERROR_MODE; //reset listener mode to enable first ADR flag can be sent to mnld upon next startup
                    }
                    if(msg->length < sizeof(mtk_uint32)) {
                        monitor_period = 0;
                    } else {
                        memcpy( &monitor_period,((mtk_int8 *)msg) + sizeof(MPE_MSG), sizeof(mtk_uint32) );
                        if(monitor_period > MPE_MONITOR_TIMEOUT) {
                            monitor_period = MPE_MONITOR_TIMEOUT;
                        }
                    }
                    FLPD("monitor_period = %d\n",monitor_period);
#endif
                } else if( msg->type == CMD_GET_ADR_STATUS_REQ ) {
                    memcpy( &mnl_in,((mtk_int8*)msg)+sizeof(MPE_MSG), msg->length );
                    //Call SE lib to check buffer size & get SE data
                    gps_sec = mnl_in.gps_sec;
                    leap_sec = mnl_in.leap_sec;

                    if(isInit){
                        SE_data_cnt = SE_Acquire_data_cnt(gps_sec, leap_sec, &SE_listener_mode);
                        //FLPD("SE data size  =%d, gps_sec=%ld, leap_sec=%ld, mode =%d \n",SE_data_cnt,gps_sec, leap_sec, SE_listener_mode);

                        //Return DR result
                        mpe_mnl_out_set(&mnl_in, &mnl_out);
                        if(isfirst_baro == 1) {
                            mnl_out.height = -16000;
                        }
                        msg1 = MPE_Mem_Alloc( (mtk_uint16)(sizeof(MPE_MSG)+ sizeof(MNL_location_output_t)) );
                        if(msg1 != NULL) {
                            msg1->length = sizeof(MNL_location_output_t);
                            msg1->type = CMD_SEND_ADR_STATUS_RES;
                            memcpy( ((mtk_int8*)msg1)+sizeof(MPE_MSG), &mnl_out, sizeof(MNL_location_output_t));
                            MPE_sys_socket_send( mpe_mnl_socket_server_fd, msg1,sock_mpemnl_srv_addr );
                            MPE_mem_free(msg1);
                            FLPD("return ADR success, vout=%d, baro %f", mnl_out.vout, mnl_out.height);
                        }
                        /*if(data_file_local != NULL) {
                        lla_in_acc = sqrt((mnl_in.lla_in_acc[0]*mnl_in.lla_in_acc[0] +
                        mnl_in.lla_in_acc[1]*mnl_in.lla_in_acc[1] + mnl_in.lla_in_acc[2]*mnl_in.lla_in_acc[2])/3.0 );
                        fprintf(data_file_local,"& %lf %lf %lf %d %d %d %d %d\n", (double)(mnl_in.LLA[0]),(double)(mnl_in.LLA[1]),(double)(mnl_in.LLA[2]),
                        (int)(mnl_in.vned_in[0]*1e6),(int)(mnl_in.vned_in[1]*1e6),
                        (int)(lla_in_acc*1e6), (int)(mnl_in.ThreeD_vel_1sigma*1e6),(int)(mnl_in.HDOP*1e6));
                        }*/
                    } else {
                        //reinit mpe in case auto-stop mpe is faulty
                        //run setting, do not send response to gos since mnl assume mpe is running
                        SE_set_gpstime(gps_sec,leap_sec);
                        if(SE_listener_mode != MPE_SENSOR_HARDWARE_NA_MODE) {
                            SE_listener_mode = SE_sensor_run(MPE_LOC_SOURCE_GNSS);
                            isRunning_source |= MPE_LOC_SOURCE_GNSS;
                            
                            if(SE_listener_mode == MPE_RUNTIME_MODE) {//isInit is false for other mode since selistener will not be deinit automatically
                                //Init SensorExplorer+ ksensor lib
                                isInit = TRUE;
                                FLPD("SE run = %d, isRunning_source = %d", SE_listener_mode, isRunning_source);
                            }
                        }
                    }
                } else if( msg->type == CMD_GET_PDR_STATUS_REQ ) {
                    memcpy( &flp_in,((mtk_int8*)msg)+sizeof(MPE_MSG), msg->length );
                    //Return DR result
                    msg1 = MPE_Mem_Alloc( (mtk_uint16)(sizeof(MPE_MSG)+ sizeof(FLP_location_output_t)) );
                    flp_out.vout = (float)dr_status;

                    if(msg1 != NULL) {
                        msg1->length = sizeof(FLP_location_output_t);
                        msg1->type = CMD_SEND_PDR_STATUS_RES;
                        memcpy( ((mtk_int8*)msg1)+sizeof(MPE_MSG), &flp_out, sizeof(FLP_location_output_t));
                        MPE_sys_socket_send( mpe_mnl_socket_server_fd, msg1,sock_mpemnl_srv_addr );
                        FLPD("return PDR success");
                        MPE_mem_free(msg1);
                    }
                } else if( msg->type == CMD_SEND_FROM_MNLD ) {
                    memcpy(&log_rec,((mtk_int8*)msg)+sizeof(MPE_MSG),sizeof(int));
                    memcpy(&rec_loc,((mtk_int8*)msg)+sizeof(MPE_MSG)+sizeof(int),sizeof(int));
                    memcpy(mpe_debuglog_file_name,((mtk_int8*)msg)+sizeof(MPE_MSG)+2*sizeof(int),MPE_DEBUG_LOG_FILE_NAME_MAX_LEN);
                    FLPD("log_rec =%d, rec_loc=%d, mpelog_path:%s", log_rec, rec_loc,mpe_debuglog_file_name );
                    SE_mtklogger_check((mtk_int16)log_rec, &mpe_debuglog_file_name, (mtk_int8)rec_loc);
                } else if( msg->type == CMD_DEINIT_MPE_REQ ) {
                    g_ThreadExitMPE = TRUE;
                    ret = SE_sensor_stop();
                    FLPD("SE deinit = %d",ret);
                    pthread_exit(NULL);
                    return;
                } else if(msg->type == CMD_FLP_START_SENSOR) {
                    if(!isInit) {
                        //run setting
                        sensor_delta = 0;
                        SE_listener_mode = SE_sensor_run(MPE_LOC_SOURCE_FLP);
                        isRunning_source |= MPE_LOC_SOURCE_FLP;
                        FLPD("SE run = %d, mode =%d", SE_listener_mode, isRunning_source);

                        if(SE_listener_mode == MPE_RUNTIME_MODE) {//isInit is false for other mode since selistener will not be deinit automatically
                            isInit = TRUE;
                            msg1 = MPE_Mem_Alloc( (mtk_uint16)(sizeof(MPE_MSG)) );
                            if(msg1 != NULL) {
                                msg1->length = 0;
                                msg1->type = CMD_FLP_START_SENSOR_RES;
                                MPE_sys_socket_send( mpe_flp_sensor_socket_server_fd, msg1,sock_mpeflpsensor_srv_addr );
                                MPE_mem_free(msg1);
                            }
                        }
                    } else {
                        if( !(isRunning_source & MPE_LOC_SOURCE_FLP)) {//record initialization from multiple sources
                            isRunning_source |= MPE_LOC_SOURCE_FLP;
                        }
                        FLPD("SE continue run= %d",MPE_LOC_SOURCE_FLP);
                        SE_MPE_client(MPE_LOC_SOURCE_FLP, MPE_SET_MODE);

                        //send response to client for successful startup
                        msg1 = MPE_Mem_Alloc( (mtk_uint16)(sizeof(MPE_MSG)) );
                        if(msg1 != NULL) {
                            msg1->length = 0;
                            msg1->type = CMD_FLP_START_SENSOR_RES;
                            MPE_sys_socket_send( mpe_flp_sensor_socket_server_fd, msg1,sock_mpeflpsensor_srv_addr );
                            MPE_mem_free(msg1);
                        }
                    }
                } else if(msg->type == CMD_FLP_STOP_SENSOR) {
                    isRunning_source &= (~MPE_LOC_SOURCE_FLP); // remove current client
                    SE_MPE_client(MPE_LOC_SOURCE_FLP, MPE_RESET_MODE);

                    //stop PDR
                    if(isRunning_source == 0) {
                        //Stop MPE kernel if both FLP/MNL are inactive
                        isInit = FALSE;
                        ret = SE_sensor_stop(); //full stop ==1, partial stop ==0
                        MPE_Msg_Ring_Buf_Init((MPE_TASKID_E)MPE_TASKID_MAIN);
                        FLPD("SE stop = %d", ret);
                        SE_listener_mode = MPE_ERROR_MODE; //reset listener mode to enable first ADR flag can be sent to mnld upon next startup
                    }
                    //send response to client for successful stop
                    msg1 = MPE_Mem_Alloc( (mtk_uint16)(sizeof(MPE_MSG)) );
                    FLPD("uninit se type, source %d\n",MPE_LOC_SOURCE_FLP);

                    if(msg1 != NULL) {
                        msg1->length = 0;
                        msg1->type = CMD_FLP_STOP_SENSOR_RES;
                        MPE_sys_socket_send( mpe_flp_sensor_socket_server_fd, msg1,sock_mpeflpsensor_srv_addr );
                        MPE_mem_free(msg1);
                    }
                } else if(msg->type == CMD_SCP_SEND_ADR) {
                    if(isRunning_source & MPE_LOC_SOURCE_FLP) {
                        msg1 = MPE_Mem_Alloc( (mtk_uint16)(sizeof(MPE_MSG)+ 3*sizeof(mtk_int32)) );

                        if(msg1 != NULL) {
                            msg1->type = CMD_SCP_SEND_ADR;
                            msg1->length = 3*sizeof(mtk_int32);
                            memcpy( ((mtk_int8*)msg1)+sizeof(MPE_MSG), &pdr_global, 3*sizeof(mtk_int32));
                            FLPD("PDR %d, %d, %d\n", pdr_global[0], pdr_global[1], pdr_global[2]);
                            MPE_sys_socket_send( mpe_flp_sensor_socket_server_fd, msg1,sock_mpeflpsensor_srv_addr );
                            memset(&pdr_global, 0, 3*sizeof(mtk_int32));
                            MPE_mem_free(msg1);
                        }
                    }
                } else if(msg->type == CMD_SCP_SEND_REBOOT) {
                    msg1 = MPE_Mem_Alloc((mtk_uint16)(sizeof(MPE_MSG)));
                    if(msg1 != NULL) {
                        msg1->type = CMD_SCP_SEND_REBOOT;
                        msg1->length = 0;
                        MPE_sys_socket_send( mpe_flp_sensor_socket_server_fd, msg1,sock_mpeflpsensor_srv_addr );
                        FLPD("MPED restart done to flp\n");
                        MPE_mem_free(msg1);
                    }
                    msg2 = MPE_Mem_Alloc((mtk_uint16)(sizeof(MPE_MSG)));
                    if(msg2 != NULL) {
                        msg2->type = CMD_MPED_REBOOT_DONE;
                        msg2->length = 0;
                        MPE_sys_socket_send( mpe_mnl_socket_server_fd, msg2,sock_mpemnl_srv_addr );
                        FLPD("MPED restart done to mnld\n");
                        MPE_mem_free(msg2);
                    }
                } else {
                    FLPD("invalid msg type = %d",msg->type);
                }
                MPE_mem_free(msg);
            }
        }
    }
    return;
}
/*****************************************************************************
* FUNCTION
*  MPE_multiple_socket_connect
* DESCRIPTION
*   build socket connection with other client, curently FLP & MNL
* PARAMETERS:
* RETURNS
*    success/fail
*****************************************************************************/
static int MPE_multiple_socket_connect( void ) {
    char cmd[16], rsp[1024];
    int rsplen=0, ret = MPE_ERROR, res = -1;

    //Connect to MNL FD
    if((mpe_mnl_socket_fd = socket(AF_LOCAL, SOCK_DGRAM, 0)) == -1) {
        FLPD("mpe mnl open udp sock failed\r\n");
    } else {
        FLPD("mpe_mnl_socket_fd =%d",mpe_mnl_socket_fd);
        unlink(MPEMNL_UDP_CLI_PATH);
        memset(&sock_mpemnl_cli_addr, 0, sizeof(sock_mpemnl_cli_addr));
        sock_mpemnl_cli_addr.sun_family = AF_LOCAL;
        strcpy(sock_mpemnl_cli_addr.sun_path, MPEMNL_UDP_CLI_PATH);
        FLPD("server_fd,%d\r\n",mpe_mnl_socket_fd);
        FLPD("server_addr.sun_path,%s\r\n",sock_mpemnl_cli_addr.sun_path);
        FLPD("server_addr.sun_family,%d\r\n",sock_mpemnl_cli_addr.sun_family);

        if(bind(mpe_mnl_socket_fd, (const struct sockaddr *) &sock_mpemnl_cli_addr, sizeof(sock_mpemnl_cli_addr)) < 0) {
            close(mpe_mnl_socket_fd);
            FLPD("mpe mnl server: bind");
            mpe_mnl_socket_fd = -1;
        } else {
            res = chmod(MPEMNL_UDP_CLI_PATH, 0660);// chmod(MPEMNL_UDP_CLI_PATH, 0777);
            chown(MPEMNL_UDP_CLI_PATH, -1, AID_INET);
            if( res < 0 ) {
                FLPD("mpe mnl chmod error:%d", res);
            } else {
                if((mpe_mnl_socket_server_fd = socket(AF_LOCAL, SOCK_DGRAM, 0)) < 0) {
                    FLPD("open server sock failed\r\n");
                    return -1;
                }
                memset(&sock_mpemnl_srv_addr, 0, sizeof(sock_mpemnl_srv_addr));
                sock_mpemnl_srv_addr.sun_family = AF_LOCAL;
                strcpy(sock_mpemnl_srv_addr.sun_path, MPEMNL_UDP_SRV_PATH);
                //Debug print
                FLPD("mpe_mnl_socket_server_fd,%d\r\n",mpe_mnl_socket_server_fd);
                FLPD("sock_mpemnl_srv_addr.sun_path,%s\r\n",sock_mpemnl_srv_addr.sun_path);
                FLPD("sock_mpemnl_srv_addr.sun_family,%d\r\n",sock_mpemnl_srv_addr.sun_family);
            }
        }
    }

    //Connect to FLP_SENSOR FD
    if((mpe_flp_sensor_socket_fd = socket(AF_LOCAL, SOCK_DGRAM, 0)) == -1) {
        FLPD("mpe flp open udp sock failed\r\n");
    } else {
        FLPD("mpe_flp_sensor_socket_fd =%d",mpe_flp_sensor_socket_fd);
        unlink(MPEFLPSENSOR_UDP_CLI_PATH);
        memset(&sock_mpeflpsensor_cli_addr, 0, sizeof(sock_mpeflpsensor_cli_addr));
        sock_mpeflpsensor_cli_addr.sun_family = AF_LOCAL;
        strcpy(sock_mpeflpsensor_cli_addr.sun_path, MPEFLPSENSOR_UDP_CLI_PATH);
        FLPD("server_fd,%d\r\n",mpe_flp_sensor_socket_fd);
        FLPD("server_addr.sun_path,%s\r\n",sock_mpeflpsensor_cli_addr.sun_path);
        FLPD("server_addr.sun_family,%d\r\n",sock_mpeflpsensor_cli_addr.sun_family);

        if(bind(mpe_flp_sensor_socket_fd, (const struct sockaddr *) &sock_mpeflpsensor_cli_addr, sizeof(sock_mpeflpsensor_cli_addr)) < 0) {
            close(mpe_flp_sensor_socket_fd);
            FLPD("mpe flp server: bind");
            mpe_flp_sensor_socket_fd = -1;
        } else {
            res = chmod(MPEFLPSENSOR_UDP_CLI_PATH, 0660);
            chown(MPEFLPSENSOR_UDP_CLI_PATH, -1, AID_INET);
            if( res < 0 ) {
                FLPD("mpe flp chmod error:%d", res);
            } else {
                if((mpe_flp_sensor_socket_server_fd = socket(AF_LOCAL, SOCK_DGRAM, 0)) < 0) {
                    FLPD("open server sock failed\r\n");
                    return -1;
                }
                memset(&sock_mpeflpsensor_srv_addr, 0, sizeof(sock_mpeflpsensor_srv_addr));
                sock_mpeflpsensor_srv_addr.sun_family = AF_LOCAL;
                strcpy(sock_mpeflpsensor_srv_addr.sun_path, MPEFLPSENSOR_UDP_SRV_PATH);
                //Debug print
                FLPD("mpe_flp_sensor_socket_server_fd,%d\r\n",mpe_flp_sensor_socket_server_fd);
                FLPD("sock_mpeflpsensor_srv_addr.sun_path,%s\r\n",sock_mpeflpsensor_srv_addr.sun_path);
                FLPD("sock_mpeflpsensor_srv_addr.sun_family,%d\r\n",sock_mpeflpsensor_srv_addr.sun_family);
            }
        }
    }
    return ret;
}
/*****************************************************************************
* FUNCTION
*  thread_socket_MPE
* DESCRIPTION
*   Main Socket thread of MPE, send/recieve message to/from MNL/FLP or other client
* PARAMETERS:
* RETURNS
*****************************************************************************/
void *thread_socket_MPE(void * arg) {
    MPE_TASK_T* taskp = MPE_find_task(MPE_TASKID_SOCKET);
    mtk_int32 ret = MPE_SUCCESS;
    MPE_MSG *mpe_msg, *reboot_msg;
    char sockbuff[128];
    struct sockaddr_un sock_addr[2];
    int size;/*socklen_t*/
    int active_socket = -1;
    mtk_int32 sock_list[2];

    //Init the socket connection between MPE & FLP + MNL
    MPE_multiple_socket_connect();
    sock_list[0] = mpe_mnl_socket_fd;
    sock_list[1] = mpe_flp_sensor_socket_fd;
    sock_addr[0] = sock_mpemnl_cli_addr;
    sock_addr[1] = sock_mpeflpsensor_cli_addr;
    FLPD("socket fds = %d, %d", sock_list[0], sock_list[1]);

    //Send reboot done to FLP
    reboot_msg = MPE_Mem_Alloc( (mtk_uint16)(sizeof(MPE_MSG)) );
    if(reboot_msg != NULL) {
        reboot_msg->type = CMD_SCP_SEND_REBOOT;
        reboot_msg->length = 0;
        MPE_sys_msg_send(MPE_TASKID_MAIN,reboot_msg);
    }

    while (!g_ThreadExitSocket) {
        active_socket = MPE_sys_scan_socket(&sock_list,2);
        if( active_socket <= 0 ) {
            continue;
        }

        ret = MPE_sys_socket_recv_msg(active_socket, sock_addr, sockbuff);
        if ((ret>0 ) && (!g_ThreadExitSocket)) {
            mpe_msg = MPE_Mem_Alloc((mtk_uint16)ret);
            if(mpe_msg != NULL) {
                memcpy(mpe_msg, &sockbuff[0], ret );
                //FLPD("flp_socket_thread, read msg ok (type,%d,len:%d)\n", mpe_msg->type, mpe_msg->length);
                //Process received message from socket
                MPE_sys_msg_send(MPE_TASKID_MAIN,mpe_msg);
            }
        } else {
            FLPD("flp_socket_thread, read msg fail,exit socket thread\n");
            //read msg fail...
            g_ThreadExitSocket = TRUE;
            // [Remind] Only for Blocking-read-mechanism.
            // Since flp_socket_thread is closed , send MTK_FLP_EXIT_REQ message to service.
            // In abnormal case : This mechanism can avoid zombie process.
            mpe_msg = MPE_Mem_Alloc( sizeof(MPE_MSG) );
            if(mpe_msg != NULL) {
                mpe_msg->type = CMD_DEINIT_MPE_REQ;
                mpe_msg->length = 0;
                FLPD("MPE_socket_thread, send msg to service exit req\n");
                MPE_sys_msg_send(MPE_TASKID_MAIN, mpe_msg);
            }
        }
    }
    //----------------------------------------------------------------
    // Close socket
    //----------------------------------------------------------------
    FLPD("closing socket fd[%d],%02x\r\n",taskp->sockethandle);
    close(taskp->sockethandle);
    taskp->sockethandle = C_INVALID_SOCKET;
    //unlink (MTKMPE_COMM_SOCK_PATH);

    FLPD("MPE_socket_thread, exit\n");
    g_ThreadExitSocket = TRUE;
    pthread_exit(NULL);
    return NULL;
}

/*****************************************************************************
 * FUNCTION
 *  MPE_sensor_cb
 * DESCRIPTION
 *  Callback function register in sensor driver, enabled upon sensor raw data recipient, calculate fusion data & batching to global
 * PARAMETERS
 *  1). sensor data
 *  2). sensor len
 * RETURNS
 *  data: successed or failed
 *****************************************************************************/
int MPE_sensor_cb(IMU* data, mtk_uint16 len) {
    int i=0;
    int ret=0;
    int adr_status = -1;
    int algo_ret=0;
    int delta_t = 0;
    int GYRO_RATE_US = 5300;
    int pdr_local[3] ={0};
    float attitude[3]={0.0f};

    //IMU* g_local_ksensor;
    MPE_SENSOR_FUSION* local_attitude;

    //mutex
    if(data == NULL) {
        FLPD("MPE_sensor data NULL\n");
        return MPE_ERROR;
    }
    local_attitude = MPE_Mem_Alloc(len*sizeof(MPE_SENSOR_FUSION));
    memset(local_attitude,0,len*sizeof(MPE_SENSOR_FUSION));

    if( (data == NULL) || (local_attitude == NULL)) {
        FLPD("allocate sensor cb error\n");
        return MPE_ERROR;
    }

    for( i=0; i<len; i++ ) {
        if(data+i != NULL) {
            if(last_ttick == 0) {
                last_ttick = data[i].input_time_gyro;
                continue;
            }
            mpe_set_fusion_mode(SENSOR_FUSION_MODE_PDR);
#if 0
            if((sensor_delta == 0)) {
                delta_t = GYRO_RATE_US;  //first data point, set ad default value
                last_ttick = data[i].input_time_gyro;
                sensor_delta = delta_t;
            } else {
                if(((data[i].input_time_gyro - last_ttick)/1000.0 < 6000) && 
                    ((data[i].input_time_gyro - last_ttick) > 4000 )) {

                    delta_t = (int)((float)(data[i].input_time_gyro - last_ttick)/1000.f);
                    sensor_delta = delta_t;
                    last_ttick = data[i].input_time_gyro;
                } else {
                    delta_t = sensor_delta;
                    FLPD("delta_t error = %d, %lld, %lld\n", (int)((float)(data[i].input_time_gyro - last_ttick)/1000.f),data[i].input_time_gyro,last_ttick);
                    last_ttick = data[i].input_time_gyro;
                }
            }
#else
            delta_t = (int)((float)(data[i].input_time_gyro - last_ttick)/1000.f);
            sensor_delta = delta_t;
            last_ttick = data[i].input_time_gyro;
#endif

            if(!mpe_update_posture(data+i, delta_t)) {
                algo_ret = MPE_API_position_update_dr(data+i,(int *)&pdr_local,delta_t, (int *)&adr_status, &mnl_in);
            }
            
#ifdef __ANDROID_AXIS__
            local_attitude[i].yaw = attitude[0];
            local_attitude[i].roll = attitude[1];
            local_attitude[i].pitch = attitude[2];
#else
            local_attitude[i].yaw = attitude[0];
            local_attitude[i].roll = attitude[2];
            local_attitude[i].pitch = attitude[1];
#endif
            dr_status = adr_status;
            mpe_update_altitude(data+i, &abs_height, &rel_height );

            pdr_global[0] += pdr_local[0];
            pdr_global[1] += pdr_local[1];
            pdr_global[2] += pdr_local[2];
        } else {
            FLPD("accept null data\n");
        }
    }
    MPE_mem_free(local_attitude);
    return MPE_SUCCESS;
}

void mpe_mnl_out_set(MNL_location_input_t *mnl_in,MNL_location_output_t *mnl_out ) {
    mnl_out->lla_out[0] = mnl_in->lla_in[0];
    mnl_out->lla_out[1] = mnl_in->lla_in[1];
    mnl_out->lla_out[2] = mnl_in->lla_in[2];
    mnl_out->heading_out = 0;
    mnl_out->vout = dr_status;
    mnl_out->height = abs_height;

    if((SE_listener_mode == MPE_RUNTIME_MODE) || (SE_listener_mode == MPE_REPLAY_RF_MODE)) {
        mnl_out->validation_flag = 1;
    } else {
        mnl_out->validation_flag = 0;
    }
}

void mpe_uninit_sensor( void ) {
    mtk_int32 run_source;
    MPE_MSG *mpe_msg;

    mpe_msg = MPE_Mem_Alloc(sizeof(MPE_MSG) + sizeof(mtk_int32));
    if(mpe_msg != NULL) {
        mpe_msg->type = CMD_STOP_MPE_REQ;
        mpe_msg->length = sizeof(mtk_int32)+sizeof(MPE_MSG);
        run_source = MPE_LOC_SOURCE_GNSS;
        memcpy( ((mtk_int8 *)mpe_msg) + sizeof(MPE_MSG),&run_source, sizeof(mtk_int32) );
        isUninit_SE = TRUE;
        FLPD("send uninit request from listener \n");
        MPE_sys_msg_send(MPE_TASKID_MAIN,mpe_msg);
    }
}

void mpe_run_algo( double input_time,  mtk_uint16 data_cnt) {
    BL ret;
    int data_ret=0;
    int valid_flag=0;
    char name[128], str[128];
    IMU *SE_data;
    FILE *adr_file;
    MPE_MSG *flp_msg;
#ifndef MPE_FIFO_ENABLE
    MNL_location_output_t mnl_out = {{0}};
    MPE_MSG *msg1 = NULL;
#endif

    SE_data = MPE_Mem_Alloc(data_cnt*sizeof(IMU));
    memset(SE_data, 0 ,data_cnt*sizeof(IMU));

    if( SE_data != NULL ) {
        ret = SE_Acquire_Data(SE_data,data_cnt);
        data_ret = MPE_sensor_cb(SE_data, data_cnt);

        if(isRunning_source & MPE_LOC_SOURCE_GNSS ) {
            if((SE_listener_mode == MPE_RUNTIME_MODE) || (SE_listener_mode == MPE_REPLAY_RF_MODE)) {
                valid_flag = 1;
            } else {
                valid_flag = 0;
            }

            if(data_ret == MPE_SUCCESS) {
#ifdef MPE_BACKGROUND_MONITOR
	            if(monitor_state && (monitor_period > 0)) {
	                mpe_run_cnt++;
	                if(dr_status == 0 )
	                    static_count++;
	            }
#endif

                if((dr_flag != dr_status) || (current_run_mode != SE_listener_mode) ) {
                    FLPD("mpe_algo,%lf,%d,%d\n",input_time, dr_status, valid_flag);

#ifdef MPE_FIFO_ENABLE
                    sprintf(str, "%lf %d %d", input_time, dr_status, valid_flag);
                    if( client_to_server == -1) {
                        client_to_server = open(myfifo, O_WRONLY);
                        FLPD("reopen client_to_server");
                    }

                    if( (client_to_server != -1)) {
                        if(!pipe_close) {
                            write(client_to_server, str, strlen(str));
                        } else {
                            FLPD("pipe broken \n");
                        }
                    }
#else // mped mnld communication via socket only
                    //Return DR result
                    if(monitor_state == 0) {
                        mpe_mnl_out_set(&mnl_in, &mnl_out);
                        if(isfirst_baro == 1) {
                            mnl_out.height = -16000;
                        }
                        msg1 = MPE_Mem_Alloc( (mtk_uint16)(sizeof(MPE_MSG)+ sizeof(MNL_location_output_t)) );
                        if(msg1 != NULL) {
                            msg1->length = sizeof(MNL_location_output_t);
                            msg1->type = CMD_SEND_ADR_STATUS_RES;
                            memcpy( ((mtk_int8*)msg1)+sizeof(MPE_MSG), &mnl_out, sizeof(MNL_location_output_t));
                            MPE_sys_socket_send( mpe_mnl_socket_server_fd, msg1,sock_mpemnl_srv_addr );
                            MPE_mem_free(msg1);
                            FLPD("return ADR success, vout=%d, baro %f", mnl_out.vout, mnl_out.height);
                        }
                    }
#endif
                    dr_flag = dr_status;
                    current_run_mode = SE_listener_mode;
                }
            }
        }

        if(isRunning_source & MPE_LOC_SOURCE_FLP ) {
            //fake pdr for flp fused
            //pdr_global[0] = 64;
            //pdr_global[1] = 8;
            //pdr_global[2] = 0;
            //FLPD("pdr1 = %d, %d, %d\n", pdr_global[0],pdr_global[1], pdr_global[2]);
            if((pdr_global[0] != 0) || (pdr_global[1] != 0) || (pdr_global[2] != 0)) {
                flp_msg = MPE_Mem_Alloc(sizeof(MPE_MSG));
                flp_msg->type = CMD_SCP_SEND_ADR;
                flp_msg->length = 0;
                MPE_sys_msg_send(MPE_TASKID_MAIN,flp_msg);
            }
        }

        MPE_mem_free(SE_data);
    }
}

#ifdef MPE_FIFO_ENABLE
void check_pipe_handler( int signum ) {
    if(signum == SIGPIPE ) {
        pipe_close = 1;
        FLPD("SIGPIPE recv \n");
    }
}
#endif

#ifdef MPE_BACKGROUND_MONITOR
void MPE_run_statistic(MPE_MONITORING_CONV mode) {
    MPE_MSG *msg1 = NULL;
    double current_time = 0.0, delta_time = 0.0;
    int elapsed_time = 0, static_percentage = 0;

    get_time_stamp(&current_time,leap_sec);

    if(global_time == 0) {
        delta_time = 0;
        static_percentage = 0;
    } else {
        if(mode == MPE_TIMEOUT_CONV) {
            delta_time = monitor_period;
        } else {
            delta_time = current_time - global_time;
        }
        if(mpe_run_cnt>0) {
            static_percentage = (int)(((float)static_count/(float)mpe_run_cnt)*100.f);
        } else {
            static_percentage = 0;
        }
    }

    elapsed_time = (int)delta_time;
    msg1 = MPE_Mem_Alloc( (mtk_uint16)(sizeof(MPE_MSG)+ 2*sizeof(int)) );

    if(msg1 != NULL) {
        msg1->length = 2*sizeof(int);
        msg1->type = CMD_SEND_GPS_TIME_REQ;
        memcpy( ((mtk_int8*)msg1)+sizeof(MPE_MSG), &elapsed_time, sizeof(int));
        memcpy( ((mtk_int8*)msg1)+sizeof(MPE_MSG)+sizeof(int), &static_percentage, sizeof(int));
        MPE_sys_socket_send( mpe_mnl_socket_server_fd, msg1,sock_mpemnl_srv_addr );
        MPE_mem_free(msg1);
        FLPD("mpe statistic: %lf, %d %d %d\n",delta_time, static_percentage, static_count,mpe_run_cnt);
    }
    static_count = 0;
    mpe_run_cnt = 0;
}
#endif

/*****************************************************************************
 * FUNCTION
 *  main
 * DESCRIPTION
 *  main function of MPE Daemon, create upon startup
 * PARAMETERS
 * RETURNS
 *  data: successed or failed
 *****************************************************************************/
int main (int argc ) {
    BL ret = FALSE;
    int res=0;

    FLPD("MPE Daemon main\n");

    //Init tasks & threads
    MPE_task_init();
    ret = MPE_threads_create();
    usleep(1000);
    FLPD("MPE thread create=%d\n",ret);

    if (TRUE == ret) {
        thread_main_MPE();     //hal thread will run in main process
    } else {
        FLPD("thread_main_MPE fail\n");
        g_ThreadExitSocket = TRUE;
        g_ThreadExitMPE =TRUE;
    }
#ifdef MPE_FIFO_ENABLE
    if(client_to_server != -1) {
        close(client_to_server);
    }
#endif
    ret = MPE_task_uninit();
    res = MPE_threads_release();
    FLPD("MPE task & thread release =%d, %d", ret, res );
    return (MPE_SUCCESS);
}

#ifdef __cplusplus
  extern "C" }
#endif

#endif //#ifndef MPE_FUSION_MAIN_C
