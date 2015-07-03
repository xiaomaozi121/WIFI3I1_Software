//;****************************************************
//;Company :  WIFI WIRELESS
//;File Name :  wifi_set_psk
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
 * @fn           int16 wifi_set_psk(void)
 * @brief        UART 
 * @param[in]    wifi_uJoin
 * @param[out]   none
 * @return       errCode
 *               -1 = Module busy / Timeout
 *               0  = SUCCESS
 * @section description  
 * 
 */
/*=============================================================================*/
int16 wifi_set_psk(wifi_uJoin *uJoinFrame)
{
	int16						retval;
	char sendCmd[44]="";
    strcpy(sendCmd,wifi_PSK_CMD);
	strcat(sendCmd,(char *)uJoinFrame->joinFrameSnd.psk);
	strcat(sendCmd,WIFI_SEND_END);
	retval=USART_OUT(USART1,(char *)sendCmd,strlen(sendCmd));
	return retval;
}
