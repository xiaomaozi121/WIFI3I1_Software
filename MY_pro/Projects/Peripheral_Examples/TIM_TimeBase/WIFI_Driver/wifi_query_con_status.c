//;****************************************************
//;Company :  WIFI WIRELESS
//;File Name :  wifi_query_con_status
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
 * @fn           int16 wifi_query_con_status(void)
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
int16 wifi_query_con_status(void)
{
	int16	retval;
	char sendCmd[22]="";
	strcpy(sendCmd,wifi_QRY_CON_STATUS_CMD);
	strcat(sendCmd,WIFI_SEND_END);
	retval=USART_OUT(USART1,(char *)sendCmd,strlen(sendCmd));
	return retval;
}
