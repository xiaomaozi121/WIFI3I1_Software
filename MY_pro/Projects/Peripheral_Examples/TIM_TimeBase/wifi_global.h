#ifndef _WIFIGLOBAL_H_
#define _WIFIGLOBAL_H_
/*
 * @ Type Definitions
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned char	uint8;
typedef unsigned short	uint16;
typedef unsigned long	uint32;
typedef signed char	    int8;
typedef signed short	int16;
typedef signed long	     int32;


/*********************  Interface Definition  ***********************************/
#define RXBUFSIZE 1500
#define JSON_RECV_LENTH   1024
#define UPDATA_SOFT_LENTH  1024




#define    RESET_PORT             P4
#define    RESET_PIN              2
#define    RESET_PORT_PIN         P42	   //wifi RESET pin


/********************** The AT command definition **********************************/

/********************** 管理命令 **********************************/
#define    wifi_QRY_MAC_CMD                    "at+mac"
#define    wifi_QRY_VERSION_CMD                "at+version"
#define    wifi_PWRMODE_CMD                    "at+pwrmode="	     //@Param: 0：normal 1：sleep 2: deep sleep  3：shut down
#define    wifi_RESET_CMD                      "at+reset"
#define    wifi_ASCII_CMD                      "at+ascii=1"

/********************** 网络操作命令 **********************************/
#define    wifi_SCAN_CMD                   "at+scan="	 
#define    wifi_GET_SCAN_CMD               "at+get_scan="	      //@Param: number 
#define    wifi_PSK_CMD                    "at+psk=" 			  //@Param: 
#define    wifi_CHANNEL_CMD                "at+channel="			  //@Param: 1-13
#define    wifi_AP_CMD                     "at+ap="				  //@Param:	ssid
#define    wifi_ADHOC_CMD                  "at+adhoc="			  //@Param:	ssid
#define    wifi_CONN_CMD                   "at+connect="			  //@Param:	ssid  
#define    wifi_IPSTATIC_CMD               "at+ipstatic="		  //@Param: <ip>,<mask>,<gateway>,<dns server1 >,< dns server2>
#define    wifi_IPDHCP_CMD             	  "at+ipdhcp="			  //@Param: 0 DHCP CLIENT  1 DHCP SERVER
#define    wifi_EASY_CONFIG_CMD            "at+easy_config"
#define    wifi_WPS_CMD                    "at+wps"
#define    wifi_QRY_CON_STATUS_CMD         "at+con_status"
#define    wifi_QRY_IPCONFIG_CMD           "at+ipconfig"
#define    wifi_RSSI_CMD                   "at+rssi"	   
#define    wifi_DNS_CMD                    "at+dns="				  //@Param: domain name
#define    wifi_PING_CMD                   "at+ping="			  //@Param:	<host>, <count>, <size>
#define    wifi_AP_CONFIG_CMD              "at+apconfig="		  //@Param:	<hidden>,<contry code>
#define    wifi_LISTEN_CMD 	          "at+listen="			  //@Param:	<listen interval>
#define    wifi_DIS_AP_CMD                 "at+disc" 	



#define    WIFI_RELD_MUDOL_CMD                 "AT+RELD" 	                   //@Param:	<check if wifimudol linked ap>
#define    WIFI_CHK_LINK_CMD                 "AT+WSLK" 	                   //@Param:	<check if wifimudol linked ap>
#define    WIFI_CHK_IPSET_CMD                 "AT+NETP" 	                   //@Param:	<check if wifimudol linked ap>
#define    WIFI_SET_SIP_CMD                 "AT+NETP" 	                   //@Param:	<check if wifimudol linked ap>
#define    WIFI_TCP_LK_CMD                 "AT+TCPLK"                      //@Param:	<check if socket had build>
#define    WIFI_TCP_DIS_CMD                 "AT+TCPDIS"
#define    WIFI_TCP_SEND_DAT_CMD                 "AT+SEND"
#define    WIFI_TCP_RECV_DAT_CMD                 "AT+RECV"


