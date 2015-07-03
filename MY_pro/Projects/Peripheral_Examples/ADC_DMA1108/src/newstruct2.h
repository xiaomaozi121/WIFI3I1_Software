/*
 * mystruct.h
 *
 *  Created on: 2013-7-3
 *      Author: Administrator
 */

#ifndef NEWSTRUCT2_H_
#define NEWSTRUCT2_H_
/*********************************************************************************
 * �������������ͽӿ�
 */
typedef unsigned char     BYTE;	    // 8-bit
typedef unsigned int	  WORD;		// 16-bit
typedef unsigned long  	  DWORD;    // 32-bit

/**********************************************************************************
 * ϵͳȫ������־
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
//------------------Ӧ�ú�������------------------------------��
/**********************************************************************************
 * ϵͳȫ������־
 */

/**********************************************************************************
 * ��̫��ȫ������־
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
 * ͨ����������
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
���ݽṹ
 */
//__packed typedef struct _ts_096_dat_pro_               //
/*
typedef struct            
{ //D_zlx_pro_max byte
	volatile u32 frame;  //����֡��
	volatile DWORD_BYTES time;   //����ʱ��
	volatile BYTE num;  //����
	volatile BYTE d[D_zlx_pro_max-9];
}_ts_pranus_dat_pro_;
*/
typedef struct            
{ //D_zlx_pro_max byte
	volatile DWORD_BYTES time;   //����ʱ��
	volatile BYTE d[D_zlx_pro_max-4];
}_ts_pranus_dat_pro_;
/**********************************************************************************
���ݽṹ*/
/*
typedef struct            
{ //D_zlx_pro_max byte
	volatile u16 PM_V_30s;  //PM30s�˲�ֵ
	volatile u16 HCHO_V_5s;   //��ȩ5s�˲�ֵ
	volatile u16 VOC_V_5s;   //VOC1s�˲�ֵ
	volatile u16 Temp_V;  //�¶�ֵ
	volatile u16 Humi_V;  //ʪ��ֵ
	volatile u16 AQI;  //ʪ��ֵ	
}_ts_pranus_MP_pro_;
*/
typedef struct            
{ //D_zlx_pro_max byte
	volatile u8 Temp_V;  //�¶�ֵ
	volatile u8 Humi_V;  //ʪ��ֵ
	volatile u16 PM_V_30s;  //PM30s�˲�ֵ
	volatile u16 VOC_V_5s;   //VOC1s�˲�ֵ
	volatile u16 HCHO_V_5s;   //��ȩ5s�˲�ֵ
	volatile u16 CO2_V_5s;   //������̼5s�˲�ֵ
	volatile u16 AQI;   //����
	volatile u16 reserved2;   //����
	//volatile u16 AQI;  //ʪ��ֵ	
}_ts_pranus_MP_pro_;
/**********************************************************************************
 * ָ������ݽṹ
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
