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

 uint8_t write_rtc_address[7]={0x80,0x82,0x84,0x86,0x88,0x8a,0x8c}; //���ʱ�������� ���λ��дλ
 uint8_t read_rtc_address[7]={0x81,0x83,0x85,0x87,0x89,0x8b,0x8d};  

/**
  * ��ʼ��ds1203
  */
void DS1203_Init( void )
{
  
		GPIO_Init(GPIO_DS1302_PORT,(GPIO_DS1302_SCLK|GPIO_DS1302_DIO),GPIO_MODE_OUT_PP_HIGH_FAST);
		GPIO_Init(GPIO_DS1302_PORT2,GPIO_DS1302_RST,GPIO_MODE_OUT_PP_HIGH_FAST);
}

/*
********************************************************************************
** �������� �� Write_Ds1302_Byte(unsigned  char temp)
** �������� �� дһ���ֽ�
********************************************************************************
*/

void Write_Ds1302_Byte(unsigned  char temp) 
{
	uint8_t i;
	for (i=0;i<8;i++)     	//ѭ��8�� д������
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
		temp>>=1;  		//����һλ
		GPIO_WriteHigh(GPIO_DS1302_PORT,GPIO_DS1302_SCLK);
		delay_us(1);
	}
}

/*
********************************************************************************
** �������� �� Write_Ds1302( uint8_t address,uint8_t dat )
** �������� �� д��DS1302
********************************************************************************
*/   

void Write_Ds1302( uint8_t address,uint8_t dat )     
{
	GPIO_WriteLow(GPIO_DS1302_PORT2,GPIO_DS1302_RST);
	delay_us(1);
	GPIO_WriteLow(GPIO_DS1302_PORT,GPIO_DS1302_SCLK);
	delay_us(1);
	GPIO_WriteHigh(GPIO_DS1302_PORT2,GPIO_DS1302_RST);	
	delay_us(1);                    //����
	Write_Ds1302_Byte(address);	//���͵�ַ
	Write_Ds1302_Byte(dat);		//��������
	GPIO_WriteLow(GPIO_DS1302_PORT2,GPIO_DS1302_RST); 		            //�ָ�
}

/*
********************************************************************************
** �������� �� Read_Ds1302 ( uint8_t address )
** �������� �� ����DS1302����
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
	for (i=0;i<8;i++) 		//ѭ��8�� ��ȡ����
	{		
		 d = GPIO_ReadInputPin(GPIO_DS1302_PORT,GPIO_DS1302_DIO);
		if( d )
			temp|=0x80;			//ÿ�δ�����ֽ�
	GPIO_WriteHigh(GPIO_DS1302_PORT,GPIO_DS1302_SCLK);
	delay_us(1);
		temp>>=1;			//����һλ
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
	return (temp);			//����
}

/*
********************************************************************************
** �������� �� Read_RTC(void)	
** �������� �� ��ʱ������
********************************************************************************
*/

void Read_RTC(void)	        //��ȡ ����
{
	uint8_t i,*p;
	p=read_rtc_address; 	    //��ַ����
	for(i=0;i<7;i++)		    //��7�ζ�ȡ ���ʱ��������
	{
		l_tmpdate[i]=Read_Ds1302(*p);
		p++;
	}
}

/*
********************************************************************************
** �������� �� Set_RTC(void)
** �������� �� �趨ʱ������
********************************************************************************
*/

void Set_RTC(void)		    //�趨 ����
{
	uint8_t i,*p,tmp;
	
	Write_Ds1302(0x8E,0X00);
	for(i=0;i<7;i++)
	{       //BCD����
		tmp=l_tmpdate[i]/10;
		l_tmpdate[i]=l_tmpdate[i]%10;
		l_tmpdate[i]=l_tmpdate[i]+tmp*16;
	}  
 	
	
 	p=write_rtc_address;	//����ַ	
 	for(i=0;i<7;i++)		//7��д�� ���ʱ��������
 	{
		  Write_Ds1302(*p,l_tmpdate[i]);
 		  p++;  
	 }
	 Write_Ds1302(0x8E,0x80);
}

/**********************************************************/
// ��ʼ��DS1302
/*********************************************************/
void Init_ds1302(void)
{
	DS1203_Init();
	GPIO_WriteLow(GPIO_DS1302_PORT2,GPIO_DS1302_RST);
	delay_us(1);
	GPIO_WriteLow(GPIO_DS1302_PORT,GPIO_DS1302_SCLK);
	delay_us(1);	delay_us(1);
   Write_Ds1302(0x80,0x00); 
   Write_Ds1302(0x90,0x5c); //��ֹ���
   Write_Ds1302(0x8e,0x80); //д���������֣���ֹд
}
#endif