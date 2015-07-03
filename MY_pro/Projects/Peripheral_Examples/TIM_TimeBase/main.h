#include "stm32f0xx.h"
#include "stm32f0308_discovery.h"
#include "man_tim_pro.h"
#include "USART.h"
//#include "delay.h"
//#include "wifi_global.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef const uint32_t uc32;  /*!< Read Only */
typedef const uint16_t uc16;  /*!< Read Only */
typedef const uint8_t uc8;   /*!< Read Only */

typedef __IO uint32_t  vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;

typedef __I uint32_t vuc32;  /*!< Read Only */
typedef __I uint16_t vuc16;  /*!< Read Only */
typedef __I uint8_t vuc8;   /*!< Read Only */


extern uint16_t g_ms_con;