/**
  ******************************************************************************
  * @file    app.c
  * @author  JF.Song
  * @version V1.0
  * @date    17-November-2013
  * @brief   ∞¸∫¨pm2.5œ‡πÿµƒ”¶”√∫Ø ˝
  ******************************************************************************
  * @attention
  *
  
  ******************************************************************************
  */
#include "app.h"


#ifdef PV
void TimeProcess(void)
{
  static u8 minute,hour,second;

	RTC_Time_Read();//RTC ±÷”

	//cnt_5s = l_tmpdate[0]%5;
		if(second != l_tmpdate[0] )
	  {
		 second = l_tmpdate[0];
		 DisFlag = SET;
		}
		
	if(minute != l_tmpdate[1] )
	  {
		 minute = l_tmpdate[1];
		 MinuteChangeFlag = SET;
		}
	else
	 ;
	if(hour != l_tmpdate[2] )
	  {
		 hour = l_tmpdate[2];
		 HourChangeFlag = SET;
		}
	else
	 ;	
	
}

	#endif
	/**-----------------------------------
	u8  l_tmpdate[7]={0,0,12,6,12,11,20};///√Î∑÷ ±»’‘¬÷‹ƒÍ2011-07-14 12:00:00
   µ ± ±÷”∂¡»°
    ------------------------------------------------*/
				
#ifdef PV		
	void RTC_Time_Read( void )
	{	
	
		uint8_t i,tmp;
		Read_RTC();
		for(i=0;i<7;i++)
	{       //BCD¥¶¿Ì
		tmp=l_tmpdate[i]/16;
		l_tmpdate[i]=l_tmpdate[i]%16;
		l_tmpdate[i]=l_tmpdate[i]+tmp*10;
	}  
}

#endif


	 	
u16 Middat3(u16 *p)
{
	if((*p<= *(p+1))&&(*p<= *(p+2)))
	{
		if(*(p+1)<= *(p+2))
		{
			return *(p+1);
		}
		else
		return *(p+2);
	}
	else if((*p>= *(p+1))&&(*p>= *(p+2)))
	{
		if(*(p+1)<= *(p+2))
		{
			return *(p+2);
		}
		else
		return *(p+1);
	}
	else 
	{
		return *p;
	}
}

	/**-----------------------------------
		PM2.5µƒµÁ—π¥¶¿Ì
  ------------------------------------------------*/
	#if defined (PV) || defined(PH)|| defined(PHV)
void Read_PM_Value(void)
{
	/*FlagStatus flag_status;


			flag_status = ADC1_GetFlagStatus(ADC1_FLAG_EOC); 
			 if(flag_status != RESET)
				{
					u16_adc1[3] = ADC1_GetConversionValue();
					ADC1_ClearFlag(ADC1_FLAG_EOC);
					//PM_ControlOff();
					sum_adc3 += u16_adc1[3];
					sum_adc3_num++;
					if(timer5_cnt == 1 )
				  {
					 min_adc3 = u16_adc1[3];
					 max_adc3 = u16_adc1[3]; 
					}
					else
					{
          min_adc3 = min_adc3<u16_adc1[3]?min_adc3:u16_adc1[3];
					max_adc3 = max_adc3>u16_adc1[3]?max_adc3:u16_adc1[3];
			 	  }
	}*/
}
	
		 	/**-----------------------------------
   PM2.5 30S ∆Ωæ˘÷µ 5√Î∏¸–¬“ª¥Œ 5S≤Ω≥§ª¨∂Ø RTC ±º‰
    ------------------------------------------------*/	
static u16 PM_30S_Average( void)
{
	//static pm_i=0;
 static WORD PM_V_buf[30]= {0};
 //@near static WORD PM_V_buf[30];
	u8 count;
	static u16 average;
	u32 sum=0;
	PM_V_buf[cnt_s % 30] = PM_V;
	if ( cnt_s == Cnt_s_period ) cnt_s = 0;
	if( (cnt_s % STEP_P ) == 0 )
	 { 
		for ( count=0; count<30; count++ )
	  {
		sum += PM_V_buf[count];
  	}
		average = (u16)(sum/30);
   }
	// DisFlag = SET; // æ ˝À¢–¬
	return average;
}

	 	/**-----------------------------------
	
   PM2.5 ¥¶¿Ì≥Ã–Ú 5¥Œ≤…—˘∆Ωæ˘ À¢–¬ æ ˝
    ------------------------------------------------*/
		void PM_Process(void)
	{
		unsigned long int PM_V_tmp;
		u16 t;
		sum_adc3 -= (min_adc3 + max_adc3);//»•µÙ◊Ó¥Û÷µ∫Õ◊Ó–°÷  
 		sum_adc3_num -= 2;
		PM_V = (sum_adc3*3)/(sum_adc3_num);
		sum_adc3 = 0;
		sum_adc3_num = 0;
		PM_average = PM_30S_Average();
		
		if( PM_average > parameters.para.A_PM )
		{
			t = parameters.para.K1_PM;
			PM_V_tmp = (unsigned long int) (PM_average -parameters.para.A_PM)*t;
			PM_V_tmp =PM_V_tmp /parameters.para.K2_PM;
		}
		else
		PM_V_tmp = 0;
		
		ts_pranus_MP_pro->PM_V_30s = PM_V_tmp;
		MAXMINdata(ts_pranus_MP_pro->PM_V_30s,999,0);// …Ë∂®œ‘ æ∑∂Œß

	}
 #endif
#if defined (PV) || defined (HV)|| defined(PHV)
	 	
u16 VOC_k_hv(u8 T_v,u8 H_v)
{
	s16 k_h,k_t,t_v,h_v;
	h_v = H_v;
	t_v = T_v;
	k_h = 122+(85-h_v)*48/55;//-10…„ œ∂»µƒ÷µ
	//vc_test = k_h;
	k_h = k_h-13;  //÷±œﬂ∑Ω≥Ã÷–µƒb
	k_t = k_h-(t_v*13)/10;//-55;//ºŸ∂®–±¬ Œ™0.78/60 13 = 78*10/60
	//vc_test = k_t/10;
	return (u16)k_t;
}
u16 VOC_Compensation(u16 V,u16 k)
{
	u16 V_v;
	V_v = 1551/V;
	V_v = V_v - 1;
	V_v = V_v + k/100;
	V_v = 1551/V_v;
	V_v = V_v*k/100;
	
	return V_v;
	
}
void VOC_Process(void)
	{
		u8 count = 0;
		u16 sum = 0;
		u16 V_cmps;
		VOC_Temp[cnt_s%STEP_V] = u16_adc1[2];
		//if((cnt_s %STEP) == 0 )
		{
			for(count = 0; count<STEP_V; count++)
			{
				sum +=  VOC_Temp[count];

			}
			VOC_average = sum/STEP_V;
			sum = 0;
			if(VOC_average > parameters.para.A_VOC)
		  ts_pranus_MP_pro->VOC_V_5s = ((VOC_average - parameters.para.A_VOC)*parameters.para.K1_VOC)/parameters.para.K2_VOC;
			else
			ts_pranus_MP_pro->VOC_V_5s = 0;
			
			/*
			vc_test = ts_pranus_MP_pro->VOC_V_5s;
			V_cmps = VOC_Compensation(ts_pranus_MP_pro->Temp_V,ts_pranus_MP_pro->Humi_V); 
			//vc_test = V_cmps/10;  //voc Œ¬∂»≤π≥•µ˜ ‘
			V_cmps = V_cmps*ts_pranus_MP_pro->VOC_V_5s/100;
			ts_pranus_MP_pro->VOC_V_5s = V_cmps;
			*/
			vc_test = ts_pranus_MP_pro->VOC_V_5s;
			V_cmps = VOC_k_hv(ts_pranus_MP_pro->Temp_V,ts_pranus_MP_pro->Humi_V); 
			
			ts_pranus_MP_pro->VOC_V_5s = VOC_Compensation(vc_test,V_cmps);
			
			MAXMINdata(ts_pranus_MP_pro->VOC_V_5s,999,0);
		//LCD_DisplayName(TVOC,VOC_V); 
		}
	}
