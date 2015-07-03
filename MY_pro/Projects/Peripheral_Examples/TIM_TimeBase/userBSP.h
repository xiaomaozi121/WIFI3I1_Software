#include "stm32f0xx.h"
//#include "stm32f0308_discovery.h"
#include "stm32f0xx_usart.h"
//#include "USART.h"
//#include "delay.h"
#include "wifi_global.h"
#include "wifi_config.h"
#include "wifi_uart_api.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define socket_test


#define tim_dub
/** @defgroup STM32F0308_DISCOVERY_LOW_LEVEL_Exported_Types
  * @{
  */
typedef enum 
{
  LED3 = 0,
  LED4 = 1
} Led_TypeDef;

typedef enum 
{
  BUTTON_USER = 0,
} Button_TypeDef;

typedef enum 
{  
  BUTTON_MODE_GPIO = 0,
  BUTTON_MODE_EXTI = 1
} ButtonMode_TypeDef;
  
/**
  * @}
  */ 

/** @defgroup STM32F0308_DISCOVERY_LOW_LEVEL_Exported_Constants
  * @{
  */ 

/** @addtogroup STM32F0308_DISCOVERY_LOW_LEVEL_LED
  * @{
  */
#define LEDn                             2
  
#define LED3_PIN                         GPIO_Pin_0//GPIO_Pin_12//GPIO_Pin_9
#define LED3_GPIO_PORT                   GPIOF//GPIOA//GPIOC
#define LED3_GPIO_CLK                    RCC_AHBPeriph_GPIOF
  
#define LED4_PIN                         GPIO_Pin_1//GPIO_Pin_7//GPIO_Pin_8
#define LED4_GPIO_PORT                   GPIOF//GPIOA//GPIOC
#define LED4_GPIO_CLK                    RCC_AHBPeriph_GPIOF

/**
  * @}
  */ 

/** @addtogroup SSTM32F0308_DISCOVERY_LOW_LEVEL_BUTTON
  * @{
  */  
#define BUTTONn                          1

/**
 * @brief USER push-button
 */
#define USER_BUTTON_PIN                GPIO_Pin_13
#define USER_BUTTON_GPIO_PORT          GPIOC
#define USER_BUTTON_GPIO_CLK           RCC_AHBPeriph_GPIOC
#define USER_BUTTON_EXTI_LINE          EXTI_Line0
#define USER_BUTTON_EXTI_PORT_SOURCE   EXTI_PortSourceGPIOA
#define USER_BUTTON_EXTI_PIN_SOURCE    EXTI_PinSource0
#define USER_BUTTON_EXTI_IRQn          EXTI0_1_IRQn 

/**
  * @}
  */ 
  
    
/** @defgroup STM32F0308_DISCOVERY_LOW_LEVEL_Exported_Macros
  * @{
  */  
/**
  * @}
  */ 

/** @defgroup STM32F0308_DISCOVERY_LOW_LEVEL_Exported_Functions
  * @{
  */
void BSP_LEDInit(Led_TypeDef Led);
void BSP_LEDOn(Led_TypeDef Led);
void BSP_LEDOff(Led_TypeDef Led);
void BSP_LEDToggle(Led_TypeDef Led);
void BSP_PBInit(Button_TypeDef Button, ButtonMode_TypeDef Button_Mode);
uint32_t BSP_PBGetState(Button_TypeDef Button);


#define WIFI_EN_PIN                         GPIO_Pin_14//GPIO_Pin_7//GPIO_Pin_8        //WIFI wifi模块电源使能
#define WIFI_EN_GPIO_PORT                   GPIOB//GPIOA//GPIOC
#define WIFI_EN_GPIO_CLK                    RCC_AHBPeriph_GPIOB

#define WIFI_RESET_PIN                         GPIO_Pin_1//GPIO_Pin_7//GPIO_Pin_8      //wifi模块复位
#define WIFI_RESET_GPIO_PORT                   GPIOB//GPIOA//GPIOC
#define WIFI_RESET_GPIO_CLK                    RCC_AHBPeriph_GPIOB