/********************** Socket操作命令 **********************************/
#define    wifi_LTCP_CMD                   "at+ltcp="			 //@Param: <local_port>     
#define    wifi_TCP_CMD                    "at+tcp="				 //@Param: <dest_ip>,<dest_port>,<module_port>
#define    wifi_LUDP_CMD                   "at+ludp=" 			 //@Param: <local port>
#define    wifi_UDP_CMD                    "at+udp=" 			 //@Param: <dest_ip>,<dest_port>,<local_port>
#define    wifi_MULTICAST_CMD              "at+multicast="	 	 //@Param: <dest_ip>,<dest_port>,<local_port>
#define    wifi_CLS_SOCK_CMD               "at+cls="				 //@Param: <flag>
#define    wifi_SEND_DATA_CMD         	  "at+send_data="		 //@Param: <flag>,<dest_port>,<dest_ip>,<data_length> ,<data_stream>
#define    wifi_RECV_DATA_CMD         	  "at+recv_data=" 		 //@Param: <flag><dest_port><dest_ip><data_length><data_stream>																 //@Param: <socket_status><flag><dest_port><dest_ip>
#define    wifi_UART_CONFIG_CMD			  "at+uartconfig="		 //@Param: <baud rate>,<data bits>,<stop bits>,<parity>,<flow ctrol>

/********************** 参数保存命令 **********************************/
#define    wifi_STORE_CONFIG_CMD           "at+storeconfig"  //"at+storeconfig="	//@Param: param_struct  带参数保存和不带参数保存
#define    wifi_GET_STORE_CONFIG_CMD       "at+get_storeconfig" 
#define    wifi_WEB_CONFIG_CMD             "at+web_config="		 //@Param:	 param_struct
#define    wifi_GET_WEB_CONFIG_CMD         "at+get_webconfig"
#define    wifi_AUTO_CONNECT_CMD           "at+auto_connect"
#define    wifi_START_WEB_CMD              "at+start_web"

/**************************符号*******************************************/
#define    wifi_EQUAL		              "="
#define    wifi_COMMA			      ","
#define    wifi_COLON                         ":"
#define    WIFI_SEND_END		      "\r"
#define    WIFI_CR        		      "\r"
#define    WIFI_LF		              "\n"
#define    WIFI_RECV_END		      "\r\n\r\n"
#define    wifi_ZERO			      "0"
#define    wifi_on_flg                        "on"
#define    wifi_off_flg                       "off"
/**************************云服务器*******************************************/
#define    wifi_SERVER             	  "192.168.1.103"//"182.92.164.117"//"182.92.164.117\",10106,1\r\n""q.thingfabric.com"  //
#define    wifi_SERVER_PORT         		  "45102"//"1883"  //
#define    wifi_LOCAL_PORT_1         		  "15000"  //
#define    wifi_USER_NAME          	  "zhuifeng_tjy"//"aleph201409"  //924789950@qq.com
#define    wifi_USER_PASSWORD       	  "123456"//"al2014eph"  //924789950

#define    wifi_PRO_TCP                   "TCP"
#define    wifi_PRO_UDP                   "UDP"

#define    wifi_MUDL_SERVER                   "Server"
#define    wifi_MUDL_CLIENT                   "Client"




#define wifi_TCP_SOCKET                     0
#define wifi_LTCP_SOCKET                    1 			 //0:TCP 1:LTCP 2:UDP 3:LUDP  4:multicast
#define wifi_UDP_SOCKET                     2
#define wifi_LUDP_SOCKET                    3
#define wifi_MULTI_SOCKET                   4

/** **********超时设置***********/		

#define wifi_TICKS_PER_SECOND   10000 
#define wifi_INC_TIMER_1        wifi_Timer1++
#define wifi_RESET_TIMER1       wifi_Timer1=0

#define wifi_PRAR_ERROR_TIMEOUT     10 * wifi_TICKS_PER_SECOND
#define wifi_POST_DATA_TIMEOUT       2 * wifi_TICKS_PER_SECOND

/**
 * Device Parameters
 */
#define wifi_MAXSOCKETS			        8		// maximum number of open sockets
#define wifi_FRAME_CMD_RSP_LEN           10
#define wifi_MAX_PAYLOAD_SIZE			1472     // maximum recieve data payload size
#define wifi_MAX_PAYLOAD_SEND_SIZE		800       // maximum recieve data payload size
#define wifi_AP_SCANNED_MAX		        10	       // maximum number of scanned acces points


#define wifi_MAX_DOMAIN_NAME_LEN 		42
#define wifi_SSID_LEN			        33	     // maximum length of SSID
#define wifi_BSSID_LEN			        6	     // maximum length of SSID
#define wifi_IP_ADD_LEN                  4
#define wifi_MAC_ADD_LEN                 6

#define wifi_PSK_LEN						65 








   

/*==============================================*/
/*
 * Device Send  Struct
 */
/*==============================================*/
typedef  union{	
	struct{
	uint8                   sndDataCmd[sizeof(wifi_SEND_DATA_CMD)-1]; 
	uint8				    socketFlag[1];
	uint8			   	    destPort[2];			                // Port number of what we are send to
	uint8				    destIpaddr[4];				  
    uint8				    sndDataLen[2];
	}usndDataFramesend;
    uint8	usndDataBuf[sizeof(wifi_SEND_DATA_CMD)-1+9];			
} wifi_usnddata;




