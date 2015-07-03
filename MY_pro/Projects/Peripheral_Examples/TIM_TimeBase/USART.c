	 
 //#include "stm32f10x.h"
//#include "stm32f10x_usart.h"
//#include "misc.h"
#include "stm32f0xx_usart.h"
#include "USART.h"
//#include "cc1101.h"
//#include "i2c.h"
//#include "date.h"
//#include "wifi_global.h"
//#include "delay.h"

#ifdef __cplusplus
 extern "C" {
#endif
 /* Private typedef -----------------------------------------------------------*/

typedef enum { FAILED = 0, PASSED = !FAILED} TestStatus;
/*


uint8_t TxBuffer0[] ="开";*/
uint8_t TxBuffer1[] ="关";/*
uint8_t TxBuffer2[] ="布防";
uint8_t TxBuffer3[] ="撤防";
uint8_t TxBuffer4[] ="主机报警";
uint8_t TxBuffer5[] ="门磁报警";
uint8_t TxBuffer6[] ="幕帘报警";
uint8_t TxBuffer7 = 'o';

*/
 /* Private define ------------------------------------------------------------*/
/*
#define TxBufferSize0   (countof(TxBuffer0) - 1)
#define RxBufferSize0   (countof(TxBuffer0) - 1)*/
#define TxBufferSize1   (countof(TxBuffer1) - 1)
#define RxBufferSize1   (countof(TxBuffer1) - 1)/*
#define TxBufferSize2   (countof(TxBuffer2) - 1)
#define RxBufferSize2   (countof(TxBuffer2) - 1)
#define TxBufferSize3   (countof(TxBuffer3) - 1)
#define RxBufferSize3   (countof(TxBuffer3) - 1)
#define TxBufferSize4  (countof(TxBuffer4) - 1)
#define RxBufferSize4   (countof(TxBuffer4) - 1)
#define TxBufferSize5  (countof(TxBuffer5) - 1)
#define RxBufferSize5   (countof(TxBuffer5) - 1)
#define TxBufferSize6  (countof(TxBuffer6) - 1)
#define RxBufferSize6   (countof(TxBuffer6) - 1)
*/
/* Private macro -------------------------------------------------------------*/

#define countof(a)   (sizeof(a) / sizeof(*(a)))

uint8_t RxBuffer1[RxBufferSize1];


USART_InitTypeDef USART_InitStructure;


uint8_t NbrOfDataToTransfer1 = TxBufferSize1;
uint8_t NbrOfDataToRead1 = RxBufferSize1;

__IO TestStatus TransferStatus1 = FAILED; 

volatile uint8_t      read_flag = 0;			//串口接收WIFI数据标志位
volatile uint16_t UART_data_len = 0;            //串口接收长度 
uint8_t rec_f;


USART_InitTypeDef USART_InitStruct;
USART_ClockInitTypeDef USART_ClockInitStruct;
int16_t USART_FLAG;

void USART_INIT()
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
	/* Enable the USART Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	/* Enable the USART1 peripheral clock*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	/* Enable the GPIOB peripheral clock  PB 6.7*/
  RCC_AHBPeriphClockCmd(USART1_TX_GPIO_CLK|USART1_RX_GPIO_CLK, ENABLE);
	/* Configure the PB 6(TXD).7(RXD) AF Function */
  GPIO_PinAFConfig(USART1_TX_PORT, USART1_TX_SOURCE, USART1_TX_AF);
  GPIO_PinAFConfig(USART1_RX_PORT, USART1_RX_SOURCE, USART1_RX_AF);

/* USARTx configured as follow:
		- BaudRate = 115200 baud  
		- Word Length = 8 Bits
		- Two Stop Bit
		- No parity
		- Hardware flow control disabled (RTS and CTS signals)
		- Receive and transmit enabled
	*/
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  /* Configure USART Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = USART1_TX_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(USART1_TX_PORT, &GPIO_InitStructure);
  /* Configure USART Rx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = USART1_RX_PIN;
  GPIO_Init(USART1_RX_PORT, &GPIO_InitStructure);
  /* USART configuration */
  USART_Init(USART1, &USART_InitStructure);  
	/* Configure USART Receive Interrupt */
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
  /* Enable USART */
  USART_Cmd(USART1, ENABLE);


}



uint8_t USART_OUT(USART_TypeDef* USARTx, char *Data,uint16_t Len)
{ 
	uint16_t i;
	if(read_flag == TRUE)
	   return 0xFF;	
	USART_GetFlagStatus(USARTx, USART_FLAG_TC);
	for(i=0; i<Len; i++)
	{
		USART_SendData(USARTx, Data[i]);
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC)==RESET);
	}
	return 0;
}

void USART2_OUT(USART_TypeDef* USARTx, uint8_t *Data,uint16_t Len)
{ 
	uint16_t i;
	USART_GetFlagStatus(USARTx, USART_FLAG_TC);
	for(i=0; i<Len; i++)
	{
		USART_SendData(USARTx, Data[i]);
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC)==RESET);
	}
}



void USART_RxTx(void)
{
	

}
/**
  * @brief  
  * @param  None
  * @retval None
  */
void BHKS_Serial_PutString( USART_TypeDef* USARTx,uint8_t *s)
{
  while (*s != '\0')
  {
    BHKS_SerialPutChar(USARTx,*s);
    s++;
  }
}
/**
  * @brief  
  * @param  None
  * @retval None
  */
void BHKS_SerialPutChar(USART_TypeDef* USARTx,uint8_t c)
{ 
  USART_SendData(USARTx, c);
  while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET)
  {}
}

void Reset_Target(void)
{
	GPIO_ResetBits(GPIOC, GPIO_Pin_7);
   // delay_ms(20);
    GPIO_SetBits(GPIOC, GPIO_Pin_7); 
}