#define WIFI_RELD_PIN                         GPIO_Pin_8//GPIO_Pin_7//GPIO_Pin_8      //wifi模块复位
#define WIFI_RELD_GPIO_PORT                   GPIOA//GPIOA//GPIOC
#define WIFI_RELD_GPIO_CLK                    RCC_AHBPeriph_GPIOA

void WIFI_EN_init(void);
void WIFI_RESET_init(void);
void WIFI_RELD_init(void);
void WIFI_EN_ON(void);    //WIFI模块高电平使能
void WIFI_EN_OFF(void);   //低电平掉电
void WIFI_RESET_LOW(void);    //
void WIFI_RESET_HAIGH(void);   //



#define  USART1PA9_10

#ifdef  USART1PA3_4											
	#define USART1_TX_PIN                 GPIO_Pin_2
	#define USART1_TX_PORT           			GPIOA
	#define USART1_TX_GPIO_CLK            RCC_AHBPeriph_GPIOA
	#define USART1_TX_SOURCE              GPIO_PinSource2
	#define USART1_TX_AF                  GPIO_AF_1

	#define USART1_RX_PIN                 GPIO_Pin_3
	#define USART1_RX_PORT           			GPIOA
	#define USART1_RX_GPIO_CLK            RCC_AHBPeriph_GPIOA
	#define USART1_RX_SOURCE              GPIO_PinSource3
	#define USART1_RX_AF                  GPIO_AF_1
#endif
#ifdef  USART1PA9_10 											
	#define USART1_TX_PIN                 GPIO_Pin_9
	#define USART1_TX_PORT           			GPIOA
	#define USART1_TX_GPIO_CLK            RCC_AHBPeriph_GPIOA
	#define USART1_TX_SOURCE              GPIO_PinSource9
	#define USART1_TX_AF                  GPIO_AF_1

	#define USART1_RX_PIN                 GPIO_Pin_10
	#define USART1_RX_PORT           			GPIOA
	#define USART1_RX_GPIO_CLK            RCC_AHBPeriph_GPIOA
	#define USART1_RX_SOURCE              GPIO_PinSource10
	#define USART1_RX_AF                  GPIO_AF_1
#endif
#ifdef  USART1PB6_7 
	#define USART1_TX_PIN                 GPIO_Pin_6
	#define USART1_TX_PORT           			GPIOB
	#define USART1_TX_GPIO_CLK            RCC_AHBPeriph_GPIOB
	#define USART1_TX_SOURCE              GPIO_PinSource6
	#define USART1_TX_AF                  GPIO_AF_0

	#define USART1_RX_PIN                 GPIO_Pin_7
	#define USART1_RX_PORT           			GPIOB
	#define USART1_RX_GPIO_CLK            RCC_AHBPeriph_GPIOB
	#define USART1_RX_SOURCE              GPIO_PinSource7
	#define USART1_RX_AF                  GPIO_AF_0
#endif

extern uint8   wifi_DEST_IP_ADDRESS[4];// {192,168,1,102}; 
extern uint16  wifi_DEST_PORT;
extern uint16  wifi_LOCAL_PORT;

extern uint32  wifi_Timer1;
extern int8   wifi_server_ip[15];

extern void BHKS_Serial_PutString( USART_TypeDef* USARTx,uint8_t *s);
extern void BHKS_SerialPutChar(USART_TypeDef* USARTx,uint8_t c);
/*
extern uint8_t BHKS_ReveOneByte(USART_TypeDef* USARTx,uint8_t key);
extern void BHKS_SenduInt16_tString(USART_TypeDef* USARTx,uint16_t nInt);
extern void BHKS_SendFloatString(USART_TypeDef* USARTx,float nfloat);

*/
 void USART_INIT(void);
 void USART_PIN_FL(void);
 uint8_t USART_OUT(USART_TypeDef* USARTx, char *Data,uint16_t Len);
 void USART2_OUT(USART_TypeDef* USARTx, uint8_t *Data,uint16_t Len);
 void USART_RxTx(void);



 