#endif



	 	/**-----------------------------------
	
   HCHO ¥¶¿Ì≥Ã–Ú£¨300∫¡√Î»°—˘“ª¥Œ À¢–¬ æ ˝
    ------------------------------------------------*/
#if defined (PH) || defined (HV)|| defined (PHV)
 
	
	    //ÃÌº”÷–÷µ¬À≤®∫Ûµƒ¥˙¬Î ‘À––’˝≥£
void HCHO_Process(void)
	{
		u8 count = 0;
		u16 sum = 0;
		HCHO_Temp[cnt_s%STEP_H] = u16_adc1[1];
		//if((cnt_s %STEP) == 0 )
		{
			for(count = 0; count<STEP_H; count++)
			{
				sum +=  HCHO_Temp[count];

			}
			HCHO_average = sum/STEP_H;
			
			if(HCHO_average > parameters.para.A_HCHO)
			{
				#ifdef MONO_KK
				ts_pranus_MP_pro->HCHO_V_5s = ((HCHO_average-parameters.para.A_HCHO)*parameters.para.K1_HCHO)/parameters.para.K2_HCHO;
				#endif 
				#ifdef DOUB_KK
				Para_A_HCHO = parameters.para.A_HCHO - 50*parameters.para.K2_HCHO/parameters.para.K1_HCHO;
				//Para_A_HCHO «˙œﬂ¡„µ„
				Para_B_HCHO = parameters.para.A_HCHO +150*parameters.para.K2_HCHO/parameters.para.K1_HCHO;
				//Para_B_HCHO –±¬ π’µ„
				if(HCHO_average < Para_B_HCHO)
				ts_pranus_MP_pro->HCHO_V_5s = ((HCHO_average-Para_A_HCHO)*parameters.para.K1_HCHO)/(parameters.para.K2_HCHO*2);
				else
				ts_pranus_MP_pro->HCHO_V_5s = ((HCHO_average-parameters.para.A_HCHO)*parameters.para.K1_HCHO)/parameters.para.K2_HCHO;
				#endif
			}
			else
			ts_pranus_MP_pro->HCHO_V_5s = 0;
			MAXMINdata(ts_pranus_MP_pro->HCHO_V_5s,999,0);
		}
		//LCD_DisplayName(TVOC,VOC_V);
	}
	
   
#endif

	void AQI_Process( void )
	{
		

		u16 P_AQI,HCHO_AQI,VOC_AQI;
	  #if defined (PH) || defined (PV)|| defined(PHV)
		
		//#ifdef PV 
		// P_AQI = ts_pranus_MP_pro->PM_V_30s; //PVºÚªØ¥¶¿Ì ø’º‰≤ªπª
		//#endif
		//PM2.5≈®∂»”Îø’∆¯÷∏ ˝∂‘”¶±Ì
		//-------------AQI----------≈®∂»---------//	
		//---------------0-----------0---------//
		//---------------50----------35---------//	
		//---------------100---------75---------//
		//---------------150---------115---------//	
		//---------------200---------150---------//
		//---------------300---------250--------//	
		//---------------400---------350---------//
		//---------------500---------550---------//
		//#ifdef PH
		if(ts_pranus_MP_pro->PM_V_30s <= 35 ) 
	  {
		  P_AQI = ts_pranus_MP_pro->PM_V_30s*10/7;
		}
	 else if (ts_pranus_MP_pro->PM_V_30s <= 115 )
	  {
		
		 P_AQI = (ts_pranus_MP_pro->PM_V_30s - 35)*5/4 + 50;
		}
	 else if (ts_pranus_MP_pro->PM_V_30s <= 150 )
	  {
		
		 P_AQI = (ts_pranus_MP_pro->PM_V_30s - 115)*10/7 + 150;
		}
	 else if (ts_pranus_MP_pro->PM_V_30s <= 350 )
	  {
		
		 P_AQI = ts_pranus_MP_pro->PM_V_30s + 50;
		}
    else
		{
		 P_AQI = (ts_pranus_MP_pro->PM_V_30s - 350)*2/3 + 400;
		}
		//#endif
	#endif
			//º◊»©≈®∂»”Îø’∆¯÷∏ ˝∂‘”¶±Ì
		//-------------AQI----------≈®∂»---------//	
		//---------------0-----------0---------//
		//---------------50----------0.04---------//	
		//---------------100---------0.08---------//
		//---------------200---------0.12---------//	∏ƒ∫Û 100 ------0.12
		//---------------300---------0.16---------//
		//---------------400---------0.30--------//	
		//---------------500---------0.50---------//
		//---------------500---------0.5---------//
	#if defined (PH) || defined (HV)|| defined(PHV)
		#ifdef HCHO_ALAM_100
   if(ts_pranus_MP_pro->HCHO_V_5s <= 8 ) 
	  {
		  HCHO_AQI = ts_pranus_MP_pro->HCHO_V_5s*100/8;
		}

	 else if (ts_pranus_MP_pro->HCHO_V_5s <= 16)
	  {
		
		 HCHO_AQI = (ts_pranus_MP_pro->HCHO_V_5s - 12)*25 + 100;
		}
			
		else if (ts_pranus_MP_pro->HCHO_V_5s <= 20)
	  {
		
		 HCHO_AQI = (ts_pranus_MP_pro->HCHO_V_5s - 16)*50/7 + 300;
		}
	 else 
	  {
		
		 HCHO_AQI = (ts_pranus_MP_pro->HCHO_V_5s - 20)*5 + 400;
		} 
		#endif
		//º◊»©≈®∂»”Îø’∆¯÷∏ ˝∂‘”¶±Ì  ±®æØ÷µ
		//-------------AQI----------≈®∂»---------//	
		//---------------0-----------0---------//
		//---------------50----------0.06---------//	
		//---------------100---------0.12---------//	∏ƒ∫Û 100 ------0.12
		//---------------200---------0.16---------//
		//---------------400---------0.30--------//	
		//---------------500---------0.50---------//
		//---------------500---------0.5---------//
		#ifdef HCHO_ALAM_200
		if(ts_pranus_MP_pro->HCHO_V_5s <= 12 ) 
	  {
		  HCHO_AQI = ts_pranus_MP_pro->HCHO_V_5s*100/12;
		}

	 else if (ts_pranus_MP_pro->HCHO_V_5s <= 16)
	  {
		
		 HCHO_AQI = (ts_pranus_MP_pro->HCHO_V_5s - 16)*25 + 100;
		}
			
		else if (ts_pranus_MP_pro->HCHO_V_5s <= 30)
	  {
		
		 HCHO_AQI = (ts_pranus_MP_pro->HCHO_V_5s - 16)*100/7 + 200;
		}
	 else 
	  {
		
		 HCHO_AQI = (ts_pranus_MP_pro->HCHO_V_5s - 20)*5 + 400;
		} 
		#endif
	#endif
		#if defined (PV) || defined (HV)	|| defined(PHV)
	
				//VOC≈®∂»”Îø’∆¯÷∏ ˝∂‘”¶±Ì
		//-------------AQI----------≈®∂»---------//	
		//---------------0-----------0---------//
		//---------------50----------0.40---------//	
		//---------------100---------0.60---------//
		//---------------200---------1.00---------//	
		//---------------300---------1.50---------//
		//---------------400---------2.00--------//	
		//---------------500---------3.00---------//
   if(ts_pranus_MP_pro->VOC_V_5s <= 40 ) 
	  {
		  VOC_AQI = ts_pranus_MP_pro->VOC_V_5s*5/4;
		}
	#ifdef PV
	 else
		VOC_AQI = ts_pranus_MP_pro->VOC_V_5s*2-20;
	#endif
	#ifdef HV
		else if (ts_pranus_MP_pro->VOC_V_5s <= 60)
	  {
		
		 VOC_AQI = (ts_pranus_MP_pro->VOC_V_5s - 40)*5/2+ 50;
		}
	 else if(ts_pranus_MP_pro->VOC_V_5s <= 200)
	  {
		 VOC_AQI = (ts_pranus_MP_pro->VOC_V_5s - 100)*2 + 200;
		} 
	else
	  {
		
		 VOC_AQI = ts_pranus_MP_pro->VOC_V_5s + 200;
		} 	
	#endif	
	#endif
	#ifdef PV
	gMAX(ts_pranus_MP_pro->AQI,P_AQI,VOC_AQI);
	//gMAX(ts_pranus_MP_pro->AQI,P_AQI,P_AQI);
	#endif
	#ifdef PH
	gMAX(ts_pranus_MP_pro->AQI,P_AQI,HCHO_AQI);
	#endif
	#ifdef HV
	gMAX(ts_pranus_MP_pro->AQI,VOC_AQI,HCHO_AQI);
	if(ts_pranus_MP_pro->AQI == VOC_AQI)
	{
		ts_pranus_MP_pro->AQI=(VOC_AQI*9+HCHO_AQI)/10;
	}
	ts_pranus_MP_pro->AQI += 3;
	#endif
	#ifdef PHV
	gMAX(ts_pranus_MP_pro->AQI,VOC_AQI,HCHO_AQI);
	gMAX(ts_pranus_MP_pro->AQI,P_AQI,ts_pranus_MP_pro->AQI);
	//ts_pranus_MP_pro->AQI = ts_pranus_MP_pro->AQI*2/10;
	#endif
	MAXMINdata(ts_pranus_MP_pro->AQI,500,0);
	}

		void Bat_Process( void )
	{
		static u8 cnt = 0;
		
		Bat_test_com++;
		Bat_his_sum +=u16_adc1[0];
		if(Bat_test_com == 20)
		{
			Bat_his_sum=Bat_his_sum/20;
			Bat_test_com = 0;
			if (Bat_his_sum<529)
			{	
			  LCD_DisplayClear();
			  Beep_On();    //÷∏ æ“—æ≠…œµÁ
			  Delay_Ms(200);
			  Delay_Ms(200);
			  WatchDogFeed();
			  Delay_Ms(200);
			  Delay_Ms(200);
			  WatchDogFeed();
			  Delay_Ms(200);
			  Delay_Ms(200);
			  WatchDogFeed();
			  Delay_Ms(200);
			  Delay_Ms(200);
			  WatchDogFeed();
			  Delay_Ms(200);
			  Delay_Ms(200);
			  Beep_Off();
			  PSW_Off(); //»Áπ˚µÁ—ππ˝µÕ‘Úπÿ±’µÁ‘¥
			 }
		}
		#ifdef Bat_chargeable
		//BatChargeFlag = !(GPIO_ReadInputPin(GPIO_BAT_PORT,GPIO_CHAG)); //µÕµÁ∆Ω±Ì æ≥‰µÁ
                BatChargeFlag = !((FlagStatus)GPIO_ReadInputDataBit(GPIO_BAT_PORT,GPIO_CHAG)); //µÕµÁ∆Ω±Ì æ≥‰µÁ GPIO_ReadInputDataBit
		#endif
		#ifdef Bat_ucharge
		BatChargeFlag = RESET;
		#endif
		if (BatChargeFlag)
			{
				
				LCD_DisplayBatLogo(cnt);
				cnt++;
				if(cnt > 3)
				{
					cnt = 0;
				}
			}
		
		else
			{
				
				if(u16_adc1[0]>600)//580)//
				  {
						LCD_DisplayBatLogo(3);
				  }
				else if(u16_adc1[0]>580)//569)//
					{
						LCD_DisplayBatLogo(2);	
					}
				else if(u16_adc1[0]>540)//528)//
					{
						LCD_DisplayBatLogo(1);	
					}
				else if (u16_adc1[0]>530)//500)//	//3.41V 530
							LCD_DisplayBatLogo(0);
				/*else if (u16_adc1[0]<529)
						{	
									LCD_DisplayClear();
									Beep_On();    //÷∏ æ“—æ≠…œµÁ
									Delay_Ms(200);
									Delay_Ms(200);
									WatchDogFeed();
									Delay_Ms(200);
									Delay_Ms(200);
									WatchDogFeed();
									Delay_Ms(200);
									Delay_Ms(200);
									WatchDogFeed();
									Delay_Ms(200);
									Delay_Ms(200);
									WatchDogFeed();
									Delay_Ms(200);
									Delay_Ms(200);
									Beep_Off();
							PSW_Off(); //»Áπ˚µÁ—ππ˝µÕ‘Úπÿ±’µÁ‘¥
					  }*/
			}								
	}
		
