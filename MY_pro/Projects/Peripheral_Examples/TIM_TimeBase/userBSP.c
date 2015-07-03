#include "userBSP.h"
//#include "stm32f0xx_rcc.h"
//#include "main.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* TIMER variables ---------------------------------------------------------*/
__IO uint16_t CCR1_Val = 0;
__IO uint16_t CCR2_Val = 0;
__IO uint16_t CCR3_Val = 500;
__IO uint16_t CCR4_Val = 3999;
uint16_t PrescalerValue = 0;
uint16_t g_ms_con;
/*USART variables-------------------------------------------------------------*/
//__IO TestStatus TransferStatus1 = FAILED; 

volatile uint8_t      read_flag = 0;			//串口接收WIFI数据标志位
volatile uint16_t UART_data_len = 0;            //串口接收长度 
uint8_t rec_f;


USART_InitTypeDef USART_InitStruct;
USART_ClockInitTypeDef USART_ClockInitStruct;
int16_t USART_FLAG;


static u8  fac_us=0;//us延时倍乘数
static u16 fac_ms=0;//ms延时倍乘数


/*==========================================================================================================================*/
/*=======================================LED & BUTTON==============================================================================*/
/*==========================================================================================================================*/


/** @defgroup STM32F0308_DISCOVERY_LOW_LEVEL_Private_Variables
  * @{
  */ 
GPIO_TypeDef* GPIO_PORT[LEDn] = {LED3_GPIO_PORT, LED4_GPIO_PORT};
const uint16_t GPIO_PIN[LEDn] = {LED3_PIN, LED4_PIN};
const uint32_t GPIO_CLK[LEDn] = {LED3_GPIO_CLK, LED4_GPIO_CLK};

GPIO_TypeDef* BUTTON_PORT[BUTTONn] = {USER_BUTTON_GPIO_PORT}; 

const uint16_t BUTTON_PIN[BUTTONn] = {USER_BUTTON_PIN}; 

const uint32_t BUTTON_CLK[BUTTONn] = {USER_BUTTON_GPIO_CLK};

const uint16_t BUTTON_EXTI_LINE[BUTTONn] = {USER_BUTTON_EXTI_LINE};

const uint16_t BUTTON_PORT_SOURCE[BUTTONn] = {USER_BUTTON_EXTI_PORT_SOURCE};
								 
const uint16_t BUTTON_PIN_SOURCE[BUTTONn] = {USER_BUTTON_EXTI_PIN_SOURCE}; 

const uint16_t BUTTON_IRQn[BUTTONn] = {USER_BUTTON_EXTI_IRQn};

/**
  * @}
  */ 


/** @defgroup STM32F0308_DISCOVERY_LOW_LEVEL_Private_FunctionPrototypes
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup STM32F0308_DISCOVERY_LOW_LEVEL_Private_Functions
  * @{
  */ 

/**
  * @brief  Configures LED GPIO.
  * @param  Led: Specifies the Led to be configured. 
  *   This parameter can be one of following parameters:
  *     @arg LED3
  *     @arg LED4
  * @retval None
  */
void BSP_LEDInit(Led_TypeDef Led)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  /* Enable the GPIO_LED Clock */
  RCC_AHBPeriphClockCmd(GPIO_CLK[Led], ENABLE);

  /* Configure the GPIO_LED pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN[Led];
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIO_PORT[Led], &GPIO_InitStructure);
  /*GPIO_InitStructure.GPIO_Pin = GPIO_BL;
  GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
  GPIO_Init(GPIO_BL_PORT, &GPIO_InitStructure);*/
  /*GPIO_InitStructure.GPIO_Pin = GPIO_PIN[Led];
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//GPIO_Mode_OUT;
  //GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_PinAFConfig(GPIO_PORT[Led], GPIO_PIN[LEDn], GPIO_AF_1)//TIM3CH4
  GPIO_Init(GPIO_PORT[Led], &GPIO_InitStructure);*/
}

/**
  * @brief  Turns selected LED On.
  * @param  Led: Specifies the Led to be set on. 
  *   This parameter can be one of following parameters:
  *     @arg LED3
  *     @arg LED4  
  * @retval None
  */
void BSP_LEDOn(Led_TypeDef Led)
{
  GPIO_PORT[Led]->BSRR = GPIO_PIN[Led];
}