/*==============================================*/
/*
 * Main struct which defines all the paramaters of the API library
 * This structure is defined as a variable, the  pointer to, which is passed
 *  toall the functions in the API
 * The struct is initialized by a set of #defines for default values
 *  or for simple use cases
 */
/*==============================================*/
// The scan command argument union/variables

typedef union 
{
  struct {
	   uint8				channel;			    // RF channel to scan, 0=All, 1-13 for 2.5GHz 
	   uint8				ssid[wifi_SSID_LEN];		// uint8[32], ssid to scan for
	  } scanFrameSnd;
  uint8 				uScanBuf[wifi_SSID_LEN + 1];		// byte format to send to the spi interface, 36 bytes
} wifi_uScan;


typedef union {
	struct {
	    uint8			    securityType ;			// 0:不加密  1：加密
		uint8				psk[wifi_PSK_LEN];		// pre-shared key, 32-byte string
		uint8				ssid[wifi_SSID_LEN];	    // ssid of access point to join to, 33-byte string
	} joinFrameSnd;
	uint8					uJoinBuf[wifi_SSID_LEN + wifi_PSK_LEN + 1];			
} wifi_uJoin;

typedef union {
	struct {
	    uint8				nwType;					// 0 sta 1 AP 2 ADHOC
		uint8			    securityType ;			// 0:不加密  1：加密
		uint8				ssid[wifi_SSID_LEN];	    // ssid of access point to join to, 33-byte string
		uint8				apMode;					// ap mode	 是否隐藏
		uint8				ibssApChannel;			// rf channel number for Ad-Hoc (IBSS) mode or  AP mode
	} apAdhocFrameSnd;
	uint8					uApAdhocBuf[wifi_SSID_LEN + 4];			
} wifi_uApAdhoc;

typedef union {
	struct {
		uint8				dhcpMode;		        // 0=dhcp client, 1=ip static
		uint8				ipaddr[4];			// IP address of this module if in manual mode
		uint8				netmask[4];		        // Netmask used if in manual mode
		uint8				gateway[4];			// IP address of default gateway if in manual mode
		uint8               dnssvr1[4];
		uint8               dnssvr2[4];
		uint8				padding;
	} ipparamFrameSnd;
	uint8					uIpparamBuf[22];		
} wifi_uIpparam;


typedef union {
	struct {
		uint8 				DomainName[wifi_MAX_DOMAIN_NAME_LEN];   // 42 bytes, Domain name like www.google.com 
	} dnsFrameSnd;
	uint8					uDnsBuf[wifi_MAX_DOMAIN_NAME_LEN];			       
} wifi_uDns;


typedef union {
	struct {
	    uint8				socketType;					   //0:TCP 1:LTCP 2:UDP 3:LUDP 
		uint8				moduleSocket[2];		       // Our local module port number
		uint8				destSocket[2];			       // Port number of what we are connecting to
		uint8				destIpaddr[4];			       // IP address of socket we are connecting to
	} socketFrameSnd;
	uint8					uSocketBuf[10];			       
} wifi_uSocket;

typedef struct {

	uint8					powerMode;				
	uint8					macAddress[6];				// 6 bytes, mac address
	wifi_uScan				uScanFrame;
	wifi_uJoin				uJoinFrame;
	wifi_uApAdhoc            uApAdhocFrame;    
	wifi_uIpparam		    uIpparamFrame;
	wifi_uDns          		uDnsFrame;
	wifi_uSocket				uSocketFrame;
	wifi_usnddata      		usnddataFrame;	
	uint8             		listeninterval[2];		   //new
} wifi_api;

/**********************************************************************************************************/
typedef union{
	struct {
		uint8                  rspCode[2];  			   			
		uint8	 			   end[2]; 
	} mgmtframe;
	uint8				       mgmtFrameRcv[6];
} wifi_mgmtResponse;




typedef enum 
{
  ON = 1,
  OFF = 2
  
} _ON_OFF_VAL_;

typedef enum 
{
  CMD_RE_OK = 1,
  CMD_RE_NOK = 2
  
} W_CMD_RE_OK_;
typedef enum 
{
  OK_INFO = 1,
  OK_NONE_INFO = 2,
  RESP_ERROR = 3,
  NONE_RESP =4
  
} W_CMD_STATUS_OK_;
typedef enum 
{
  WSLK_UNKNOW = 0,
  WIFI_CONNECT = 1,
  UN_WIFI_CONNECT = 2
  
} W_WSLK_OK_;
typedef enum 
{
  NETP_UNKNOW = 0,
  SER_IP_SET = 1,
  UN_SER_IP_SET = 2
  
} W_NETP_OK_;