/**-----------------------------------
∞¥º¸…®√Ë≥Ã–Ú
------------------------------------------------*/
		
void KeyScan( void )
{
  u8 Key1,Key2,Key3,Key4;
  Key1 = Key_SW1();
  Key2 = Key_SW2();
  Key3 = Key_SW3();
  Key4 = Key_SW4();
  //  Key = (Key3|Key2|Key1)>>1;
  //Key = (Key1>>3) | (Key2>>3) | (Key3<<1) | (Key4>>3)  ;
  Key = (Key1>>4) | (Key2>>4) | (Key3>>5) | (Key4>>7)  ;
}
/**-----------------------------------
∞¥º¸ ∂±≥Ã–Ú£¨≈–∂œ∞¥º¸ «∑ÒΩ· ¯£¨∞¥º¸ ±º‰≥§∂Ã
//[key1 on/off; key2 light; key3 alrm]
[key1 on/off; key3 set; key2 Up; key4 Light]
------------------------------------------------*/	
void KeyIdentify( void )
{
  if( !KeyOk )
  {
    if( KeyFlag )
    {
      if(Key != 0 && KeyClearFlag)
      {
        if(Key == OldKey)
        {
          KeyCnt ++;
        }
        else
        {
          OldKey = Key;
          KeyCnt =0;
        }
        if( KeyCnt > 100)	//∞¥º¸æÕ∑¥”≥ ∂¯≤ª «∞¥ÕÍ À…ø™∫Û∑¥”≥
        {
          KeyOk = SET;	
          KeyClearFlag = RESET;
        } 
      }
      else
      {
        if(KeyCnt > 5)
        {
          KeyOk = SET;
        }
        else
        {
          ;
        }
        KeyFlag = RESET;
      }
    }
    else
    {
      if(Key != 0)
      {
        OldKey = Key;
        KeyFlag = SET;
      }
      else
      {
        KeyClearFlag = SET;
      }
    }
  }
  else
    ;
}
		
