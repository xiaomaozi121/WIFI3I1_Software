//;****************************************************
//;Company :  WIFI WIRELESS
//;File Name : wifi_WIFI_DRIVER.c
//;Author :    Junhua
//;Create Data : 2014-03-15
//;Last Modified : 
//;Description : WIFI413 WIFI UART  DRIVER
//;Version : 1.0.1
//;****************************************************

//#include "BSP_Driver.h"
#include "userBSP.h"
//#include "delay.h"
//#include "date.h"

wifi_api wifi_strApi;



/* Set SOCKET CONFIG */
uint8   wifi_DEST_IP_ADDRESS[4]={192,168,1,124};// {192,168,1,102}; 
uint16  wifi_DEST_PORT=10106;
uint16  wifi_LOCAL_PORT=25000;

uint32  wifi_Timer1=0;
int8   wifi_server_ip[15]; 

//;***************************************************************
//;Description: WIFI_MODULE_INIT() 
//;input	  : void
//;Returns    : uint8_t
//;Notes      :	WIFI 对WIFI进行配置 执行出厂数据 或是Flash中的用户数据 
//;***************************************************************
uint8 WIFI_MODULE_INIT()
{
  //Wait for "Welcome to WIFI413"  Normal Boot
  //WIFI_Reset_Target();
  int16 wifi_cmd_rec_val;
  uint8 cmd_resend_con = 0;           //命令重复发送计数器
  delay_ms(500);
  WIFI_TSIN_AT();
  wifi_init_struct(&wifi_strApi);
  delay_ms(200);
  
  if(wifi_AP_STATION_MODE==0)
  {
    //扫描指定的ssid
    //wifi_RESET_TIMER1;	  wifi_ascii
    wifi_cmd_rec_val =  wifi_check_ssid_link();
    
    wifi_cmd_rec_val =  wifi_check_serIP();
    while(wifi_cmd_rec_val == OK_NONE_INFO)
    {
      wifi_cmd_rec_val = wifi_set_serip();
      wifi_cmd_rec_val =  wifi_check_serIP();
      cmd_resend_con++;
      if(cmd_resend_con > 5)
      {
        return 0;
      }
    }
    /*wifi_cmd_rec_val = wifi_reld_mudol();
    delay_s(5);
    WIFI_TSIN_AT();*/
    //wifi_cmd_rec_val =  wifi_check_TCPLK();
    if(wifi_WSLK_Response.contframe.ok_flg == WIFI_CONNECT)   //在wifi连接成立的前提下，检查ip连接是否连接
    {
      wifi_cmd_rec_val =  wifi_check_TCPLK();
      
    }
    wifi_cmd_rec_val = wifi_en_dis_tcplk(OFF);      //建立ip连接
    /*cmd_recv = Dev_Dat_Get;
    if(wifi_cmd_rec_val == OK_INFO)
    {
       wifi_cmd_rec_val = wifi_tcp_senddat();
    }
    if(wifi_cmd_rec_val == OK_INFO)
    {
       wifi_cmd_rec_val = wifi_tcp_recvdat();
    }
   */
  }
  return 0;

}

uint8 wifi_dat_send(void)
{
  int16 wifi_cmd_rec_val;
  uint8 cmd_resend_con = 0;            //命令重复发送计数器
  if(dat_send_SEC_con > DAT_SEND_PERIOD)
  {
    wifi_cmd_rec_val =  wifi_check_serIP();            //  检查 目标ip是否正确
    while(wifi_cmd_rec_val == OK_NONE_INFO)
    {
      wifi_cmd_rec_val = wifi_set_serip();
      delay_ms(20);
      wifi_cmd_rec_val =  wifi_check_serIP();
      cmd_resend_con++;
      if(cmd_resend_con > 5)
      {
        dat_send_SEC_con = 0;
        return 0;
      }
    }
    wifi_cmd_rec_val =  wifi_check_TCPLK();          // 检查  ip连接是否建立
     while(wifi_cmd_rec_val == OK_NONE_INFO)
    {
      wifi_cmd_rec_val = wifi_en_dis_tcplk(ON);      //建立ip连接
      delay_ms(20);
      wifi_cmd_rec_val = wifi_check_TCPLK();         //检查
      cmd_resend_con++;
      if(cmd_resend_con > 5)
      {
        dat_send_SEC_con = 0;
        return 0;
      }
    }
    cmd_recv = Dev_Dat_Get;
    recv_en_flg = 1;
    
    do
    {
      time_send = Time_local_buf;
      data_resend_flg = 0;
      wifi_tcp_senddat();   //发送数据
      if(recv_en_flg == 1)
      {
        wifi_tcp_recvdat();   //接收数据
        //Recv_CMD_Press(); 
        //Recv_CMD_reco();
        
        BHKS_cmd_status_pro();  //分析协议命令字 并准备数据
        //recv_en_flg = 0;
      }
      else     //recv_en_flg == 0   需要将标志改过来
      {
        recv_en_flg = 1;
      }
      
      
    }while(data_resend_flg == 1);  //命令重发
    
    wifi_cmd_rec_val = wifi_en_dis_tcplk(OFF);      //建立ip连接
    dat_send_SEC_con = 0;
  }
  
  return 1;
}



