/**
  ******************************************************************************
  * @file    TIM_Time_Base/stm32f0xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    11-October-2013
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
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
#include "stm32f0xx_it.h"
#include "userBSP.h"

/** @addtogroup STM32F0308_Discovery_Peripheral_Examples
  * @{
  */

/** @addtogroup TIM_Time_Base
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern __IO uint16_t CCR3_Val;
extern __IO uint16_t CCR4_Val;
uint16_t capture = 0;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0x8.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles TIM3 global interrupt request.
  * @param  None
  * @retval None
  */
void TIM3_IRQHandler(void)
{
  
  if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)    //1 ms  定时 
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
     
      tim3_it_ms_pro();
    //BSP_LEDToggle(LED4);
   
  }
  else if (TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET)
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);

    /* LED1 toggling with frequency = 73.24 Hz */
    /*STM_EVAL_LEDToggle(LED1);
	capture = TIM_GetCapture1(TIM3);
    TIM_SetCompare1(TIM3, capture + CCR1_Val);*/
  }
  else if (TIM_GetITStatus(TIM3, TIM_IT_CC2) != RESET)
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC2);

    /* LED2 toggling with frequency = 109.8 Hz */
    /*STM_EVAL_LEDToggle(LED2);
    capture = TIM_GetCapture2(TIM3);
    TIM_SetCompare2(TIM3, capture + CCR2_Val);*/
  }
  else if (TIM_GetITStatus(TIM3, TIM_IT_CC3) != RESET)
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC3);

    /* LED3 toggling with frequency = 219.7 Hz */
    //STM_EVAL_LEDToggle(LED3);
    //STM_EVAL_LEDOff(LED3);
    /*capture = TIM_GetCapture3(TIM3);
    TIM_SetCompare3(TIM3, capture + CCR3_Val);*/
  }
  else
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC4);

    /* LED4 toggling with frequency = 439.4 Hz */
    BSP_LEDToggle(LED3);
    //STM_EVAL_LEDOn(LED3);
    capture = TIM_GetCapture4(TIM3);
    TIM_SetCompare4(TIM3, capture + CCR3_Val);
    if(capture >65534)TIM_SetCompare4(TIM3,  CCR3_Val);
  }
  
}

void USART1_IRQHandler(void)
{
  /*uint8_t a;
	a = USART_ReceiveData(USART1);
	//USART_OUT(USART1, char *Data,uint16_t Len)
        BHKS_SerialPutChar(USART1,a);*/
  //unsigned int i;
  //unsigned char bInChar[1]={0};
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {	
     
    ///* Read one byte from the receive data register 
	//TIM_Cmd(TIM3,DISABLE);
	USART_ClearITPendingBit(USART1,USART_IT_RXNE);
    //bInChar[0] = USART_ReceiveData(USART1);
	//RxBuffer8[RxCounter1++] = bInChar[0];                //读取字符Read the char	
    if(UART_data_len < RXBUFSIZE)                        //测缓冲区满否 Check if buffer full
    {
        //uCmdRspFrame.uCmdRspBuf[UART_data_len] = bInChar[0];        //Enqueue the character
        uCmdRspFrame.uCmdRspBuf[UART_data_len] =USART_ReceiveData(USART1);        //Enqueue the character
        UART_data_len++;
        recv_byte_con = 0;
    }
   // TIM_SetCounter(TIM3,0);   //复位计数器
    //TIM_Cmd(TIM3,ENABLE);                                     //开始计时 1ms之内不能再次进入uart接收中断，则read_flag 置位，一段数据接收完成
  }
  if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
  {   
   
 //   USART_SendData(USART1, TxBuffer1[TxCounter1++]);

  //  if(TxCounter1 == NbrOfDataToTransfer1)
  //  {
     
      USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
  //  }     
  }		 
}

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
