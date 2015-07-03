//;****************************************************
//;Company :  BHKS_wifi_demo
//;File Name : wifi_check_link
//;Author :    jy_t
//;Create Data : 2014-12-8
//;Last Modified : 
//;Description : bhks userwifi WIFI UART  DRIVER
//;Version : 1.0.1
//;****************************************************
//#include "BSP_Driver.h"
#include "userBSP.h"
#include "wifi_global.h"

/*=============================================================================*/
/**
 * @fn           int16 wifi_set_pwrmode(void)
 * @brief        UART 
 * @param[in]    powerMode
 * @param[out]   none
 * @return       errCode
 *               -1 = Module  busy / Timeout
 *               0  = SUCCESS
 * @section description  
 * 
 */
/*=============================================================================*/
int16 wifi_chk_link_cmd(void)
{
  int16						retval;
  char sendCmd[16]="";
  strcpy(sendCmd,WIFI_CHK_LINK_CMD);
  strcat(sendCmd,WIFI_SEND_END);
  retval=USART_OUT(USART1,(char *)sendCmd,strlen(sendCmd));
  return retval;
}

int16 wifi_check_ssid_link(void)
{
  int8 buf_j ,buf_i ;
   wifi_WSLK_Response.contframe.ok_flg  = WSLK_UNKNOW;
  do 
  {
    retval=wifi_chk_link_cmd();   //查看无线是否连接     retval = 0表示已经发送  非0表示正在读取不能发送
    recv_byte_con = 0;
    if(retval!=0)
    {			 			  
      //return retval;
      return OK_NONE_INFO;
    }	
    while(read_flag == FALSE);
    read_flag = FALSE;
    //if(	wifi_INC_TIMER_1>10) break;			
  }while( strncmp((char *)uCmdRspFrame.uCmdRspBuf,"AT+WSLK\n\r+ok",12) != 0);
  wifi_cmd_recv_ok_flg = CMD_RE_OK;  //收到ok，表示命令响应正常，下边识别命令响应信息
  if(strncmp((char *)uCmdRspFrame.uCmdRspBuf,"AT+WSLK\n\r+ok=Disconnected",25) == 0)
  {
    wifi_WSLK_Response.contframe.ok_flg = UN_WIFI_CONNECT;
    return OK_NONE_INFO;
  }
  else
  {
    buf_j = 0;
    buf_i = 0;
    while('=' != uCmdRspFrame.uCmdRspBuf[buf_j++]);         //find the start of the ssid info
    while((uCmdRspFrame.uCmdRspBuf[buf_j] !='\r')&&(uCmdRspFrame.uCmdRspBuf[buf_j+1] !='\n'))
    {
      
      wifi_WSLK_Response.contframe.ssid_info[buf_i++] = uCmdRspFrame.uCmdRspBuf[buf_j++];      //Wifi_Wslk_Ssid_Info 记录下ssid的心机，ssid(mac) BHKS(D8:15:D:8D:93:AE)
    }
    wifi_WSLK_Response.contframe.ok_flg = WIFI_CONNECT;
    return OK_INFO;
  
  }
  
  
    
}

