#include "userBSP.h"
//#include "stm32f0xx_rcc.h"
//#include "main.h"
#include "stm32f0308_discovery.h"

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

void Pranus_CLK_Config(void)
{
	RCC_ClocksTypeDef RCC_ClocksSet;
	RCC_DeInit();
	RCC_HSEConfig(RCC_HSE_OFF);
	RCC_HSICmd(ENABLE);
	while(!RCC_GetFlagStatus(RCC_FLAG_HSIRDY));
	RCC_PLLConfig(RCC_PLLSource_HSI_Div2,RCC_PLLMul_12);      //48Mhz
	RCC_PLLCmd(ENABLE);
	while(!RCC_GetFlagStatus(RCC_FLAG_PLLRDY));
	FLASH_PrefetchBufferCmd(ENABLE);
	while(!FLASH_GetPrefetchBufferStatus());
	FLASH_SetLatency(FLASH_Latency_1);
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	if(RCC_GetSYSCLKSource()!=PLL_Used)
	{
		while(1);
	}
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLKConfig(RCC_HCLK_Div1);
	RCC_GetClocksFreq(&RCC_ClocksSet);
	if(RCC_ClocksSet.SYSCLK_Frequency!=48000000)
	{
		while(1);
	}
}

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
  TIM_TimeBaseStructure.TIM_Period = 20;//4000-1;//2000-1;//1ms
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
  if(g_ms_con == 1000)
  {
    STM_EVAL_LEDToggle(LED3);
    g_ms_con = 0;
    USART_OUT(USART1,char_test,16);
  }
#endif
  //USART_OUT(USART1,char_test,16);
  
	 	TIM_ClearITPendingBit(TIM3,TIM_FLAG_Update);
		TIM_Cmd(TIM3,DISABLE);
 
    
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
	//GPIO_ResetBits(GPIOC, GPIO_Pin_7);
        //GPIO_ResetBits(GPIO_reset_413, GPIO_Pin_reset_413);
        GPIO_ResetBits(LED4_GPIO_PORT, LED4_PIN);
   delay_ms(20);
   // GPIO_SetBits(GPIOC, GPIO_Pin_7); 
   //GPIO_SetBits(GPIO_reset_413, GPIO_Pin_reset_413);
   GPIO_SetBits(LED4_GPIO_PORT, LED4_PIN);
}


/*==========================================================================================================================*/
/*=======================================DELAY==============================================================================*/
/*==========================================================================================================================*/

