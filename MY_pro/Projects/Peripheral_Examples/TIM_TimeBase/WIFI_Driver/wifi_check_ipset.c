//;****************************************************
//;Company :  BHKS_wifi_demo
//;File Name : wifi_check_ipset
//;Author :    jy_t
//;Create Data : 2014-12-9
//;Last Modified : 
//;Description : bhks userwifi WIFI UART  DRIVER
//;Version : 1.0.1
//;****************************************************
//#include "BSP_Driver.h"
#include "userBSP.h"
#include "wifi_global.h"

/*=============================================================================*/
/**
 * @fn           wifi_check_ipset
 * @brief        UART 
 * @param[in]    none
 * @param[out]   retval
 * @return       errCode
 *               -1 = Module  busy / Timeout
 *               0  = SUCCESS
 * @section description  
 * 
 */
/*=============================================================================*/
int16 wifi_chk_ipset_cmd(void)
{
  int16						retval;
  char sendCmd[16]="";
  strcpy(sendCmd,WIFI_CHK_IPSET_CMD);
  strcat(sendCmd,WIFI_SEND_END);
  retval=USART_OUT(USART1,(char *)sendCmd,strlen(sendCmd));
  return retval;
}

int16 wifi_check_serIP(void)
{
  int8 buf_j ,buf_i ;
   /**/wifi_NETP_Response.contframe.ok_flg  = NETP_UNKNOW;
  do 
  {
    retval=wifi_chk_ipset_cmd();   //查看无线是否连接     retval = 0表示已经发送  非0表示正在读取不能发送
    recv_byte_con = 0;
    if(retval!=0)
    {			 			  
      //return retval;
      return OK_NONE_INFO;
    }	
    while(read_flag == FALSE);
    read_flag = FALSE;
    //if(	wifi_INC_TIMER_1>10) break;			
  /**/}while( strncmp((char *)uCmdRspFrame.uCmdRspBuf,"AT+NETP\n\r+ok",12) != 0);
  wifi_cmd_recv_ok_flg = CMD_RE_OK;  //收到ok，表示命令响应正常，下边识别命令响应信息
  if(strncmp((char *)uCmdRspFrame.uCmdRspBuf,"AT+NETP\n\r+ok=TCP,Client,45102,192.168.1.103",43) == 0)
  //if(strncmp((char *)uCmdRspFrame.uCmdRspBuf,"AT+NETP\n\r+ok=TCP,Client,10106,182.92.164.117",44) == 0)
  {
    wifi_NETP_Response.contframe.ok_flg = SER_IP_SET;
    return OK_INFO;
  }
  else
  {
    buf_j = 0;
    buf_i = 0;
    while('=' != uCmdRspFrame.uCmdRspBuf[buf_j++]);         //find the start of the ssid info
    while((uCmdRspFrame.uCmdRspBuf[buf_j] !='\r')&&(uCmdRspFrame.uCmdRspBuf[buf_j+1] !='\n'))
    {
      
      wifi_NETP_Response.contframe.server_IPinfo[buf_i++] = uCmdRspFrame.uCmdRspBuf[buf_j++];      //Wifi_Wslk_Ssid_Info 记录下ssid的心机，ssid(mac) BHKS(D8:15:D:8D:93:AE)
    }
    wifi_NETP_Response.contframe.ok_flg = UN_SER_IP_SET;
    return OK_NONE_INFO;
  
  }
  
  
    
}