typedef enum 
{
  RECV_UN_DONE = 0,
  Recv_num_FLG = 1,
  Json_head_FLG = 2,
  Dev_ID_FLG = 3,
  Soft_V_FLG = 4,
  Cmd_FLG = 5,
  Status_FLG = 6,
  Data_Fram_FLG = 7,//此时程序要识别是上传模式还是配置模式，以选择下一步跳转的位置
  
  Tim_Zone_FLG = 8,
  Tim_Year_FLG = 9,
  Tim_Mon_FLG = 10,
  Tim_Day_FLG = 11,
  Tim_Hour_FLG = 12,
  Tim_Min_FLG = 13,
  Tim_Sec_FLG = 14,
  
  Hcho_Val_FLG = 15,
  PM25_Val_FLG = 16,
  Temp_Val_FLG = 17,
  Humi_Val_FLG = 18,
  
  Hcho_K1_FLG = 15,
  Hcho_K2_FLG = 16,
  Hcho_A_FLG = 17,

  PM25_K1_FLG = 18,
  PM25_K2_FLG = 19,
  PM25_Ref_FLG = 20,
  PM25_A_FLG = 21,
  Rsp_Reco_Done = 22

}_RSP_PRESS_CON_FLG_;

typedef union
{
  struct
  {
    W_WSLK_OK_             ok_flg;  		 // "+ok"	
    uint8		   ssid_info[wifi_SSID_LEN*2];			// 33-byte ssid of scanned access point   // 33-byte ssid of scanned access point
  } contframe;
  uint8	          errorFrameRcv[10];
} _WIFI_WSLK_Resp_;

typedef union
{
  struct
  {
    W_NETP_OK_             ok_flg;  		 // "+ok"	
    uint8		   server_IPinfo[wifi_SSID_LEN*2];			// 33-byte ssid of scanned access point   // 33-byte ssid of scanned access point
  } contframe;
  uint8	          errorFrameRcv[10];
} _WIFI_GET_SER_IP_Resp_;


/****************************************************************************/

typedef union
{
  struct
  {
    uint8             name[9];  		 // "Dev_ID":	
    uint8	      cont[26]; //"JY3I1HHT01v201411201B3C",
  } contframe;
  uint8	          FrameRcv[12];
} _UPLOAD_DAT_DEVID_;

typedef union
{
  struct
  {
    uint8             name[11];  		 // "Soft_Ver":
    uint8	      cont[19]; //"JY3I1HHT20141120",	
  } contframe;
  uint8	          FrameRcv[12];
} _UPLOAD_DAT_SOFVER_;

typedef union
{
  struct
  {
    uint8             name[6];  		 // "CMD":	
    uint8	      cont[6]; //"111",
  } contframe;
  uint8	          FrameRcv[12];
} _UPLOAD_DAT_CMD_;
typedef union
{
  struct
  {
    uint8             name[9];  		//"STATUS":	
    uint8	      cont[6]; //"210",
  } contframe;
  uint8	          FrameRcv[15];
} _UPLOAD_DAT_STATUS_;

typedef union
{
  struct
  {
    uint8             name[10];  		//"Dat_num":	
    uint8	      cont[7]; //"210",
  } contframe;
  uint8	          FrameRcv[17];
}_UPLOAD_SOFT_UPD_NUM_ ;   

typedef union
{
  struct
  {
    uint8             name[7];  		//"Dat":"	
    uint8	      cont[1024]; //210",
  } contframe;
  uint8	          FrameRcv[1031];
}_UPLOAD_SOFT_UPD_CONT_ ;

typedef union
{
  struct
  {
    uint8             name[11];  		 // "Tim_Zone":
    uint8	      cont[8]; //"UTC+8",	
  } contframe;
  uint8	          FrameRcv[19];
} _UPLOAD_DAT_TIMZ_;

typedef union
{
  struct
  {
    uint8             name[7];  		 // "Year":
    uint8	      cont[7]; //"2014",	
  } contframe;
  uint8	          FrameRcv[14];
} _UPLOAD_DAT_YEAR_;

typedef union
{
  struct
  {
    uint8             name[6];  		 // "Mon":
    uint8	      cont[5]; //"11",	
  } contframe;
  uint8	          FrameRcv[11];
} _UPLOAD_DAT_MON_;

typedef union
{
  struct
  {
    uint8             name[6];  		 // "Day":
    uint8	      cont[5]; //"24",
  } contframe;
  uint8	          FrameRcv[11];
} _UPLOAD_DAT_DAY_;