//初始化延迟函数
//SYSTICK的时钟固定为HCLK时钟的1/8
//SYSCLK:系统时钟
void delay_init(u8 SYSCLK)
{
	SysTick->CTRL&=0xfffffffb;//bit2清空,选择外部时钟  HCLK/8
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
void Delay_Ms(uint16_t ms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)ms*fac_ms;//时间加载(SysTick->LOAD为24bit)
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

/*==========================================================================================================================*/
/*=======================================AD_DMA=============================================================================*/
/*==========================================================================================================================*/
__IO uint32_t TempSensVoltmv = 0, VrefIntVoltmv = 0;
__IO uint16_t RegularConvData_Tab[4];

/**
  * @brief  ADC1 channel with DMA configuration
  * @param  None
  * @retval None
  */
void ADC_CH_DMA_Config(void)
{
  ADC_InitTypeDef     ADC_InitStructure;
  DMA_InitTypeDef     DMA_InitStructure;
  
  /* ADC1 DeInit */  
  ADC_DeInit(ADC1);
  
  /* ADC1 Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  
  /* DMA1 clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1 , ENABLE);
  
  /* DMA1 Channel1 Config */
  DMA_DeInit(DMA1_Channel1);
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC1_DR_Address;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)RegularConvData_Tab;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = 4;//2;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);
  
  /* DMA1 Channel1 enable */
  DMA_Cmd(DMA1_Channel1, ENABLE);
  
  /* ADC DMA request in circular mode */
  ADC_DMARequestModeConfig(ADC1, ADC_DMAMode_Circular);
  
  /* Enable ADC_DMA */
  ADC_DMACmd(ADC1, ENABLE);  
  
  /* Initialize ADC structure */
  ADC_StructInit(&ADC_InitStructure);
  
  
  /* Configure the ADC1 in continous mode withe a resolutuion equal to 12 bits  */
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_10b;//ADC_Resolution_12b;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; 
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Backward;
  ADC_Init(ADC1, &ADC_InitStructure); 
 
  /* Convert the ADC1 temperature sensor  with 55.5 Cycles as sampling time */ 
  /*ADC_ChannelConfig(ADC1, ADC_Channel_TempSensor , ADC_SampleTime_55_5Cycles);  
  ADC_TempSensorCmd(ENABLE);*/
  
  /* Convert the ADC1 Vref  with 55.5 Cycles as sampling time */ 
  /*ADC_ChannelConfig(ADC1, ADC_Channel_Vrefint , ADC_SampleTime_55_5Cycles); 
  ADC_VrefintCmd(ENABLE);*/
  ADC_ChannelConfig(ADC1, ADC_Channel_ELE , ADC_SampleTime_55_5Cycles);
  ADC_ChannelConfig(ADC1, ADC_Channel_Sensor1 , ADC_SampleTime_55_5Cycles);
  ADC_ChannelConfig(ADC1, ADC_Channel_Sensor2 , ADC_SampleTime_55_5Cycles);
  ADC_ChannelConfig(ADC1, ADC_Channel_Sensor3 , ADC_SampleTime_55_5Cycles);
  /* ADC Calibration */
  ADC_GetCalibrationFactor(ADC1);
  
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);     
  
  /* Wait the ADRDY falg */
  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADRDY));//ADC_CFGR1_ALIGN)); 
  
  /* ADC1 regular Software Start Conv */ 
  ADC_StartOfConversion(ADC1);
}


	/**-----------------------------------
  * ADC初始化
	 配置ADIN0~ADIN2为模拟输入，扫描单次
  */
		void Init_ADC02(void)
{
  /*
  //ADC1_DeInit();
  ADC1_ConversionConfig(ADC1_CONVERSIONMODE_SINGLE, ADC1_CHANNEL_2, ADC1_ALIGN_RIGHT);    //单次
  ADC1_ScanModeCmd(ENABLE); //扫描模式 
  ADC1_DataBufferCmd(ENABLE);//开启数据缓存
  ADC1_Cmd(ENABLE);*/
  
}

	/**-----------------------------------
  * ADC初始化
	 配置ADIN0~ADIN2为模拟输入，扫描单次
  */
		void Init_ADC3(void)
{
  int a ;/*
  //ADC1_DeInit();
  ADC1_ConversionConfig(ADC1_CONVERSIONMODE_SINGLE, ADC1_CHANNEL_3, ADC1_ALIGN_RIGHT);    //单次
  ADC1_PrescalerConfig(ADC1_PRESSEL_FCPU_D2);
  ADC1_Cmd(ENABLE);*/
}

	/**-----------------------------------
  * 读取ADC转换结果，到 u16_adc1[3]数组中
  ------------------------------------------------*/
//void ADC1_GetSConversionValueFromBuffer((uint16_t*)AD_Value, uint8_t Num)
void ADC1_GetSConversionValueFromBuffer(void)
{	
  //uint8_t temph = 0;
  //uint8_t templ = 0;
  uint16_t temp = 0;
		
  uint16_t *pre = u16_adc1;
  uint8_t i;
  for(i=0; i<3; i++)
  {
    //if ((ADC1->CR2 & ADC1_CR2_ALIGN) != 0) /* Right alignment */
    if (((DMA_GetFlagStatus(DMA1_FLAG_TC1)) == RESET)&&((ADC1->CFGR1&ADC_FLAG_ADRDY)==0))  
    {                                                                 
        /* Read LSB first */
      //templ = *( &(ADC1->DB0RL) + i*2 ) ;
        /* Then read MSB */
      //temph = *( &(ADC1->DB0RH) + i*2 ) ;
				
      //temp = RegularConvData_Tab[i];
      //*pre = (uint16_t)(templ | (uint16_t)(temph << (uint8_t)8));
     //*pre = temp;
     // pre ++;
      u16_adc1[i] = RegularConvData_Tab[i];
     }
    else /* Left alignment */
    {
        /* Read MSB firts*/
      //temph = *( &(ADC1->DB0RH) + i*2 ) ;
         /* Then read LSB */
      //templ = *( &(ADC1->DB0RL) + i*2 ) ;
      //*pre = (uint16_t)((uint16_t)((uint16_t)templ << 6) | (uint16_t)((uint16_t)temph << 8));
     // pre ++;
      ;
    }
			

  }

}



/**-----------------------------------
  *IO初始化
	 配置ADIN0~ADIN3为模拟输入，扫描单次
  */

