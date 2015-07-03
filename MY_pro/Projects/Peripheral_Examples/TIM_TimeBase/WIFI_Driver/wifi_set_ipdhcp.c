//;****************************************************
//;Company :  WIFI WIRELESS
//;File Name :  wifi_set_ipdhcp
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
 * @fn           int16 wifi_set_ipdhcp(void)
 * @brief        UART 
 * @param[in]    wifi_uIpparam
 * @param[out]   none
 * @return       errCode
 *               -1 = Module busy / Timeout
 *               0  = SUCCESS
 * @section description  
 * 
 */
 /*=============================================================================*/
int16 wifi_set_ipdhcp(wifi_uIpparam *uIpparamFrame)
{
	int16						retval;
	char sendCmd[14]="";
	char dhcpmode[2]="";
	strcpy(sendCmd,wifi_IPDHCP_CMD);
	dhcpmode[0]=uIpparamFrame->ipparamFrameSnd.dhcpMode+0x30;
	strcat(sendCmd,dhcpmode);
	strcat(sendCmd,WIFI_SEND_END);
	retval=USART_OUT(USART1,(char *)sendCmd,strlen(sendCmd));
	return retval;
}