void KeyProcessSet( void )
{
//--- ∂±∞¥º¸ «∑Ò”––ß£¨∞¥º¸µƒ÷÷¿‡∫Õ≥§∂Ã		
			

	//∞¥º¸¥¶¿Ì≥Ã–Ú	
	//[key1 on/off; key2 light; key3 alrm]	
	//[key1 on/off; key3 set; key2 Up; key4 Light]
	   if(KeyOk)
			{
				
				switch(OldKey)
			  {
					case 0x0b:     //1011
								ParameterSetFlag = SET;
								BackLED_On();
								LCD_DisplayClear();
								SetCnt = 0;	
								#ifdef PV
								LCD_DisplayName(TVOC,SetCnt);
								LCD_DisplayName(PM25,parameters.pW[SetCnt]%1000);
								LCD_DisplayName(Second,parameters.pW[SetCnt]/1000);
								#endif
								#ifdef PH
								LCD_DisplayName(PM25,SetCnt);
								LCD_DisplayName(HCHO,parameters.pW[SetCnt]%1000);
								LCD_DisplayName(Pollution,parameters.pW[SetCnt]/1000);								
								#endif
								#if defined (HV)	|| defined(PHV)
								LCD_DisplayName(TVOC,SetCnt);
								LCD_DisplayName(HCHO,parameters.pW[SetCnt]%1000);
								LCD_DisplayName(Pollution,parameters.pW[SetCnt]/1000);								
								#endif
									break;
					case 8:

								SetCnt++;
								#ifdef PV
								LCD_DisplayName(TVOC,SetCnt);
								LCD_DisplayName(PM25,parameters.pW[SetCnt]%1000);
								LCD_DisplayName(Second,parameters.pW[SetCnt]/1000);
								#endif
								#ifdef PH
								LCD_DisplayName(PM25,SetCnt);
								LCD_DisplayName(HCHO,parameters.pW[SetCnt]%1000);
								LCD_DisplayName(Pollution,parameters.pW[SetCnt]/1000);								
								#endif
								#if  defined (HV)	|| defined(PHV)
								LCD_DisplayName(TVOC,SetCnt);
								LCD_DisplayName(HCHO,parameters.pW[SetCnt]%1000);
								LCD_DisplayName(Pollution,parameters.pW[SetCnt]/1000);								
								#endif
								if( SetCnt > (ParameterLength/2) )//word ≥§∂»
									{
										SetCnt = 0;
										ParameterSetFlag = RESET;
										E2P_Write(ParaAdd,(u16 *)&parameters,ParameterLength);
										PSW_Off();										
									}
								break;
					case 2:
								if( ParameterSetFlag )
								{
									if(SetCnt == 8|| SetCnt == 9  )
									 { 
									   parameters.pW[SetCnt]+= 5 ;
									 }
									 else
									parameters.pW[SetCnt]++;
								#ifdef PV
								LCD_DisplayName(TVOC,SetCnt);
								LCD_DisplayName(PM25,parameters.pW[SetCnt]%1000);
								LCD_DisplayName(Second,parameters.pW[SetCnt]/1000);
								#endif
								#ifdef PH
								LCD_DisplayName(PM25,SetCnt);
								LCD_DisplayName(HCHO,parameters.pW[SetCnt]%1000);
								LCD_DisplayName(Pollution,parameters.pW[SetCnt]/1000);								
								#endif
								#if defined (HV)	|| defined(PHV)
								LCD_DisplayName(TVOC,SetCnt);
								LCD_DisplayName(HCHO,parameters.pW[SetCnt]%1000);
								LCD_DisplayName(Pollution,parameters.pW[SetCnt]/1000);								
								#endif
							  }
									break;
					case 1:
								if( ParameterSetFlag )
								{
										if(SetCnt == 8 || SetCnt == 9 )
									 { 
									   parameters.pW[SetCnt]-= 5 ;
									 }
									 else
									parameters.pW[SetCnt]--;
								#ifdef PV
								LCD_DisplayName(TVOC,SetCnt);
								LCD_DisplayName(PM25,parameters.pW[SetCnt]%1000);
								LCD_DisplayName(Second,parameters.pW[SetCnt]/1000);
								#endif
								#ifdef PH
								LCD_DisplayName(PM25,SetCnt);
								LCD_DisplayName(HCHO,parameters.pW[SetCnt]%1000);
								LCD_DisplayName(Pollution,parameters.pW[SetCnt]/1000);								
								#endif
								#if defined (HV)	|| defined(PHV)
								LCD_DisplayName(TVOC,SetCnt);
								LCD_DisplayName(HCHO,parameters.pW[SetCnt]%1000);
								LCD_DisplayName(Pollution,parameters.pW[SetCnt]/1000);								
								#endif
							  }
									break;
						default: break;

				}	
			  KeyOk = RESET;
				KeyCnt = 0;
			}
}	


	#ifdef PV
	/**-----------------------------------
	
	∞¥º¸¥¶¿Ì≥Ã–Ú
	//[key1 on/off; key2 light; key3 alrm]
	[key1 on/off; key3 set; key2 Up; key4 Light]
    ------------------------------------------------*/		
		void KeyProcess( void )
		{
			
			
		u16 temp = 0; 
    //u8 i;
	//--- ∂±∞¥º¸ «∑Ò”––ß£¨∞¥º¸µƒ÷÷¿‡∫Õ≥§∂Ã		
			

	//∞¥º¸¥¶¿Ì≥Ã–Ú	
	//[key1 on/off; key2 light; key3 alrm]	
	//[key1 on/off; key3 set; key2 Up; key4 Light]
	   if(KeyOk)
			{
				//Beep_On();”––ß∞¥º¸‘ŸœÏ
				switch(OldKey)
			  {
					case 8:      //1000 onoff
								if( KeyCnt>50 )
								{
								Beep_On();
								PS3_Off();
								PS1_Off();
								PS2_Off();
							//	Beep_On();
								Delay_Ms(200);
								LCD_DisplayClear();
								Beep_Off();
								PSW_Off();
								
								BackLED_Off();   //πÿ±’À˘”–…Ë±∏µÁ‘¥ Ω¯»Îπÿª˙À¿—≠ª∑
								#ifdef FS
								MOTOR_Off();
								#endif
								
								while(1)
								{
									PSW_Off();
									Delay_Ms(200);
									WatchDogFeed();
								}
							}
							
						#ifdef WIFI
							if( KeyCnt<50 )
							{
								if( wifi_PWR_FLG == RESET)
								{
									wifi_PWR_FLG = SET;
									usrwifi232_pwON();  //¥•∑¢
									Beep_On();    //÷∏ æ“—æ≠…œµÁ
									Delay_Ms(200);
									Beep_Off();
									WatchDogFeed();
									Delay_Ms(200);
									Delay_Ms(200);
									Beep_On();
									WatchDogFeed();
									Delay_Ms(200);
									Beep_Off();
									/*usrwifi232_pwON();  //¥•∑¢
									Beep_On();
									WatchDogFeed();
									Delay_Ms(200);
									Beep_Off();
									
									//wifi_con();*/
									/*Beep_On();
									WatchDogFeed();
									Delay_Ms(200);
									Beep_Off();*/
								}
								else
								{
									wifi_PWR_FLG =RESET;
									usrwifi232_pwOFF();
									
									Beep_On();  //÷∏ æ“—πÿ±’
									Delay_Ms(200);
									Beep_Off();
								}
							}
						#endif
								break;
					case 3:     //0011 alarm+light
					      
								if( KeyCnt>100 )
							   {  
								  Beep_On();
						//#ifdef PV
									temp = V_def*parameters.para.K2_VOC/parameters.para.K1_VOC;
								if( VOC_average > temp ) 
									{parameters.para.A_VOC = VOC_average - temp;
									ts_pranus_MP_pro->VOC_V_5s = V_def;
							   	}
								else
									 parameters.para.A_VOC = 0;
                   DisFlag = SET; // æ ˝À¢–¬
          //  #endif
									}
								else
								 ;
								//  parameters.para.A_VOC = 0;
                 E2P_Write(ParaAdd,(u8 *)&parameters,ParameterLength);
							#ifdef PRA_DUB
								 /*BackLED_On();
								 LCD_DisplayName(TVOC,ts_pranus_MP_pro->VOC_V_5s);	
								 Delay_Ms(200);
								 Delay_Ms(200);
								 WatchDogFeed();
								 Delay_Ms(200);
								 Delay_Ms(200);
								 BackLED_Off();
								 WatchDogFeed();
								 Delay_Ms(200);
								 Delay_Ms(200);
								 WatchDogFeed();
								 Delay_Ms(200);*/
								 BackLED_On();
								 LCD_DisplayName(TVOC,VOC_average);	
								 Delay_Ms(200);
								 Beep_Off();
								 WatchDogFeed();
								 Delay_Ms(200);
								 Delay_Ms(200);
								 WatchDogFeed();
								 Delay_Ms(200);
							#endif
								 Delay_Ms(200);
								 BackLED_Off();
								 WatchDogFeed();
								break;
					case 5:      //0101   max+light
					      
								if( KeyCnt>100 )
							   {  
								  Beep_On();
						//#ifdef PV
									temp = (u16)((u32)(parameters.para.Ref_PM)*parameters.para.K2_PM/parameters.para.K1_PM);
								if( PM_average > temp ) 
								   {
										parameters.para.A_PM = PM_average - temp;
											ts_pranus_MP_pro->PM_V_30s = parameters.para.Ref_PM;
											DisFlag = SET; // æ ˝À¢–¬
								   }
								else
								  parameters.para.A_PM = 0;
									
                 E2P_Write(ParaAdd,(u8 *)&parameters,ParameterLength);
							#ifdef PRA_DUB
								 /*BackLED_On();
								 LCD_DisplayName(PM25,ts_pranus_MP_pro->PM_V_30s);
								 Delay_Ms(200);
								 Delay_Ms(200);
								 WatchDogFeed();
								 Delay_Ms(200);
								 Delay_Ms(200);
								 WatchDogFeed();
								 BackLED_Off();
								 Delay_Ms(200);
								 Delay_Ms(200);
								 WatchDogFeed();
								 Delay_Ms(200);*/
								 BackLED_On();
								 LCD_DisplayName(PM25,PM_average);
								 Delay_Ms(200);
								 Beep_Off();
								 WatchDogFeed();
								 Delay_Ms(200);
								 Delay_Ms(200);
								 WatchDogFeed();
								 Delay_Ms(200);
								 Delay_Ms(200);
								 WatchDogFeed();
								 Delay_Ms(200);
								 Delay_Ms(200);
								 WatchDogFeed();
							#endif
								 Delay_Ms(200);
								 BackLED_Off();
								 }
								else
								{
								//if(BackLEDFlag) BackLED_Off();
								//else BackLED_On();
								}
								break;
					 case 1:   //0001  light
								if(KeyCnt<=80)
								{
									Beep_On();
								
									if(BackLEDFlag) 
										{
											BackLED_Off();
											BackLEDFlag	=RESET;  
										}
									else
										{
											BackLED_On();
											BackLEDFlag	=SET; 
										}
										Delay_Ms(200);
								}
								
#ifdef WIFI
								if( KeyCnt>100 &&(wifi_PWR_FLG == SET))
								{
									Beep_On();    //÷∏ æ“—æ≠…œµÁ
									Delay_Ms(200);
									Beep_Off();
									WatchDogFeed();
									Delay_Ms(200);
									Delay_Ms(200);
									WatchDogFeed();
									Beep_On();
									Delay_Ms(200);
									Beep_Off();
									WatchDogFeed();
									
									wifi232_RLD_SET();  //¥•∑¢
									for(KeyCnt = 0;KeyCnt<30;KeyCnt++)
									{
									Delay_Ms(200);
									WatchDogFeed();
									}	
									wifi232_RLD_RESET();
									
									for(KeyCnt = 0;KeyCnt<10;KeyCnt++)
									{
									Delay_Ms(200);
									WatchDogFeed();
									}	
									KeyCnt = 110;
									//wifi_con();*/  ∑≈‘⁄’‚¿Ôª·≤ªƒ‹’˝≥£Ω¯»Îat ÷∏¡Óƒ£ Ω
									
									Beep_On();
									Delay_Ms(200);
									Beep_Off();
									
								}
#endif
								  
								break;
					case 4:     //0100
								
									if(TimeSetFlag)
									{
									 Beep_On();
								   SetCnt++;
									 if( SetCnt > 2 )
										{
											SetCnt = 0;
											TimeSetFlag = RESET;
											l_tmpdate[1]=SetTemp[0];
											l_tmpdate[2]=SetTemp[1];
											Set_RTC(); 
											//BackLED_Off();										
										}
									
									}									
									else
									{
								   if (KeyCnt > 50) //¥Û”⁄0.5√Î
										{
										Beep_On();
										SetCnt++;
										TimeSetFlag = SET;
										Lcd_SetCol(1);
										//BackLED_On();
										SetTemp[0] = l_tmpdate[1];
										SetTemp[1] = l_tmpdate[2];
										
										}
								 }
								
								break;
					case 2:     //0010
					      Beep_On();
								if( TimeSetFlag )
								{
									switch (SetCnt)
								  {
									  case 1:
												
												if(SetTemp[0] >= 59 ) SetTemp[0] = 0;
												else
												SetTemp[0]++;
		                    LCD_DisplayName(Second,SetTemp[0]);//∑÷
												break;
										case 2:
												if(SetTemp[1] >= 23 ) SetTemp[1] = 0;
													else
												SetTemp[1]++;
												LCD_DisplayName(Minute,SetTemp[1]);// ±
												break;
										default: break;
									}
									//Set_RTC(); 	
								}
								else
								{
									if(PM_HourAverageFlag == RESET ) 
									{ 
									 Lcd_SetHourAverage(1);
									 
									 PM_Hour_Average.word = (u16)(sum_PM_Hour/sum_cnt);
									 VOC_Hour_Average.word = (u16)(sum_VOC_Hour/sum_cnt);
									 LCD_DisplayName(PM25,PM_Hour_Average.word);
									 LCD_DisplayName(TVOC,VOC_Hour_Average.word);
									 LCD_DisplayName(Minute,l_tmpdate[2]);// ±
		               LCD_DisplayName(Second,0);//∑÷
									 Lcd_DisplayRank(PM_Hour_Average.word);
									 Lcd_SetCol(1);
									 PM_HourAverageFlag	=SET;  
								  }
									else
								  {
									 Lcd_SetHourAverage(0);
									 PM_HourAverageFlag	=RESET;  
								  }
								}
						
						
							break;
					case 10:
							#ifdef WIFI
								
								if( KeyCnt>100 &&(wifi_PWR_FLG == SET))
								{
									//wifi232_WPS_SET();  //¥•∑¢
									Beep_On();    //÷∏ æ“—æ≠…œµÁ
									Delay_Ms(200);
									Beep_Off();
									Delay_Ms(200);
									Beep_On();
									WatchDogFeed();
									//wifi232_WPS_RESET();
									Delay_Ms(200);
									Beep_Off();
									
									Delay_Ms(200);
									Delay_Ms(200);
									wifi_con();
									wifi232_WPS_SET();  //¥•∑¢
									Delay_Ms(200);
									Delay_Ms(200);
									Delay_Ms(200);
									wifi232_WPS_RESET();
									for(KeyCnt = 0;KeyCnt<10;KeyCnt++)
									{
										Delay_Ms(200);
										WatchDogFeed();
									}
									KeyCnt = 110;
									
									Beep_On();    //÷∏ æ“—æ≠…œµÁ
									Delay_Ms(200);
									Beep_Off();
								}
							#endif
							break;
					case 12:
							#ifdef WIFI
								if( KeyCnt>100 &&(wifi_PWR_FLG == SET))
								{
									Beep_On();    
									Delay_Ms(200);
									Beep_Off();
									WatchDogFeed();
									Delay_Ms(200);
									Beep_On();    //÷∏ æ“—æ≠…œµÁ
									Delay_Ms(200);
									Beep_Off();
									WatchDogFeed();
									
									Delay_Ms(200);
									Delay_Ms(200);
									wifi_con();
									
									wifi232_RLD_SET();  //¥•∑¢
									Delay_Ms(500);
									wifi232_RLD_RESET();
									
									for(KeyCnt = 0;KeyCnt<10;KeyCnt++)
									{
										Delay_Ms(200);
										WatchDogFeed();
									}
									KeyCnt = 110;
									Beep_On();    //÷∏ æ“—æ≠…œµÁ
									Delay_Ms(200);
									Beep_Off();
									WatchDogFeed();
									
								}
							#endif
							break;	
					default: break;	
				}
				Delay_Ms(50);
				Beep_Off();
			  KeyOk = RESET;
				KeyCnt = 0;
			}
		}	
		