void GPIO_User_Init(void)
{
       
   GPIO_InitTypeDef  GPIO_InitStructure;
   
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);

    /*Configure the GPIO_LED pin */ //PD0~3 设置为复用 AD0~AD3
   //GPIO_Init(GPIO_AD_PORT, (GPIO_ADC0|GPIO_ADC1|GPIO_ADC2|GPIO_ADC3), GPIO_MODE_IN_FL_NO_IT);
  GPIO_InitStructure.GPIO_Pin = (GPIO_ADC0|GPIO_ADC1|GPIO_ADC2|GPIO_ADC3);
  GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIO_AD_PORT, &GPIO_InitStructure);
   
  //GPIO_Init(GPIO_Beep_PORT,GPIO_Beep,GPIO_MODE_OUT_PP_HIGH_FAST);
  GPIO_InitStructure.GPIO_Pin = GPIO_Beep;
  GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIO_Beep_PORT, &GPIO_InitStructure);
  
 //GPIO_Init(GPIO_VCC5_PORT,GPIO_VCC5_EN,GPIO_MODE_OUT_PP_HIGH_SLOW);
  GPIO_InitStructure.GPIO_Pin = GPIO_VCC5_EN;
  GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIO_VCC5_PORT, &GPIO_InitStructure);
// 	GPIO_Init(GPIO_LCD_PORT,GPIO_LCD_Power,GPIO_MODE_OUT_PP_HIGH_FAST);
	
  //GPIO_Init(GPIO_Key12_PORT,(GPIO_Key_SW1|GPIO_Key_SW2),GPIO_MODE_IN_PU_NO_IT);
  //GPIO_Init(GPIO_Key3_PORT,GPIO_Key_SW3,GPIO_MODE_IN_PU_NO_IT);
  GPIO_InitStructure.GPIO_Pin = GPIO_Key_SW1|GPIO_Key_SW2|GPIO_Key_SW3;
  GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIO_Key12_PORT, &GPIO_InitStructure);
  
  //GPIO_Init(GPIO_Key4_PORT,GPIO_Key_SW4,GPIO_MODE_IN_PU_NO_IT);
  GPIO_InitStructure.GPIO_Pin = GPIO_Key_SW4;
  GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIO_Key4_PORT, &GPIO_InitStructure);
  
  //GPIO_Init(GPIO_PSW_PORT,GPIO_PSW,GPIO_MODE_OUT_PP_LOW_FAST);
  //GPIO_Init(GPIO_PS1_PORT,GPIO_PS1,GPIO_MODE_OUT_PP_LOW_FAST);
  //GPIO_Init(GPIO_PS2_PORT,GPIO_PS2,GPIO_MODE_OUT_PP_LOW_FAST);
  //GPIO_Init(GPIO_PS3_PORT,GPIO_PS3,GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_InitStructure.GPIO_Pin = GPIO_PSW|GPIO_PS1|GPIO_PS2|GPIO_PS3;
  GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIO_PSW_PORT, &GPIO_InitStructure);
	
  //GPIO_Init(GPIO_PM_PORT,GPIO_I_control,GPIO_MODE_OUT_PP_LOW_FAST);
  //GPIO_Init(GPIO_BAT_PORT,GPIO_CE,GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_InitStructure.GPIO_Pin = GPIO_CE|GPIO_I_control;
  GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
  GPIO_Init(GPIO_BAT_PORT, &GPIO_InitStructure);
  
  //GPIO_Init(GPIO_BAT_PORT,GPIO_CHAG,GPIO_MODE_IN_PU_NO_IT);
  GPIO_InitStructure.GPIO_Pin = GPIO_CHAG;
  GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
  GPIO_Init(GPIO_BAT_PORT, &GPIO_InitStructure);
        
  //GPIO_WriteHigh(GPIO_BAT_PORT,GPIO_CE);
  GPIO_SetBits(GPIO_BAT_PORT, GPIO_CE);
  
  //GPIO_Init(GPIO_MOTOR_PORT,GPIO_MOTOR_EN,GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_InitStructure.GPIO_Pin = GPIO_MOTOR_EN;
  GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
  GPIO_Init(GPIO_MOTOR_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_BL;
  GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
  GPIO_Init(GPIO_BL_PORT, &GPIO_InitStructure);

  //GPIO_SetBits(GPIO_BL_PORT, GPIO_BL);
  

  
  //GPIO_Init(GPIOD, wifi_EN,GPIO_MODE_OUT_PP_LOW_SLOW);     //init pwr_ctl_io
  //GPIO_WriteHigh(GPIOD,wifi_EN);   //off
	
  //GPIO_Init(GPIOA, GPIO_PIN_3, GPIO_MODE_OUT_OD_HIZ_FAST);//串口TX
  moni_spi_Init();
 }	
