/**
  ******************************************************************************
  * @file    mi_spi.c
  * @author  JF.Song
  * @version V1.0
  * @date    16-November-2013
  * @brief   This file contains all the functions use GPIO to moni SPI
  ******************************************************************************
  * @attention
  *2014年1月20日 PM2.5 TVOC液晶
	2014年3月5日 改为PH液晶显示
  ******************************************************************************
  */
	
	/* Includes ------------------------------------------------------------------*/
#include "ht1621.h"

//unsigned char AA[13]={0};
//unsigned char face_num[3]={0, 0 ,0};
//0,1,2,3,4,5,6,7,8,9,无
#if defined ( HV )|| defined(PHV) ||defined ( PH ) ||defined ( PV ) 
unsigned char LED_H[]={   //数码管显示编码
0x05,0,0x06,0x02,0x03,0x03,0x07,0x00,0x07,0x03,0};
unsigned char LED_L[]={   //数码管显示编码
0x0f,6,0x0b,0x0f,0x06,0x0d,0x0d,0x07,0x0f,0x0f,0};
#endif
#if defined ( HV )|| defined(PHV)
unsigned char LED_H2[]={   //数码管显示编码
0x05,0,0x03,0x02,0x06,0x06,0x07,0x00,0x07,0x06,0};
unsigned char LED_L2[]={   //数码管显示编码
0x0f,6,0x0d,0x0f,0x06,0x0b,0x0b,0x0e,0x0f,0x0f,0};
#endif
#if defined ( PV )||defined ( PH )
unsigned char LED_H2[]={   //数码管显示编码
0x05,0,0x03,0x02,0x06,0x06,0x07,0x00,0x07,0x06,0};
unsigned char LED_L2[]={   //数码管显示编码
0x0f,6,0x0d,0x0f,0x06,0x0b,0x0b,0x0e,0x0f,0x0f,0};
#endif
#if defined ( PH )
unsigned char LED_H3[]={   //数码管显示编码
0x0a,0,0x0c,0x04,0x06,0x06,0x0e,0x00,0x0e,0x06,0};
/*unsigned char LED_L3[]={   //数码管显示编码
0x0f,6,0x0b,0x0f,0x06,0x0d,0x0d,0x07,0x0f,0x0f,0};
*/
#endif
#ifdef PV
unsigned char Buffer[10] ={
0x00,0x00,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00};  //缓存
//T2  COL S2/T5 S3   S4  S5   S6   S7   S8    S9  
#endif
#ifdef PH 
unsigned char Buffer[6] ={
0x03,0x00,0x00,0x00,0x00,0x04};  //缓存
//S13 S14  S15  D2  D3 D4/S1/S2 
#endif
#if defined(HV) || defined(PHV)
/*unsigned char Buffer[3] ={
0x08,        0x00, 0x00};  //缓存*/
//S5/s6/s7  S10     S11   
unsigned char Buffer[7] ={
0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x0f};  //缓存
//face 11-s5 9-s10 7-s11  bat 27-s4 25-s3 31-s2  lodsp 32-s6 s7
#endif
/**
  * 初始化模拟SPI 
  */
void moni_spi_Init( void )
{
  
		GPIO_Init(GPIO_SPI_PORT,(GPIO_SPI_CS|GPIO_SPI_WR|GPIO_SPI_RD|GPIO_SPI_DATA),\
							GPIO_MODE_OUT_PP_HIGH_FAST);
		
}

/**-----------------------------------
/**-----------------------------------
  * us 延时
    系统主时钟16M
  */
/*static void DelayUs(uint8_t us)
{
  uint8_t i;
	for(i=0; i<us*16; i++)
	{
		;
	}
}*/
/**-----------------------------------
  * SPI 写 1
	   WR   上升沿  _|-- 
		 DATA 1       ---- 
  */
static void moni_spi_Write_High (void)
{
		GPIO_WriteLow(GPIO_SPI_PORT,GPIO_SPI_WR);
		delay_us(1);
		GPIO_WriteHigh(GPIO_SPI_PORT,GPIO_SPI_DATA);
		delay_us(1);
		GPIO_WriteHigh(GPIO_SPI_PORT,GPIO_SPI_WR);
		delay_us(1);

}


/**
  * SPI 写 0
	   WR   上升沿  _|-- 
		 DATA 0       ____ 
  */
static void moni_spi_Write_Low (void)
{
		GPIO_WriteLow(GPIO_SPI_PORT,GPIO_SPI_WR);
		delay_us(1);
		GPIO_WriteLow(GPIO_SPI_PORT,GPIO_SPI_DATA);
		delay_us(1);
		GPIO_WriteHigh(GPIO_SPI_PORT,GPIO_SPI_WR);
		delay_us(1);
}

/**
  * 读命令 SPI 写 110
  */
static void LCD_COM_Read( void )
{   // 1
		moni_spi_Write_High();
		// 1
		moni_spi_Write_High();	
		// 0
		moni_spi_Write_Low();			

}

