/*
 * mystruct.h
 *
 *  Created on: 2013-7-3
 *      Author: Administrator
 */

#ifndef NEWSTRUCT2_H_
#define NEWSTRUCT2_H_
/*********************************************************************************
 * 编译器数据类型接口
 */
typedef unsigned char     BYTE;	    // 8-bit
typedef unsigned int	  WORD;		// 16-bit
typedef unsigned long  	  DWORD;    // 32-bit

/**********************************************************************************
 * 系统全局主标志
 */
typedef union _MAIN_FLAG
{
	BYTE byte;
	struct
	{
		unsigned timer:1;
		unsigned dec:1;
		unsigned bit2:1;
		unsigned bit3:1;
		unsigned bit4:1;
		unsigned bit5:1;
		unsigned bit6:1;
		unsigned bit7:1;
	}bits;
}MAIN_FLAG;

typedef union _EDGE_FALG
{
	BYTE byte;
	struct
	{
		unsigned high:1;
		unsigned low:1;
		unsigned high2low:1;
		unsigned low2high:1;
		unsigned err:1;
		unsigned enable:1;
		unsigned bit6:1;
		unsigned bit7:1;
	}bits;
}EDGE_FALG;
//------------------应用函数声名------------------------------、
/**********************************************************************************
 * 系统全局主标志
 */

/**********************************************************************************
 * 以太网全局主标志
 */
typedef union _ETH_FLAG
{
	BYTE byte;
	struct
	{
		unsigned send:1;
		unsigned link:1;
		unsigned ack:1;
		unsigned debug:1;
		unsigned bit4:1;
		unsigned bit5:1;
		unsigned bit6:1;
		unsigned bit7:1;
	}bits;
}ETH_FLAG;
/**********************************************************************************
 * 通用数据类型
 */
typedef union _BYTE_BITS
{
    BYTE byte;
    struct
    {
        unsigned  bit0:1;
        unsigned  bit1:1;
        unsigned  bit2:1;
        unsigned  bit3:1;
        unsigned  bit4:1;
        unsigned  bit5:1;
        unsigned  bit6:1;
        unsigned  bit7:1;
    } bits;
} BYTE_BITS;

typedef union _WORD_BYTES
{
    WORD word;
    BYTE bytes[2];
    struct
    {
        BYTE low;
        BYTE high;
    } byte;
    struct
    {
        unsigned  bit0:1;
        unsigned  bit1:1;
        unsigned  bit2:1;
        unsigned  bit3:1;
        unsigned  bit4:1;
        unsigned  bit5:1;
        unsigned  bit6:1;
        unsigned  bit7:1;
        unsigned  bit8:1;
        unsigned  bit9:1;
        unsigned  bit10:1;
        unsigned  bit11:1;
        unsigned  bit12:1;
        unsigned  bit13:1;
        unsigned  bit14:1;
        unsigned  bit15:1;
    } bits;
} WORD_BYTES;
typedef union _DWORD_BYTE
{
    DWORD dword;
	WORD words[2];
    BYTE bytes[4];
    struct
    {
        WORD low;
        WORD high;
    } word;
    struct
    {
        BYTE LB;
        BYTE HB;
        BYTE UB;
        BYTE MB;
    } byte;
    struct
    {
        unsigned  bit0:1;
        unsigned  bit1:1;
        unsigned  bit2:1;
        unsigned  bit3:1;
        unsigned  bit4:1;
        unsigned  bit5:1;
        unsigned  bit6:1;
        unsigned  bit7:1;
        unsigned  bit8:1;
        unsigned  bit9:1;
        unsigned  bit10:1;
        unsigned  bit11:1;
        unsigned  bit12:1;
        unsigned  bit13:1;
        unsigned  bit14:1;
        unsigned  bit15:1;
        unsigned  bit16:1;
        unsigned  bit17:1;
        unsigned  bit18:1;
        unsigned  bit19:1;
        unsigned  bit20:1;
        unsigned  bit21:1;
        unsigned  bit22:1;
        unsigned  bit23:1;
        unsigned  bit24:1;
        unsigned  bit25:1;
        unsigned  bit26:1;
        unsigned  bit27:1;
        unsigned  bit28:1;
        unsigned  bit29:1;
        unsigned  bit30:1;
        unsigned  bit31:1;
    } bits;
} DWORD_BYTES;

