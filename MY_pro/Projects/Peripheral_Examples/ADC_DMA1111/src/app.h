 /**
  ******************************************************************************
  * @file    app.h
  * @author  JF.Song
  * @version V1.0
  * @date    16-November-2013
  * @brief   app.c 的预定义和生命
  ******************************************************************************
  * @attention
  *
  
  ******************************************************************************
  */
	
	/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __APP_H
#define __APP_H

/* Includes ------------------------------------------------------------------*/
#include "includes.h"
#include "userBSP.h"
#include "newstruct2.h"
	
//#define	 FIRST 
//#define	 FIRST 
//#define	 FIRST 
//#define  PRINT 

//<<<<<<< .mine
//#define  PV
#define PH 
//=======
//#define  PV

//#define PH 
//>>>>>>> .r16
//#define PHV
//#define HV 


//#define Beep_Active

//#define  WIFI

#define  FS
#define Bat_chargeable
//#define Bat_ucharge
#define SINGLE  //无中值滤波
//#define MID     //滑移平均 中值滤波
//#define HCHO_ALAM_100
#define HCHO_ALAM_200  //甲醛 0.2 报警 
//#define DOUB_KK   //双斜率
#define MONO_KK  //单斜率
//#define DHT11
#define DHT22
#define PRA_DUB  //校准时是否显示绝对值

#define VERSION 825//711  
#define ParaAdd 0
#define PMAdd  0x14
#define VOCAdd 0x64
#if defined (PH) || defined (HV) || defined(PHV)
#define STEP_P 5
#define STEP_H  15
#define NMID_H 3


#endif 


#if defined (PV) || defined (HV) || defined(PHV)
#define STEP_V 5
#define STEP_P 5
#define NMID_V 3
#endif

//#define ParameterLength 22
#define ParameterLength  11


#define V_def   30
#define H_def   03

#define Cnt_s_period 60
//#define P_def   70
#define ts_pranus_pro_Def  {25,2,25,22,33,30}
//------------------宏定义 IO口 --------------------------------//
#define  GPIO_AD_PORT GPIOA
#define  GPIO_ADC0    GPIO_Pin_4
#define  GPIO_ADC1    GPIO_Pin_5
#define  GPIO_ADC2    GPIO_Pin_6
#define  GPIO_ADC3    GPIO_Pin_7

#define  GPIO_BL_PORT 	GPIOA
#define  GPIO_BL      	GPIO_Pin_12

//#define  GPIO_LCD_PORT 	GPIOD
//#define  GPIO_LCD_Power GPIO_PIN_5

#define  GPIO_Key12_PORT  GPIOB
#define  GPIO_Key_SW1    GPIO_Pin_13
#define  GPIO_Key_SW2    GPIO_Pin_14
#define  GPIO_Key3_PORT  GPIOB 
#define  GPIO_Key_SW3    GPIO_Pin_15
#define  GPIO_Key4_PORT  GPIOA 
#define  GPIO_Key_SW4    GPIO_Pin_8

#define  GPIO_PSW_PORT   GPIOB 
#define  GPIO_PSW       GPIO_Pin_12

#define  GPIO_PS1_PORT  GPIOB
#define  GPIO_PS1       GPIO_Pin_0
#define  GPIO_PS2_PORT  GPIOB
#define  GPIO_PS2       GPIO_Pin_1
#define  GPIO_PS3_PORT  GPIOB
#define  GPIO_PS3       GPIO_Pin_2

#define  GPIO_PM_PORT   GPIOB
#define  GPIO_I_control GPIO_Pin_10

#define  GPIO_BAT_PORT   GPIOB 
#define  GPIO_CHAG       GPIO_Pin_9
#define  GPIO_CE         GPIO_Pin_11

#define GPIO_DS1302_PORT 	GPIOB
#define GPIO_DS1302_SCLK	GPIO_Pin_3  //PA15	
#define GPIO_DS1302_DIO 	GPIO_Pin_4
#define GPIO_DS1302_PORT2 	GPIOC
#define GPIO_DS1302_RST 	GPIO_Pin_5

#define  GPIO_DHT11_PORT    GPIOC
#define  DHT11_DATA         GPIO_Pin_0
//#define  DHT11_EN           GPIO_PIN_5