/**
  * 写命令 SPI 写 101
  */
static void LCD_COM_Write( void )
{    // 1
		moni_spi_Write_High();
		// 0
		moni_spi_Write_Low();	
	  // 1
		moni_spi_Write_High();	
		
}

/**
  * 操作命令 SPI 写 100
  */
static void LCD_COM_Cmd( void )
{    // 1
		moni_spi_Write_High();
		// 0
		moni_spi_Write_Low();		
		// 0
		moni_spi_Write_Low();			
}

/**
  * 读LCD RAM
	 @ Addr RAM 的地址 6bit  A5 --- A 0
	 返回读到的数据 4bit     D0 --- D3
  */
/*static uint8_t LCD_Read( uint8_t Addr )
{
	uint8_t i;
	uint8_t data = 0;
	uint8_t addr1 = Addr;
	GPIO_WriteLow(GPIO_SPI_PORT,GPIO_SPI_CS);//LCD使能
	LCD_COM_Read();
	
	for(i=0; i<6; i++)  //写要读的RAM地址
	{
		GPIO_WriteLow(GPIO_SPI_PORT,GPIO_SPI_WR);
		

		if (	addr1&0x20 )
		{
			moni_spi_Write_High();
		}
		else
		{
				moni_spi_Write_Low();
		}
		addr1 = ( addr1 << 1 );
		GPIO_WriteHigh(GPIO_SPI_PORT,GPIO_SPI_WR);				
	}	
	
	GPIO_Init(GPIO_SPI_PORT,GPIO_SPI_DATA,GPIO_MODE_IN_PU_NO_IT);	 //数据线变为输入脚
	for(i=0; i<4; i++)  //读4bit数据
	{
		GPIO_WriteLow(GPIO_SPI_PORT,GPIO_SPI_RD);
		data = ( data << 1 );
		data |=GPIO_ReadInputPin(GPIO_SPI_PORT,GPIO_SPI_DATA);
		GPIO_WriteHigh(GPIO_SPI_PORT,GPIO_SPI_RD);						
	}
	GPIO_Init(GPIO_SPI_PORT,GPIO_SPI_DATA,GPIO_MODE_OUT_PP_HIGH_FAST);	
	
	GPIO_WriteHigh(GPIO_SPI_PORT,GPIO_SPI_CS);//停止 LCD使能	
	return data;
}*/

/**
  * 写LCD RAM
	 @ Addr RAM 的地址
	 @ data 要写的数据 4bit
  */
static void LCD_Write( uint8_t Addr , uint8_t Data )
{
	uint8_t i;
	uint8_t data1 = Data;
	uint8_t addr1 = Addr;
	GPIO_WriteLow(GPIO_SPI_PORT,GPIO_SPI_CS);//LCD使能
	LCD_COM_Write();
	
	for(i=0; i<6; i++)
	{
		
		if (addr1 & 0x20)
		{
			moni_spi_Write_High();
		}
		else
		{
				moni_spi_Write_Low();
		}
		addr1 = ( addr1 << 1 );			
	}	
	for(i=0; i<4; i++)
	{

		if (data1&0x01)
		{
			moni_spi_Write_High();
		}
		else
		{
				moni_spi_Write_Low();
		}
		data1 = ( data1 >> 1 );
	
	}
	GPIO_WriteHigh(GPIO_SPI_PORT,GPIO_SPI_CS);//停止 LCD使能	
}

/**
  * 读和写LCD RAM
	 @ Addr RAM 的地址
	 @ data 要写的数据 4bit
  */
/*static void LCD_ReadWrite( uint8_t Addr  )
{
	uint8_t i;
	uint8_t data1,data;
	uint8_t addr1 = Addr;
	GPIO_WriteLow(GPIO_SPI_PORT,GPIO_SPI_CS);//LCD使能
	LCD_COM_Write();
	
	for(i=0; i<6; i++)
	{
		
		if (addr1 & 0x01)
		{
			moni_spi_Write_High();
		}
		else
		{
				moni_spi_Write_Low();
		}
		addr1 = ( addr1 << 1 );			
	}	
	
	
	
	GPIO_Init(GPIO_SPI_PORT,GPIO_SPI_DATA,GPIO_MODE_IN_PU_NO_IT);	 //数据线变为输入脚
	for(i=0; i<4; i++)  //读4bit数据
	{
		GPIO_WriteLow(GPIO_SPI_PORT,GPIO_SPI_RD);
		data = ( data << 1 );
		data |=GPIO_ReadInputPin(GPIO_SPI_PORT,GPIO_SPI_DATA);
		GPIO_WriteHigh(GPIO_SPI_PORT,GPIO_SPI_RD);						
	}
	//对读出的数据进行操作
	data1 = data;
	GPIO_Init(GPIO_SPI_PORT,GPIO_SPI_DATA,GPIO_MODE_OUT_PP_HIGH_FAST);	
	for(i=0; i<4; i++)
	{
		
		data1 &= 0x01;
		if (data1&0x01)
		{
			moni_spi_Write_High();
		}
		else
		{
			moni_spi_Write_Low();
		}
		data1 = ( data1 >> 1 );		
	}
	GPIO_WriteHigh(GPIO_SPI_PORT,GPIO_SPI_CS);//停止 LCD使能
}*/
/**
  * 对LCD的操作命令
	 @ Cmd 进行的操作 9bit
  */

