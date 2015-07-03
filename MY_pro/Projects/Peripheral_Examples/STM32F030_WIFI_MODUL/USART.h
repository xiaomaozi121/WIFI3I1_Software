#ifndef _USART_H_
#define _USART_H_
   /******************** (C) COPYRIGHT 2009 www.armjishu.com ************************
* File Name          : date.h
* Author             : www.armjishu.com Team
* Version            : V1.0
* Date               : 12/1/2009
* Description        : 日期相关函数
*******************************************************************************/
 #include "stm32f0xx_usart.h"
#define  USART1PA3_4

#ifdef  USART1PA3_4											
	#define USART1_TX_PIN                 GPIO_Pin_2
	#define USART1_TX_PORT           			GPIOA
	#define USART1_TX_GPIO_CLK            RCC_AHBPeriph_GPIOA
	#define USART1_TX_SOURCE              GPIO_PinSource2
	#define USART1_TX_AF                  GPIO_AF_1

	#define USART1_RX_PIN                 GPIO_Pin_3
	#define USART1_RX_PORT           			GPIOA
	#define USART1_RX_GPIO_CLK            RCC_AHBPeriph_GPIOA
	#define USART1_RX_SOURCE              GPIO_PinSource3
	#define USART1_RX_AF                  GPIO_AF_1
#endif
#ifdef  USART1PA9_10 											
	#define USART1_TX_PIN                 GPIO_Pin_9
	#define USART1_TX_PORT           			GPIOA
	#define USART1_TX_GPIO_CLK            RCC_AHBPeriph_GPIOA
	#define USART1_TX_SOURCE              GPIO_PinSource9
	#define USART1_TX_AF                  GPIO_AF_1

	#define USART1_RX_PIN                 GPIO_Pin_10
	#define USART1_RX_PORT           			GPIOA
	#define USART1_RX_GPIO_CLK            RCC_AHBPeriph_GPIOA
	#define USART1_RX_SOURCE              GPIO_PinSource10
	#define USART1_RX_AF                  GPIO_AF_1
#endif
#ifdef  USART1PB6_7 
	#define USART1_TX_PIN                 GPIO_Pin_6
	#define USART1_TX_PORT           			GPIOB
	#define USART1_TX_GPIO_CLK            RCC_AHBPeriph_GPIOB
	#define USART1_TX_SOURCE              GPIO_PinSource6
	#define USART1_TX_AF                  GPIO_AF_0

	#define USART1_RX_PIN                 GPIO_Pin_7
	#define USART1_RX_PORT           			GPIOB
	#define USART1_RX_GPIO_CLK            RCC_AHBPeriph_GPIOB
	#define USART1_RX_SOURCE              GPIO_PinSource7
	#define USART1_RX_AF                  GPIO_AF_0
#endif


extern void BHKS_Serial_PutString( USART_TypeDef* USARTx,uint8_t *s);
extern void BHKS_SerialPutChar(USART_TypeDef* USARTx,uint8_t c);
extern uint8_t BHKS_ReveOneByte(USART_TypeDef* USARTx,uint8_t key);
extern void BHKS_SenduInt16_tString(USART_TypeDef* USARTx,uint16_t nInt);
extern void BHKS_SendFloatString(USART_TypeDef* USARTx,float nfloat);


 void USART_INIT(void);
 uint8_t USART_OUT(USART_TypeDef* USARTx, char *Data,uint16_t Len);
 void USART2_OUT(USART_TypeDef* USARTx, uint8_t *Data,uint16_t Len);
 void USART_RxTx(void);
 void Reset_Target(void);

 extern unsigned char KJ_flag;
 extern unsigned char BF_flag;
 extern unsigned char PIR_flag;
 extern unsigned char ML_flag;
 extern unsigned char SW_off;
 extern unsigned char SW_on;
 extern unsigned char CC;
 extern unsigned char  ZJ_miao; 
 extern unsigned char  ML_miao; 
 extern unsigned char  MC_miao; 
 extern unsigned char MC_flag;
 extern unsigned char CF_flag;
 extern unsigned char ALL_BF;
 extern unsigned char XF_flag;
 extern unsigned char SECURITY_flag;
 extern uint8_t RxBufferLs[10];
extern uint8_t TxBufferLs[10]; 

extern uint8_t MlBufferRet[14];
extern uint8_t McBufferRet[14];
extern uint8_t PirBufferRet[14];
#endif