#define  GPIO_Beep_PORT    GPIOB
#define  GPIO_Beep         GPIO_Pin_8

#define  GPIO_MOTOR_PORT    GPIOF
#define  GPIO_MOTOR_EN         GPIO_Pin_6

#define GPIO_VCC5_PORT      GPIOB
#define GPIO_VCC5_EN        GPIO_Pin_11

#define gMAX(res,dat1,dat2) {res=dat1>dat2?dat1:dat2;}

//------------------全局变量外部声名------------------------------、

extern FlagStatus Timer5CntOverFlag;
extern FlagStatus PM_ProcessFlag,flag_ad,KeyScanFlag,AD_ScanFlag;
extern FlagStatus KeyClearFlag;
extern FlagStatus BackLEDFlag;
extern FlagStatus AlarmEnFlag; 
extern FlagStatus AlarmOnFlag; 
extern FlagStatus BatDisFlag,BatChargeFlag;
extern FlagStatus DhtFlag;
extern FlagStatus ParameterSetFlag,TimeSetFlag;
extern FlagStatus PM_HourAverageFlag,PM_En_Flag;
extern FlagStatus MinuteChangeFlag,HourChangeFlag;
extern FlagStatus MaxHoldFlag;
extern FlagStatus DisFlag;
extern FlagStatus PrintFlag;
extern u16 u16_adc1[4];
extern u8  l_tmpdate[7];//秒分时日月周年2011-07-14 12:00:00
extern u16 timer_cnt;
extern u16 timer5_cnt;
//extern WORD PM_V_buf[30];
//extern MAIN_FLAG main_flag;
//extern u16 cnt1;
//extern u16 cnt2;
extern u8  cnt_s;
extern u8 SetCnt;
extern u8  SetTemp[2]; //设置时间缓存
extern u32 sum_adc3;
extern u16 sum_adc3_num;
extern u16 min_adc3;
extern u16 max_adc3;
extern u8  Key;
extern u8    OldKey;
extern u8    KeyCnt;
extern BitStatus  KeyFlag;
extern BitStatus  KeyOk;

extern u16 PM_average;
extern u16 PM_V;


extern u32 sum_PM_Hour;
extern u16 sum_cnt;
extern u32 sum_VOC_Hour;
extern WORD_BYTES PM_Hour_Average;
extern WORD_BYTES VOC_Hour_Average;

#if defined (PV) || defined (HV) || defined(PHV)
extern u16 VOC_average;
extern u16 VOC_V;
extern u16 VOC_Temp[STEP_V];
extern u16 VOC_Tmid[NMID_V];
extern u16 V_temp;
extern u16 vc_test,V_cmps;
extern u16 Para_A_VOC;
extern u16 Para_B_VOC;
extern s16 det_v_cval;
#endif
#if defined (PH) || defined (HV) || defined(PHV)
extern u16 HCHO_average;
extern u16 HCHO_V;
extern u16 HCHO_Temp[STEP_H];
extern u16 HCHO_Tmid[NMID_H];
extern u16 H_temp;
extern u16 Para_A_HCHO;
extern u16 Para_B_HCHO;
extern s16 det_h_cval;

extern u16 Max_HCHO;
extern u16 Max_PM;
extern u16 Max_AQI;
extern u16 Max_VOC;
#endif

#define MAXMINdata(dat,Max,Min) {dat=dat>Min?(dat>Max?Max:dat):Min;}

extern _ts_pranus_pro_     ts_pranus_pro;
extern _ts_pranus_dat_pro_    *ts_pranus_dat_pro;
extern _ts_pranus_MP_pro_     *ts_pranus_MP_pro;
extern u16 BatQuantity;
extern u16 Bat_his_sum;
extern u8  Bat_test_com;
//extern _wifi_package  dP;

extern PARAMETER  parameters;
extern FlagStatus wifi_nRLD_FLG;
extern FlagStatus wifi_PWR_FLG;
extern FlagStatus wifi_WPS_FLG;

//extern FlagStatus wifi_nRLD_FLG;