/**
  * @brief  Turns selected LED Off.
  * @param  Led: Specifies the Led to be set off. 
  *   This parameter can be one of following parameters:
  *     @arg LED3
  *     @arg LED4 
  * @retval None
  */
void BSP_LEDOff(Led_TypeDef Led)
{
  GPIO_PORT[Led]->BRR = GPIO_PIN[Led];
}

/**
  * @brief  Toggles the selected LED.
  * @param  Led: Specifies the Led to be toggled. 
  *   This parameter can be one of following parameters:
  *     @arg LED3
  *     @arg LED4  
  * @retval None
  */
void BSP_LEDToggle(Led_TypeDef Led)
{
  GPIO_PORT[Led]->ODR ^= GPIO_PIN[Led];
}

/**
  * @brief  Configures Button GPIO and EXTI Line.
  * @param  Button: Specifies the Button to be configured.
  *   This parameter can be:
  *     @arg BUTTON_USER: User Push Button      
  * @param  Button_Mode: Specifies Button mode.
  *   This parameter can be one of following parameters:   
  *     @arg BUTTON_MODE_GPIO: Button will be used as simple IO 
  *     @arg BUTTON_MODE_EXTI: Button will be connected to EXTI line with interrupt
  *                            generation capability
  * @retval None
  */
void BSP_PBInit(Button_TypeDef Button, ButtonMode_TypeDef Button_Mode)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable the BUTTON Clock */
  RCC_AHBPeriphClockCmd(BUTTON_CLK[Button], ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

  /* Configure Button pin as input */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = BUTTON_PIN[Button];
  GPIO_Init(BUTTON_PORT[Button], &GPIO_InitStructure);
  

    /* Enable and set Button EXTI Interrupt to the lowest priority */
    NVIC_InitStructure.NVIC_IRQChannel = BUTTON_IRQn[Button];
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0x03;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure); 
  
}

/**
  * @brief  Returns the selected Button state.
  * @param  Button: Specifies the Button to be checked.
  *   This parameter can be one of following parameters:
  *     @arg BUTTON_USER: User Push Button    
  * @retval The Button GPIO pin value.
  */
uint32_t BSP_PBGetState(Button_TypeDef Button)
{
  /* There is no Wakeup button on STM32f0308 Discovery Kit */
  return GPIO_ReadInputDataBit(BUTTON_PORT[Button], BUTTON_PIN[Button]);
}

/*==========================================================================================================================*/
/*=======================================TIM==============================================================================*/
/*==========================================================================================================================*/


/**
  * @brief  Configure the TIM IRQ Handler.
  * @param  None
  * @retval None
  */
void TIM_Config(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  //TIM_OCInitTypeDef  TIM_OCInitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  /* TIM3 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  /* Enable the TIM3 gloabal Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;// TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  /* -----------------------------------------------------------------------
    TIM3 Configuration: Output Compare Timing Mode:
    
    In this example TIM3 input clock (TIM3CLK) is set to APB1 clock (PCLK1),  
      => TIM3CLK = PCLK1 = SystemCoreClock = 48 MHz
          
    To get TIM3 counter clock at 6 MHz, the prescaler is computed as follows:
       Prescaler = (TIM3CLK / TIM3 counter clock) - 1
       Prescaler = (PCLK1 /6 MHz) - 1
                                                  
    CC3 update rate = TIM3 counter clock / CCR3_Val = 439.4 Hz
    ==> Toggling frequency = 219.7 Hz
    
    CC4 update rate = TIM3 counter clock / CCR4_Val = 878.9 Hz
    ==> Toggling frequency = 439.4 Hz

    Note: 
     SystemCoreClock variable holds HCLK frequency and is defined in system_stm32f2xx.c file.
     Each time the core clock (HCLK) changes, user had to call SystemCoreClockUpdate()
     function to update SystemCoreClock variable value. Otherwise, any configuration
     based on this variable will be incorrect.    
  ----------------------------------------------------------------------- */   

  /* Compute the prescaler value */
 //PrescalerValue = (uint16_t) (SystemCoreClock  / 6000000) - 1;
  PrescalerValue = (uint16_t) (SystemCoreClock  / 20000) - 1;  //48m/24k =2k

  /* Time base configuration */
  //TIM_TimeBaseStructure.TIM_Period = 65535;
  TIM_TimeBaseStructure.TIM_Period = 20-1;//4000-1;//2000-1;//1ms
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  /* Prescaler configuration */
  TIM_PrescalerConfig(TIM3, PrescalerValue, TIM_PSCReloadMode_Immediate);

 
  /* Output Compare Timing Mode configuration: Channel1 */
  /*TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  */
  /* Output Compare Timing Mode configuration: Channel2 */
  /*TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR2_Val;
  TIM_OC2Init(TIM3, &TIM_OCInitStructure);

  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Disable);*/
  /* Output Compare Timing Mode configuration: Channel3 */
  /*TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR3_Val;

  TIM_OC3Init(TIM3, &TIM_OCInitStructure);

  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Disable);*/

  /* Output Compare Timing Mode configuration: Channel4 */
  /*TIM_OCInitStructure.TIM_OutputState = TIM_OCMode_Timing;//TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR4_Val;

  TIM_OC4Init(TIM3, &TIM_OCInitStructure);

  TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Disable);*/
   
  /* TIM Interrupts enable */
  TIM_ITConfig(TIM3, TIM_IT_Update , ENABLE);//TIM_ITConfig(TIM3, TIM_IT_CC3 | TIM_IT_CC4, ENABLE);| TIM_IT_CC3 | TIM_IT_CC4

  /* TIM3 enable counter */
  TIM_Cmd(TIM3, ENABLE);
}

