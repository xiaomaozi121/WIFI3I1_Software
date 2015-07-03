/**
  ******************************************************************************
  * @file    ht1621.h
  * @author  JF.Song
  * @version V1.0
  * @date    16-November-2013
  * @brief   moni_spi.c ��Ԥ���������
  ******************************************************************************
  * @attention
  *
  
  ******************************************************************************
  */
	
	/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MONI_SPI_H
#define __MONI_SPI_H

/* Includes ------------------------------------------------------------------*/
//#include "stm8s_gpio.h"
#include "includes.h"
//�����õ���ģ��SPI IO��
#define GPIO_SPI_PORT 	GPIOA
#define GPIO_SPI_CS	 	GPIO_PIN_6	
#define GPIO_SPI_WR 	 	GPIO_PIN_4
#define GPIO_SPI_RD   	GPIO_PIN_5
#define GPIO_SPI_DATA 	GPIO_PIN_3


//HT1621 ������� 

#define SYS_DIS  0b000000001 //����ϵͳ������LCDƫѹ������
#define TOPT     0b111000001 //����ģʽ
#define TNORMAL  0b111000111 //��ͨģʽ
#define BIAS     0b001010110 //1/3duty 4com
#define XTAL     0b000101000 //�ⲿ��ʱ��
#define RC256    0b000110000 //�ڲ�ʱ��
#define SYS_EN   0b000000011 //��ϵͳ����
#define LCD_OFF  0b000000101 //��LCDƫѹ
#define LCD_ON   0b000000111 //��LCDƫѹ
#define WDTDIS   0b000001010 //��ֹ���Ź�
/* Exported functions ------------------------------------------------------- */
/** @addtogroup GPIO_Exported_Functions
  * @{
  */

 typedef enum {
  PM25 = (uint8_t)0x01,  /*��ȩʾ�� */
  TVOC = (uint8_t)0x02,  /*VOCʾ��*/
	Humidity  = (uint8_t)0x03,
	Temperature = (uint8_t)0x04,
	Minute  = (uint8_t)0x05,
	Second = (uint8_t)0x06,
	Pollution   =  (uint8_t)0x07,
	HCHO  =  (uint8_t)0x08    
} Name_TypeDef;


void Lcd_DisplayBackground(void);
void LCD_DisplayClear(void);
void LCD_DisplayNum(unsigned char z,unsigned char n);//
void LCD_DisplayNum_Clr(unsigned char z);
void LCD_DisplayBatLogo(unsigned char b);//��ظ�����ʾ 0 1 2 3
void LCD_DisplayName(Name_TypeDef Name,u16 value );	
void LCD_DisplayName_Clr(Name_TypeDef Name);
void Lcd_DisplayRank(u16 data);
void Lcd_DisplayRankAll(void);
void Lcd_SetCol(u8 d);
void Lcd_SetHourAverage(u8 d);
void AlarmEnable(void);
void AlarmDisable(void);
//void moni_spi_Init( void );	
//uint8_t LCD_Read( uint8_t Addr );	
//void LCD_Write( uint8_t Addr , uint8_t Data );	
//void LCD_ReadWrite( uint8_t Addr  );	
//void LCD_Cmd( uint16_t Cmd );
void LCD_Init(void);
void LCD_DisplayTest(void);
#endif