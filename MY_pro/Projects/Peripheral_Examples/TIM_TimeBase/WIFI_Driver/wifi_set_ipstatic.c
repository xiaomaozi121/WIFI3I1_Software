//;****************************************************
//;Company :  WIFI WIRELESS
//;File Name :  wifi_set_ipstatic
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
 * @fn           int16 wifi_set_ipstatic(void)
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
int16 wifi_set_ipstatic(wifi_uIpparam *uIpparamFrame)
{
	int16						retval;
	char sendCmd[80]="";
	uint8 ipparmddr[14]="";
	strcpy(sendCmd,wifi_IPSTATIC_CMD);
	wifi_bytes4ToAsciiDotAddr(uIpparamFrame->ipparamFrameSnd.ipaddr,ipparmddr);
	strcat(sendCmd,(char *)ipparmddr);
	strcat(sendCmd,wifi_COMMA);
	wifi_bytes4ToAsciiDotAddr(uIpparamFrame->ipparamFrameSnd.netmask,ipparmddr);
	strcat(sendCmd,(char *)ipparmddr);
	strcat(sendCmd,wifi_COMMA);
	wifi_bytes4ToAsciiDotAddr(uIpparamFrame->ipparamFrameSnd.gateway,ipparmddr);
	strcat(sendCmd,(char *)ipparmddr);
	strcat(sendCmd,wifi_COMMA);
	wifi_bytes4ToAsciiDotAddr(uIpparamFrame->ipparamFrameSnd.dnssvr1,ipparmddr);
	strcat(sendCmd,(char *)ipparmddr);
	strcat(sendCmd,wifi_COMMA);
	wifi_bytes4ToAsciiDotAddr(uIpparamFrame->ipparamFrameSnd.dnssvr2,ipparmddr);
	strcat(sendCmd,(char *)ipparmddr);
	strcat(sendCmd,WIFI_SEND_END);
	retval=USART_OUT(USART1,(char *)sendCmd,strlen(sendCmd));
	return retval;
}