static void LCD_Cmd( uint16_t Cmd )
{
  
	
	uint8_t i;
	uint16_t cmd = Cmd;
	GPIO_WriteLow(GPIO_SPI_PORT,GPIO_SPI_CS);//LCD使能
	LCD_COM_Cmd();
	
	for(i=0; i<9; i++)
	{
		
		if (cmd & 0x100)
		{
				moni_spi_Write_High();
		}
		else
		{
				moni_spi_Write_Low();
		}
		cmd = ( cmd << 1 );			
	}
	
GPIO_WriteHigh(GPIO_SPI_PORT,GPIO_SPI_CS);//停止 LCD使能
}

/**
  * 对LCD的初始化
  */

void LCD_Init(void)
{
		moni_spi_Init();
		LCD_Cmd(BIAS);
		LCD_Cmd(RC256);
		LCD_Cmd(SYS_EN);
		LCD_Cmd(WDTDIS);
		//LCD_Cmd(TOPT);
		LCD_Cmd(LCD_ON);

}

/**
  * 对LCD全部显示
  */

void LCD_DisplayTest(void)
{
		uint8_t i;
			for(i=0; i<32; i++)
	{
		
		LCD_Write(i,0xFF);	
	}

}
/**
  * 对LCD全部清零
  */

void LCD_DisplayClear(void)
{
		uint8_t i;
			for(i=0; i<32; i++)
	{
		
		LCD_Write(i,0x00);	
	}
	
	
}
/**
  * 对LCD显示背景  暨静态显示部分
  */
#ifdef PV
void Lcd_DisplayBackground(void)
{
	LCD_Write(29,8); //34 T1 PM2.5 
	LCD_Write(17,0x5); //22 T4  TVOC T6 mg/m3
	LCD_Write(16,0xE); //S1 21 T7 T8 温湿度 空气质量指数
  LCD_Write(25,8); //30 T3 ug/m3
	LCD_Write(13,8); //18 T9 温度单位
	LCD_Write(9,8); //14 T10 湿度单位
}
#endif
#ifdef PH
void Lcd_DisplayBackground(void)
{
	LCD_Write(31,4); //32 D1 电池
	LCD_Write(26,0x1); //27 S7 。C
	LCD_Write(22,0x1); // 23 S3 甲醛
  LCD_Write(20,1); //21 S4 mg/m3
	LCD_Write(18,1); //19 S5 PM2.5
	LCD_Write(12,1); //12 S6 ug/m3
	LCD_Write(24,1); //25 P 
	LCD_Write(5,8); // 10 S12 污染指数
	LCD_Write(4,3); // 9 S11 湿度 S10 RH
	LCD_Write(2,8); // 7 S9 %
	LCD_Write(0,8); // 5 S8 温度
}
#endif

#if defined (HV) || defined(PHV)
/*
void Lcd_DisplayBackground(void)
{
	LCD_Write(18,1); //36 S1 电池
	LCD_Write(28,0x8); //26 S15 。C
	LCD_Write(19,0x8); //35 S5 甲醛
 // LCD_Write(20,1); //21 S4 mg/m3
	LCD_Write(24,8); //30 S16 化学污染物 mg/m3
	//LCD_Write(12,1); //12 S6 ug/m3
	LCD_Write(2,1); //7 S9 point
	LCD_Write(22,8); //22 S13 point
	LCD_Write(6,1); // 11 S12 污染指数
	LCD_Write(26,8); // 28 S14 湿度 S10 RH
  //LCD_Write(2,8); // 7 S9 %
	LCD_Write(28,8); // 26 S15 温度
}
*/
void Lcd_DisplayBackground(void)
{
	LCD_Write(31,9); //0 S1 电池  s8甲醛 mg/m3
	LCD_Write(18,3); //19 S16 化学污染物 mg/m3  s15温度
	LCD_Write(28,8); //29 S9 point
	LCD_Write(22,8); //23 S13 point
	LCD_Write(0,8); // 5 S12 污染指数
	LCD_Write(8,8); //13 S14 湿度 S10 RH

}
#endif

#ifdef PV
/**
  * 对LCD缓存刷新
  */
//unsigned char Buffer[10] ={
//0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};  //缓存
// T2  COL  S2/T5 S3   S4   S5   S6   S7   S8    S9  