/*
uint8 wifi_dat_send_2()//备选方案框架
{
  do
  {
    switch (data_send_status)
    {
    case WSK_LK:   //查询wifi是否连接
      {
        break;
      }
    case IP_CHECK:  //查询ip信息是否正确
      {
        break;
      }
    case TCP_LK:  //查询tcp连接是否建立 建立
      {
        break;
      }
    case DATA_SEND:  //发送数据包
      {
        break;
      }
    case DATA_RECV:  //接收数据包
      {
        break;
      }
    case CMD_PRESS:  //处理协议交互
      {
        break;
      }
    }
    if(ask_con > 5)    //同一操作超过五次，表示错误，直接返回
    {
      return error;
    }
  }while(data_send_status == DAT_TRANS_DONE)
}
*/

void WIFI_TSIN_AT(void)  //进入AT模式
{
  u8 i;
  do
  {
    do
    {
		
      for(i=0;i<3;i++)              //发送+++
      {
        BHKS_SerialPutChar(USART1,'+');
      }
      read_flag == TRUE;
      recv_byte_con = 0;
      //while (UART2_GetFlagStatus(UART2_FLAG_RXNE) == RESET);/* 读取数据寄存器 */
      //c = UART2_ReceiveData8();
      //UART2_ClearFlag(UART2_FLAG_RXNE);
      while(read_flag == FALSE);
      read_flag = FALSE; 
    }while( uCmdRspFrame.uCmdRspBuf[0] != 'a');
  
     BHKS_SerialPutChar(USART1,'a');
     while(read_flag == FALSE);
     read_flag = FALSE;
  }while( strncmp((char *)uCmdRspFrame.uCmdRspBuf,"+ok",3) != 0);
  
}

void BHKS_cmd_status_pro(void)
{
  if(Recv_Jchar_numb == 0)
  {
    //data_resend_flg =1;  //如果接收到数据长度为0 即未接收到数据，则重新发送数据
    return;
  }
  Recv_CMD_reco();
  Recv_STATUS_reco();
  
  switch(cmd_recv)
  {
  case Dev_Dat_Get :
    {
      Recv_TIME_reco();
      cmd_send = cmd_recv;
      if(upd_soft_flg == 1)   //结束固件更新
      {
        status_send = Upd_Done;
        upd_soft_flg = 0;
        
        recv_en_flg = 0;   //下个一个循环不需要接收ack
        data_resend_flg = 1;                         //需要再发一次
        
      }
      else if(status_recv == Caling)  //保持校准        //不需要再发一次
      {
        status_send = Cal_Done;
        dev_cal_flg = 0;
      }
      else
      {
        status_send = Test;
      }
      
      break;
    }
  case Dev_Cal_Start :                                  //不需要再发一次
    {
      Recv_TIME_reco();
      dev_cal_flg = 1;
      cmd_send = cmd_recv;
      status_send = Caling; 
      break;
    }
  case Dev_Dat_Rget :                                //
    {
      Recv_TIME_reco();
      data_resend_flg = 1;                           //需要再发一次     需要接收ack
      cmd_send = cmd_recv;
      status_send = Test;
      break;
    }
  case Get_Dev_Para :
    {
      Recv_TIME_reco();
      data_resend_flg = 1;                           //需要再发一次 
      //recv_en_flg = 0;                              //下个一个循环不需要接收ack   服务器段可能会有ack暂时需要接收 若没有，接收到数据长度为0 不做处理
      cmd_send = cmd_recv;
      status_send = Get_Done;
      break;
    }
  case Set_Dev_Para :
    {
      Recv_TIME_reco();
      Recv_HCHO_reco();
      Recv_PM25_reco();
      data_resend_flg = 1;                           //需要再发一次 
      recv_en_flg = 0;                              //下个一个循环不需要接收ack
      cmd_send = cmd_recv;
      status_send = Set_Done;
      break;
    }
  case Upd_Dev_Soft :
    {
      Recv_UPD_reco();
      upd_soft_flg = 1;
      data_resend_flg = 1;                          //需要再发一次    需要接收ack
      cmd_send = cmd_recv;
      status_send = Updataing;
      break;
    }
  default :
    {
      
    }
  }
}