void tim3_it_ms_pro(void)
{
#ifdef tim_dub
  g_ms_con++;
  if(g_ms_con > 100)
  {
    BSP_LEDToggle(LED4);
    g_ms_con = 0;
    //USART_OUT(USART1,char_test,16);
  }
#endif
  //USART_OUT(USART1,char_test,16);
  
  TIM_ClearITPendingBit(TIM3,TIM_FLAG_Update);
  //TIM_Cmd(TIM3,DISABLE);
  /*read_flag = TRUE;				   //串口接收完一包
  //USART2_OUT(USART2,uCmdRspFrame.uCmdRspBuf,UART_data_len);
  data_len = UART_data_len;
  UART_data_len=0;	//本次数据包接收完毕，计数器清空 
*/
  if(recv_byte_con != 0xff)     //0xff为字节间 停止计时标志，recv_byte_con != 0xff 时代表需要字节间计时
  {
    recv_byte_con++;     
    if(recv_byte_con>100)           //字节间 计时超过100ms 超时 
    {
      read_flag = TRUE;				   //串口接收完一包
      //USART2_OUT(USART2,uCmdRspFrame.uCmdRspBuf,UART_data_len);
      data_len = UART_data_len;           //得到数据长度
      UART_data_len=0;	                //本次数据包接收完毕，计数器清空 
      recv_byte_con = 0xff;              //禁止字节间计时
    }
    
  }
  m_sec_con++;
  if(m_sec_con > 1000)
  {
    m_sec_con = 0;
    if(dat_send_SEC_con < (DAT_SEND_PERIOD+1))
    {
      dat_send_SEC_con++;        //举例上一次发送开始计时 计时累加
    } 
    Time_local_buf.frame.sec++;
    if(Time_local_buf.frame.sec == 60)
    {
      Time_local_buf.frame.sec = 0;
      Time_local_buf.frame.min++;
      if(Time_local_buf.frame.min == 60)
      {
        Time_local_buf.frame.min = 0;
        Time_local_buf.frame.hour++;
      }
    }
  }
  
  if(BSP_PBGetState(BUTTON_USER) == 1)
  {
    WIFI_RELD_GPIO_PORT->BSRR = WIFI_RELD_PIN;
    if(wifi_rld_off_flg == 1)
    {
      at_re_in_flg = 1;
      wifi_rld_off_flg = 0;
    }
  }else
  {
    //BSP_LEDOff(LED3);
   WIFI_RELD_GPIO_PORT->BRR = WIFI_RELD_PIN;
   wifi_rld_off_flg = 1;
  }
  
}