static void writeS( u8 f)
{
	u8 i;
	for(i =2; i<=f; i++ )
	 {Buffer[i] = Buffer[i]|(0x8);}
	for(i =f+1; i<10; i++ )
	{ Buffer[i] = Buffer[i]&(0x7);}
}
static void DisplayBuffer( void )
{
 LCD_Write(27,Buffer[0]); 
 LCD_Write(4,Buffer[1]); 
 LCD_Write(17,Buffer[2]); 
 LCD_Write(19,Buffer[3]); 
 LCD_Write(23,Buffer[4]); 
 LCD_Write(0,Buffer[5]); 
 LCD_Write(2,Buffer[6]); 
 LCD_Write(6,Buffer[7]); 
 LCD_Write(11,Buffer[8]); 
 LCD_Write(15,Buffer[9]); 
}

void Lcd_DisplayRank(u16 data)
{
  if(data > 350)
	  writeS(9);
  else if(data > 300)
    writeS(8); 
	else if(data > 250)
    writeS(7);
	else if(data > 200)
    writeS(6);
	else if(data > 150)
    writeS(5);
	else if(data > 100)
    writeS(4);
	else if(data > 50)
    writeS(3);
	else if(data > 00)
    writeS(2);
	else if(data == 00)
    writeS(1);	
  else		
	;
	
	DisplayBuffer();
}
#endif

#ifdef PH
/*Buffer[6] ={
0x03,0x00,0x00,0x00,0x00,0x04};  //缓存
//S13 S14  S15  D2  D3 D4/S1/S2 */
static void DisplayBuffer( void )
{
 LCD_Write(4,Buffer[0]); 
 LCD_Write(7,Buffer[1]); 
 LCD_Write(9,Buffer[2]); 
 LCD_Write(28,Buffer[3]); 
 LCD_Write(30,Buffer[4]); 
 LCD_Write(31,Buffer[5]); 
}

void Lcd_DisplayRankAll(void)
{
		Buffer[0] = 7;   //显示3个脸
		Buffer[1] = 0x8|Buffer[1];
		Buffer[2] = 0x8|Buffer[2];	
		DisplayBuffer();	
}

void Lcd_DisplayRank(u16 data)
{
	if(data > 16)//200)  //200是以整体空气质量指数为标准 16是 以甲醛含量为标准
   {
				Buffer[0] = 3;
				Buffer[1] = 0x8|Buffer[1];
				Buffer[2] = 0x7&Buffer[2];	
	 }
	else if(data > 8)//100)  //100是以整体空气质量指数为标准 8是 以甲醛含量为标准
	 {

				Buffer[0] = 3;
				Buffer[1] = 0x7&Buffer[1];
				Buffer[2] = 0x8|Buffer[2];					
	 }
	else if(data >= 00)
	{
				Buffer[0] = 7;
				Buffer[1] = 0x7&Buffer[1];
				Buffer[2] = 0x7&Buffer[2];	 
	}
  else		
	;
	DisplayBuffer();
}
#endif

#if defined (HV) || defined(PHV)
/*Buffer[6] ={
0x03,0x00,0x00,0x00,0x00,0x04};  //缓存
//S13 S14  S15  D2  D3 D4/S1/S2 */
static void DisplayBuffer( void )
{
 LCD_Write(6,Buffer[0]);  //1 face
 LCD_Write(4,Buffer[1]);  //2 face
 LCD_Write(2,Buffer[2]);  //3 face
 
 LCD_Write(26,Buffer[3]);  //1 bat
 LCD_Write(24,Buffer[4]);   //2 bat
 LCD_Write(31,Buffer[5]);  //3 bat
 
 LCD_Write(31,Buffer[6]);  //sond

}

void Lcd_DisplayRankAll(void)
{
		Buffer[0] = 0x8|Buffer[0];   //显示3个脸
		Buffer[1] = 0x8|Buffer[1];
		Buffer[2] = 0x8|Buffer[2];	
		DisplayBuffer();	
}

void Lcd_DisplayRank(u16 data)
{
	if(data > 200)
   {
				Buffer[0] = Buffer[0]&0x7;
				Buffer[1] = Buffer[1]&0x7;
				Buffer[2] = 0x8|Buffer[2];	// Buffer[0]&0xe;
	 }
	else if(data > 100)
	 {

				Buffer[0] = Buffer[0]&0x7;
				Buffer[1] = 0x8|Buffer[1];
				Buffer[2] = Buffer[2]&0x7;	// Buffer[0]&0xe;					
	 }
	else if(data >= 00)
	{
				Buffer[0] = 0x8|Buffer[0];
				Buffer[1] = Buffer[1]&0x7;
				Buffer[2] = Buffer[2]&0x7;	// Buffer[0]&0xe;	 
	}
  else		
	;
	DisplayBuffer();
}
#endif