typedef union
{
  struct
  {
    uint8             name[7];  		 // "Hour":
    uint8	      cont[5]; //"14",
  } contframe;
  uint8	          FrameRcv[12];
} _UPLOAD_DAT_HOUR_;

typedef union
{
  struct
  {
    uint8             name[6];  		 // "Min":
    uint8	      cont[5]; //"23",
  } contframe;
  uint8	          FrameRcv[11];
} _UPLOAD_DAT_MIN_;

typedef union
{
  struct
  {
    uint8             name[6];  		 // "Sec":
    uint8	      cont[5]; //"23",
  } contframe;
  uint8	          FrameRcv[11];
} _UPLOAD_DAT_SEC_;



typedef union
{
  struct
  {
    uint8             name[10];  		 // "HCHO_K1":
    uint8	      cont[6]; //"550",
  } contframe;
  uint8	          FrameRcv[16];
} _UPLOAD_DAT_HK1_;

typedef union
{
  struct
  {
    uint8             name[10];  		 // "HCHO_K2":
    uint8	      cont[6]; //"550",
  } contframe;
  uint8	          FrameRcv[16];
} _UPLOAD_DAT_HK2_;

typedef union
{
  struct
  {
    uint8             name[9];  		 // "HCHO_A":
    uint8	      cont[7]; //"5500",
  } contframe;
  uint8	          FrameRcv[16];
} _UPLOAD_DAT_HA_;

typedef union
{
  struct
  {
    uint8             name[9];  		 // "HCHO_V":
    uint8	      cont[6]; //"550",
  } contframe;
  uint8	          FrameRcv[15];
} _UPLOAD_DAT_HV_;

typedef union
{
  struct
  {
    uint8             name[10];  		 // "PM25_K1":
    uint8	      cont[6]; //"550",
  } contframe;
  uint8	          FrameRcv[16];
} _UPLOAD_DAT_PK1_;

typedef union
{
  struct
  {
    uint8             name[10];  		 // "PM25_K2":
    uint8	      cont[6]; //"550",
  } contframe;
  uint8	          pk2FrameRcv[16];
} _UPLOAD_DAT_PK2_;

typedef union
{
  struct
  {
    uint8             name[9];  		 // "PM25_A":
    uint8	      cont[7]; //"5500",
  } contframe;
  uint8	          paFrameRcv[16];
} _UPLOAD_DAT_PA_;

typedef union
{
  struct
  {
    uint8             name[11];  		 // "PM25_Ref":
    uint8	      cont[6]; //"150",
  } contframe;
  uint8	          prFrameRcv[17];
} _UPLOAD_DAT_PR_;

typedef union
{
  struct
  {
    uint8             name[9];  		 // "PM25_V":
    uint8	      cont[6]; //"550",
  } contframe;
  uint8	          FrameRcv[15];
} _UPLOAD_DAT_PV_;

typedef union
{
  struct
  {
    uint8             name[9];  		 // "Temp_V":
    uint8	      cont[6]; //"550",
  } contframe;
  uint8	          FrameRcv[15];
} _UPLOAD_DAT_TEMV_;

typedef union
{
  struct
  {
    uint8             name[9];  		 // "Humi_V":
    uint8	      cont[6]; //"550",
  } contframe;
  uint8	          FrameRcv[15];
} _UPLOAD_DAT_HUMV_;

