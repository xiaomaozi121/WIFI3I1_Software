/**
  ******************************************************************************
  * @file    ADC_DMA/main.c 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    11-October-2013
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"
#include "stm32f0308_discovery.h"
#include "userBSP.h"
#include "app.h"


/** @addtogroup STM32F0308_Discovery_Peripheral_Examples
  * @{
  */

/** @addtogroup ADC_DMA
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


 FlagStatus Timer5CntOverFlag;
 FlagStatus PM_ProcessFlag,flag_ad,KeyScanFlag,AD_ScanFlag;
 FlagStatus KeyClearFlag;//按键松开标志位
 FlagStatus BackLEDFlag = RESET ;

 FlagStatus BatChargeFlag;
 FlagStatus DhtFlag;
 FlagStatus ParameterSetFlag,TimeSetFlag;
 FlagStatus DisFlag; 
 FlagStatus PM_En_Flag;

 
 #ifdef PV
 FlagStatus PM_HourAverageFlag;
 FlagStatus MinuteChangeFlag,HourChangeFlag;
#endif
#ifdef PRINT
 FlagStatus PrintFlag;
#endif
#if defined (PH) || defined (HV) || defined(PHV)
 FlagStatus MaxHoldFlag;
 FlagStatus AlarmEnFlag; 
 FlagStatus AlarmOnFlag; 
#endif 
 u16 u16_adc1[4];//存储4组电压值。0-2扫描采集 AD3单独采集
 #ifdef PV
 u8  l_tmpdate[7]={0,0,0,4,4,14,20};///秒分时日月周年2011-07-14 12:00:00
 #endif
//@near static WORD PM_V_buf[30];
u8  cnt_s;
//u16 timer_cnt=0;
u16 timer_cnt;
//u16 cnt1,cnt2;        //10ms
u16 timer5_cnt = 0;

u8 SetCnt= 0;//设置计数

u8 DhtFlagCnt = 0 ; //温湿度每秒钟置位一次，但DHT11采样率为2秒，所以计数
 #ifdef PV
//u8  SetTemp[2] = {0}; //设置时间缓存
u8  SetTemp[2];
 #endif
//@near WORD PM_V_buf[30]= {P_def};

u8  Key = 0;//[[key1 on/off; key2 light; key3 set;key4 up]]
u8    OldKey = 0;
u8    KeyCnt =  0;
BitStatus  KeyFlag; //有键按下
BitStatus  KeyOk;
			

_ts_pranus_pro_     ts_pranus_pro = ts_pranus_pro_Def;
_ts_pranus_dat_pro_    *ts_pranus_dat_pro;
_ts_pranus_MP_pro_     *ts_pranus_MP_pro;


u32 sum_adc3 = 0;
u16 sum_adc3_num = 0;
u16 min_adc3 = 100;
u16 max_adc3 = 100;
u16 PM_average;//30秒的电压平均值
u16 PM_V ;//1秒钟采集到的电压平均值
u32 sum_PM_Hour ;
u16 sum_cnt = 0;
u32 sum_VOC_Hour;
#ifdef PV
WORD_BYTES PM_Hour_Average ;
WORD_BYTES VOC_Hour_Average ;
#endif

#if defined (PV) || defined (HV) || defined(PHV)
u16 VOC_average;
u16 VOC_V;
u16 VOC_Temp[STEP_V];
u16 VOC_Tmid[NMID_V];
u16 V_temp;
u16 vc_test,V_cmps;
u16 Para_A_VOC;
u16 Para_B_VOC;
s16 det_v_cval;
#endif

#if defined (PH) || defined (HV) || defined(PHV)
u16 HCHO_average;
u16 HCHO_V;
u16 HCHO_Temp[STEP_H];
u16 HCHO_Tmid[NMID_H];
u16 H_temp;
u16 Para_A_HCHO;
u16 Para_B_HCHO;
s16 det_h_cval;
//u16 HCHO_Temp2[16] = {0};
#endif
#if defined (PH) || defined (HV) || defined(PHV)
#if  defined(PH) || defined(PHV)
u16 Max_PM;
#endif
#if defined(HV) || defined(PHV)
u16 Max_VOC;
#endif
u16 Max_HCHO;
u16 Max_AQI;
#endif
u16 BatQuantity;
u16 Bat_his_sum;
u8  Bat_test_com;
//PARAMETER  parameters = {40,47,64,6,9,150,165,256,200,30,427};6.30前
PARAMETER  parameters = {40,47,67/**/,6,9,707/**/,165,256,200,30,518/**/};
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f0xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f0xx.c file
     */
  
  /* ADC1 channel with DMA configuration */
  //ADC_CH_DMA_Config();

  /* Infinite loop */
  //while (1)
  //{
    /* Test DMA1 TC flag */
   // while((DMA_GetFlagStatus(DMA1_FLAG_TC1)) == RESET ); 
    
    /* Clear DMA TC flag */
    //DMA_ClearFlag(DMA1_FLAG_TC1);
    
    /* Convert temperature sensor voltage value in mv */
    //TempSensVoltmv = (uint32_t)((RegularConvData_Tab[0]* 3300) / 0xFFF);
    
    /* Convert Vref voltage value in mv */
   // VrefIntVoltmv  = (uint32_t)((RegularConvData_Tab[1]* 3300) / 0xFFF);  
  //}
   uint16_t *p;
