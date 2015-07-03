#ifndef _WIFIGLOBAL_H_
#define _WIFIGLOBAL_H_
/*
 * @ Type Definitions
 */
typedef unsigned char	uint8;
typedef unsigned short	uint16;
typedef unsigned long	uint32;
typedef signed char	    int8;
typedef signed short	int16;
typedef signed long	     int32;


/*********************  Interface Definition  ***********************************/
#define RXBUFSIZE 1500

#define    RESET_PORT             P4
#define    RESET_PIN              2
#define    RESET_PORT_PIN         P42	   //wifi RESET pin


/********************** The AT command definition **********************************/

/********************** 管理命令 **********************************/
#define    wifi_QRY_MAC_CMD                    "at+mac"
#define    wifi_QRY_VERSION_CMD                "at+version"
#define    wifi_PWRMODE_CMD                    "at+pwrmode="	     //@Param: 0：normal 1：sleep 2: deep sleep  3：shut down
#define    wifi_RESET_CMD                      "at+reset"

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
#define    wifi_LISTEN_CMD 			      "at+listen="			  //@Param:	<listen interval>
#define    wifi_DIS_AP_CMD                 "at+disc" 	


/********************** Socket操作命令 **********************************/
#define    wifi_LTCP_CMD                   "at+ltcp="			 //@Param: <local_port>     
#define    wifi_TCP_CMD                    "at+tcp="				 //@Param: <dest_ip>,<dest_port>,<module_port>
#define    wifi_LUDP_CMD                   "at+ludp=" 			 //@Param: <local port>
#define    wifi_UDP_CMD                    "at+udp=" 			 //@Param: <dest_ip>,<dest_port>,<local_port>
#define    wifi_MULTICAST_CMD              "at+multicast="	 	 //@Param: <dest_ip>,<dest_port>,<local_port>
#define    wifi_CLS_SOCK_CMD               "at+cls="				 //@Param: <flag>
#define    wifi_SEND_DATA_CMD         	  "at+send_data="		 //@Param: <flag>,<dest_port>,<dest_ip>,<data_length> ,<data_stream>
#define    wifi_RECV_DATA_CMD         	  "at+recv_data=" 		 //@Param: <flag><dest_port><dest_ip><data_length><data_stream>
																 //@Param: <socket_status><flag><dest_port><dest_ip>
#define    wifi_UART_CONFIG_CMD			  "at+uartconfig="		 //@Param: <baud rate>,<data bits>,<stop bits>,<parity>,<flow ctrol>

/********************** 参数保存命令 **********************************/
#define    wifi_STORE_CONFIG_CMD           "at+storeconfig"  //"at+storeconfig="	//@Param: param_struct  带参数保存和不带参数保存
#define    wifi_GET_STORE_CONFIG_CMD       "at+get_storeconfig" 
#define    wifi_WEB_CONFIG_CMD             "at+web_config="		 //@Param:	 param_struct
#define    wifi_GET_WEB_CONFIG_CMD         "at+get_webconfig"
#define    wifi_AUTO_CONNECT_CMD           "at+auto_connect"
#define    wifi_START_WEB_CMD              "at+start_web"

/**************************符号*******************************************/
#define    wifi_EQUAL					  "="
#define    wifi_COMMA					  ","
#define    wifi_END						  "\r\n"


#define wifi_TCP_SOCKET                     0
#define wifi_LTCP_SOCKET                    1 			 //0:TCP 1:LTCP 2:UDP 3:LUDP  4:multicast
#define wifi_UDP_SOCKET                     2
#define wifi_LUDP_SOCKET                    3
#define wifi_MULTI_SOCKET                   4

/** **********超时设置***********/		

#define wifi_TICKS_PER_SECOND   100 
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

typedef union {
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


typedef union{
	struct {
		uint8                  rspCode[2];  			   			
		uint8	 			   end[2]; 
	} mgmtframe;
	uint8				       mgmtFrameRcv[6];
} wifi_mgmtResponse;

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
		uint8                   socketDescriptordata; 
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

extern wifi_api wifi_strApi;
int8 * wifi_bytes4ToAsciiDotAddr(uint8 *hexAddr,uint8 *strBuf);
void wifi_asciiDotAddressTo4Bytes(uint8 *hexAddr, int8 *asciiDotAddress,  uint8 length);
uint16 wifi_init_struct(wifi_api *ptrStrApi);
#include "wifi_uart_api.h"
#include "wifi_config.h"
#endif