typedef union
{
  struct
  {
    char                          *Resp_num_p;
    char                          *Json_head_p;
    _UPLOAD_DAT_DEVID_             *Dev_ID_p;
    _UPLOAD_DAT_SOFVER_            *Soft_V_p;
    _UPLOAD_DAT_CMD_               *cmd_p;
    _UPLOAD_DAT_STATUS_            *status_p;
    _UPLOAD_DAT_TIMZ_              *tim_zone_p;
    _UPLOAD_DAT_YEAR_              *year_p;
    _UPLOAD_DAT_MON_               *mon_p;
    _UPLOAD_DAT_DAY_               *day_p;
    _UPLOAD_DAT_HOUR_              *hour_p;
    _UPLOAD_DAT_MIN_               *min_p;
    _UPLOAD_DAT_SEC_               *sec_p;
    _UPLOAD_DAT_HV_                *hcho_v_p;
    _UPLOAD_DAT_PV_                *pm25_v_p;
    _UPLOAD_DAT_TEMV_              *tem_v_p;
    _UPLOAD_DAT_HUMV_              *hum_v_p;
    
  } uploadframe;
  struct
  {
    char                          *Resp_num_p;
    char                          *Json_head_p;
    _UPLOAD_DAT_DEVID_             *Dev_ID_p;
    _UPLOAD_DAT_SOFVER_            *Soft_V_p;
    _UPLOAD_DAT_CMD_               *cmd_p;
    _UPLOAD_DAT_STATUS_            *status_p;
    _UPLOAD_DAT_TIMZ_              *tim_zone_p;
    _UPLOAD_DAT_YEAR_              *year_p;
    _UPLOAD_DAT_MON_               *mon_p;
    _UPLOAD_DAT_DAY_               *day_p;
    _UPLOAD_DAT_HOUR_              *hour_p;
    _UPLOAD_DAT_MIN_               *min_p;
    _UPLOAD_DAT_SEC_               *sec_p;
    _UPLOAD_DAT_HK1_               *hcho_k1_p;
    _UPLOAD_DAT_HK2_               *hcho_k2_p;
    _UPLOAD_DAT_HA_                *hcho_a_p;
    _UPLOAD_DAT_PK1_               *pm25_k1_p;
    _UPLOAD_DAT_PK2_               *pm25_k2_p;
    _UPLOAD_DAT_PA_                *pm25_a_p;
    _UPLOAD_DAT_PR_                *pm25_ref_p;

  } setframe;
  struct
  {
    char                          *Resp_num_p;
    char                          *Json_head_p;
    _UPLOAD_DAT_DEVID_             *Dev_ID_p;
    _UPLOAD_DAT_SOFVER_            *Soft_V_p;
    _UPLOAD_DAT_CMD_               *cmd_p;
    _UPLOAD_DAT_STATUS_            *status_p;
    _UPLOAD_SOFT_UPD_NUM_          *UPD_Dat_num_p;
    _UPLOAD_SOFT_UPD_CONT_         *UPD_Soft_cont_p;    
  } soft_updframe;
  uint8  	          *FrameRcv[20];
} _UPLOAD_DAT_PRINTER_;

typedef enum 
{
  Dev_Dat_Get   = 110,
  Dev_Cal_Start  = 111,
  Dev_Dat_Rget   = 112,
  Get_Dev_Para   = 120,
  Set_Dev_Para    =121,
  Upd_Dev_Soft   = 122,
  CMD_Null          = 0
} _CMD_CODE_;

typedef enum 
{
  Test   = 210,
  Caling  = 211,
  Cal_Done   = 212,
  Set_Done    =221,
  Get_Done   = 222,
  Ask_Tim    = 223,
  Updataing  =231,
  Upd_Done   =232,
  STATUS_Null       =0
} _CSTATUS_CODE_;

typedef union
{
  struct
  {
    uint16                  zone;
    uint16                  year;
    uint16                  mon;  
    uint16                  day;
    uint16                  hour;
    uint16                  min;
    uint16                  sec;
  } frame;
  uint16	          FrameBuf[8];
} _TIME_STRUCT_;

typedef union
{
  struct
  {
    uint16                  k1;
    uint16                  k2;
    uint16                  a;  
    uint16                  ad_v; 
    uint16                  value;
  } frame;
  uint16	          FrameBuf[5];
} _HCHO_STRUCT_;

typedef union
{
  struct
  {
    uint16                  k1;
    uint16                  k2;
    uint16                  a; 
    uint16                  Ref;
    uint16                  ad_v; 
    uint16                  value;
  } frame;
  uint16	          FrameBuf[6];
} _PM25_STRUCT_;

typedef union
{
  struct
  {
    _HCHO_STRUCT_           hcho_param;
    _PM25_STRUCT_           pm25_param; 
    char                   temp_param;
    char                   humi_param;
  } frame;
  uint8	          FrameBuf[6];
} _ALLPARAM_STRUCT_;
/***************************************************************************/

/*
typedef union
{
  struct
  {
    uint8                  cmd_back[strlen(WIFI_CHK_LINK_CMD)+2];   //""
    uint8                  ok_flg[3];  		 // "+ok"	
    //uint8		   ssid[wifi_SSID_LEN];			// 33-byte ssid of scanned access point   // 33-byte ssid of scanned access point
    
    uint8	 	   info[2];               //
  } errorframe;
  uint8	          errorFrameRcv[6];
} wifi_AT_WSLK_Response;

typedef union
{
  struct
  {
    uint8                  cmd_back[strlen(WIFI_CHK_IPSET_CMD)+2];   //"AT"
    uint8                  ok_flg[3];  		 // "+ok"	
    //uint8		   ssid[wifi_SSID_LEN];			// 33-byte ssid of scanned access point   // 33-byte ssid of scanned access point
    
    uint8	 	   info[2];               //
  } errorframe;
  uint8	          errorFrameRcv[6];
} wifi_CHK_IPSET_Response;
*/