#endif


#if defined (PH) || defined (HV) || defined(PHV)
	/**-----------------------------------
	
	∞¥º¸¥¶¿Ì≥Ã–Ú
	//[key1 on/off; key2 light; key3 alrm]
	[key1 on/off; key3 Max; key2 Up; key4 Light]
    ------------------------------------------------*/		
		void KeyProcess( void )
		{
		u16 temp = 0; 

	//--- ∂±∞¥º¸ «∑Ò”––ß£¨∞¥º¸µƒ÷÷¿‡∫Õ≥§∂Ã		
			

	//∞¥º¸¥¶¿Ì≥Ã–Ú	
	//[key1 on/off; key2 light; key3 alrm]	
	//[key1 on/off; key3 set; key2 Up; key4 Light]
	   if(KeyOk)
			{
				//Beep_On();
				switch(OldKey)
			  {
					case 8:  //1000 onoff
							if( KeyCnt>100 )
							{
								Beep_On();
								PS3_Off();
								PS1_Off();
								PS2_Off();
							//	Beep_On();
								Delay_Ms(200);
								LCD_DisplayClear();
								Beep_Off();
								PSW_Off();
								
								BackLED_Off();  //πÿ±’À˘”–…Ë±∏µÁ‘¥ Ω¯»Îπÿª˙À¿—≠ª∑
								#ifdef FS
								MOTOR_Off();
								#endif
								Delay_Ms(200);
								Delay_Ms(200);
								Delay_Ms(200);
								Delay_Ms(200);
								while(1)
								{
									PSW_Off();
									Delay_Ms(200);
									WatchDogFeed();
									BackLED_On();
									Delay_Ms(200);
									WatchDogFeed();
									BackLED_Off();
								}
							}
#ifdef WIFI
							if( KeyCnt<50 )
							{
								if( wifi_PWR_FLG == RESET)
								{
									wifi_PWR_FLG = SET;
									usrwifi232_pwON();  //¥•∑¢
									
									Beep_On();    //÷∏ æ“—æ≠…œµÁ
									Delay_Ms(200);
									Beep_Off();
									WatchDogFeed();
									Delay_Ms(200);
									Delay_Ms(200);
									Beep_On();
									WatchDogFeed();
									Delay_Ms(200);
									Beep_Off();
									
									//usrwifi232_pwON();  //¥•∑¢
									/*Beep_On();
									WatchDogFeed();
									Delay_Ms(200);
									Beep_Off();*/
								}
								else
								{
									wifi_PWR_FLG =RESET;
									usrwifi232_pwOFF();
									
									Beep_On();  //÷∏ æ“—πÿ±’
									Delay_Ms(200);
									Beep_Off();
								}
							}
#endif
								
								break;
					case 3://0011 alarm+light
					      
								if( KeyCnt>100 )
							   {  
								  Beep_On();
									temp = H_def*parameters.para.K2_HCHO/parameters.para.K1_HCHO;
								if( HCHO_average > temp ) 
									{parameters.para.A_HCHO = HCHO_average - temp;
									 //ts_pranus_MP_pro->HCHO_V_5s = H_def;
									 
									 ts_pranus_MP_pro->HCHO_V_5s = HCHO_average;
									 det_h_cval = ts_pranus_MP_pro->HCHO_V_5s - H_def;
							  	}
								else
									parameters.para.A_HCHO = 0; //»Áπ˚Œﬁ∑®¥ÔMAx£¨‘Ú¡„µ„÷√Œ™0 
									//MAXMINdata(parameters.para.A_HCHO,75,67);// …Ë∂®œ‘ æ∑∂Œß
							#if defined (HV)	|| defined(PHV)
									temp = V_def*parameters.para.K2_VOC/parameters.para.K1_VOC;
								if( VOC_average > temp ) 
									{parameters.para.A_VOC = VOC_average - temp;
									//ts_pranus_MP_pro->VOC_V_5s = V_def;	
									
									ts_pranus_MP_pro->VOC_V_5s = VOC_average;
									 det_v_cval = ts_pranus_MP_pro->VOC_V_5s - V_def;
							   	}
								else
								  parameters.para.A_VOC = 0;
							#endif
									DisFlag = SET; // æ ˝À¢–¬
									E2P_Write(ParaAdd,(u16 *)&parameters,ParameterLength);
									BackLED_On();
						#ifdef PRA_DUB
									/*
							#if defined (HV)	|| defined(PHV)|| defined(PV)
									LCD_DisplayName(TVOC,ts_pranus_MP_pro->VOC_V_5s);	
							#endif
							#if defined (HV)	|| defined(PHV)|| defined(PH)
									LCD_DisplayName(HCHO,ts_pranus_MP_pro->HCHO_V_5s);
							#endif
									Delay_Ms(200);
									Delay_Ms(200);
									Delay_Ms(200);
									Delay_Ms(200);
									BackLED_Off();
									Delay_Ms(200);
									Delay_Ms(200);
									Delay_Ms(200);*/
									BackLED_On();
							#if defined (HV)	|| defined(PHV)|| defined(PV)
									LCD_DisplayName(TVOC,parameters.para.A_VOC);	
							#endif
							#if defined (HV)	|| defined(PHV)|| defined(PH)
									LCD_DisplayName(HCHO,parameters.para.A_HCHO);
							#endif
									Delay_Ms(200);
									Beep_Off();
									Delay_Ms(200);
									WatchDogFeed();
									Delay_Ms(200);
									Delay_Ms(200);
									WatchDogFeed();
						#endif
									Delay_Ms(200);
									BackLED_Off();
								}
								else
								{
								//if(BackLEDFlag) BackLED_Off();
								//else BackLED_On();
								;
								}
								//HV_cal_flag = 1;
								// æ ˝‘⁄–£◊º∫Û¥”œ÷ µµƒ–£◊º≤Œ ˝ª∫¬˝œ¬ΩµµΩ≤‚ ‘÷µ£¨¥À◊ˆ∑®¥øŒ™¡ÀøÕªßø¥∆¿¥±‰ªØª∫¬˝µƒπ˝≥Ã◊ˆ
								/*
								#if defined (HV)	|| defined(PHV)
								ts_pranus_MP_pro->VOC_V_5s = V_def +det_v_cval;
								#endif
									ts_pranus_MP_pro->HCHO_V_5s = H_def + det_h_cval;
									LCD_DisplayName(TVOC,ts_pranus_MP_pro->VOC_V_5s);	
									LCD_DisplayName(HCHO,ts_pranus_MP_pro->HCHO_V_5s);
									Delay_Ms(200);
									Delay_Ms(200);
									WatchDogFeed();
									Delay_Ms(200);
									Delay_Ms(200);
									Delay_Ms(200);
									WatchDogFeed();
								for(temp = 6;temp>0;temp--)
								{
									#if defined (HV)	|| defined(PHV)
									ts_pranus_MP_pro->VOC_V_5s = V_def +det_v_cval*temp/6;
									#endif
									ts_pranus_MP_pro->HCHO_V_5s = H_def + det_h_cval*temp/6;;
									LCD_DisplayName(TVOC,ts_pranus_MP_pro->VOC_V_5s);	
									LCD_DisplayName(HCHO,ts_pranus_MP_pro->HCHO_V_5s);
									Delay_Ms(200);
									Delay_Ms(200);
									WatchDogFeed();
									Delay_Ms(200);
									Delay_Ms(200);
									Delay_Ms(200);
									WatchDogFeed();
									*/
									/*LCD_DisplayName_Clr(TVOC);
									LCD_DisplayName_Clr(HCHO);
									Delay_Ms(200);
									Delay_Ms(200);
									WatchDogFeed();*/
								
								//}
								
								break;
					case 5://0101   max+light
		#if defined (PH)	|| defined(PHV)		      
								if( KeyCnt>100 )
							   {  
								  Beep_On();
						//#ifdef PV
									temp = (u16)((u32)(parameters.para.Ref_PM)*parameters.para.K2_PM/parameters.para.K1_PM);
								if( PM_average > temp ) 
								   {
										parameters.para.A_PM = PM_average - temp;
										ts_pranus_MP_pro->PM_V_30s = parameters.para.Ref_PM;
										DisFlag = SET; // æ ˝À¢–¬	
								   }
								else
                 parameters.para.A_PM = 0;
								 
                 E2P_Write(ParaAdd,(u16 *)&parameters,ParameterLength);
								 BackLED_On();
							#ifdef PRA_DUB
								 /*LCD_DisplayName(PM25,ts_pranus_MP_pro->PM_V_30s);
								 Delay_Ms(200);
								 Delay_Ms(200);
								 Delay_Ms(200);
								 Delay_Ms(200);
								 BackLED_Off();
								 Delay_Ms(200);
								 Delay_Ms(200);
								 Delay_Ms(200);*/
								 //BackLED_On();
								 LCD_DisplayName(PM25,PM_average);
								 Delay_Ms(200);
								 Beep_Off();
								 Delay_Ms(200);
								 WatchDogFeed();
								 Delay_Ms(200);
								 Delay_Ms(200);
								 WatchDogFeed();
								 Delay_Ms(200);
								 Delay_Ms(200);
								 WatchDogFeed();
								 Delay_Ms(200);
							#endif
								 Delay_Ms(200);
								 BackLED_Off();
								 }
								else
								{
								//if(BackLEDFlag) BackLED_Off();
								//else BackLED_On();
								}
		#endif
		             ;
								break;
					 case 1://0001  light     ≥§ RLD
								if(KeyCnt<=80)
								{
									if(BackLEDFlag) 
										{
											Beep_On();
											BackLED_Off();
											BackLEDFlag	=RESET;  
										}
									else
										{
											Beep_On();
											BackLED_On();
											BackLEDFlag	=SET; 
										}
								  Delay_Ms(200);
								}									
#ifdef WIFI
								if( KeyCnt>100 &&(wifi_PWR_FLG == SET))
								{
									Beep_On();    //÷∏ æ“—æ≠…œµÁ
									Delay_Ms(200);
									Beep_Off();
									WatchDogFeed();
									Delay_Ms(200);
									Delay_Ms(200);
									Beep_On();
									Delay_Ms(200);
									Beep_Off();
									WatchDogFeed();
									
									wifi232_RLD_SET();  //¥•∑¢
									for(KeyCnt = 0;KeyCnt<20;KeyCnt++)
									{
									Delay_Ms(200);
									WatchDogFeed();
									}
									KeyCnt = 110;
									
									wifi232_RLD_RESET();
									
									for(KeyCnt = 0;KeyCnt<5;KeyCnt++)
									{
									Delay_Ms(200);
									WatchDogFeed();
									}	
									KeyCnt = 110;
									wifi_con();
									Beep_On();
									Delay_Ms(200);
									Beep_Off();
									WatchDogFeed();
									
								}
#endif
								break;
					case 2://0010 alarm      ∂Ã RLD
								if(KeyCnt<=80)
								{
									if(AlarmEnFlag) 
										{
											Beep_On();
											AlarmDisable();
										AlarmEnFlag	=RESET;  
										}
									else
										{
											Beep_On();
											AlarmEnable();
											AlarmEnFlag	=SET; 
										}
										Delay_Ms(200);
								}					
#ifdef WIFI
								if( KeyCnt>100 &&(wifi_PWR_FLG == SET))
								{
									wifi232_RLD_SET();  //¥•∑¢
									Delay_Ms(200);
									Delay_Ms(200);
									wifi232_RLD_RESET();
									
									Beep_On();   
									WatchDogFeed();
									Delay_Ms(200);
									Beep_Off();
									Delay_Ms(200);
									WatchDogFeed();
									Beep_On();    //÷∏ æ“—æ≠…œµÁ
									Delay_Ms(200);
									Beep_Off();
								}
#endif
																	
								break;
					case 4:
								if(KeyCnt<=80)
								{
									if(MaxHoldFlag) 
										{
											Beep_On();
										// AlarmDisable();
										MaxHoldFlag	=RESET;  
										}
									else
										{
											Beep_On();
										//AlarmEnable();
										MaxHoldFlag	=SET; 
										}
								  Delay_Ms(200);
								}
#ifdef WIFI
								if( KeyCnt>100 &&(wifi_PWR_FLG == SET))
								{
									wifi232_WPS_SET();  //¥•∑¢
									Beep_On();    //÷∏ æ“—æ≠…œµÁ
									Delay_Ms(200);
									Beep_Off();
									Delay_Ms(200);
									Beep_On();
									Delay_Ms(200);
									wifi232_WPS_RESET();
									Delay_Ms(200);
									Beep_Off();
									for(KeyCnt = 0;KeyCnt<10;KeyCnt++)
									{
										Delay_Ms(200);
										Delay_Ms(200);
									}
									
									/*
									wifi232_WPS_SET();  //¥•∑¢
									Delay_Ms(500);
									wifi232_WPS_RESET();
									for(KeyCnt = 0;KeyCnt<10;KeyCnt++)
									Delay_Ms(200);
									KeyCnt = 110;
									
									Delay_Ms(200);
									Beep_On();
									Delay_Ms(200);
									Beep_Off();
									*/
									
								}
#endif
					      
							break;		
					default: break;	
				}
				Delay_Ms(5);
				Beep_Off();
			  KeyOk = RESET;
				KeyCnt = 0;
			}
		}	
		
