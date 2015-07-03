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
  ADC_CH_DMA_Config();

  /* Infinite loop */
  while (1)
  {
    /* Test DMA1 TC flag */
    while((DMA_GetFlagStatus(DMA1_FLAG_TC1)) == RESET ); 
    
    /* Clear DMA TC flag */
    DMA_ClearFlag(DMA1_FLAG_TC1);
    
    /* Convert temperature sensor voltage value in mv */
    TempSensVoltmv = (uint32_t)((RegularConvData_Tab[0]* 3300) / 0xFFF);
    
    /* Convert Vref voltage value in mv */
    VrefIntVoltmv  = (uint32_t)((RegularConvData_Tab[1]* 3300) / 0xFFF);  
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
