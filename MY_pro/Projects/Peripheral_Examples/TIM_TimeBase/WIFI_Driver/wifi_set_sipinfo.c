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
int16 wifi_set_serip_cmd(void)
{
  int16						retval;
  char sendCmd[64]="";
  strcpy(sendCmd,WIFI_CHK_IPSET_CMD);//"at+netp"
  strcat(sendCmd,wifi_EQUAL);        //"="
  strcat(sendCmd,wifi_PRO_TCP);      //"TCP"
  strcat(sendCmd,wifi_COMMA);        //","
  strcat(sendCmd,wifi_MUDL_CLIENT);  //"Client"
  strcat(sendCmd,wifi_COMMA);        //","
  strcat(sendCmd,wifi_SERVER_PORT);  //"10106"
  strcat(sendCmd,wifi_COMMA);        //","
  strcat(sendCmd,wifi_SERVER);       //"182.92.164.117"
  strcat(sendCmd,WIFI_SEND_END);     //"\r"
  retval=USART_OUT(USART1,(char *)sendCmd,strlen(sendCmd));
  return retval;
}

int16 wifi_set_serip(void)
{
  //int8 buf_j ,buf_i ;
   ///**/wifi_NETP_Response.contframe.ok_flg  = NETP_UNKNOW;
  do 
  {
    retval=wifi_set_serip_cmd();   //查看无线是否连接     retval = 0表示已经发送  非0表示正在读取不能发送
    recv_byte_con = 0;
    if(retval!=0)
    {			 			  
      //return retval;
      return OK_NONE_INFO;
    }	
    while(read_flag == FALSE);
    read_flag = FALSE;
    //if(	wifi_INC_TIMER_1>10) break;			
  /**/}while( strncmp((char *)uCmdRspFrame.uCmdRspBuf,"AT+NETP",7) != 0);
  //wifi_cmd_recv_ok_flg = CMD_RE_OK;  //收到ok，表示命令响应正常，下边识别命令响应信息
 
    return OK_INFO;
    
}