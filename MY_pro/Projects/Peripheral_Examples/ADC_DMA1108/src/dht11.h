/*****************************************************************************/
/*****************************************************************************/
//�ļ������뱣��Ϊdht111.h
#ifndef __DHT11_H__
#define __HDT11_H__
//�趨��־(static unsigned char status)�ĺ�ֵ
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
//������ֽ����ݵ�����
static unsigned char value_array[SIZE];
/*�����������ļ�������ʪ��ֵ,ʵ�����¶ȵ�������10 ��
��dht11 ���ص��¶���26,��temp_value = 260, ʪ��ͬ��*/
extern int temp_value, humi_value;
//�����ķ���ֵ��ʾ��ȡ�����Ƿ�ɹ� OK ��ʾ�ɹ� ERROR ��ʾʧ��
 unsigned char DHT11_ReadTempAndHumi(void);

#endif
/*****************************************************************************/
/*****************************************************************************/