//;****************************************************
//;Company :  BHKS_wifi_demo
//;File Name : wifi_tcp_send_recv
//;Author :    jy_t
//;Create Data : 2014-12-11
//;Last Modified : 
//;Description : bhks userwifi WIFI UART  DRIVER
//;Version : 1.0.1
//;****************************************************
//#include "BSP_Driver.h"
#include "userBSP.h"
#include "wifi_global.h"

/*=============================================================================*/
/**
 * @fn           int16 wifi_set_pwrmode(void)
 * @brief        UART 
 * @param[in]    powerMode
 * @param[out]   none
 * @return       errCode
 *               -1 = Module  busy / Timeout
 *               0  = SUCCESS
 * @section description  
 * 
 */
/*=============================================================================*/
uint16 wifi_json_send_perss(void)
{
  hcho_send.frame.value = Time_local_buf.frame.sec+3;   //假数据
  pm25_send.frame.value = Time_local_buf.frame.sec+7;
  temp_value   =   Time_local_buf.frame.sec-10;
  humi_value   =   Time_local_buf.frame.sec-5;
  
  switch(cmd_recv)
  {
  case Dev_Dat_Get :
    {
      Json_upload_pro();     
      break;
    }
  case Dev_Cal_Start :                                  //不需要再发一次
    {
      Json_upload_pro();
      break;
    }
  case Dev_Dat_Rget :                                //
    {
      Json_upload_pro();
      break;
    }
  case Get_Dev_Para :
    {
      Json_paraset_pro();
      //status_send = Test;      //发送完get_done 后 状态转换为测试模式
      break;
    }
  case Set_Dev_Para :
    {
      Json_paraset_pro();
      //status_send = Test;      //发送完set_done 后 状态转换为测试模式
      break;
    }
  case Upd_Dev_Soft :
    {
      
      Json_updata_pro();
      break;
    }
  default :
    {
      
    }
  }
}
void AfterSend_status_press(void) //发送指令完成后，处理本机状态码
{
  switch(status_send)
  {
  case Test :
    {   
      break;
    }
  case Caling :                                  //不需要再发一次
    {
      break;
    }
  case Cal_Done :                                //
    {
      status_send = Test;      //发送完get_done 后 状态转换为测试模式
      break;
    }
  case Set_Done :
    {
      status_send = Test;      //发送完get_done 后 状态转换为测试模式
      break;
    }
  case Get_Done :
    {
      status_send = Test;      //发送完set_done 后 状态转换为测试模式
      break;
    }
  case Ask_Tim :
    {
      break;
    }
  case Updataing :
    {
      
      break;
    }
  case Upd_Done :
    {
      status_send = Test;      //发送完get_done 后 状态转换为测试模式
      break;
    }
  default :
    {
      
    }
  }
}

int16 wifi_tcp_senddat_cmd(uint16 dat_lenth,char sendCmd[])
{
  int16	retval;
  char datLen_buf[4] ="";
  strcpy(sendCmd,WIFI_TCP_SEND_DAT_CMD);  //"at+send"
  strcat(sendCmd,wifi_EQUAL);    //"="
  retval= sprintf(datLen_buf,"%d",dat_lenth);  //转换长度为字符串表示
  strcat(sendCmd,datLen_buf);    //加入数据长度项
  strcat(sendCmd,WIFI_LF);   //结束标识符，回车换行
  retval=USART_OUT(USART1,(char *)sendCmd,strlen(sendCmd));
  return retval;
}
int16 wifi_tcp_recvdat_cmd(char sendCmd[])
{
  int16	retval;
  char datLen_buf[4] ="";
  strcpy(sendCmd,WIFI_TCP_RECV_DAT_CMD);
  strcat(sendCmd,wifi_EQUAL);    //"="
  retval= sprintf(datLen_buf,"%d",1000);//RXBUFSIZE);  //转换长度为字符串表示
  strcat(sendCmd,datLen_buf);    //"="
  strcat(sendCmd,WIFI_LF);
  retval=USART_OUT(USART1,(char *)sendCmd,strlen(sendCmd));
  return retval;
}


