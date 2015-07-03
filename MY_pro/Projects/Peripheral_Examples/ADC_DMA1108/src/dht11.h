/*****************************************************************************/
/*****************************************************************************/
//文件名必须保存为dht111.h
#ifndef __DHT11_H__
#define __HDT11_H__
//设定标志(static unsigned char status)的宏值
#include "includes.h"
#define OK 1
#define ERROR 0



//#ifdef DHT11
#define NUMBER 50
#define SIZE 5
//#endif
/*
#ifdef DHT22
#define NUMBER 50
#define SIZE 5
#endif
*/
static unsigned char status;
//存放五字节数据的数组
static unsigned char value_array[SIZE];
/*可在其他的文件引用温湿度值,实际是温度的整数的10 倍
如dht11 读回的温度是26,则temp_value = 260, 湿度同理*/
extern int temp_value, humi_value;
//函数的返回值表示读取数据是否成功 OK 表示成功 ERROR 表示失败
 unsigned char DHT11_ReadTempAndHumi(void);

#endif
/*****************************************************************************/
/*****************************************************************************/