typedef union{
	struct {
		uint8                  rspCode[2];
		uint8                  errorCode;  			   			
		uint8	 			   end[2]; 
	} errorframe;
	uint8				       errorFrameRcv[6];
} wifi_errorResponse;


typedef struct {
	uint8					ssid[wifi_SSID_LEN];			// 33-byte ssid of scanned access point
	uint8					bssid[wifi_BSSID_LEN];			// 32-byte bssid of scanned access point
	uint8					rfChannel;				// rf channel to us, 0=scan for all
	uint8					rssiVal;				// absolute value of RSSI
	uint8					securityMode;				// security mode
} wifi_getscanInfo;

typedef  union {	
	struct {
		uint8                  rspCode[2];  			   //0= success	   !0= Failure
		uint8				   scanCount;				// uint8, number of access points found
		uint8	 			   end[2]; 
	} scanframe;
	uint8				      scanFrameRcv[6]  ;			// uint8, socket descriptor, like a file handle, usually 0x00
} wifi_scanResponse;

typedef  union {	
	struct {
		uint8                   rspCode[2]; 
		wifi_getscanInfo		    strScanInfo[wifi_AP_SCANNED_MAX];	// 32 maximum responses from scan command
		uint8	 				end[2]; 
	} getscanframe;
	uint8				      getscanFrameRcv[44]  ;			// uint8, socket descriptor, like a file handle, usually 0x00
} wifi_getscanResponse;


typedef union {
	struct {
		uint8                       rspCode[2];  			   
		uint8				    	status;				      
		uint8	 					end[2]; 
	}qryconFrame;
	uint8				      qryconFrameRcv[6]  ;
} wifi_qryconResponse; 

typedef struct {
	uint8                   rspCode[2]; 			    
	uint8					ssid[wifi_SSID_LEN];			//33-byte ssid of wps connect access point 
	uint8					securityMode;				//security mode
	uint8					psk[wifi_PSK_LEN];			    //65Byte
	uint8                   end[2];						//\r\n
} wifi_wpseasyResponse; 



typedef  union {
	
	struct {
		uint8                   rspCode[2];  	 //0=connected  -2=no connect
		uint8                   rssi;
		uint8	 			    end[2]; 
	} qryrssiframe;
	uint8				      qryrssiFrameRcv[6]  ;			// uint8, socket descriptor, like a file handle, usually 0x00
} wifi_qryrssiResponse; 


typedef  union {	
	struct {
		uint8                       rspCode[2];  			
		uint8				        macAddr[6];				// MAC address of this module
		uint8				        ipAddr[4];				// Configured IP address
		uint8				        netMask[4];				// Configured netmask
		uint8				        gateWay[4];				// Configured default gateway
		uint8				        dns1[4];				// dns1
		uint8				        dns2[4];				// dns2
		uint8	 					end[2];  
	} ipconfigframe;
	uint8				          ipconfigFrameRcv[30];			// uint8, socket descriptor, like a file handle, usually 0x00
} wifi_ipconfigResponse; 


typedef  union{	
	struct {
	   uint8                   rspCode[2];  			   //0= success	   !0= Failure
	   uint8				   domainAddr[4];				//  
	   uint8	 			   end[2]; 
	} qrydnsframe;
	uint8				       qrydnsFrameRcv[8];			// uint8, socket descriptor, like a file handle, usually 0x00
} wifi_qrydnsResponse;


typedef union{
	struct {
		uint8                  rspCode[2];  			   
		uint8				   status;			
		uint8	 			   end[2]; 
	} pingframe;
	uint8				       pingFrameRcv[6];
} wifi_pingResponse;


typedef union {	
	struct {
		uint8                   rspCode[2];                    		// command code 
		char                   socketDescriptordata; //uint8
		uint8	 				end[2];   
	} socketframe;
	uint8				       socketFrameRcv[6]  ;			// uint8, socket descriptor, like a file handle, usually 0x00
} wifi_socketFrameRcv;



typedef  union {
	
	struct {
		uint8                  CMDCode[13]; 		   
		uint8				   socketDescriptor;
		uint8				   destPort[2];
		uint8				   destIp[4];
		uint8				   recDataLen[2];
		uint8                  recvdataBuf[wifi_MAX_PAYLOAD_SIZE];
		uint8	 			   end[2]; 
	} recvdataframe;
	struct {
		uint8                   CMDCode[13]; 		   // 0x01 TCP/UCP 0xFF recieve error 0x80 TCP con	0x81 TCP dis 0x82 0x83
		uint8				    rspCode;//socketstatus;		
		uint8				    socketDescriptor;
		uint8					destPort[2];
		uint8					destIp[4];
		uint8	 			    end[2];
	} recvstatuframe;
	uint8				      socketFrameRcv[wifi_MAX_PAYLOAD_SIZE+24]  ;			// uint8, socket descriptor, like a file handle, usually 0x00
} wifi_recvdataFrame;