int16 wifi_tcp_senddat(void)
{
  //nt8 buf_j ,buf_i ;
  uint16 dat_len;
  char sendCmd[16]="";
  char send_cmd_re[64]= "";
  
  do 
  { 
    dat_len = wifi_json_send_perss();                 //编辑json文件
    retval=wifi_tcp_senddat_cmd(dat_len,sendCmd);     //发送  数据发送命令
    recv_byte_con = 0;
    strcpy(send_cmd_re,sendCmd);
    strcat(send_cmd_re,WIFI_CR); 
    strcat(send_cmd_re,">");
    if(retval!=0)
    {			 			  
      //return retval;
      return OK_NONE_INFO;
    }	
    while(read_flag == FALSE);
    read_flag = FALSE;
    //if(	wifi_INC_TIMER_1>10) break;
    
  }while( strncmp((char *)uCmdRspFrame.uCmdRspBuf,send_cmd_re,strlen(send_cmd_re)) != 0);
  dat_len = wifi_json_send_perss();
  retval=USART_OUT(USART1,(char *)uCmdRspFrame.uCmdRspBuf,strlen((char *)uCmdRspFrame.uCmdRspBuf)); 
  UART_data_len = 0;
  while(read_flag == FALSE);
  read_flag = FALSE;
  AfterSend_status_press();
  if( strncmp((char *)uCmdRspFrame.uCmdRspBuf,"+ok",3) == 0)     //等待发送完毕
  {
    wifi_cmd_recv_ok_flg = CMD_RE_OK;  //收到ok，表示命令响应正常，下边识别命令响应信息
    return OK_INFO;
  }else
  {
     wifi_cmd_recv_ok_flg = CMD_RE_NOK;  //收到ok，表示命令响应正常，下边识别命令响应信息
    return RESP_ERROR;
  }
}

