//;****************************************************
//;Company :  WIFI WIRELESS
//;File Name : wifi_set_webconfig
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
 * @fn           int16 wifi_set_webconfig(void)
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
int16 wifi_set_webconfig(webconfig_t* param)
{
	int16		retval;

	retval=USART_OUT(USART1,wifi_WEB_CONFIG_CMD,strlen(wifi_WEB_CONFIG_CMD));
	retval=USART_OUT(USART1,(char *)param,sizeof(webconfig_t));
	retval=USART_OUT(USART1,WIFI_SEND_END,strlen(WIFI_SEND_END));	
	return retval;
}