#endif
	/**-----------------------------------
	
–¥FLASH ˝æ›
    ------------------------------------------------*/
				
		
void E2P_Write(unsigned int addr, uint16_t* p_data, unsigned int len)
{
  u8 i;
  //FLASH_Unlock(FLASH_MEMTYPE_DATA);
  FLASH_Unlock();
		
  for(i = 0; i < len; i++)
  {
    //FLASH_ProgramByte(0x4000 + addr + i, *(p_data + i));//¥”0X4000ø™ º—∞÷∑
    EE_WriteVariable(addr + i, *(p_data + i));//0x4000 + addr + i
   }

 // FLASH_Lock(FLASH_MEMTYPE_DATA);
  FLASH_Lock();
}

	/**-----------------------------------
	
	∂¡FLASH ˝æ›
    ------------------------------------------------*/
				
		
void E2P_Read(unsigned int addr, uint16_t* p_data, unsigned int len)
{
  u8 i;
  //FLASH_Unlock(FLASH_MEMTYPE_DATA);
  FLASH_Unlock();
		
  for(i = 0; i < len; i++)
  {
    //*(p_data + i) =  FLASH_ReadByte(0x4000 + addr + i);//¥”0X4000ø™ º—∞÷∑
    EE_ReadVariable(addr + i,(p_data + i));//¥”0X4000ø™ º—∞÷∑FLASH_GetUserOptionByte 0x4000 + addr + i
   }

  //FLASH_Lock(FLASH_MEMTYPE_DATA);
  FLASH_Lock();
}

	/**-----------------------------------
	
	∂¡FLASH ˝æ›
    ------------------------------------------------*/
