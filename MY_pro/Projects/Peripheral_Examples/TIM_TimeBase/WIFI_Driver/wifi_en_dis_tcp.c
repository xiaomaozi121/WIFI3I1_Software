//;****************************************************
//;Company :  WIFI WIRELESS
//;File Name :  wifi_open_socket.c
//;Author :    Junhua
//;Create Data : 2014-03-15
//;Last Modified : 
//;Description : WIFI413 WIFI UART  DRIVER
//;Version : 1.0.1
//;****************************************************
//#include "BSP_Driver.h"
#include "userBSP.h"
int8 wifi_bytes2ToAscii(uint16 hex,uint8 *strBuf)
{
  uint8			i,j=0;							// loop counter
  uint8		    hexAddr[5];

  hexAddr[0]=hex/10000+0x30;
  hexAddr[1]=hex/1000%10+0x30;
  hexAddr[2]=hex/100%10+0x30;
  hexAddr[3]=hex/10%10+0x30;
  hexAddr[4]=hex%10+0x30;						
 
    for (i = 0; i< 5; i++) {
  	  if(hexAddr[i]==0x30)
	  {
	    j++	;
	  }
	  else break;
   }
  for (i = 0; i< 5-j; i++) {							
 	strBuf[i]= hexAddr[i+j];
  }
  strBuf[5-j]=0;
  return 1;
}
/*=============================================================================*/
/**
 * @fn           int16 wifi_open_socket(void)
 * @brief        UART, 
 * @param[in]    local_Port,dest_Port,wifi_SocketCmd,dest_Ip
 * @param[out]   none
 * @return       errCode
 *               -1 = Module  busy / Timeout
 *               0  = SUCCESS
 * @section description  
 * 
 */
/*=============================================================================*/
int16 wifi_open_socket(uint16 local_Port,uint16 dest_Port,uint8 wifi_SocketCmd,uint8 *dest_Ip)  //0:TCP 1:LTCP 2:UDP 3:LUDP
{
	int16						retval;
	char sendCmd[42]="";
	char port[16]="";

	
	switch (wifi_SocketCmd)
	{
	  
	  case 0x00: 
	      { 
		  strcpy(sendCmd,wifi_TCP_CMD);
		  wifi_bytes4ToAsciiDotAddr(dest_Ip,(uint8 *)port);
		  strcat(sendCmd,port);
		  strcat(sendCmd,wifi_COMMA);
		  wifi_bytes2ToAscii(dest_Port,(uint8 *)port);
		  strcat(sendCmd,port);
		  strcat(sendCmd,wifi_COMMA);
		  wifi_bytes2ToAscii(local_Port,(uint8 *)port);
		  strcat(sendCmd,port); 
		  }

	      break;
	  
	  case 0x01:
	      { 
		  strcpy(sendCmd,wifi_LTCP_CMD );
		  wifi_bytes2ToAscii(local_Port,(uint8 *)port);
		  strcat(sendCmd,port);
		 }
	  
	      break;

     case 0x02: 
	     { 
		  strcpy(sendCmd,wifi_UDP_CMD);
		  wifi_bytes4ToAsciiDotAddr(dest_Ip,(uint8 *)port);
		  strcat(sendCmd,port);
		  strcat(sendCmd,wifi_COMMA);
		  wifi_bytes2ToAscii(dest_Port,(uint8 *)port);
		  strcat(sendCmd,port);
		  strcat(sendCmd,wifi_COMMA);
		  wifi_bytes2ToAscii(local_Port,(uint8 *)port);
		  strcat(sendCmd,port);		
		 }

	     break;

	  case 0x03: 
	      { 
		  strcpy(sendCmd,wifi_LUDP_CMD);
		  wifi_bytes2ToAscii(local_Port,(uint8 *)port);
		  strcat(sendCmd,port);
		  }

	      break;
	  case 0x04: 
	      { 
		  strcpy(sendCmd,wifi_MULTICAST_CMD);
		  wifi_bytes4ToAsciiDotAddr(dest_Ip,(uint8 *)port);
		  strcat(sendCmd,port);
		  strcat(sendCmd,wifi_COMMA);
		  wifi_bytes2ToAscii(dest_Port,(uint8 *)port);
		  strcat(sendCmd,port);
		  strcat(sendCmd,wifi_COMMA);
		  wifi_bytes2ToAscii(local_Port,(uint8 *)port);
		  strcat(sendCmd,port);	
		  }

	    break;

	
	}
	strcat(sendCmd,WIFI_SEND_END);
	retval=USART_OUT(USART1,(char *)sendCmd,strlen(sendCmd));
	return retval;
}

/*=============================================================================*/
/**
 * @fn           int16 wifi_open_socket(void)
 * @brief        UART, 
 * @param[in]    local_Port,dest_Port,wifi_SocketCmd,dest_Ip
 * @param[out]   none
 * @return       errCode
 *               -1 = Module  busy / Timeout
 *               0  = SUCCESS
 * @section description  
 * 
 */
/*=============================================================================*/
int16 wifi_en_tcplk_cmd(void)  //0:TCP 1:LTCP 2:UDP 3:LUDP
{
  int16	retval;
  char sendCmd[42]="";
  strcpy(sendCmd,WIFI_TCP_DIS_CMD);  //"at+tcpdis"
  strcat(sendCmd,wifi_EQUAL);        //"="
  strcat(sendCmd,wifi_on_flg);       //"on"
  strcat(sendCmd,WIFI_SEND_END);     
  retval=USART_OUT(USART1,(char *)sendCmd,strlen(sendCmd));
  return retval;
}

int16 wifi_dis_tcplk_cmd(void)  //0:TCP 1:LTCP 2:UDP 3:LUDP
{
  int16	retval;
  char sendCmd[42]="";
  strcpy(sendCmd,WIFI_TCP_DIS_CMD);  //"at+tcpdis"
  strcat(sendCmd,wifi_EQUAL);        //"="
  strcat(sendCmd,wifi_off_flg);       //"on"
  strcat(sendCmd,WIFI_SEND_END);     
  retval=USART_OUT(USART1,(char *)sendCmd,strlen(sendCmd));
  return retval;
}

int16 wifi_en_dis_tcplk(_ON_OFF_VAL_ on_off_flg)
{
  //int8 buf_j ,buf_i ;
  do 
  {
    switch (on_off_flg)
    {
    case ON:
      retval=wifi_en_tcplk_cmd();
      break;
    case OFF:
      retval=wifi_dis_tcplk_cmd();
      break;
    default:
      retval=wifi_en_tcplk_cmd();
    }
    recv_byte_con = 0;
    if(retval!=0)
    {			 			  
      //return retval;
      return OK_NONE_INFO;
    }	
    while(read_flag == FALSE);
    read_flag = FALSE;
    //if(	wifi_INC_TIMER_1>10) break;			
  }while( strncmp((char *)uCmdRspFrame.uCmdRspBuf,"AT+TCPDIS\n\r+ok",strlen("AT+TCPDIS")) != 0);
  wifi_cmd_recv_ok_flg = CMD_RE_OK;  //收到ok，表示命令响应正常，下边识别命令响应信息
  if(strncmp((char *)uCmdRspFrame.uCmdRspBuf,"AT+TCPDIS\n\r+ok=on",strlen("AT+TCPDIS=on+ok")) == 0)
  {
    wifi_tcponoff_flg = ON;
    return OK_INFO;
  }
  else
  {
    wifi_tcponoff_flg = OFF;
    return OK_INFO;
  
  }
}


