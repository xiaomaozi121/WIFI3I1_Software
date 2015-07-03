/**
  ******************************************************************************
  * @file    ds1302.c
  * @author  JF.Song
  * @version V1.0
  * @date    21-December-2013
  * @brief   This file contains all the functions use GPIO to moni SPI
  ******************************************************************************
  * @attention
  *
  
  ******************************************************************************
  */
	
	/* Includes ------------------------------------------------------------------*/
#include "ds1302.h"

#ifdef PV

 uint8_t write_rtc_address[7]={0x80,0x82,0x84,0x86,0x88,0x8a,0x8c}; //秒分时日月周年 最低位读写位
 uint8_t read_rtc_address[7]={0x81,0x83,0x85,0x87,0x89,0x8b,0x8d};  

/**
  * 初始化ds1203
  */
void DS1203_Init( void )
{
  
		GPIO_Init(GPIO_DS1302_PORT,(GPIO_DS1302_SCLK|GPIO_DS1302_DIO),GPIO_MODE_OUT_PP_HIGH_FAST);
		GPIO_Init(GPIO_DS1302_PORT2,GPIO_DS1302_RST,GPIO_MODE_OUT_PP_HIGH_FAST);
}

/*
********************************************************************************
** 函数名称 ： Write_Ds1302_Byte(unsigned  char temp)
** 函数功能 ： 写一个字节
********************************************************************************
*/

void Write_Ds1302_Byte(unsigned  char temp) 
{
	uint8_t i;
	for (i=0;i<8;i++)     	//循环8次 写入数据
	{ 
		GPIO_WriteLow(GPIO_DS1302_PORT,GPIO_DS1302_SCLK);
		delay_us(1);
		if(temp&0x01)
		{
		GPIO_WriteHigh(GPIO_DS1302_PORT,GPIO_DS1302_DIO);
		}
		else
	  {
		GPIO_WriteLow(GPIO_DS1302_PORT,GPIO_DS1302_DIO);
		}
		delay_us(1);
		temp>>=1;  		//右移一位
		GPIO_WriteHigh(GPIO_DS1302_PORT,GPIO_DS1302_SCLK);
		delay_us(1);
	}
}

/*
********************************************************************************
** 函数名称 ： Write_Ds1302( uint8_t address,uint8_t dat )
** 函数功能 ： 写入DS1302
********************************************************************************
*/   

void Write_Ds1302( uint8_t address,uint8_t dat )     
{
	GPIO_WriteLow(GPIO_DS1302_PORT2,GPIO_DS1302_RST);
	delay_us(1);
	GPIO_WriteLow(GPIO_DS1302_PORT,GPIO_DS1302_SCLK);
	delay_us(1);
	GPIO_WriteHigh(GPIO_DS1302_PORT2,GPIO_DS1302_RST);	
	delay_us(1);                    //启动
	Write_Ds1302_Byte(address);	//发送地址
	Write_Ds1302_Byte(dat);		//发送数据
	GPIO_WriteLow(GPIO_DS1302_PORT2,GPIO_DS1302_RST); 		            //恢复
}

/*
********************************************************************************
** 函数名称 ： Read_Ds1302 ( uint8_t address )
** 函数功能 ： 读出DS1302数据
********************************************************************************
*/

uint8_t Read_Ds1302 ( uint8_t address )
{
	uint8_t i,temp=0x00;
	BitStatus d;
	GPIO_WriteLow(GPIO_DS1302_PORT2,GPIO_DS1302_RST);
	delay_us(1);
	delay_us(1);
	GPIO_WriteLow(GPIO_DS1302_PORT,GPIO_DS1302_SCLK);
	delay_us(1);
	GPIO_WriteHigh(GPIO_DS1302_PORT2,GPIO_DS1302_RST);	
	delay_us(1); 
	Write_Ds1302_Byte(address);
	GPIO_Init(GPIO_DS1302_PORT,GPIO_DS1302_DIO,GPIO_MODE_IN_PU_NO_IT);
	for (i=0;i<8;i++) 		//循环8次 读取数据
	{		
		 d = GPIO_ReadInputPin(GPIO_DS1302_PORT,GPIO_DS1302_DIO);
		if( d )
			temp|=0x80;			//每次传输低字节
	GPIO_WriteHigh(GPIO_DS1302_PORT,GPIO_DS1302_SCLK);
	delay_us(1);
		temp>>=1;			//右移一位
	delay_us(1);
	delay_us(1);
	GPIO_WriteLow(GPIO_DS1302_PORT,GPIO_DS1302_SCLK);
	delay_us(1);
	} 
	GPIO_WriteLow(GPIO_DS1302_PORT2,GPIO_DS1302_RST);
	delay_us(1);
	delay_us(1);
	GPIO_WriteLow(GPIO_DS1302_PORT,GPIO_DS1302_SCLK);
	delay_us(1);
	delay_us(1);
	GPIO_WriteHigh(GPIO_DS1302_PORT,GPIO_DS1302_SCLK);
	delay_us(1);
	delay_us(1);
	GPIO_Init(GPIO_DS1302_PORT,GPIO_DS1302_DIO,GPIO_MODE_OUT_PP_HIGH_FAST);
	GPIO_WriteLow(GPIO_DS1302_PORT,GPIO_DS1302_DIO);
	delay_us(1);
	delay_us(1);
	GPIO_WriteHigh(GPIO_DS1302_PORT,GPIO_DS1302_DIO);
	delay_us(1);
	delay_us(1);
	return (temp);			//返回
}

/*
********************************************************************************
** 函数名称 ： Read_RTC(void)	
** 函数功能 ： 读时钟数据
********************************************************************************
*/

void Read_RTC(void)	        //读取 日历
{
	uint8_t i,*p;
	p=read_rtc_address; 	    //地址传递
	for(i=0;i<7;i++)		    //分7次读取 秒分时日月周年
	{
		l_tmpdate[i]=Read_Ds1302(*p);
		p++;
	}
}

/*
********************************************************************************
** 函数名称 ： Set_RTC(void)
** 函数功能 ： 设定时钟数据
********************************************************************************
*/

void Set_RTC(void)		    //设定 日历
{
	uint8_t i,*p,tmp;
	
	Write_Ds1302(0x8E,0X00);
	for(i=0;i<7;i++)
	{       //BCD处理
		tmp=l_tmpdate[i]/10;
		l_tmpdate[i]=l_tmpdate[i]%10;
		l_tmpdate[i]=l_tmpdate[i]+tmp*16;
	}  
 	
	
 	p=write_rtc_address;	//传地址	
 	for(i=0;i<7;i++)		//7次写入 秒分时日月周年
 	{
		  Write_Ds1302(*p,l_tmpdate[i]);
 		  p++;  
	 }
	 Write_Ds1302(0x8E,0x80);
}

/**********************************************************/
// 初始化DS1302
/*********************************************************/
void Init_ds1302(void)
{
	DS1203_Init();
	GPIO_WriteLow(GPIO_DS1302_PORT2,GPIO_DS1302_RST);
	delay_us(1);
	GPIO_WriteLow(GPIO_DS1302_PORT,GPIO_DS1302_SCLK);
	delay_us(1);	delay_us(1);
   Write_Ds1302(0x80,0x00); 
   Write_Ds1302(0x90,0x5c); //禁止充电
   Write_Ds1302(0x8e,0x80); //写保护控制字，禁止写
}
#endif