void GPIO_BL_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
 
  RCC_AHBPeriphResetCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_BL;
  GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
  GPIO_Init(GPIO_BL_PORT, &GPIO_InitStructure);
   
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_BL;
  GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
  GPIO_Init(GPIO_BL_PORT, &GPIO_InitStructure);

 
}

#if defined (PV) || defined(PH) || defined(PHV)
	/**-----------------------------------
  *初始化定时器，时钟为fcpu 周期为16 实测定时周期为10us
  ------------------------------------------------*/
void Init_Timer4(void)
{
  u8 a;

	//TIM6_DeInit();
	//TIM4_TimeBaseInit(TIM4_PRESCALER_1, 0xA0);
  /* Clear TIM4 update flag */
 // TIM4_ClearFlag(TIM4_FLAG_UPDATE);
	
	/* Enable update interrupt */
	//TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);

}
#endif
	/**-----------------------------------
  *初始化定时器，时钟为fcpu 周期为255 实测定时周期为10ms
  ------------------------------------------------*/
/*void Init_Timer5(void)
{

	//TIM6_DeInit();
	TIM5_TimeBaseInit(TIM5_PRESCALER_256, 625);
  TIM5_ClearFlag(TIM5_FLAG_UPDATE);
	TIM5_ITConfig(TIM5_IT_UPDATE, ENABLE);
	//TIM5_Cmd(ENABLE);
}*/

void Init_Timer3(void)
{
  TIM_Config();
	//TIM6_DeInit();
  /*TIM3_TimeBaseInit(TIM3_PRESCALER_256, 625);
  TIM3_ClearFlag(TIM3_FLAG_UPDATE);
  TIM3_ITConfig(TIM3_IT_UPDATE, ENABLE);*/
	//TIM5_Cmd(ENABLE);
}
	/**-----------------------------------
  * 初始化看门狗
  ------------------------------------------------*/
	void WatchD_Init(void)
 {
   int a ;
  /*IWDG_Enable();
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
  IWDG_SetPrescaler(IWDG_Prescaler_256);
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Disable);
		//IWDG_Enable();*/
 }
	
void Beep_On(void)
{
  #ifdef Beep_Active
  GPIO_SetBits(GPIO_Beep_PORT,GPIO_Beep); 
  #else
  //BEEP_Cmd(ENABLE);
  TIM_CtrlPWMOutputs(TIM1, ENABLE);
  #endif
}

void Beep_Off(void)
{
 
  #ifdef Beep_Active
  GPIO_ResetBits(GPIO_Beep_PORT,GPIO_Beep);  
  #else
  //BEEP_Cmd(DISABLE);
  TIM_CtrlPWMOutputs(TIM1, DISABLE);
  //if PV
  //GPIO_WriteLow(GPIO_Beep_PORT,GPIO_Beep);   //蜂鸣器关掉
  #endif
}
	/**-----------------------------------
  * 喂狗函数
  ------------------------------------------------*/
