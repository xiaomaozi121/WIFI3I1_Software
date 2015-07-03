#include "stm32f0xx.h"
#include "stm32f0308_discovery.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_usart.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_adc.h"
//#include "USART.h"
//#include "delay.h"
//#include "rak_global.h"
//#include "rak_config.h"
//#include "rak_uart_api.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


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


#define ADC1_DR_Address                0x40012440

extern __IO uint32_t TempSensVoltmv, VrefIntVoltmv;
extern __IO uint16_t RegularConvData_Tab[2];

extern void BHKS_Serial_PutString( USART_TypeDef* USARTx,uint8_t *s);
extern void BHKS_SerialPutChar(USART_TypeDef* USARTx,uint8_t c);
/*
extern uint8_t BHKS_ReveOneByte(USART_TypeDef* USARTx,uint8_t key);
extern void BHKS_SenduInt16_tString(USART_TypeDef* USARTx,uint16_t nInt);
extern void BHKS_SendFloatString(USART_TypeDef* USARTx,float nfloat);

*/
 void USART_INIT(void);
 uint8_t USART_OUT(USART_TypeDef* USARTx, char *Data,uint16_t Len);
 void USART2_OUT(USART_TypeDef* USARTx, uint8_t *Data,uint16_t Len);
 void USART_RxTx(void);
 void Reset_Target(void);


 
extern uint8_t rec_f;
extern uint8_t RxBuffer8[14];
extern uint8_t RxBuffer9[14];

extern uint8_t RxBufferLs[10];
extern uint8_t TxBufferLs[10]; 

extern uint8_t MlBufferRet[14];
extern uint8_t McBufferRet[14];
extern uint8_t PirBufferRet[14];

extern __IO uint8_t TxCounter1;
extern __IO uint8_t RxCounter1 ; 
extern uint8_t NbrOfDataToHeart ;




typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef const uint32_t uc32;  /*!< Read Only */
typedef const uint16_t uc16;  /*!< Read Only */
typedef const uint8_t uc8;   /*!< Read Only */

typedef __IO uint32_t  vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;

typedef __I uint32_t vuc32;  /*!< Read Only */
typedef __I uint16_t vuc16;  /*!< Read Only */
typedef __I uint8_t vuc8;   /*!< Read Only */



extern uint16_t g_ms_con;


extern char char_test[16];
/* Private function prototypes -----------------------------------------------*/
void TIM_Config(void);
void tim3_it_ms_pro(void);

void USART_INIT();
uint8_t USART_OUT(USART_TypeDef* USARTx, char *Data,uint16_t Len);
void USART2_OUT(USART_TypeDef* USARTx, uint8_t *Data,uint16_t Len);
void USART_RxTx(void);
void BHKS_Serial_PutString( USART_TypeDef* USARTx,uint8_t *s);
void BHKS_SerialPutChar(USART_TypeDef* USARTx,uint8_t c);
void Reset_Target(void);

void delay_init(u8 SYSCLK);
void delay_ms(u16 nms);
void Delay_Ms(uint8_t ms);
void delay_us(u32 nus);
void delay_s(u16 ns);

void ADC_CH_DMA_Config(void);

void Init_ADC02(void);
void Init_ADC3(void);
void ADC1_GetSConversionValueFromBuffer(void);
void Init_Timer3(void);
void Init_Timer4(void);void GPIO_Init_User(void);	
void WatchD_Init(void);void GetAD_Value02(void);