#ifdef PV
void Display(void)
{
		LCD_DisplayName(Temperature,ts_pranus_MP_pro->Temp_V);
		LCD_DisplayName(Humidity,ts_pranus_MP_pro->Humi_V);
		LCD_DisplayName(PM25,ts_pranus_MP_pro->PM_V_30s);
		//LCD_DisplayName(PM25,PM_average);
	  LCD_DisplayName(TVOC,ts_pranus_MP_pro->VOC_V_5s);
		Lcd_DisplayRank(ts_pranus_MP_pro->AQI);
		//Time_Display();
    if(TimeSetFlag == RESET)
		{
		LCD_DisplayName(Minute,l_tmpdate[2]);// ±
		LCD_DisplayName(Second,l_tmpdate[1]);//∑÷
		Lcd_SetCol(l_tmpdate[0]%2);
	  }
		else
	  {
			if(l_tmpdate[0]%2)
		  {
			LCD_DisplayName(Minute,SetTemp[1]);// ±
			LCD_DisplayName(Second,SetTemp[0]);//∑÷
			}
		  else
		  {
			  switch(SetCnt)
			 {
			  case(1):
					LCD_DisplayName(Minute,SetTemp[1]);// ±
			    LCD_DisplayNum (13,0xa);//∑÷
					LCD_DisplayNum (14,0xa);//∑÷
					break;
				case(2):
					LCD_DisplayName(Second,SetTemp[0]);//∑÷
			    LCD_DisplayNum (11,0xa);// ±
					LCD_DisplayNum (12,0xa);// ±
					break;
				default: break;
			 }
			}
		
		}
			/*LCD_DisplayName(Temperature,23);
		LCD_DisplayName(Humidity,45);
		LCD_DisplayName(PM25,156);
	  LCD_DisplayName(TVOC,50);
		Lcd_DisplayRank(170);
		//Time_Display();
    if(TimeSetFlag == RESET)
		{
		LCD_DisplayName(Minute,9);// ±
		LCD_DisplayName(Second,45);//∑÷
		Lcd_SetCol(1);
	  }
		else
	  {
			if(l_tmpdate[0]%2)
		  {
			LCD_DisplayName(Minute,9);// ±
			LCD_DisplayName(Second,45);//∑÷
			}
		  else
		  {
			  switch(SetCnt)
			 {
			  case(1):
					LCD_DisplayName(Minute,SetTemp[1]);// ±
			    LCD_DisplayNum (13,0xa);//∑÷
					LCD_DisplayNum (14,0xa);//∑÷
					break;
				case(2):
					LCD_DisplayName(Second,SetTemp[0]);//∑÷
			    LCD_DisplayNum (11,0xa);// ±
					LCD_DisplayNum (12,0xa);// ±
					break;
				default: break;
			 }
			}
		
		}	*/
		
}
#endif