#define  BackLED_On()  GPIO_SetBits(GPIO_BL_PORT,GPIO_BL) //  *点亮液晶背光
#define  BackLED_Off()  GPIO_ResetBits(GPIO_BL_PORT,GPIO_BL)
#define  Key_SW1() GPIO_ReadInputDataBit(GPIO_Key12_PORT,GPIO_Key_SW1) //SW1数值 电源开关
#define  Key_SW2() GPIO_ReadInputDataBit(GPIO_Key12_PORT,GPIO_Key_SW2)
#define  Key_SW4() GPIO_ReadInputDataBit(GPIO_Key4_PORT,GPIO_Key_SW4)
#define Key_SW3() GPIO_ReadInputDataBit(GPIO_Key3_PORT,GPIO_Key_SW3)
#define PSW_On() GPIO_SetBits(GPIO_PSW_PORT,GPIO_PSW) //电源 IO控制关
#define PSW_Off() GPIO_ResetBits(GPIO_PSW_PORT,GPIO_PSW)//GPIO_Init(GPIO_PSW_PORT,GPIO_PSW,GPIO_MODE_OUT_OD_LOW_FAST);   注意，开关机需要测试 20141107 v0.1
#define PS1_On()  GPIO_SetBits(GPIO_PS1_PORT,GPIO_PS1) //*电源 传感器 开始 甲醛
#define PS1_Off() GPIO_ResetBits(GPIO_PS1_PORT,GPIO_PS1) 
#define PS2_On() GPIO_SetBits(GPIO_PS2_PORT,GPIO_PS2) //电源 传感器 开始 VOC
#define PS2_Off() GPIO_ResetBits(GPIO_PS2_PORT,GPIO_PS2)
#define PS3_On() GPIO_SetBits(GPIO_PS3_PORT,GPIO_PS3)
#define PS3_Off() GPIO_ResetBits(GPIO_PS3_PORT,GPIO_PS3) 	//电源 传感器 关闭 PM2.5
#define MOTOR_On() GPIO_SetBits(GPIO_MOTOR_PORT,GPIO_MOTOR_EN)
#define MOTOR_Off() GPIO_ResetBits(GPIO_MOTOR_PORT,GPIO_MOTOR_EN) 	//电源 传感器 关闭 风扇
#define VCC5_On() GPIO_SetBits(GPIO_VCC5_PORT,GPIO_VCC5_EN)
#define VCC5_Off() GPIO_ResetBits(GPIO_VCC5_PORT,GPIO_VCC5_EN) 	//电源 传感器 关闭 风扇
#if defined (PV) || defined(PH) || defined(PHV)
#define PM_ControlOn() GPIO_SetBits(GPIO_PM_PORT,GPIO_I_control)
#define PM_ControlOff() GPIO_ResetBits(GPIO_PM_PORT,GPIO_I_control)
#endif


//void BackLED_On(void);
//void BackLED_Off(void);
//void LCD_On(void);
//void LCD_Off(void);



//void Delay_Ms(uint8_t ms);
//void delay_us(uint8_t us);


//BitStatus Key_SW1(void);
//BitStatus Key_SW2(void);
//BitStatus Key_SW3(void);
//BitStatus Key_SW4(void);
//void PSW_On(void);
//void PSW_Off(void);

//void PS1_On(void);
//void PS1_Off(void);

//void PS2_On(void);
//void PS2_Off(void);

//void PS3_On(void);
//void PS3_Off(void);

//void PM_ControlOn(void);
//void PM_ControlOff(void);


u16 Middat3(u16 *p);
void Read_PM_Value(void);
void PM_Process(void);
u16 VOC_k_hv(u8 T_v,u8 H_v);
u16 VOC_Compensation(u16 V,u16 k);
void VOC_Process(void);
void HCHO_Process(void);
void Bat_Process(void);
void AQI_Process( void );
void TimeProcess(void);

void KeyScan( void );
void KeyIdentify( void );
void KeyProcess( void );
void KeyProcessSet( void );
void Display(void);
void Alarm(void);
//void AlarmEnable(void);
//void AlarmDisable(void);
void RTC_Time_Read(void);
//void Time_Display( void );

void E2P_Write(unsigned int addr, uint16_t* p_data, unsigned int len);
void E2P_Read(unsigned int addr, uint16_t* p_data, unsigned int len);
void Send(uint8_t dat);
void Data_Sent_Host(void);
void WatchDogFeed(void);
#endif 