int16 wifi_tcp_recvdat(void)
{
  int8 buf_j ,buf_i ,point_find_FLG,Rsp_point_pre_econ;
  //uint16 dat_len;
  _RSP_PRESS_CON_FLG_  Rsp_p_conFLG;
  wifi_cmd_recv_ok_flg = CMD_RE_NOK;
  char *Rsp_pointer;
  char sendCmd[16]="";
  char send_cmd_re[64]= "";
  for(buf_i = 0;buf_i<20;buf_i++)
  {
    uCmdRspFrame.uCmdRspBuf[buf_i] =0;
  }
  do 
  {
    UART_data_len = 0;
    retval=wifi_tcp_recvdat_cmd(sendCmd);
    
    while(read_flag == FALSE);
    //recv_byte_con = 0xff;
    if(retval!=0)
    {			 			  
      //return retval;
      return OK_NONE_INFO;
    }	
    
    strcpy(send_cmd_re,sendCmd);
    strcat(send_cmd_re,WIFI_CR);
    /*strcat(send_cmd_re,WIFI_LF);
    strcat(send_cmd_re,WIFI_CR);
    strcat(send_cmd_re,WIFI_LF);*/
    read_flag = FALSE;
    //if(	wifi_INC_TIMER_1>10) break;
    //delay_s(20);
  }while( strncmp((char *)uCmdRspFrame.uCmdRspBuf,send_cmd_re,strlen(send_cmd_re)-1) != 0); //检测命令相应是否正确
  UART_data_len = 0;
  recv_byte_con = 0xff;
  while(read_flag == FALSE);                                 //等待数据接收
  read_flag = FALSE;  
  /*if( strncmp((char *)uCmdRspFrame.uCmdRspBuf,"+ok",3) == 0)
  {
    wifi_cmd_recv_ok_flg = CMD_RE_OK;  //收到ok，表示命令响应正常，下边识别命令响应信息
  }
  else
  {
    return RESP_ERROR;
  }*/
  point_find_FLG = 0;
  Rsp_point_pre_econ = 0;    //识别过程中的错误次数
  Rsp_pointer = (char *)uCmdRspFrame.uCmdRspBuf;
  Rsp_p_conFLG = Recv_num_FLG;
  do
  {
    switch(Rsp_p_conFLG)
    {
    case Recv_num_FLG:
      {
        if(strncmp(Rsp_pointer,"+ok=",4) == 0)
        {
          Rsp_pointer = Rsp_pointer+4;
          Rsp_Cont_Pointer.uploadframe.Resp_num_p = Rsp_pointer;
          Rsp_p_conFLG = Json_head_FLG;   //识别包长度完成，跳转到json headflg 过程
          if(strncmp(Rsp_pointer,"0",1) == 0)
          {
            Recv_Jchar_numb = 0;
            wifi_cmd_recv_ok_flg = CMD_RE_OK;  //收到ok，表示命令响应正常，下边识别命令响应信息
            return OK_INFO;//OK_NONE_INFO
          }
          else
          {
            Recv_Jchar_numb = 0;
            while(*Rsp_pointer != ',')    //注意识别当接受数据长度不为0时，读出数据长度值
            {
              Recv_Jchar_numb = Recv_Jchar_numb*10+(*Rsp_pointer-'0');
              Rsp_pointer++;
            }
          }
        }
        else
        {
          Rsp_pointer++;
        }
        break;
      }
    case Json_head_FLG:
      {
        if(strncmp(Rsp_pointer,"{",1) == 0)
        {
          Rsp_Cont_Pointer.uploadframe.Json_head_p = Rsp_pointer;
          Rsp_p_conFLG = Dev_ID_FLG;   //识别json 开头 “{” 完成 跳转到 Dev_ID_FLG 识别
        }
        else
        {
          Rsp_pointer++;
        }
        break;
      }
    case Dev_ID_FLG:
      {
        if(strncmp(Rsp_pointer,"\"Dev_ID\"",strlen("\"Dev_ID\"")) == 0)
        {
          Rsp_Cont_Pointer.uploadframe.Dev_ID_p = (_UPLOAD_DAT_DEVID_*)Rsp_pointer;
          Rsp_p_conFLG = Soft_V_FLG;   //识别Dev_ID 完成 跳转
        }
        else
        {
          Rsp_pointer++;
        }
        break;
      }
    case Soft_V_FLG:
      {
        if(strncmp(Rsp_pointer,"\"Soft_Ver\"",strlen("\"Soft_Ver\"")) == 0)
        {
          Rsp_Cont_Pointer.uploadframe.Soft_V_p = (_UPLOAD_DAT_SOFVER_*)Rsp_pointer;
          Rsp_p_conFLG = Cmd_FLG;   //识别Soft_V_FLG 完成 跳转
        }
        else
        {
          Rsp_pointer++;
        }
        break;
      }
    case Cmd_FLG:
      {
        if(strncmp(Rsp_pointer,"\"CMD\"",strlen("\"CMD\"")) == 0)
        {
          Rsp_Cont_Pointer.uploadframe.cmd_p = (_UPLOAD_DAT_CMD_*)Rsp_pointer;
          Rsp_p_conFLG = Status_FLG;   //识别Cmd_FLG 完成 跳转
        }
        else
        {
          Rsp_pointer++;
        }
        break;
      }
    case Status_FLG:
      {
        if(strncmp(Rsp_pointer,"\"STATUS\"",strlen("\"STATUS\"")) == 0)
        {
          Rsp_Cont_Pointer.uploadframe.status_p = (_UPLOAD_DAT_STATUS_*)Rsp_pointer;
          Rsp_p_conFLG = Tim_Zone_FLG;   //识别Status_FLG 完成 跳转
        }
        else
        {
          Rsp_pointer++;
        }
        break;
      }
    case Tim_Zone_FLG:
      {
        if(strncmp(Rsp_pointer,"\"Tim_Zone\"",strlen("\"Tim_Zone\"")) == 0)
        {
          Rsp_Cont_Pointer.uploadframe.tim_zone_p = (_UPLOAD_DAT_TIMZ_*)Rsp_pointer;
          Rsp_p_conFLG = Tim_Year_FLG;   //识别Tim_Zone_FLG 完成 跳转
        }
        else if(strncmp(Rsp_pointer,"\"Dat_num\"",strlen("\"Dat_num\"")) == 0)           //识别是否需要固件升级 固件升级的字节数
        {
          Rsp_Cont_Pointer.soft_updframe.UPD_Dat_num_p = (_UPLOAD_SOFT_UPD_NUM_*)Rsp_pointer;
          Rsp_p_conFLG = Tim_Year_FLG;   //识别Tim_Zone_FLG 完成 跳转
        }
        else
        {
          Rsp_pointer++;
        }
        break;
      }
    case Tim_Year_FLG:
      {
        if(strncmp(Rsp_pointer,"\"Year\"",strlen("\"Year\"")) == 0)
        {
          Rsp_Cont_Pointer.uploadframe.year_p = (_UPLOAD_DAT_YEAR_*)Rsp_pointer;
          Rsp_p_conFLG = Tim_Mon_FLG;   //识别Tim_Year_FLG 完成 跳转
        }
        else if(strncmp(Rsp_pointer,"\"Dat\"",strlen("\"Dat\"")) == 0)                           ////识别是否需要固件升级 固件升级的内容
        {
          Rsp_Cont_Pointer.soft_updframe.UPD_Soft_cont_p = (_UPLOAD_SOFT_UPD_CONT_*)Rsp_pointer;
          Rsp_p_conFLG = Rsp_Reco_Done;   //识别结束 完成 跳转
        }
        else
        {
          Rsp_pointer++;
        }
        break;
      }
    case Tim_Mon_FLG:
      {
        if(strncmp(Rsp_pointer,"\"Mon\"",strlen("\"Mon\"")) == 0)
        {
          Rsp_Cont_Pointer.uploadframe.mon_p = (_UPLOAD_DAT_MON_*)Rsp_pointer;
          Rsp_p_conFLG = Tim_Day_FLG;   //识别Tim_Mon_FLG 完成 跳转
        }
        else
        {
          Rsp_pointer++;
        }
        break;
      }
    case Tim_Day_FLG:
      {
        if(strncmp(Rsp_pointer,"\"Day\"",strlen("\"Day\"")) == 0)
        {
          Rsp_Cont_Pointer.uploadframe.day_p = (_UPLOAD_DAT_DAY_*)Rsp_pointer;
          Rsp_p_conFLG = Tim_Hour_FLG;   //识别Tim_Day_FLG 完成 跳转
        }
        else
        {
          Rsp_pointer++;
        }
        break;
      }
    case Tim_Hour_FLG:
      {
        if(strncmp(Rsp_pointer,"\"Hour\"",strlen("\"Hour\"")) == 0)
        {
          Rsp_Cont_Pointer.uploadframe.hour_p = (_UPLOAD_DAT_HOUR_*)Rsp_pointer;
          Rsp_p_conFLG = Tim_Min_FLG;   //识别Tim_Hour_FLG 完成 跳转
        }
        else
        {
          Rsp_pointer++;
        }
        break;
      }
    case Tim_Min_FLG:
      {
        if(strncmp(Rsp_pointer,"\"Min\"",strlen("\"Min\"")) == 0)
        {
          Rsp_Cont_Pointer.uploadframe.min_p = (_UPLOAD_DAT_MIN_*)Rsp_pointer;
          Rsp_p_conFLG = Tim_Sec_FLG;   //识别Tim_Min_FLG完成 跳转
        }
        else
        {
          Rsp_pointer++;
        }
        break;
      }
    case Tim_Sec_FLG:
      {
        if(strncmp(Rsp_pointer,"\"Sec\"",strlen("\"Sec\"")) == 0)
        {
          Rsp_Cont_Pointer.uploadframe.sec_p = (_UPLOAD_DAT_SEC_*)Rsp_pointer;
          Rsp_p_conFLG = Hcho_Val_FLG;   //通用段识别完成 表转到数据识别 程序
        }
        else
        {
          Rsp_pointer++;
        }
        break;
      }
    case Hcho_Val_FLG:  //HCHO_V  HCHO_K1
      {
        if(strncmp(Rsp_pointer,"\"HCHO_V\"",strlen("\"HCHO_V\"")) == 0)
        {
          Rsp_Cont_Pointer.uploadframe.hcho_v_p = (_UPLOAD_DAT_HV_*)Rsp_pointer;
          Rsp_p_conFLG = PM25_Val_FLG;   //通用段识别完成 表转到数据识别 程序
        }
        else if(strncmp(Rsp_pointer,"\"HCHO_K1\"",strlen("\"HCHO_K1\""))== 0)
        {
          Rsp_Cont_Pointer.setframe.hcho_k1_p = (_UPLOAD_DAT_HK1_*)Rsp_pointer;
          Rsp_p_conFLG = PM25_Val_FLG;   //通用段识别完成 表转到数据识别 程序
        }
        else
        {
          Rsp_pointer++;
        }
        break;
      }
    case PM25_Val_FLG:
      {
        if(strncmp(Rsp_pointer,"\"PM25_V\"",strlen("\"PM25_V\"")) == 0)
        {
          Rsp_Cont_Pointer.uploadframe.pm25_v_p = (_UPLOAD_DAT_PV_*)Rsp_pointer;
          Rsp_p_conFLG = Temp_Val_FLG;   //通用段识别完成 表转到数据识别 程序
        }
        else if(strncmp(Rsp_pointer,"\"HCHO_K2\"",strlen("\"HCHO_K2\""))== 0)
        {
          Rsp_Cont_Pointer.setframe.hcho_k2_p = (_UPLOAD_DAT_HK2_*)Rsp_pointer;
          Rsp_p_conFLG = Temp_Val_FLG;   //通用段识别完成 表转到数据识别 程序
        }
        else
        {
          Rsp_pointer++;
        }
        break;
      }
    case Temp_Val_FLG:
      {
        if(strncmp(Rsp_pointer,"\"Temp_V\"",strlen("\"Temp_V\"")) == 0)
        {
          Rsp_Cont_Pointer.uploadframe.tem_v_p = (_UPLOAD_DAT_TEMV_*)Rsp_pointer;
          Rsp_p_conFLG = Humi_Val_FLG;   //通用段识别完成 表转到数据识别 程序
        }
        else if(strncmp(Rsp_pointer,"\"HCHO_A\"",strlen("\"HCHO_A\""))== 0)
        {
          Rsp_Cont_Pointer.setframe.hcho_a_p = (_UPLOAD_DAT_HA_*)Rsp_pointer;
          Rsp_p_conFLG = Humi_Val_FLG;   //通用段识别完成 表转到数据识别 程序
        }
        else
        {
          Rsp_pointer++;
        }
        break;
      }
    case Humi_Val_FLG:
      {
        if(strncmp(Rsp_pointer,"\"Humi_V\"",strlen("\"Humi_V\"")) == 0)
        {
          Rsp_Cont_Pointer.uploadframe.hum_v_p = (_UPLOAD_DAT_HUMV_*)Rsp_pointer;
          Rsp_p_conFLG = Rsp_Reco_Done;   //识别结束 完成 跳转
        }
        else if(strncmp(Rsp_pointer,"\"PM25_K1\"",strlen("\"PM25_K1\""))== 0)
        {
          Rsp_Cont_Pointer.setframe.pm25_k1_p = (_UPLOAD_DAT_PK1_*)Rsp_pointer;
          Rsp_p_conFLG = PM25_K2_FLG;   //通用段识别完成 表转到数据识别 程序
        }
        else
        {
          Rsp_pointer++;
        }
        break;
      }
    case PM25_K2_FLG:
      {
        if(strncmp(Rsp_pointer,"\"PM25_K2\"",strlen("\"PM25_K2\"")) == 0)
        {
          Rsp_Cont_Pointer.setframe.pm25_k2_p = (_UPLOAD_DAT_PK2_*)Rsp_pointer;
          Rsp_p_conFLG = PM25_A_FLG;   //通用段识别完成 表转到数据识别 程序
        }
        else
        {
          Rsp_pointer++;
        }
        break;
      }
    case PM25_A_FLG:
      {
        if(strncmp(Rsp_pointer,"\"PM25_A\"",strlen("\"PM25_A\"")) == 0)
        {
          Rsp_Cont_Pointer.setframe.pm25_a_p = (_UPLOAD_DAT_PA_*)Rsp_pointer;
          Rsp_p_conFLG = PM25_Ref_FLG;   //通用段识别完成 表转到数据识别 程序
        }
        else
        {
          Rsp_pointer++;
        }
        break;
      }
    case PM25_Ref_FLG:
      {
        if(strncmp(Rsp_pointer,"\"PM25_Ref\"",strlen("\"PM25_Ref\"")) == 0)
        {
          Rsp_Cont_Pointer.setframe.pm25_ref_p = (_UPLOAD_DAT_PR_*)Rsp_pointer;
          Rsp_p_conFLG = Rsp_Reco_Done;   //识别结束 完成 跳转
        }
        else
        {
          Rsp_pointer++;
        }
        break;
      }
    default:
      {
        Rsp_pointer = (char *)uCmdRspFrame.uCmdRspBuf;
        Rsp_point_pre_econ++;
        if(Rsp_point_pre_econ > 3 )
        {
          return RESP_ERROR;   //识别错误超过3次，返回 错误
        }
      }    
    }

  }while(Rsp_p_conFLG != Rsp_Reco_Done);   //用于识别 devid  soft_ver  cmd  status
  //Recv_CMD_Press();
  
    wifi_cmd_recv_ok_flg = CMD_RE_OK;  //收到ok，表示命令响应正常，下边识别命令响应信息
    return OK_INFO;
  
}
int16 Recv_CMD_reco(void)
{
  uint8   par_reco_flg , pi;
  char   *param_pointer;
  
  param_pointer = (char*)Rsp_Cont_Pointer.uploadframe.cmd_p->contframe.cont;
  cmd_recv   = 0;
  par_reco_flg = 0;
  pi = 0;
  do
  {
    if((par_reco_flg == 0)&&(*(param_pointer+pi)-'\"' == 0))
    {
      par_reco_flg = 1;
      pi++;
      continue;
    }
    if((par_reco_flg == 1))
    {
      if(*(param_pointer+pi)-'\"' == 0)
      {
        par_reco_flg = 2;
      }
      else if((*(param_pointer+pi)>='0')&&(*(param_pointer+pi)<='9'))
      {
        cmd_recv = cmd_recv*10+(*(param_pointer+pi)-'0');
      }
      else
      {
        return 0;
      }
      
    }
    pi++;
  }while(par_reco_flg < 2);
  return 1;

}
int16 Recv_STATUS_reco(void)
{
  uint8 par_reco_flg,pi;
  char   *param_pointer;
  
  param_pointer = (char*)Rsp_Cont_Pointer.uploadframe.status_p->contframe.cont;
  par_reco_flg = 0;
  pi = 0;
  do
  {
    if((par_reco_flg == 0)&&(*(param_pointer+pi)-'\"' == 0))
    {
      par_reco_flg = 1;
      pi++;
      continue;
    }
    if((par_reco_flg == 1))
    {
      if(*(param_pointer+pi)-'\"' == 0)
      {
        par_reco_flg = 2;
      }
      else if((*(param_pointer+pi)>='0')&&(*(param_pointer+pi)<='9'))
      {
        status_recv = status_recv*10+(*(param_pointer+pi)-'0');
      }
      else
      {
        return 0;
      }
      
    }
    pi++;
  }while(par_reco_flg < 2);
  return 1;
}

