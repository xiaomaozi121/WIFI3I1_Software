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

//volatile uint8_t      read_flag = 0;			//���ڽ���WIFI���ݱ�־λ
//volatile uint16_t UART_data_len = 0;            //���ڽ��ճ��� 
char DEV_ID[23] = "JY3I1HHT01V201411201B3C";    //�豸id
char SOFT_VER[16] = "JY3I1HHT20141120";
uint16_t data_len = 0;
wifi_uCmdRsp	uCmdRspFrame;
char   TCP_server_socket_num;	     //TCPS ͨ��socket//uint8
uint8   retval;					   //����ִ�з���ֵ
uint8 recv_byte_con;
W_CMD_RE_OK_ wifi_cmd_recv_ok_flg;    //������Ӧ�а���+ok ��ʾ����������Ӧ
_WIFI_WSLK_Resp_   wifi_WSLK_Response; 
_WIFI_GET_SER_IP_Resp_  wifi_NETP_Response;
_ON_OFF_VAL_  wifi_tcponoff_flg = OFF;  //TCP���ӽ����Ͽ���־
uint16 dat_send_SEC_con = 0;    //���ʱ
uint16 m_sec_con = 0;     //���뼼��
uint16 Recv_Jchar_numb = 0;        //tcp��������ʱ��socket�յ������� ���ַ�����
uint16 Soft_upd_datnumb = 0;      //�̼�����ʱ���յ������ݳ���
 
uint16  cmd_send = CMD_Null;                //cmd_send ����������cmd��ֵ
uint16  cmd_recv = CMD_Null;                //cmd_send ����������cmd��ֵ
uint16  status_recv = Test;                 //���������е�statusֵ

_ALLPARAM_STRUCT_ data_allparam_buf;
_TIME_STRUCT_  Time_recv_buf,Time_local_buf;
_HCHO_STRUCT_  *HCHO_param_buf;
_PM25_STRUCT_  *PM25_param_buf;
char          *Temp_buf;
char          *Humi_buf;


_TIME_STRUCT_    time_send;                       //�������ݰ��е� time
_HCHO_STRUCT_    hcho_send;                      //�������ݰ��е� hcho����
_PM25_STRUCT_    pm25_send;                      //�������ݰ��е�pm25����
uint8 temp_value;
uint8 humi_value;

uint8 dev_cal_flg = 0;    //У׼ģʽ��־
uint8 upd_soft_flg = 0;   //����ģʽ��־
uint8 data_resend_flg = 0; //�ط����ݰ���־
uint8 recv_en_flg    = 1;   //��Ҫ����ack ��־   0��ʾ������ 1��ʾ����

uint8 wifi_rld_off_flg = 0;  //wifiģ��smartlink ������������Ҫ���½���atָ���־
uint8 at_re_in_flg = 0;   //wifiģ��smartlink ������������Ҫ���½���atָ���־

_CSTATUS_CODE_    status_send = STATUS_Null;          //status_send ���������� status��ֵ

_UPLOAD_DAT_PRINTER_   json_recv_printer;
_UPLOAD_DAT_PRINTER_   Rsp_Cont_Pointer;  //����ʶ���յ���json�ļ�����

  

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
  WIFI_EN_ON();    //WIFIģ��ߵ�ƽʹ��
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
  //TCP_server_socket_num ;	     //TCPS ͨ��socket//uint8
  retval =0;					   //����ִ�з���ֵ
  recv_byte_con = 0xff;
  wifi_tcponoff_flg = OFF;  //TCP���ӽ����Ͽ���־
  dat_send_SEC_con = 0;

  cmd_send = CMD_Null;                //cmd_send ����������cmd��ֵ
  status_send = Test;          //status_send ���������� status��ֵ
  
  time_send.frame.zone = 8;                       //�������ݰ��е� time
  time_send.frame.year = 2014;
  time_send.frame.mon = 12;
  time_send.frame.day = 12;
  time_send.frame.hour = 11;
  time_send.frame.min = 45;
  time_send.frame.sec = 23;
  
  hcho_send.frame.k1 = 47;                      //�������ݰ��е� hcho����
  hcho_send.frame.k2 = 65;
  hcho_send.frame.a  = 40;
  hcho_send.frame.ad_v = 560;
  hcho_send.frame.value = 40;
  
  pm25_send.frame.k1 = 9;                      //�������ݰ��е�pm25����
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