#ifdef PV
//显示时均值字
void Lcd_SetCol(u8 d)
{
	if( d )
	{
	Buffer[1] = Buffer[1]|(0x8);
  }
  else
  {
	Buffer[1] = Buffer[1]&(0x7);
	}
	 LCD_Write(4,Buffer[1]); 
}
//显示时间点
void Lcd_SetHourAverage(u8 d)
{
	if( d )
	{
	Buffer[0] = Buffer[0]|(0x8);
	Buffer[2] = Buffer[2]|(0x2);
  }
  else
  {
	Buffer[0] = Buffer[0]&(0x7);
	Buffer[2] = Buffer[2]&(0xd);
	}
	DisplayBuffer();
}
#endif

#ifdef PH
void AlarmEnable(void)
{
  Buffer[5] =  Buffer[5]|0x2;
	Buffer[5] =  Buffer[5]&0xe;
	DisplayBuffer();
}
void AlarmDisable(void)
{
  Buffer[5] =  Buffer[5]|0x1;
	Buffer[5] =  Buffer[5]&0xd;
	DisplayBuffer();
}

#endif

#if defined (HV) || defined(PHV)
void AlarmEnable(void)
{
	Buffer[6] =  Buffer[6]|0x2;
	Buffer[6] =  Buffer[6]&0xb;
	DisplayBuffer();
}
void AlarmDisable(void)
{
	Buffer[6] =  Buffer[6]|0x4;
	Buffer[6] =  Buffer[6]&0xd;
	DisplayBuffer();
}

#endif

#ifdef PV
/**
  * 对电池电量显示
  */
		void LCD_DisplayBatLogo(unsigned char b)
	{	switch(b)
		{
			case 0:			
			LCD_Write(30,1); //35
			LCD_Write(31,0); //36
			break;		
			case 1:
			LCD_Write(30,1); 
			LCD_Write(31,2); 
			break;
			case 2:
			LCD_Write(30,0x3); 
			LCD_Write(31,2); 
			break;	
			case 3:
			LCD_Write(30,0x3); 
			LCD_Write(31,0x3); 				
			break;	
		}
}	
#endif

#if defined (HV) || defined(PHV)
/**
  * 对电池电量显示
  */
	void LCD_DisplayBatLogo(unsigned char b)
	{	switch(b)
		{
			case 0:			
				//LCD_Write(18,8); 
				//Buffer[3] =  Buffer[3]|0x8;
				Buffer[3] =  Buffer[3]&0x7;
				Buffer[4] =  Buffer[4]&0x7;
				Buffer[5] =  Buffer[5]&0x7;
				
			break;		
			case 1:
				//LCD_Write(18,9);
				//Buffer[4] =  Buffer[4]|0x8;
				Buffer[3] =  Buffer[3]|0x8;
				Buffer[4] =  Buffer[4]&0x7;
				Buffer[5] =  Buffer[5]&0x7;
			break;
			case 2:
				//LCD_Write(18,0xb); 
				//Buffer[5] =  Buffer[5]|0x8;	
				Buffer[3] =  Buffer[3]|0x8;
				Buffer[4] =  Buffer[4]|0x8;
				Buffer[5] =  Buffer[5]&0x7;
			 break;
			case 3:
				//LCD_Write(18,0xF); 
				Buffer[3] =  Buffer[3]|0x8;
				Buffer[4] =  Buffer[4]|0x8;
				Buffer[5] =  Buffer[5]|0x8;
			break;	
			default:		
			break;	
			
		}
	}
#endif

#ifdef PH
/**
  * 对电池电量显示
  */
	/*Buffer[6] ={
0x03,0x00,0x00,0x00,0x00,0x04};  //缓存
//S13 S14  S15  D2  D3 D4/S1/S2 */
	void LCD_DisplayBatLogo(unsigned char b)
	{	switch(b)
		{
			case 0:			
       Buffer[3] =  Buffer[3]&0x7;
			 Buffer[4] =  Buffer[4]&0x7;
			 Buffer[5] =  Buffer[5]&0x7;
			break;		
			case 1:
       Buffer[3] =  Buffer[3]|0x8;
			 Buffer[4] =  Buffer[4]&0x7;
			 Buffer[5] =  Buffer[5]&0x7;
			break;
			case 2:
       Buffer[3] =  Buffer[3]|0x8;
			 Buffer[4] =  Buffer[4]|0x8;
			 Buffer[5] =  Buffer[5]&0x7;
			 break;
			case 3:
       Buffer[3] =  Buffer[3]|0x8;
			 Buffer[4] =  Buffer[4]|0x8;
			 Buffer[5] =  Buffer[5]|0x8;
			break;	
			default:		
			break;	
			
		}
			DisplayBuffer();
	}
#endif
/**
  * 数值显示
  */
