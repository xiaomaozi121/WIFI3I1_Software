//;****************************************************
//;Company :  WIFI WIRELESS
//;File Name :  wifi_set_channel
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
 * @fn           int16 wifi_set_channel(void)
 * @brief        UART 
 * @param[in]    wifi_uApAdhoc
 * @param[out]   none
 * @return       errCode
 *               -1 = Module  busy / Timeout
 *               0  = SUCCESS
 * @section description  
 * 
 */
 /*=============================================================================*/
int16 wifi_set_channel(wifi_uApAdhoc *uApAdhocFrame)
{
	int16						retval;
	char sendCmd[18]="";
	char set_channel[3]="";
    strcpy(sendCmd,wifi_CHANNEL_CMD);
	if(uApAdhocFrame->apAdhocFrameSnd.ibssApChannel<10){set_channel[0]=uApAdhocFrame->apAdhocFrameSnd.ibssApChannel+0x30;}
	   else{set_channel[0]=(uApAdhocFrame->apAdhocFrameSnd.ibssApChannel)/10+0x30;set_channel[1]=(uApAdhocFrame->apAdhocFrameSnd.ibssApChannel)%10+0x30;}
	strcat(sendCmd,set_channel);
	strcat(sendCmd,WIFI_SEND_END);
	retval=USART_OUT(USART1,(char *)sendCmd,strlen(sendCmd));
	return retval;
}
