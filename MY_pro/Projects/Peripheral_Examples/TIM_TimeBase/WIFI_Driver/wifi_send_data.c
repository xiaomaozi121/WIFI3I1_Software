//;****************************************************
//;Company :  WIFI WIRELESS
//;File Name :  wifi_send_data
//;Author :    Junhua
//;Create Data : 2014-03-15
//;Last Modified : 
//;Description : WIFI413 WIFI UART  DRIVER
//;Version : 1.0.1
//;****************************************************

//#include "BSP_Driver.h"
#include "userBSP.h"
extern uint8 retval;
extern uint16  data_len;

/*=============================================================================*/
/**
 * @fn           int16 wifi_send_data(void)
 * @brief        UART
 * @param[in]    socket_flag,Send_Data,Send_DataLen
 * @param[out]   none
 * @return       errCode
 *               -1 = Module busy / Timeout
 *               0  = SUCCESS
 * @section description  
 * 
 */
 /*=============================================================================*/


uint8 wifi_Send_data(uint8 socket_flag,uint16 dest_Port,uint8 *dest_Ip,uint16 Send_DataLen,uint8 *Send_Data)
{

	 char wifi_sendHeader[100]="";
	 char ipframe[16]="";
	 uint16  headLen=0;
	 wifi_bytes4ToAsciiDotAddr(dest_Ip,(uint8 *)ipframe);
	 headLen= sprintf(wifi_sendHeader,"%s%c%s%d%s%s%s%d%s",wifi_SEND_DATA_CMD,socket_flag,wifi_COMMA,dest_Port,wifi_COMMA,ipframe,wifi_COMMA,Send_DataLen,wifi_COMMA);
	 retval=USART_OUT(USART1,wifi_sendHeader,headLen);
         retval=USART_OUT(USART1,(char *)Send_Data,Send_DataLen);
	 retval=USART_OUT(USART1,WIFI_SEND_END,strlen(WIFI_SEND_END));
	 if(retval!=0)
	 {			 			  
	    return retval;					
	 }				 
	 return retval;
}


/*=============================================================================*/
/**
 * @fn           int16 wifi_send_data(void)
 * @brief        UART
 * @param[in]    socket_flag,Send_Data,Send_DataLen
 * @param[out]   none
 * @return       errCode
 *               -1 = Module busy / Timeout
 *               0  = SUCCESS
 * @section description  
 * 
 */
 /*=============================================================================*/


uint8 wifi_Send_mqtt_data(uint8 socket_flag,char *dest_Ip,uint16 Send_DataLen,uint8 *Send_Data)
{

	 char wifi_sendHeader[100]="";
	 uint16  headLen=0;
	 /*strcpy(wifi_sendHeader,wifi_SEND_DATA_CMD);
	 strcat(wifi_sendHeader,wifi_ZERO);
	 strcat(wifi_sendHeader,wifi_COMMA);
	 strcat(wifi_sendHeader,wifi_SERVER_PORT);
	 strcat(wifi_sendHeader,wifi_COMMA);
	 strcat(wifi_sendHeader,dest_Ip);
	 headLen=sprintf(wifi_sendHeader,"%d%s",Send_DataLen,wifi_COMMA);*/
	 headLen=sprintf(wifi_sendHeader,"%s%s%s%s%s%s%s%d%s",wifi_SEND_DATA_CMD,wifi_ZERO,wifi_COMMA,wifi_SERVER_PORT,wifi_COMMA,dest_Ip,wifi_COMMA,Send_DataLen,wifi_COMMA);
//	 USART2_OUT(USART2,wifi_sendHeader,headLen);
//	 USART_OUT(USART2,(char *)Send_Data,Send_DataLen);
//	 USART_OUT(USART2,wifi_END,strlen(wifi_END));

	 retval=USART_OUT(USART1,wifi_sendHeader,headLen);
     retval=USART_OUT(USART1,(char *)Send_Data,Send_DataLen);
	 retval=USART_OUT(USART1,WIFI_SEND_END,strlen(WIFI_SEND_END));

	 if(retval!=0)
	 {			 			  
	    return retval;					
	 }				 
	 return retval;
}

