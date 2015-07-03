/**
  ******************************************************************************
  * @file    TIM_Time_Base/main.c 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    11-October-2013
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
//#include "stm32f0xx.h"
//#include "stm32f0308_discovery.h"
#include "userBSP.h"


/** @addtogroup STM32F0308_Discovery_Peripheral_Examples
  * @{
  */

/** @addtogroup TIM_Time_Base
  * @{
  */
char char_test[16]= "123456789abcdern";

//uint8_t rec_f;
uint8_t RxBuffer8[14] = {0};
uint8_t RxBuffer9[14] = {0};
uint8_t RxBufferLs[10] = {0};
uint8_t TxBufferLs[10] = {0};


__IO uint8_t TxCounter1 = 0x00;
__IO uint8_t RxCounter1 = 0x00; 
uint8_t NbrOfDataToHeart = 0x04;

//volatile uint8_t      read_flag = 0;			//串口接收WIFI数据标志位
//volatile uint16_t UART_data_len = 0;            //串口接收长度 
char DEV_ID[23] = "JY3I1HHT01V201411201B3C";    //设备id
char SOFT_VER[16] = "JY3I1HHT20141120";
uint16_t data_len = 0;
wifi_uCmdRsp	uCmdRspFrame;
char   TCP_server_socket_num;	     //TCPS 通信socket//uint8
uint8   retval;					   //函数执行返回值
uint8 recv_byte_con;
W_CMD_RE_OK_ wifi_cmd_recv_ok_flg;    //命令响应中包含+ok 表示命令正常响应
_WIFI_WSLK_Resp_   wifi_WSLK_Response; 
_WIFI_GET_SER_IP_Resp_  wifi_NETP_Response;
_ON_OFF_VAL_  wifi_tcponoff_flg = OFF;  //TCP连接建立断开标志
uint16 dat_send_SEC_con = 0;    //秒计时
uint16 m_sec_con = 0;     //毫秒技术
uint16 Recv_Jchar_numb = 0;        //tcp接收数据时，socket收到的数据 的字符数量
uint16 Soft_upd_datnumb = 0;      //固件更新时，收到的数据长度
 
uint16  cmd_send = CMD_Null;                //cmd_send 发送命令中cmd的值
uint16  cmd_recv = CMD_Null;                //cmd_send 发送命令中cmd的值
uint16  status_recv = Test;                 //接收数据中的status值

_ALLPARAM_STRUCT_ data_allparam_buf;
_TIME_STRUCT_  Time_recv_buf,Time_local_buf;
_HCHO_STRUCT_  *HCHO_param_buf;
_PM25_STRUCT_  *PM25_param_buf;
char          *Temp_buf;
char          *Humi_buf;


_TIME_STRUCT_    time_send;                       //发送数据包中的 time
_HCHO_STRUCT_    hcho_send;                      //发送数据包中的 hcho参数
_PM25_STRUCT_    pm25_send;                      //发送数据包中的pm25参数
uint8 temp_value;
uint8 humi_value;

uint8 dev_cal_flg = 0;    //校准模式标志
uint8 upd_soft_flg = 0;   //升级模式标志
uint8 data_resend_flg = 0; //重发数据包标志
uint8 recv_en_flg    = 1;   //需要接收ack 标志   0表示不接受 1表示接收

uint8 wifi_rld_off_flg = 0;  //wifi模块smartlink 后重新联网需要重新进入at指令标志
uint8 at_re_in_flg = 0;   //wifi模块smartlink 后重新联网需要重新进入at指令标志

_CSTATUS_CODE_    status_send = STATUS_Null;          //status_send 发送命令中 status的值

_UPLOAD_DAT_PRINTER_   json_recv_printer;
_UPLOAD_DAT_PRINTER_   Rsp_Cont_Pointer;  //用于识别收到的json文件数据

  

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f0xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f0xx.c file
     */

  /* TIM Configuration */
  recv_byte_con = 0xff;
  glob_dat_init();
  TIM_Config() ;
  USART_INIT();
  //USART_PIN_FL();
  delay_init(48);
  /* Initialize Leds mounted on STM32F030-Discovery */
  BSP_LEDInit(LED3);
  BSP_LEDInit(LED4);
  BSP_PBInit(BUTTON_USER,BUTTON_MODE_GPIO);
  BSP_LEDOff(LED3);
  BSP_LEDOff(LED4);
  WIFI_EN_init();
  WIFI_RESET_init();
  WIFI_RELD_init();
  WIFI_EN_ON();    //WIFI模块高电平使能
  delay_s(1);
  WIFI_Reset_Target();
  delay_s(5);

  /* Turn on LED3 and LED4 */
  //BSP_LEDOn(LED3);
  //BSP_LEDOn(LED4);
  //WIFI_MODULE_INIT();
  WIFI_MODULE_INIT();
  
  /* Infinite loop */
  while (1)
  {
    //USART_OUT(USART1,char_test,16);
    /*BSP_LEDToggle(LED3);
    delay_s(1);*/
    /*if(at_re_in_flg == 1)
    {
      at_re_in_flg = 0;
      delay_ms(800);
      WIFI_TSIN_AT();
      delay_ms(800);
    }*/
    wifi_dat_send();
  }
}

void glob_dat_init(void)
{
  data_len = 0;
  //wifi_uCmdRsp	uCmdRspFrame;
  //TCP_server_socket_num ;	     //TCPS 通信socket//uint8
  retval =0;					   //函数执行返回值
  recv_byte_con = 0xff;
  wifi_tcponoff_flg = OFF;  //TCP连接建立断开标志
  dat_send_SEC_con = 0;

  cmd_send = CMD_Null;                //cmd_send 发送命令中cmd的值
  status_send = Test;          //status_send 发送命令中 status的值
  
  time_send.frame.zone = 8;                       //发送数据包中的 time
  time_send.frame.year = 2014;
  time_send.frame.mon = 12;
  time_send.frame.day = 12;
  time_send.frame.hour = 11;
  time_send.frame.min = 45;
  time_send.frame.sec = 23;
  
  hcho_send.frame.k1 = 47;                      //发送数据包中的 hcho参数
  hcho_send.frame.k2 = 65;
  hcho_send.frame.a  = 40;
  hcho_send.frame.ad_v = 560;
  hcho_send.frame.value = 40;
  
  pm25_send.frame.k1 = 9;                      //发送数据包中的pm25参数
  pm25_send.frame.k2 = 6;
  pm25_send.frame.a = 707;
  pm25_send.frame.Ref = 600;
  pm25_send.frame.ad_v = 800;
  pm25_send.frame.value = 150;
  
  temp_value = 25;
  humi_value = 65;
  
  HCHO_param_buf = &(data_allparam_buf.frame.hcho_param);
  PM25_param_buf = &(data_allparam_buf.frame.pm25_param);
  Temp_buf = &(data_allparam_buf.frame.temp_param);
  Humi_buf = &(data_allparam_buf.frame.humi_param);
  
}




#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