/*---------------------标志位初始化--------------*/
	 KeyClearFlag = SET;
	 DisFlag = SET;
	 Bat_test_com=0;//电量检测断电计数
//#ifdef WIFI
//	wifi_ioinit();   //wifi 不上电
//#endif
#if defined (PH) || defined (HV)
	 MaxHoldFlag = RESET;
	 AlarmEnFlag = RESET;
	 AlarmOnFlag = RESET;
#endif
  Pranus_CLK_Config();	
  delay_init(48);
  //CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);//16M
  GPIO_User_Init();
  ADC_CH_DMA_Config();
  BackLED_Off();
  Beep_Off(); 
  VCC5_On();
  MOTOR_On();
  LCD_DisplayClear();
  Delay_Ms(200);			
  PSW_On();
#ifdef Beep_Active
     Beep_On();
#else
  BEEP_Init(BEEP_FREQUENCY_2KHZ);
  Beep_On(); 
#endif

  PS3_On();
  PS1_On();
  PS2_On();
  //Beep_Off();
  #ifdef FS
  MOTOR_On();
  #endif
  LCD_Init();
  LCD_DisplayTest();
  Delay_Ms(200);
  Delay_Ms(100);
  Beep_Off();
  LCD_DisplayClear();
  LCD_DisplayTest();
  Delay_Ms(200);
  /*
  LCD_DisplayTest();
  while(1)
  {
    STM_EVAL_LEDOn(LED3);
    delay_ms(1000);
    STM_EVAL_LEDOff(LED3);
    delay_ms(1000);
  }
  */
  //BEEP_Cmd(ENABLE);
  //BEEP_Cmd(DISABLE);	
  //BEEP_LSICalibrationConfig(128000);
  // BEEP_Init(BEEP_FREQUENCY_2KHZ);
  // BEEP_Cmd(ENABLE);  

  // AlarmEnable();
  // AlarmDisable();
		
#ifdef FIRST
  p = (u16 *)&parameters;
  parameters.para.Version = VERSION;
  E2P_Write(ParaAdd,p,ParameterLength);
  #ifdef PV
  Set_RTC();
  #endif
  //WatchD_Init();
  while(1)
  {
    //VCC5_On();
    Delay_Ms(200);
    BackLED_On();
    Beep_On();
    //VCC5_Off();
    Delay_Ms(200);
    Beep_Off();
    BackLED_Off();
    KeyScan();
    KeyIdentify();
    KeyProcess();
    WatchDogFeed();
  }
#else
  p = (u16 *)&parameters;
  E2P_Read(ParaAdd,p,ParameterLength);
  parameters.para.Version = VERSION;
  E2P_Write(ParaAdd,p,ParameterLength);
#endif
  //KeyScan();
  do  //按键放开
  {
    KeyScan();
    KeyIdentify();
    KeyProcessSet();
    Delay_Ms(20);		
  }while( Key != 0 || ParameterSetFlag );
#ifdef PV	
  Init_ds1302();
#endif
#if defined (PV) || defined(PH) || defined(PHV)
	//Init_Timer4();
	//TIM4_Cmd(DISABLE);
#endif
	Init_Timer3();
	LCD_DisplayClear();///                 不清平直接执行background 会出问题，原因是background这个函数
	Lcd_DisplayBackground();
	
#if defined (HV) || defined(PH) || defined(PHV)
		//AlarmEnable();
		AlarmDisable();
#endif
	//enableInterrupts();
	//WatchD_Init();

#ifdef PRINT
	UART2_Init((u32)115200, UART2_WORDLENGTH_8D, UART2_STOPBITS_1, UART2_PARITY_NO, UART2_SYNCMODE_CLOCK_DISABLE, UART2_MODE_TX_ENABLE);
#endif