int16 Recv_TIME_reco(void)
{
  uint8 par_reco_flg,pi,i;
  char   *param_pointer;
  uint16 temp;
  for(i = 0;i<7;i++)
  {
    if(i == 0)
        param_pointer = (char*)(Rsp_Cont_Pointer.setframe.tim_zone_p->contframe.cont);
    if(i == 1)
        param_pointer = (char*)(Rsp_Cont_Pointer.setframe.year_p->contframe.cont);
    if(i == 2)
        param_pointer = (char*)(Rsp_Cont_Pointer.setframe.mon_p->contframe.cont);
    if(i == 3)
        param_pointer = (char*)(Rsp_Cont_Pointer.setframe.day_p->contframe.cont);
    if(i == 4)
        param_pointer = (char*)(Rsp_Cont_Pointer.setframe.hour_p->contframe.cont);
    if(i == 5)
        param_pointer = (char*)(Rsp_Cont_Pointer.setframe.min_p->contframe.cont);
    if(i == 6)
        param_pointer = (char*)(Rsp_Cont_Pointer.setframe.sec_p->contframe.cont);

    par_reco_flg = 0;
    pi = 0;
    temp = 0;
    do
    {
      if((par_reco_flg == 0)&&(*(param_pointer+pi)-'\"' == 0))
      {
        par_reco_flg = 1;
        pi++;
        continue;
      }
      if((par_reco_flg == 1))
      {
        if(*(param_pointer+pi)-'\"' == 0)
        {
          par_reco_flg = 2;
        }
        else if((*(param_pointer+pi)>='0')&&(*(param_pointer+pi)<='9'))
        {
           temp= temp*10+(*(param_pointer+pi)-'0');
        }
        /*else
        {
          return 0;
        }
        */
      }
      pi++;
    }while(par_reco_flg < 2);
    Time_recv_buf.FrameBuf[i] = temp;
  }
  Time_local_buf=Time_recv_buf;
  
  return 1;
  
}

