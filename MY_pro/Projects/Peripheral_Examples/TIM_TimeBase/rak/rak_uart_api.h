#ifndef _wifi_UART_API_H_
#define _wifi_UART_API_H_
#include <libemqtt.h>

/*******************  correlation function ******************/

uint8 WIFI_MODULE_INIT(void);
uint8 wifi_connect_server(void);
uint8 wifi_Send_data(uint8 socket_flag,uint16 dest_Port,uint8 *dest_Ip,uint16 Send_DataLen,uint8 *Send_Data);
int16 wifi_query_fwversion(void);
int16 wifi_set_pwrmode(uint8 powerMode);
int16 wifi_scan_ap(wifi_uScan *uScanFrame);
int16 wifi_set_psk(wifi_uJoin *uJoinFrame);
int16 wifi_set_channel(wifi_uApAdhoc *uApAdhocFrame);
int16 wifi_connect_ap(wifi_uJoin *uJoinFrame);
int16 wifi_set_ApAdhoc_psk(wifi_uApAdhoc *uApAdhocFrame);
int16 wifi_creat_apadhoc(wifi_uApAdhoc *uApAdhocFrame);
int16 wifi_set_ipstatic(wifi_uIpparam *uIpparamFrame);
int16 wifi_set_ipdhcp(wifi_uIpparam *uIpparamFrame);
int16 wifi_query_dns(wifi_uDns *uDnsFrame);
int16 wifi_query_rssi(void);
int16 wifi_wps(void);
int16 wifi_easyconfig(void);
int16 wifi_storeconfig(int8 param_en,config_t* param);
int16 wifi_set_webconfig(webconfig_t* param);
int16 wifi_start_webconfig(void);
int16 wifi_query_ipconfig(void);
int16 wifi_open_socket(uint16 local_Port,uint16 dest_Port,uint8 wifi_SocketCmd,uint8 *dest_Ip);
int16 wifi_query_con_status(void);
int16 wifi_ascii(void);
void wifi_readAsciiDotAddress(int8 *WriteAddr, int8 *ReadAsciiDotAddress);
int16 wifi_open__tcp_socket(char *dest_Ip);
uint8 wifi_Send_mqtt_data(uint8 socket_flag,char *dest_Ip,uint16 Send_DataLen,uint8 *Send_Data);
int init_socket(mqtt_broker_handle_t* broker, int keepalive);
uint8_t send_packet(uint8_t socket_info, const void* buf, unsigned int count);
void init_mqtt(void);

#endif

