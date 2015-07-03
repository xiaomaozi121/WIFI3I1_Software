#ifndef _wifi_UART_API_H_
#define _wifi_UART_API_H_
#include <libemqtt.h>

/*******************  correlation function ******************/

uint8 WIFI_MODULE_INIT(void);
void WIFI_TSIN_AT(void);  //进入AT模式
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

uint8 wifi_Send_mqtt_data(uint8 socket_flag,char *dest_Ip,uint16 Send_DataLen,uint8 *Send_Data);
int init_socket(mqtt_broker_handle_t* broker, int keepalive);
uint8_t send_packet(uint8_t socket_info, const void* buf, unsigned int count);
void init_mqtt(void);

/**********************************************************************/

int16 wifi_reld_cmd(void);
int16 wifi_reld_mudol(void);


int16 wifi_chk_link_cmd(void);
int16 wifi_check_ssid_link(void);

int16 wifi_chk_ipset_cmd(void);   //查询服务器ip参数
int16 wifi_check_serIP(void);
int16 wifi_set_serip_cmd(void);
int16 wifi_set_serip(void);   //设置服务器ip参数

int16 wifi_en_tcplk_cmd(void);
int16 wifi_dis_tcplk_cmd(void);
int16 wifi_en_dis_tcplk(_ON_OFF_VAL_ on_off_flg);

int16 wifi_check_tcplk_cmd(void);
int16 wifi_check_TCPLK(void);


uint16 wifi_json_send_perss(void);
void AfterSend_status_press(void); //发送指令完成后，处理本机状态码
uint16 Json_upload_pro(void);
uint16 Json_paraset_pro(void);
uint16 Json_updata_pro(void);
int16 wifi_tcp_senddat_cmd(uint16 dat_lenth,char sendCmd[]);
int16 wifi_tcp_senddat(void);

uint8 wifi_dat_send(void);

int16 wifi_tcp_recvdat_cmd(char sendCmd[]);
int16 wifi_tcp_recvdat(void);
int16 Recv_CMD_reco(void);
int16 Recv_STATUS_reco(void);
int16 Recv_HCHO_reco(void);
int16 Recv_PM25_reco(void);
int16 Recv_UPD_reco(void);

void BHKS_cmd_status_pro(void);


void wifi_readIPAsciiDotAddressin4Bytes(int8 *WriteAddr, int8 *ReadAsciiDotAddress);

#endif