/*==========================================================================================================================*/
/*=======================================USART==============================================================================*/
/*==========================================================================================================================*/

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
void USART_PIN_FL(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  RCC_AHBPeriphClockCmd(USART1_TX_GPIO_CLK|USART1_RX_GPIO_CLK, ENABLE);
	/* Configure the PB 6(TXD).7(RXD) AF Function */
  GPIO_PinAFConfig(USART1_TX_PORT, USART1_TX_SOURCE, USART1_TX_AF);
  GPIO_PinAFConfig(USART1_RX_PORT, USART1_RX_SOURCE, USART1_RX_AF);

  GPIO_InitStructure.GPIO_Pin = USART1_TX_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(USART1_TX_PORT, &GPIO_InitStructure);
  /* Configure USART Rx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = USART1_RX_PIN;
  GPIO_Init(USART1_RX_PORT, &GPIO_InitStructure);
 


}



uint8_t USART_OUT(USART_TypeDef* USARTx, char *Data,uint16_t Len)
{ 
	uint16_t i;
	if(read_flag == TRUE)    //正在读取中
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



void WIFI_EN_init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  /* Enable the GPIO_LED Clock */
  RCC_AHBPeriphClockCmd(WIFI_EN_GPIO_CLK, ENABLE);

  /* Configure the GPIO_LED pin */
  GPIO_InitStructure.GPIO_Pin = WIFI_EN_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(WIFI_EN_GPIO_PORT, &GPIO_InitStructure);
}
void WIFI_RESET_init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  /* Enable the GPIO_LED Clock */
  RCC_AHBPeriphClockCmd(WIFI_RESET_GPIO_CLK, ENABLE);

  /* Configure the GPIO_LED pin */
  GPIO_InitStructure.GPIO_Pin = WIFI_RESET_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(WIFI_RESET_GPIO_PORT, &GPIO_InitStructure);
}
void WIFI_RELD_init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  /* Enable the GPIO_LED Clock */
  RCC_AHBPeriphClockCmd(WIFI_RELD_GPIO_CLK, ENABLE);

  /* Configure the GPIO_LED pin */
  GPIO_InitStructure.GPIO_Pin = WIFI_RELD_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(WIFI_RELD_GPIO_PORT, &GPIO_InitStructure);
}
void WIFI_TEST_LED_init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  /* Enable the GPIO_LED Clock */
  RCC_AHBPeriphClockCmd(WIFI_RESET_GPIO_CLK, ENABLE);

  /* Configure the GPIO_LED pin */
  GPIO_InitStructure.GPIO_Pin = WIFI_RESET_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(WIFI_RESET_GPIO_PORT, &GPIO_InitStructure);
}

void WIFI_EN_ON(void)    //WIFI模块低电平使能
{
   WIFI_EN_GPIO_PORT->BSRR = WIFI_EN_PIN;
}
void WIFI_EN_OFF(void)   //低电平掉电
{
  WIFI_EN_GPIO_PORT->BRR = WIFI_EN_PIN;
}
void WIFI_RESET_LOW(void)
{
  WIFI_RESET_GPIO_PORT->BRR = WIFI_RESET_PIN;
}
void WIFI_RESET_HAIGH(void)
{
  WIFI_RESET_GPIO_PORT->BSRR = WIFI_RESET_PIN;
}
void WIFI_Reset_Target(void)
{
   WIFI_RESET_LOW();
   delay_ms(20);
   WIFI_RESET_HAIGH();
}


/*==========================================================================================================================*/
/*=======================================DELAY==============================================================================*/
/*==========================================================================================================================*/

//初始化延迟函数
//SYSTICK的时钟固定为HCLK时钟的1/8
//SYSCLK:系统时钟
void delay_init(u8 SYSCLK)
{
	//SysTick->CTRL&=0xfffffffb;//bit2清空,选择外部时钟  HCLK/8
  SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);  //设置SysTick时钟源
	fac_us=SYSCLK/8;	
   
	fac_ms=(u16)fac_us*1000;
}							    
//延时nms
//注意nms的范围
//SysTick->LOAD为24位寄存器,所以,最大延时为:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK单位为Hz,nms单位为ms
//对72M条件下,nms<=1864 
void delay_ms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;           //清空计数器
	SysTick->CTRL=0x01 ;          //开始倒数  
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//等待时间到达   
	SysTick->CTRL=0x00;       //关闭计数器
	SysTick->VAL =0X00;       //清空计数器	  	    
}   
//延时nus
//nus为要延时的us数.		    								   
void delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; //时间加载	  		 
	SysTick->VAL=0x00;        //清空计数器
	SysTick->CTRL=0x01 ;      //开始倒数 	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//等待时间到达   
	SysTick->CTRL=0x00;       //关闭计数器
	SysTick->VAL =0X00;       //清空计数器	 
}
//延时ns
//ns为要延时的s数.
void delay_s(u16 ns)
{	 
	u16 temp;
	temp = ns;
	while(temp)
	{
		delay_ms(1000); 
		temp--;
	}		  	  
}