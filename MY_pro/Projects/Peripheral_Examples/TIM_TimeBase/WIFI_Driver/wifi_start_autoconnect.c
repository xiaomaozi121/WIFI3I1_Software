//;****************************************************
//;Company :  WIFI WIRELESS
//;File Name : wifi_start_autoconnect
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
 * @fn           int16 wifi_start_autoconnect(void)
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
int16 wifi_start_autoconnect(void)
{
	int16						retval;
	char sendCmd[20]="";
	strcpy(sendCmd,wifi_AUTO_CONNECT_CMD);
	strcat(sendCmd,WIFI_SEND_END);
	retval=USART_OUT(USART1,(char *)sendCmd,strlen(sendCmd));
	return retval;
}