int16 Recv_HCHO_reco(void)
{
  uint8 par_reco_flg,pi,i;
  char   *param_pointer;
  uint16 temp;
  for(i = 0;i<3;i++)
  {
    if(i == 0)
        param_pointer = (char*)(Rsp_Cont_Pointer.setframe.hcho_k1_p->contframe.cont);
    if(i == 1)
        param_pointer = (char*)(Rsp_Cont_Pointer.setframe.hcho_k2_p->contframe.cont);
    if(i == 2)
        param_pointer = (char*)(Rsp_Cont_Pointer.setframe.hcho_a_p->contframe.cont);
    par_reco_flg = 0;
    pi = 0;
    temp = 0;
    do
    {
      if((par_reco_flg == 0)&&(*(param_pointer+pi)-'\"' == 0))
      {
        par_reco_flg = 1;
        pi++;
        continue;
      }
      if((par_reco_flg == 1))
      {
        if(*(param_pointer+pi)-'\"' == 0)
        {
          par_reco_flg = 2;
        }
        else if((*(param_pointer+pi)>='0')&&(*(param_pointer+pi)<='9'))
        {
           temp= temp*10+(*(param_pointer+pi)-'0');
        }
        else
        {
          return 0;
        }
        
      }
      pi++;
    }while(par_reco_flg < 2);
    HCHO_param_buf->FrameBuf[i] = temp;
  }
  hcho_send = *HCHO_param_buf;
  return 1;
  
}



