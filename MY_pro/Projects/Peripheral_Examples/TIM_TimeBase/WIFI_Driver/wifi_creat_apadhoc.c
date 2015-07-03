//;****************************************************
//;Company :  WIFI WIRELESS
//;File Name : wifi_creat_apadhoc.c
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
 * @fn           int16 wifi_creat_apadhoc(void)
 * @brief        UART
 * @param[in]    wifi_uApAdhoc
 * @param[out]   none
 * @return       errCode
 *               -1 = Module  busy 
 *               0  = SUCCESS
 * @section description  
 * 
 */
 /*=============================================================================*/
int16 wifi_creat_apadhoc(wifi_uApAdhoc *uApAdhocFrame)
{
	int16	 retval = 0;
	char sendCmd[48]="";

     strcpy(sendCmd,wifi_AP_CMD);
	 strcat(sendCmd,(char *)uApAdhocFrame->apAdhocFrameSnd.ssid);
	 strcat(sendCmd,wifi_COMMA);
	 strcat(sendCmd,(char *)(uApAdhocFrame->apAdhocFrameSnd.apMode+0x30));
	 strcat(sendCmd,WIFI_SEND_END);
	 retval=USART_OUT(USART1,(char *)sendCmd,strlen(sendCmd));

	return retval;
}
