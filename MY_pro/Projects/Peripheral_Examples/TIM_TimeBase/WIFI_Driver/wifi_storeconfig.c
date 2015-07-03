//;****************************************************
//;Company :  WIFI WIRELESS
//;File Name : wifi_storeconfig
//;Author :    Junhua
//;Create Data : 2014-03-15
//;Last Modified : 
//;Description : WIFI413 WIFI UART  DRIVER
//;Version : 1.0.1
//;****************************************************
//#include "BSP_Driver.h"
#include "userBSP.h"
/*=============================================================================*/
/**
 * @fn           int16 wifi_storeconfig(void)
 * @brief        UART, 
 * @param[in]    none
 * @param[out]   none
 * @return       errCode
 *               -1 = Module busy / Timeout
 *               0  = SUCCESS
 * @section description  
 * 
 */
 /*=============================================================================*/
int16 wifi_storeconfig(int8 param_en,config_t* param)
{
	int16		retval;
	uint8	    CmdheadLen=0;
	char sendCmd[20]="";

	if(param_en)
	{
	  CmdheadLen=sprintf(sendCmd,"%s%s",wifi_STORE_CONFIG_CMD,wifi_EQUAL);
	  retval=USART_OUT(USART1,(char *)sendCmd,CmdheadLen);
	  retval=USART_OUT(USART1,(char *)param,sizeof(config_t));
	  retval=USART_OUT(USART1,WIFI_SEND_END,strlen(WIFI_SEND_END));
	}else
	{
	  strcpy(sendCmd,wifi_STORE_CONFIG_CMD);
	  strcat(sendCmd,WIFI_SEND_END);
	  retval=USART_OUT(USART1,(char *)sendCmd,strlen(sendCmd));
	}	
	return retval;
}