int16 Recv_PM25_reco(void)
{
  uint8 par_reco_flg,pi,i;
  char   *param_pointer;
  uint16 temp;
  for(i = 0;i<4;i++)
  {
    if(i == 0)
        param_pointer = (char*)(Rsp_Cont_Pointer.setframe.pm25_k1_p->contframe.cont);
    if(i == 1)
        param_pointer = (char*)(Rsp_Cont_Pointer.setframe.pm25_k2_p->contframe.cont);
    if(i == 2)
        param_pointer = (char*)(Rsp_Cont_Pointer.setframe.pm25_a_p->contframe.cont);
    if(i == 3)
        param_pointer = (char*)(Rsp_Cont_Pointer.setframe.pm25_ref_p->contframe.cont);
    par_reco_flg = 0;
    pi = 0;
    temp = 0;
    do
    {
      if((par_reco_flg == 0)&&(*(param_pointer+pi)-'\"' == 0))
      {
        par_reco_flg = 1;
        pi++;
        continue;
      }
      if((par_reco_flg == 1))
      {
        if(*(param_pointer+pi)-'\"' == 0)
        {
          par_reco_flg = 2;
        }
        else if((*(param_pointer+pi)>='0')&&(*(param_pointer+pi)<='9'))
        {
           temp= temp*10+(*(param_pointer+pi)-'0');
        }
        else
        {
          return 0;
        }
        
      }
      pi++;
    }while(par_reco_flg < 2);
    PM25_param_buf->FrameBuf[i] = temp;
  }
  pm25_send = *PM25_param_buf;
  return 1;
}