#ifdef PV
void LCD_DisplayNum(unsigned char z,unsigned char n)
{
	switch(z)
	{
	case 1:	
	LCD_Write(29,LED_H[n]+8);  //34 
  LCD_Write(28,LED_L[n]);    //33
	break;
	case 2:	
	Buffer[0] =(Buffer[0]&0x08)+LED_H[n];
	LCD_Write(27,Buffer[0]);  // 32 
  LCD_Write(26,LED_L[n]);    //31
	break;
	case 3:	
	LCD_Write(25,LED_H[n]+8);  //   
  LCD_Write(24,LED_L[n]);    //
	break;	
		
	case 4:	
	Buffer[4] =(Buffer[4]&0x08)+LED_H[n];
	LCD_Write(23,Buffer[4]);  // 
  LCD_Write(22,LED_L[n]);    //
	break;		
	
	case 5:	
	LCD_Write(21,LED_H[n]+8);  // 
  LCD_Write(20,LED_L[n]);    //

	break;		
	
	
	case 6:
	Buffer[3] =(Buffer[3]&0x08)+LED_H[n];
	LCD_Write(19,Buffer[3]);  // 24
  LCD_Write(18,LED_L[n]);    // 23
	break;		
	case 7:	
	Buffer[9] =(Buffer[9]&0x08)+LED_H[n];
	LCD_Write(15,Buffer[9]);  // 20
  LCD_Write(14,LED_L[n]);    // 19
	break;	
	
	
	case 8:	
	LCD_Write(13,LED_H[n]+8);  // 18
  LCD_Write(12,LED_L[n]);    // 17
	break;	
	
	case 9:	
	Buffer[8] =(Buffer[8]&0x08)+LED_H[n];
	LCD_Write(11,Buffer[8]);  // 16
  LCD_Write(10,LED_L[n]);    // 15
	break;	
	
	case 10:	
	LCD_Write(0x09,LED_H[n]+8);  // 
  LCD_Write(0x08,LED_L[n]);    //
	break;
	case 11:
	Buffer[5] =(Buffer[5]&0x08)+LED_H2[n];
	LCD_Write(0x00,Buffer[5]);  // 6
  LCD_Write(0x01,LED_L2[n]);    // 5
	break;

	case 12:
	Buffer[6] =(Buffer[6]&0x08)+LED_H2[n];
	LCD_Write(0x02,Buffer[6]);  // 8
  LCD_Write(0x03,LED_L2[n]);     //7
	break;	
	
	case 13:
	Buffer[1] =(Buffer[1]&0x08)+LED_H2[n];
	LCD_Write(0x04,Buffer[1]);  // 10
  LCD_Write(0x05,LED_L2[n]);    // 9
	break;
	
	case 14:
	Buffer[7] =(Buffer[7]&0x08)+LED_H2[n];
	LCD_Write(0x06,Buffer[7]);  // 12
  LCD_Write(0x07,LED_L2[n]);    // 11
	break;
	}
}

/**-----------------------------------
  *LCD 显示函数
  ------------------------------------------------*/	
void LCD_DisplayName(Name_TypeDef Name,u16 value )
{
	u8 a,b,c;
	a = value/100;
	b = (value%100)/10;
	c = (value%10);
	switch ( Name )
	{	case PM25:
			LCD_DisplayNum(1,a);
			LCD_DisplayNum(2,b);
			LCD_DisplayNum(3,c);
			break;
		case TVOC:
			LCD_DisplayNum(4,a);
			LCD_DisplayNum(5,b);
			LCD_DisplayNum(6,c);
			break;
		case Humidity:
			LCD_DisplayNum(9,b);
			LCD_DisplayNum(10,c);
			break;
		case Temperature:
			LCD_DisplayNum(7,b);
			LCD_DisplayNum(8,c);
			break;
		case Minute:
			LCD_DisplayNum(11,b);
			LCD_DisplayNum(12,c);
			break;
		case Second:
			LCD_DisplayNum(13,b);
			LCD_DisplayNum(14,c);			
			break;
		default:
			break;    
	}			
}	
#endif

	#ifdef PH
	
	void LCD_DisplayNum(unsigned char z,unsigned char n)
{
	switch(z)
	{
	case 1:	
	LCD_Write(0,LED_H2[n]+8);  //5 
  LCD_Write(1,LED_L2[n]);    //6
	break;
	case 2:	
	LCD_Write(2,LED_H2[n]+8);  //7 
  LCD_Write(3,LED_L2[n]);    //8
	break;
	case 3:	
	LCD_Write(5,LED_H2[n]+8);  //10   
  LCD_Write(6,LED_L2[n]);    //11
	break;	
		
	case 4:	
	Buffer[1] =(Buffer[1]&0x08)+LED_H2[n];
	LCD_Write(7,Buffer[1]);  // 12
  LCD_Write(8,LED_L2[n]);    //13
	break;		
	
	case 5:	
	Buffer[2] =(Buffer[2]&0x08)+LED_H2[n];
	LCD_Write(9,Buffer[2]);  // 14
  LCD_Write(10,LED_L2[n]);    //15

	break;	
	
	case 6:
	LCD_Write(12,LED_H3[n]|0x01);  // 17
  LCD_Write(11,LED_L[n]);    // 16
	break;		
	case 7:	
	LCD_Write(18,LED_H3[n]|0x01);  // 18
  LCD_Write(13,LED_L[n]);    // 19
	break;	
	
	
	case 8:	
	LCD_Write(20,LED_H3[n]|0x01);  // 21
  LCD_Write(19,LED_L[n]);    // 20
	break;	
	
	case 9:	
	LCD_Write(22,LED_H3[n]|0x01);  // 23
  LCD_Write(21,LED_L[n]);    // 22
	break;	
	
	case 10:	
	LCD_Write(24,LED_H3[n]|0x01);  // 25
  LCD_Write(23,LED_L[n]);    //24
	break;
	case 11:
	LCD_Write(26,LED_H3[n]|0x01);  // 27
  LCD_Write(25,LED_L[n]);    //26
	break;


	case 12:
	Buffer[3] =(Buffer[3]&0x08)+LED_H[n];
	LCD_Write(28,Buffer[3]);  // 8
  LCD_Write(27,LED_L[n]);     //7
	break;	
	
	case 13:
	Buffer[4] =(Buffer[4]&0x08)+LED_H[n];
	LCD_Write(30,Buffer[4]);  // 10
  LCD_Write(29,LED_L[n]);    // 9
	break;
	}
}

