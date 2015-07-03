//;****************************************************
//;Company :  WIFI WIRELESS
//;File Name :  wifi_scan_ap
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
 * @fn           int16 wifi_scan_ap(void)
 * @brief        UART
 * @param[in]    wifi_uScan
 * @param[out]   none
 * @return       errCode
 *               -1 = Module s busy / Timeout
 *               0  = SUCCESS
 * @section description  
 * 
 */
 /*=============================================================================*/
int16 wifi_scan_ap(wifi_uScan *uScanFrame)
{
	int16	retval;
	char sendCmd[36]="";
	char sendchannel[3]="";

	strcpy(sendCmd,wifi_SCAN_CMD);
	if(uScanFrame->scanFrameSnd.channel<10){sendchannel[0]=uScanFrame->scanFrameSnd.channel+0x30;}
	   else{sendchannel[0]=(uScanFrame->scanFrameSnd.channel)/10+0x30;sendchannel[1]=(uScanFrame->scanFrameSnd.channel)%10+0x30;}
	strcat(sendCmd,sendchannel);													 
	//strcat(sendCmd,wifi_COMMA);
	//strcat(sendCmd,(char *)uScanFrame->scanFrameSnd.ssid);
	strcat(sendCmd,WIFI_SEND_END);
	retval=USART_OUT(USART1,sendCmd,strlen(sendCmd));
	return retval;
}
