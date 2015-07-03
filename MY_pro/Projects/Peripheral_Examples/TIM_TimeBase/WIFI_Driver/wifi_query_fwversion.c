//;****************************************************
//;Company :  WIFI WIRELESS
//;File Name :  rsi_query_fwversion
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
 * @fn           int16 rsi_query_fwversion(void)
 * @brief        UART, QUERY FIRMWARE VERSION 
 * @param[in]    none
 * @param[out]   none
 * @return       errCode
 *               -1 = Module  busy / Timeout
 *               0  = SUCCESS
 * @section description  
 * This API is used to query the firmware version of the Wi-Fi module.
 */
 /*=============================================================================*/
int16 wifi_query_fwversion(void)
{
	int16						retval;
	char sendCmd[15]="";
    strcpy(sendCmd,wifi_QRY_VERSION_CMD);
	strcat(sendCmd,WIFI_SEND_END);
	retval=USART_OUT(USART1,(char *)sendCmd,strlen(sendCmd));
	return retval;
}