typedef union {	
	struct {
		uint8                 rspCode[2]; 
		uint8				  mac[6];				
		uint8	 			  end[2];	 
	} qryMacframe;
	uint8				      qryMacFrameRcv[18];		
} wifi_qryMacFrameRcv;

typedef union {	
	struct {
		uint8                 rspCode[2]; 
		uint8				  hostFwversion[8];				// uint8[10], firmware version text string, x.y.z as 1.3.0
		uint8				  wlanFwversion[6];
		uint8	 			  end[2];	 
	} qryFwversionframe;
	uint8				      qryFwversionFrameRcv[18]  ;			// uint8, socket descriptor, like a file handle, usually 0x00
} wifi_qryFwversionFrameRcv;


typedef struct {
    uint32   addr;
    uint32   mask;
    uint32   gw;
    uint32   dnsrv1;
    uint32   dnsrv2;     
}ip_param_t;

typedef struct {
    uint8   hidden;      //AP隐藏开关
    char    country[2];  //国家代码
}ap_config_t;

typedef struct {
    uint32        feature_bitmap;
    uint8         net_type;    
    uint8         channel;
    uint8         sec_mode;
    uint8         dhcp_mode;
    char          ssid[wifi_SSID_LEN];
    char          psk[wifi_PSK_LEN];
    ip_param_t    ip_param;
    ap_config_t   ap_config;
}config_t;

typedef struct {
    config_t       web_params;    
    char           user_name[17];
    char           user_psk[17];
}webconfig_t; 

typedef union {	
	struct {
		uint8                 rspCode[2]; 
		config_t			  config_params; 
		uint8	 			  end[2];	 
	} getStoreCfgFrame;
	uint8				      getStoreCfgFrameRcv[sizeof(config_t)+4]  ;			// uint8, socket descriptor, like a file handle, usually 0x00
}wifi_getStoreCfgFrame;

typedef union {	
	struct {
		uint8                 rspCode[2]; 
		webconfig_t 		  web_config;
		uint8	 			  end[2];	 
	} getWebCfgFrame;
	uint8				      getWebCfgFrameRcv[sizeof(webconfig_t)+4]  ;			// uint8, socket descriptor, like a file handle, usually 0x00
}wifi_getWebCfgFrame;



typedef union {
	uint8                     		rspCode;                    		 // command code response
	uint8 							bootInfo[19];						 //WIFI开机信息
	wifi_mgmtResponse				mgmtResponse;						 //返回中不带参数的判断区
    wifi_errorResponse				errorResponse;
	wifi_scanResponse          		scanResponse;
	wifi_getscanResponse          	getscanResponse;
	wifi_qryconResponse              qryconResponse;
	wifi_wpseasyResponse             wpseasyResponse;
    wifi_qryrssiResponse             qryrssiResponse;
	wifi_ipconfigResponse            ipconfigResponse;			//同DHCP client命令 和 auto_connect 命令返回
	wifi_qrydnsResponse              qrydnsResponse;
	wifi_pingResponse                pingResponse;
	wifi_qryMacFrameRcv  		    qryMacFrameRcv;
	wifi_qryFwversionFrameRcv  		qryFwversionFrameRcv;
	wifi_socketFrameRcv        		socketFrameRcv;
	wifi_recvdataFrame          		recvdataFrame;
	wifi_getStoreCfgFrame            StoreCfgFrame;
	wifi_getWebCfgFrame			    WebCfgFrame;
	uint8					        uCmdRspBuf[wifi_FRAME_CMD_RSP_LEN + wifi_MAX_PAYLOAD_SIZE];
} wifi_uCmdRsp;



extern volatile uint8 read_flag ;
extern wifi_uCmdRsp	uCmdRspFrame;
extern volatile uint16 UART_data_len;            //串口接收长度 
extern uint16 data_len;
extern wifi_api wifi_strApi;
extern char   TCP_server_socket_num;	     //TCPS 通信socket
extern uint8   retval;	
int8 * wifi_bytes4ToAsciiDotAddr(uint8 *hexAddr,uint8 *strBuf);
void wifi_asciiDotAddressTo4Bytes(uint8 *hexAddr, int8 *asciiDotAddress,  uint8 length);
uint16 wifi_init_struct(wifi_api *ptrStrApi);
#include "wifi_uart_api.h"
#include "wifi_config.h"

#endif

