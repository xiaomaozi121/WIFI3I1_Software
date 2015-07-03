/*
 * mystruct.h
 *
 *  Created on: 2013-7-3
 *      Author: Administrator
 */

#ifndef MYSTRUCT_H_
#define MYSTRUCT_H_
/*********************************************************************************
 * 编译器数据类型接口
 */
typedef unsigned char     BYTE;	    // 8-bit
typedef unsigned short	  WORD;		// 16-bit
typedef unsigned int  	  DWORD;    // 32-bit




//#define   BitStatus FlagStatus;
//#define   BitAction FlagStatus;//,wifi_nRLD_FLG;



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



#endif /* MYSTRUCT_H_ */