void WatchDogFeed(void)
{
  int a ;
	/*IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_ReloadCounter();
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Disable);*/
}
	/**-----------------------------------
  定时器中断后处理函数 中断服务 10ms计数循环
  ------------------------------------------------*/
	

 void Timer4Cnt_Process_IRQ(void)
{
  
//#if defined (PV) || defined(PH)	|| defined(PHV)
  int a ;
/*		   if(flag_ad)
		     {
				 Read_PM_Value();
				 flag_ad = RESET;
			   }
	//#enif
		switch (timer_cnt)
	  {
		case 32://21
			PM_ControlOff();
			TIM4_Cmd(DISABLE);
				break;
		case 28:
			if(flag_ad == RESET)
			{

			ADC1_StartConversion();
			flag_ad = SET;
		  }
				break;
		case 0:
			PM_ControlOn();
				break;
		default:
				break;
	  }
#endif
		timer_cnt++;
		//TIM6_Cmd(ENABLE);
		//enableInterrupts();
*/		
		
}
//#endif

 void Timer3Cnt_Process_IRQ(void)
{
  KeyScanFlag = SET;
  //WatchDogFeed();
  switch(timer5_cnt)
  {
#if defined (PV) || defined(PH) || defined(PHV) 
    case 0:
      //TIM6_Cmd(ENABLE);
      PM_En_Flag = SET;
      //Init_ADC3();
      break;
  case 30:
    PM_En_Flag =RESET;
    PM_ProcessFlag = SET;
    //TIM4_Cmd(DISABLE);
    break;
#endif 
			
  case 31:
    DhtFlag = SET;
    break;
#ifdef SINGLE
  case 32:
    AD_ScanFlag = SET; 
    break;
#endif
  default:
    break;
  }

#if defined (PV) || defined(PH) || defined(PHV) 
  if(	PM_En_Flag )
  {
    timer_cnt = 0;
    //TIM4_Cmd(ENABLE);
  }
#endif 
  if(timer5_cnt ==100)           //秒 计数
  {
    timer5_cnt = 0;	
    cnt_s ++;   
#ifdef PRINT  //串口1S钟打印一次
    PrintFlag = SET;
#endif
    //STM_EVAL_LEDToggle(LED3);
    //DisFlag = SET; //没秒一次示数刷新
  }
  else
    timer5_cnt++;
//#endif
}
/**-----------------------------------
	
  采样AD0-2路的电压值
    ------------------------------------------------*/
void GetAD_Value02(void)
{
  FlagStatus flag_status = RESET;
  //Init_ADC02();
  //ADC1_StartConversion();
  /*while(flag_status == RESET)// SET or RESET
  {
    flag_status = ADC1_GetFlagStatus(ADC1_FLAG_EOC); 
  }*/
  while((DMA_GetFlagStatus(DMA1_FLAG_TC1)) == RESET );
  DMA_ClearFlag(DMA1_FLAG_TC1);
  ADC1_GetSConversionValueFromBuffer();
  ////////////////////////ADC1_ClearFlag(ADC1_FLAG_EOC);

}



void BEEP_Init(u16 frequency)
{
  uint16_t TimerPeriod = 0;
  uint16_t Channel1Pulse = 0;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  /* GPIOA Clocks enable */
  RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOB, ENABLE);
  
  /* GPIOA Configuration: Channel 1, 2, 3 and 4 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Beep ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIO_Beep_PORT, &GPIO_InitStructure);
  
  GPIO_PinAFConfig(GPIO_Beep_PORT, GPIO_PinSource8, GPIO_AF_2);

  
  /* TIM1 Configuration ---------------------------------------------------
   Generate PWM signals with 4 different duty cycles:
   TIM1 input clock (TIM1CLK) is set to APB2 clock (PCLK2)    
    => TIM1CLK = PCLK2 = SystemCoreClock
   TIM1CLK = SystemCoreClock, Prescaler = 0, TIM1 counter clock = SystemCoreClock
   SystemCoreClock is set to 48 MHz for STM32F0xx devices
   
   The objective is to generate 4 PWM signal at 17.57 KHz:
     - TIM1_Period = (SystemCoreClock / 17570) - 1
   The channel 1 and channel 1N duty cycle is set to 50%
   The Timer pulse is calculated as follows:
     - ChannelxPulse = DutyCycle * (TIM1_Period - 1) / 100
   
   Note: 
    SystemCoreClock variable holds HCLK frequency and is defined in system_stm32f0xx.c file.
    Each time the core clock (HCLK) changes, user had to call SystemCoreClockUpdate()
    function to update SystemCoreClock variable value. Otherwise, any configuration
    based on this variable will be incorrect. 
  ----------------------------------------------------------------------- */
  /* Compute the value to be set in ARR regiter to generate signal frequency at 17.57 Khz */
  TimerPeriod = (SystemCoreClock / 20000 ) - 1;//17570
  /* Compute CCR1 value to generate a duty cycle at 50% for channel 1 */
  Channel1Pulse = (uint16_t) (((uint32_t) 5 * (TimerPeriod - 1)) / 10);

  /* TIM1 clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM16 , ENABLE);
  
  /* Time Base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = TimerPeriod;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

  /* Channel 1, 2, 3 and 4 Configuration in PWM mode */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;

  TIM_OCInitStructure.TIM_Pulse = Channel1Pulse;
  TIM_OC1Init(TIM16, &TIM_OCInitStructure);

  /* TIM1 counter enable */
  TIM_Cmd(TIM16, ENABLE);

  /* TIM1 Main Output Enable */
  TIM_CtrlPWMOutputs(TIM16, DISABLE);
  
}

