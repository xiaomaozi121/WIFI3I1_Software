//;****************************************************
//;Company :  WIFI WIRELESS
//;File Name : wifi_connect_ap.c
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
 * @fn           int16 wifi_connect_ap(void)
 * @brief        UART, Connet_Ap 
 * @param[in]    wifi_uJoin 
 * @param[out]   none
 * @return       errCode
 *               -1 = Module s busy 
 *               0  = SUCCESS
 * @section description  
 * 
 */
 /*=============================================================================*/
int16 wifi_connect_ap(wifi_uJoin *uJoinFrame)
{
	int16						retval;
	char sendCmd[48]="";
    strcpy(sendCmd,wifi_CONN_CMD);
	strcat(sendCmd,(char *)uJoinFrame->joinFrameSnd.ssid);
	strcat(sendCmd,WIFI_SEND_END);
	retval=USART_OUT(USART1,(char *)sendCmd,strlen(sendCmd));
	return retval;
}