/**-----------------------------------
  *LCD 显示函数
  ------------------------------------------------*/	
void LCD_DisplayName(Name_TypeDef Name,u16 value )
{
	u8 a,b,c;
	a = value/100;
	b = (value%100)/10;
	c = (value%10);
	switch ( Name )
	{	case PM25:
			LCD_DisplayNum(8,a);
			LCD_DisplayNum(7,b);
			LCD_DisplayNum(6,c);
			break;
		case HCHO:
			LCD_DisplayNum(11,a);
			LCD_DisplayNum(10,b);
			LCD_DisplayNum(9,c);
			break;
		case Humidity:
			LCD_DisplayNum(1,b);
			LCD_DisplayNum(2,c);
			break;
		case Temperature:
			LCD_DisplayNum(13,b);
			LCD_DisplayNum(12,c);
			break;
		case Pollution:
			LCD_DisplayNum(3,a);
			LCD_DisplayNum(4,b);
			LCD_DisplayNum(5,c);
			break;
		default:
			break;    
	}			
}
	#endif
	
	
#if defined (HV) || defined(PHV)
		void LCD_DisplayNum(unsigned char z,unsigned char n)
{
	switch(z)
	{
	case 1:	
	Buffer[5] =(Buffer[5]&0x08)+LED_H[n];//Buffer[1] =(Buffer[1]&0x01)+LED_H[n];   // s2 电量3
	LCD_Write(30,Buffer[5]);  //5 
	LCD_Write(29,LED_L[n]);  //6
	break;
	case 2:	
	LCD_Write(28,LED_H[n]+8);  //7              // s9 dot hcho
	LCD_Write(27,LED_L[n]);    //8
	break;
	case 3:	
	Buffer[3] =(Buffer[3]&0x08)+LED_H[n];//Buffer[1] =(Buffer[2]&0x01)+LED_H[n];&0x08  //s4 电量1
	LCD_Write(26,Buffer[3]);  //10   
	LCD_Write(25,LED_L[n]);    //11
	break;	
		
	case 4:	
	Buffer[4] =(Buffer[4]&0x08)+LED_H[n];    ////s3 电量2
	LCD_Write(24,Buffer[4]);  // 12
	LCD_Write(23,LED_L[n]);    //13
	break;		
	
	case 5:	
	LCD_Write(22,LED_H[n]|0x08);  // 17     //s13 dot tvoc
	LCD_Write(21,LED_L[n]);    // 16
	break;	
	
	case 6:
	LCD_Write(20,LED_H[n]);  // 17
  LCD_Write(19,LED_L[n]);    // 16
	break;		
	case 7:	
	LCD_Write(0,LED_H2[n]|0x08);  // 18 //LCD_Write(0,LED_H2[n]|0x01);  // s12 dot 污染指数
  LCD_Write(1,LED_L2[n]);    // 19
	break;	
	
	
	case 8:	
	Buffer[2] =(Buffer[2]&0x08)+LED_H2[n];
	LCD_Write(2,Buffer[2]);  // 21     //  笑脸3
  LCD_Write(3,LED_L2[n]);    // 20
	break;	
	
	case 9:	
		Buffer[1] =(Buffer[1]&0x08)+LED_H2[n];
		LCD_Write(4,Buffer[1]);  // 23   //笑脸2
		LCD_Write(5,LED_L2[n]);    // 22
	break;	
	
	case 10:
		Buffer[0] =(Buffer[0]&0x08)+LED_H2[n];
		LCD_Write(6,Buffer[0]);  // 25     笑脸1
		LCD_Write(7,LED_L2[n]);    //24
	break;
	case 11:
	LCD_Write(8,LED_H2[n]|0x08);  // 27   //LCD_Write(8,LED_H2[n]|0x01);  // 27   //s14 湿度
  LCD_Write(9,LED_L2[n]);    //26
	break;


	case 12:
	LCD_Write(11,LED_H[n]);  // 27
	LCD_Write(10,LED_L[n]);    //26
	break;	
	
	case 13:
	LCD_Write(13,LED_H[n]);  // 27
	LCD_Write(12,LED_L[n]);    //26
	break;
	}
}