#if defined (HV) || defined (PH)|| defined(PHV)

void Display(void)
{
	

	if(MaxHoldFlag)
	  
	  {
	 
		gMAX(Max_HCHO,ts_pranus_MP_pro->HCHO_V_5s,Max_HCHO);
		LCD_DisplayName(HCHO,Max_HCHO);	

		#ifdef PH
			gMAX(Max_PM,ts_pranus_MP_pro->PM_V_30s,Max_PM);
			LCD_DisplayName(PM25,Max_PM);
		#endif
		#if defined (HV)	|| defined(PHV)
			gMAX(Max_VOC,ts_pranus_MP_pro->VOC_V_5s,Max_VOC);
			LCD_DisplayName(TVOC,Max_VOC);	
		#endif
		#if defined(PHV)
			gMAX(Max_PM,ts_pranus_MP_pro->PM_V_30s,Max_PM);
		LCD_DisplayName(Pollution,Max_PM);		 
		#elseif
		gMAX(Max_AQI,ts_pranus_MP_pro->AQI,Max_AQI);		
		LCD_DisplayName(Pollution,Max_AQI);
		#endif
		LCD_DisplayName(Temperature,ts_pranus_MP_pro->Temp_V);
		LCD_DisplayName(Humidity,ts_pranus_MP_pro->Humi_V);

		Lcd_DisplayRank(Max_AQI);
    Lcd_DisplayRankAll();
		
		}
	else
	{
		Max_HCHO = 0;
	#if defined (PH)	|| defined(PHV)
		Max_PM = 0;
  #endif
	#if defined (HV)	|| defined(PHV)
		Max_VOC = 0;	
  #endif		
	  Max_AQI = 0;
		LCD_DisplayName(Temperature,ts_pranus_MP_pro->Temp_V);
		//LCD_DisplayName(Temperature,0);//¥´∏–∆˜µ˜ ‘
		LCD_DisplayName(Humidity,ts_pranus_MP_pro->Humi_V);
		#ifdef PH
		LCD_DisplayName(PM25,ts_pranus_MP_pro->PM_V_30s);
		#endif
		#if defined(HV)|| defined(PHV)
		LCD_DisplayName(TVOC,ts_pranus_MP_pro->VOC_V_5s);
		//LCD_DisplayName(TVOC,(ts_pranus_MP_pro->Temp_V*10)%100);//¥´∏–∆˜µ˜ ‘
		
		#endif

	  LCD_DisplayName(HCHO,ts_pranus_MP_pro->HCHO_V_5s);
		//LCD_DisplayName(HCHO,vc_test);//voc≤π≥•≤‚ ‘
		
		//LCD_DisplayName(HCHO,ts_pranus_MP_pro->Temp_V/10);//¥´∏–∆˜µ˜ ‘
		
		
		#if defined(PHV)
		LCD_DisplayName(Pollution,ts_pranus_MP_pro->PM_V_30s);		 
		#elseif	
		LCD_DisplayName(Pollution,ts_pranus_MP_pro->AQI);
		#endif
		//Lcd_DisplayRank(ts_pranus_MP_pro->AQI);   //“‘ø’∆¯÷ ¡ø÷∏ ˝Œ™±Í◊º
		Lcd_DisplayRank(ts_pranus_MP_pro->HCHO_V_5s);//“‘º◊»©∫¨¡øŒ™±Í◊º
	
	}
	
		/*LCD_DisplayName(Temperature,22);
		LCD_DisplayName(Humidity,42);
		LCD_DisplayName(PM25,125);
	  LCD_DisplayName(HCHO,5);
		LCD_DisplayName(Pollution,60);
		Lcd_DisplayRank(70);*/
}

void Alarm(void)
{
	//static alrm_on = 0;
 if(AlarmEnFlag)
	{
	 if( ts_pranus_MP_pro->AQI > 200)//100)
	   {
		 
		 if(timer5_cnt < 30)
		   {
				if (AlarmOnFlag == RESET)
				{
			   Beep_On();
				 AlarmOnFlag = SET;
			   BackLED_On();
				
			  }
		   }
		 else
		  {
			 Beep_Off();
			 AlarmOnFlag = RESET;
			 BackLED_Off();
			}
	   }
	 else
	   {
		  Beep_Off();
			AlarmOnFlag = RESET;
			if(BackLEDFlag)
			BackLED_On();
			else
			{
			BackLED_Off();
			}
		 }
	}
	else
	{
	    Beep_Off();
			if(BackLEDFlag)
			//BackLED_Simple_ON;
			BackLED_On();
			else
			{
			BackLED_Off();
			AlarmOnFlag = RESET;
			}
	}

}
#endif



	void Send(uint8_t dat)
{
  //while(( UART2_GetFlagStatus(UART2_FLAG_TXE)==RESET));
   while(( USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET));
	
		//UART2_SendData8(dat);
   BHKS_SerialPutChar(USART1,dat);
	
}
#ifdef PRINT
	/**-----------------------------------
	
…œŒªª˙¥Ú”° ˝æ› √ø√Î1÷°
    ------------------------------------------------*/
				
void Data_Sent_Host(void)
{
 //  static t;
	 

	  u8 i;
  	u8 *p;
	//	if( cnt_s %2 == 0  )
		{
		/*#ifdef PV
		ts_pranus_dat_pro->time.bytes[0] = l_tmpdate[0];
		ts_pranus_dat_pro->time.bytes[1] = l_tmpdate[1];
		ts_pranus_dat_pro->time.bytes[2] = l_tmpdate[2];
		ts_pranus_dat_pro->time.bytes[3] = l_tmpdate[3];
		ts_pranus_dat_pro->frame++;
		#endif*/
			ts_pranus_dat_pro->time.bytes[0]++;
		p = (u8 *)&ts_pranus_pro;
		for (i = 0; i<25; i++)
	  {
		 Send(*p);
		 p++;
		}
	  }
		//else
		//  t = cnt_s;
		
}
#endif