extern uint8_t rec_f;
extern uint8_t RxBuffer8[14];
extern uint8_t RxBuffer9[14];

extern uint8_t RxBufferLs[10];
extern uint8_t TxBufferLs[10]; 

extern uint8_t MlBufferRet[14];
extern uint8_t McBufferRet[14];
extern uint8_t PirBufferRet[14];

extern __IO uint8_t TxCounter1;
extern __IO uint8_t RxCounter1 ; 
extern uint8_t NbrOfDataToHeart ;



/************************************************************************/
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


/*****************************************************************************/

#define DAT_SEND_PERIOD    20

extern char DEV_ID[23];
extern char SOFT_VER[16];
extern uint16_t g_ms_con;
extern uint8 recv_byte_con;
extern W_CMD_RE_OK_       wifi_cmd_recv_ok_flg;    //命令响应中包含+ok 表示命令正常响应
extern _WIFI_WSLK_Resp_   wifi_WSLK_Response; 
extern _WIFI_GET_SER_IP_Resp_  wifi_NETP_Response;
extern _ON_OFF_VAL_  wifi_tcponoff_flg ;  //TCP连接建立断开标志

extern uint16 dat_send_SEC_con ;    //数据发送间隔计数器
extern uint16 m_sec_con ;     //毫秒技术
extern uint16 Recv_Jchar_numb ;
extern uint16 Soft_upd_datnumb;      //固件更新时，收到的数据长度

extern uint16  cmd_send;                //cmd_send 发送命令中cmd的值
extern uint16  cmd_recv;                //cmd_send 接收命令中cmd的值
extern uint16  status_recv;                 //接收数据中的status值

extern _ALLPARAM_STRUCT_ data_allparam_buf;
extern _TIME_STRUCT_  Time_recv_buf,Time_local_buf;
extern _HCHO_STRUCT_  *HCHO_param_buf;
extern _PM25_STRUCT_  *PM25_param_buf;
extern char          *Temp_buf;
extern char          *Humi_buf;


extern _CSTATUS_CODE_    status_send;          //status_send 发送命令中 status的值
extern _TIME_STRUCT_    time_send;                       //发送数据包中的 time
extern _HCHO_STRUCT_    hcho_send;                      //发送数据包中的 hcho参数
extern _PM25_STRUCT_    pm25_send;                      //发送数据包中的pm25参数
extern uint8 temp_value;
extern uint8 humi_value;

extern uint8 dev_cal_flg ;    //校准模式标志
extern uint8 upd_soft_flg ;   //升级模式标志
extern uint8 data_resend_flg; //重发数据包标志
extern uint8 recv_en_flg ;   //需要接收ack 标志   0表示不接受 1表示接收


extern uint8 wifi_rld_off_flg;  //wifi模块smartlink 后重新联网需要重新进入at指令标志
extern uint8 at_re_in_flg ;   //wifi模块smartlink 后重新联网需要重新进入at指令标志

extern _UPLOAD_DAT_PRINTER_   json_recv_printer;
extern _UPLOAD_DAT_PRINTER_   Rsp_Cont_Pointer;  //用于识别收到的json文件数据
//extern _ALLPARAM_STRUCT_      all_param_buf;  //用于存放 可计算的测量参数

extern char char_test[16];
/* Private function prototypes -----------------------------------------------*/
void glob_dat_init(void);
void TIM_Config(void);
void tim3_it_ms_pro(void);

void USART_INIT();
uint8_t USART_OUT(USART_TypeDef* USARTx, char *Data,uint16_t Len);
void USART2_OUT(USART_TypeDef* USARTx, uint8_t *Data,uint16_t Len);
void USART_RxTx(void);
void BHKS_Serial_PutString( USART_TypeDef* USARTx,uint8_t *s);
void BHKS_SerialPutChar(USART_TypeDef* USARTx,uint8_t c);
//void Reset_Target(void);
void WIFI_Reset_Target(void);

void delay_init(u8 SYSCLK);
void delay_ms(u16 nms);
void delay_us(u32 nus);
void delay_s(u16 ns);
