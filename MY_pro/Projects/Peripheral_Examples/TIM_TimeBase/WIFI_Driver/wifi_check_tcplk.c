//;****************************************************
//;Company :  BHKS_wifi_demo
//;File Name : wifi_check_TCPLK
//;Author :    jy_t
//;Create Data : 2014-12-11
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
int16 wifi_tcplk_cmd(void)
{
  int16	retval;
  char sendCmd[16]="";
  strcpy(sendCmd,WIFI_TCP_LK_CMD);
  strcat(sendCmd,WIFI_SEND_END);
  retval=USART_OUT(USART1,(char *)sendCmd,strlen(sendCmd));
  return retval;
}

int16 wifi_check_TCPLK(void)
{
  //int8 buf_j ,buf_i ;
  do 
  {
    retval=wifi_tcplk_cmd();   //查看无线是否连接     retval = 0表示已经发送  非0表示正在读取不能发送
    recv_byte_con = 0;
    if(retval!=0)
    {			 			  
      //return retval;
      return OK_NONE_INFO;
    }	
    while(read_flag == FALSE);
    read_flag = FALSE;
    //if(	wifi_INC_TIMER_1>10) break;			
  }while( strncmp((char *)uCmdRspFrame.uCmdRspBuf,"AT+TCPLK\n\r+ok",13) != 0);
  wifi_cmd_recv_ok_flg = CMD_RE_OK;  //收到ok，表示命令响应正常，下边识别命令响应信息
  if(strncmp((char *)uCmdRspFrame.uCmdRspBuf,"AT+TCPLK\n\r+ok=on",16) == 0)
  {
    return OK_INFO;
  }
  else if(strncmp((char *)uCmdRspFrame.uCmdRspBuf,"AT+TCPLK\n\r+ok=off",17) == 0)
  {
    return OK_NONE_INFO;
  }
  else 
  {
    return RESP_ERROR;
  } 
}




/*=============================================================================*/
/**
 * @fn			void wifi_asciiDotAddressTo4Bytes(uint8 *hexAddr, int8 *asciiDotAddress)
 * @brief		Convert an ASCII . notation network address to 4-byte hex address
 * @param[in]		int8 *asciiDotFormatAddress, source address to convert, must be a null terminated string
 * @param[out]		uint8 *hexAddr,	Output value is passed back in the 4-byte Hex Address
 * @return		none
 */
/*=============================================================================*/
void wifi_readIPAsciiDotAddressin4Bytes(int8 *WriteAddr, int8 *ReadAsciiDotAddress)
{
  uint8			i,j;
  // loop counter
  int8			cBufPos;													
  j = 0;
  for(i = 0;i<4;i++)
  {
    WriteAddr[i] = 0;
  }
  i = 0;   //初始化为0
  while('=' != ReadAsciiDotAddress[j++]);
  cBufPos = ReadAsciiDotAddress[j];
  while('\r' != cBufPos)
  {
    if(ReadAsciiDotAddress[j] == ':')
    {
      i++;
      continue;
    }
    WriteAddr[i] *= 10;
    WriteAddr[i] += (ReadAsciiDotAddress[j]-'0');
    cBufPos = ReadAsciiDotAddress[j];
    j++;
  }
  WriteAddr[i] = 0;
}