int16 Recv_UPD_reco(void)
{
  uint8 par_reco_flg,pi;
  char   *param_pointer;
  uint16 temp;
  //for(i = 0;i<3;i++)
  {
    param_pointer = (char*)(Rsp_Cont_Pointer.soft_updframe.UPD_Dat_num_p->contframe.cont);
    //param_pointer = (char*)Rsp_Cont_Pointer.FrameRcv[16+i];
    par_reco_flg = 0;
    pi = 0;
    temp = 0;
    do
    {
      if((par_reco_flg == 0)&&(*(param_pointer+pi)-'\"' == 0))
      {
        par_reco_flg = 1;
        pi++;
        continue;
      }
      if((par_reco_flg == 1))
      {
        if(*(param_pointer+pi)-'\"' == 0)
        {
          par_reco_flg = 2;
        }
        else if((*(param_pointer+pi)>='0')&&(*(param_pointer+pi)<='9'))
        {
           temp= temp*10+(*(param_pointer+pi)-'0');
        }
        else
        {
          return 0;
        }
        
      }
      pi++;
    }while(par_reco_flg < 2);
    Soft_upd_datnumb = temp;
  }
  param_pointer = (char*)(Rsp_Cont_Pointer.soft_updframe.UPD_Soft_cont_p->contframe.cont+1);
  //param_pointer = (char*)Rsp_Cont_Pointer.FrameRcv[16+i];
  par_reco_flg = 0;
  pi = 0;
  temp = 0;

  return 1;
}