void LCD_DisplayNum_Clr(unsigned char z)
{
	switch(z)
	{
	case 1:	
	Buffer[5] =(Buffer[5]&0x08)+0;//Buffer[1] =(Buffer[1]&0x01)+LED_H[n];   // s2 电量3
	LCD_Write(30,Buffer[5]);  //5 
	LCD_Write(29,0);  //6
	break;
	case 2:	
	LCD_Write(28,0+8);  //7              // s9 dot hcho
	LCD_Write(27,0);    //8
	break;
	case 3:	
	Buffer[3] =(Buffer[3]&0x08)+0;//Buffer[1] =(Buffer[2]&0x01)+LED_H[n];&0x08  //s4 电量1
	LCD_Write(26,Buffer[3]);  //10   
	LCD_Write(25,0);    //11
	break;	
		
	case 4:	
	Buffer[4] =(Buffer[4]&0x08)+0;    ////s3 电量2
	LCD_Write(24,Buffer[4]);  // 12
	LCD_Write(23,0);    //13
	break;		
	
	case 5:	
	LCD_Write(22,0|0x08);  // 17     //s13 dot tvoc
	LCD_Write(21,0);    // 16
	break;	
	
	case 6:
	LCD_Write(20,0);  // 17
  LCD_Write(19,0);    // 16
	break;		
	case 7:	
	LCD_Write(0,0|0x08);  // 18 //LCD_Write(0,LED_H2[n]|0x01);  // s12 dot 污染指数
  LCD_Write(1,0);    // 19
	break;	
	
	
	case 8:	
	Buffer[2] =(Buffer[2]&0x08)+0;
	LCD_Write(2,Buffer[2]);  // 21     //  笑脸3
  LCD_Write(3,0);    // 20
	break;	
	
	case 9:	
		Buffer[1] =(Buffer[1]&0x08)+0;
		LCD_Write(4,Buffer[1]);  // 23   //笑脸2
		LCD_Write(5,0);    // 22
	break;	
	
	case 10:
		Buffer[0] =(Buffer[0]&0x08)+0;
		LCD_Write(6,Buffer[0]);  // 25     笑脸1
		LCD_Write(7,0);    //24
	break;
	case 11:
	LCD_Write(8,0|0x08);  // 27   //LCD_Write(8,LED_H2[n]|0x01);  // 27   //s14 湿度
  LCD_Write(9,0);    //26
	break;


	case 12:
	LCD_Write(11,0);  // 27
	LCD_Write(10,0);    //26
	break;	
	
	case 13:
	LCD_Write(13,0);  // 27
	LCD_Write(12,0);    //26
	break;
	}
}

/**-----------------------------------
  *LCD 显示函数
  ------------------------------------------------*/	
void LCD_DisplayName(Name_TypeDef Name,u16 value )
{
	u8 a,b,c;
	a = value/100;
	b = (value%100)/10;
	c = (value%10);
	switch ( Name )
	{	case TVOC:
			LCD_DisplayNum(4,a);
			LCD_DisplayNum(5,b);
			LCD_DisplayNum(6,c);
			break;
		case HCHO:
			LCD_DisplayNum(1,a);
			LCD_DisplayNum(2,b);
			LCD_DisplayNum(3,c);
			break;
		case Humidity:
			LCD_DisplayNum(10,b);
			LCD_DisplayNum(11,c);
			break;
		case Temperature:
			LCD_DisplayNum(13,b);
			LCD_DisplayNum(12,c);
			break;
		case Pollution:
			LCD_DisplayNum(7,a);
			LCD_DisplayNum(8,b);
			LCD_DisplayNum(9,c);
			break;
		default:
			break;    
	}			
}
void LCD_DisplayName_Clr(Name_TypeDef Name)
{

	switch ( Name )
	{	case TVOC:
			LCD_DisplayNum_Clr(4);
			LCD_DisplayNum_Clr(5);
			LCD_DisplayNum_Clr(6);
			break;
		case HCHO:
			LCD_DisplayNum_Clr(1);
			LCD_DisplayNum_Clr(2);
			LCD_DisplayNum_Clr(3);
			break;
		case Humidity:
			LCD_DisplayNum_Clr(10);
			LCD_DisplayNum_Clr(11);
			break;
		case Temperature:
			LCD_DisplayNum_Clr(13);
			LCD_DisplayNum_Clr(12);
			break;
		case Pollution:
			LCD_DisplayNum_Clr(7);
			LCD_DisplayNum_Clr(8);
			LCD_DisplayNum_Clr(9);
			break;
		default:
			break;    
	}			
}
	#endif
	