//UART_init();
/*
ts_pranus_pro.FIlter1 = 0xff;
ts_pranus_pro.FIlter2 = 0xfe;
ts_pranus_pro.add = 0x35;
ts_pranus_pro.len = 20;
ts_pranus_dat_pro = (_ts_pranus_dat_pro_ *)&ts_pranus_pro.d[0];
ts_pranus_MP_pro  = (_ts_pranus_MP_pro_ *)&(ts_pranus_dat_pro->d[0]);
*/
ts_pranus_pro.FIlter1 = 0xff;
ts_pranus_pro.FIlter2 = 0xfe;
ts_pranus_pro.Fac_N = 0x25;
ts_pranus_pro.Dev_Type = 0x0f;
ts_pranus_pro.Dev_N = 0x0a;
ts_pranus_pro.Alarm_N = 0x0b;
ts_pranus_dat_pro = (_ts_pranus_dat_pro_ *)&ts_pranus_pro.d[0];
ts_pranus_MP_pro  = (_ts_pranus_MP_pro_ *)&(ts_pranus_dat_pro->d[0]);

	//enableInterrupts();
	WatchD_Init();
	/*while(1)
  {
			//VCC5_On();
			Delay_Ms(200);
			BackLED_On();
			//Beep_On();
			//VCC5_Off();
			Delay_Ms(200);
			//Beep_Off();
			BackLED_Off();
			KeyScan();
			KeyIdentify();
			KeyProcess();
			WatchDogFeed();
	}*/
  while (1)
  {
	//WatchDogFeed();
    while()
    {
      df
    }
#ifdef PV
    TimeProcess();
#endif
    /*if(Timer5CntOverFlag)
    {
      if(BackLEDFlag) 
      {
        BackLED_Off();
        BackLEDFlag	=RESET;  
      }
      else
      {
        BackLED_On();
        BackLEDFlag=SET;
      }
      Timer5CntOverFlag = RESET;
    }*/
#if defined (PV) || defined(PH) || defined(PHV)
    if( PM_ProcessFlag )
    {
      PM_Process();
      PM_ProcessFlag = RESET;
      DisFlag = SET; //示数刷新
    }
    /*if( cnt_s < 60 )
    {
      Beep_On();
	 //PM_Process();
	 //PM_ProcessFlag = RESET;
	 //DisFlag = SET; //示数刷新
    }
    else
    {
      Beep_Off(); 
    }*/
#endif	
    if( AD_ScanFlag )
    {
      GetAD_Value02();
      AD_ScanFlag = RESET;
#if defined (PV) || defined(HV) || defined(PHV)
      VOC_Process();
#endif

#if defined (PH) || defined(HV) || defined(PHV)
      HCHO_Process();
#endif
      Bat_Process();
      DisFlag = SET; //示数刷新
    }
    if(KeyScanFlag)
    {
      KeyScan();
      KeyIdentify();
      KeyScanFlag = RESET;
      KeyProcess();
    }
    if( DhtFlag )
    {
      DhtFlag = RESET;
      DhtFlagCnt++;
      if (DhtFlagCnt == 3)
      {
        DhtFlagCnt = 0;	
        //disableInterrupts();
        DHT11_ReadTempAndHumi();
        //enableInterrupts();
        DisFlag = SET; //示数刷新
      }
    }
#if defined (HV) || defined(PH) || defined(PHV)
     Alarm();
#endif	
		
#ifdef PRINT
    if(PrintFlag)//&&(wifi_PWR_FLG == SET))
    {
      Data_Sent_Host();
      PrintFlag = RESET;
    }
#endif

if(DisFlag)
 {
   AQI_Process();
#ifdef PV				
   if(MinuteChangeFlag)
   {
     sum_PM_Hour = sum_PM_Hour + ts_pranus_MP_pro->PM_V_30s;
     sum_VOC_Hour = sum_VOC_Hour + ts_pranus_MP_pro->VOC_V_5s;	
     sum_cnt++;	
     if(HourChangeFlag)
     {
       PM_Hour_Average.word = (u16)(sum_PM_Hour/sum_cnt);
       VOC_Hour_Average.word = (u16)(sum_VOC_Hour/sum_cnt);
       sum_PM_Hour = 0;
       sum_VOC_Hour = 0;
       sum_cnt = 0;
       HourChangeFlag = RESET;
       p = (u8 *)&PM_Hour_Average;
       E2P_Read(PMAdd+l_tmpdate[2]-1,p,2);
       p = (u8 *)&VOC_Hour_Average;
       E2P_Read(VOCAdd+l_tmpdate[2]-1,p,2);
       //VOCAdd 
     }
     MinuteChangeFlag = RESET;
   }
   if( PM_HourAverageFlag == RESET)
   {
     Display();
   }
#endif
	
#if defined (HV) || defined(PH) || defined (PHV)
   Display();
#endif	
  }

	DisFlag = RESET;
 }	
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