typedef union _PARAMETER
{

	struct
	{

		u16 K1_HCHO;
		u16 K2_HCHO;
		u16 A_HCHO;
		u16 K1_VOC;
		u16 K2_VOC;
		u16 A_VOC;
		u16 K1_PM;
		u16 K2_PM;
		u16 A_PM;
		u16 Ref_PM;
		u16 Version;
	}para;
	u8  pB[22];
	u16 pW[11];
} PARAMETER;


typedef enum {
    FLASH_MEMTYPE_PROG      = (uint8_t)0xFD, /*!< Program memory */
    FLASH_MEMTYPE_DATA      = (uint8_t)0xF7  /*!< Data EEPROM memory */
} FLASH_MemType_TypeDef;


#define D_zlx_pro_max	18

/**********************************************************************************
数据结构
 */
//__packed typedef struct _ts_096_dat_pro_               //
/*
typedef struct            
{ //D_zlx_pro_max byte
	volatile u32 frame;  //数据帧号
	volatile DWORD_BYTES time;   //数据时标
	volatile BYTE num;  //个数
	volatile BYTE d[D_zlx_pro_max-9];
}_ts_pranus_dat_pro_;
*/
typedef struct            
{ //D_zlx_pro_max byte
	volatile DWORD_BYTES time;   //数据时标
	volatile BYTE d[D_zlx_pro_max-4];
}_ts_pranus_dat_pro_;
/**********************************************************************************
数据结构*/
/*
typedef struct            
{ //D_zlx_pro_max byte
	volatile u16 PM_V_30s;  //PM30s滤波值
	volatile u16 HCHO_V_5s;   //甲醛5s滤波值
	volatile u16 VOC_V_5s;   //VOC1s滤波值
	volatile u16 Temp_V;  //温度值
	volatile u16 Humi_V;  //湿度值
	volatile u16 AQI;  //湿度值	
}_ts_pranus_MP_pro_;
*/
typedef struct            
{ //D_zlx_pro_max byte
	volatile u8 Temp_V;  //温度值
	volatile u8 Humi_V;  //湿度值
	volatile u16 PM_V_30s;  //PM30s滤波值
	volatile u16 VOC_V_5s;   //VOC1s滤波值
	volatile u16 HCHO_V_5s;   //甲醛5s滤波值
	volatile u16 CO2_V_5s;   //二氧化碳5s滤波值
	volatile u16 AQI;   //保留
	volatile u16 reserved2;   //保留
	//volatile u16 AQI;  //湿度值	
}_ts_pranus_MP_pro_;
/**********************************************************************************
 * 指令加数据结构
 */
//__packed typedef struct _ts_096_dat_pro_               //
/*typedef struct                
{ //D_zlx_pro_max byte
	volatile BYTE  FIlter1;  
	volatile BYTE  FIlter2;
	volatile BYTE  add;
	volatile WORD  len;
	volatile WORD  ocr;
	volatile BYTE  d[D_zlx_pro_max];
} _ts_pranus_pro_;
*/

typedef struct                
{ //D_zlx_pro_max byte
	volatile BYTE  FIlter1;  
	volatile BYTE  FIlter2;
	volatile BYTE  Fac_N;
	volatile BYTE  Dev_Type;
	volatile BYTE  Dev_N;
	volatile BYTE  Alarm_N;
	volatile BYTE  d[D_zlx_pro_max];
	volatile BYTE  crc;
} _ts_pranus_pro_;

#endif /* MYSTRUCT_H_ */
