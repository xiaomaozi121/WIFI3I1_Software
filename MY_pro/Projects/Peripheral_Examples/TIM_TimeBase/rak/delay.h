#ifndef __DELAY_H
#define __DELAY_H 			   
#include "stm32f0xx.h"
#include "main.h"

void delay_init(u8 SYSCLK);
void delay_ms(u16 nms);
void delay_us(u32 nus);
void Delay(vu32 nCount);
void delay_s(u16 ns);
#endif





























