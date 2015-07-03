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
uint16 Json_upload_pro(void)
{
  int8 data2charbuf[6];
  uint16 headLen=0;
  strcpy(uCmdRspFrame.uCmdRspBuf,"{\"Dev_ID\":\"");  //Éè±¸id
  strcat(uCmdRspFrame.uCmdRspBuf,DEV_ID);
  strcat(uCmdRspFrame.uCmdRspBuf,"\",");
  strcat(uCmdRspFrame.uCmdRspBuf,"\"Soft_Ver\":\"");  //¹Ì¼þ°æ±¾
  strcat(uCmdRspFrame.uCmdRspBuf,SOFT_VER);
  strcat(uCmdRspFrame.uCmdRspBuf,"\",");
  
  strcat(uCmdRspFrame.uCmdRspBuf,"\"CMD\":\""); //ÃüÁîÂðcmd
  headLen= sprintf(data2charbuf,"%d",cmd_send);
  strcat(uCmdRspFrame.uCmdRspBuf,data2charbuf);
  strcat(uCmdRspFrame.uCmdRspBuf,"\",");
  
  strcat(uCmdRspFrame.uCmdRspBuf,"\"STATUS\":\""); //×´Ì¬cmd
  headLen= sprintf(data2charbuf,"%d",status_send);
  strcat(uCmdRspFrame.uCmdRspBuf,data2charbuf);
  strcat(uCmdRspFrame.uCmdRspBuf,"\",");
  
  strcat(uCmdRspFrame.uCmdRspBuf,"\"Tim_Zone\":\"UTC+"); //time_zone
  headLen= sprintf(data2charbuf,"%d",time_send.frame.zone);
  strcat(uCmdRspFrame.uCmdRspBuf,data2charbuf);
  strcat(uCmdRspFrame.uCmdRspBuf,"\",");
  
  strcat(uCmdRspFrame.uCmdRspBuf,"\"Year\":\""); //time_zone
  headLen= sprintf(data2charbuf,"%d",time_send.frame.year);
  strcat(uCmdRspFrame.uCmdRspBuf,data2charbuf);
  strcat(uCmdRspFrame.uCmdRspBuf,"\",");
  
  strcat(uCmdRspFrame.uCmdRspBuf,"\"Mon\":\""); //time_zone
  headLen= sprintf(data2charbuf,"%d",time_send.frame.mon);
  strcat(uCmdRspFrame.uCmdRspBuf,data2charbuf);
  strcat(uCmdRspFrame.uCmdRspBuf,"\",");
  
  strcat(uCmdRspFrame.uCmdRspBuf,"\"Day\":\""); //time_zone
  headLen= sprintf(data2charbuf,"%d",time_send.frame.day);
  strcat(uCmdRspFrame.uCmdRspBuf,data2charbuf);
  strcat(uCmdRspFrame.uCmdRspBuf,"\",");
  
  strcat(uCmdRspFrame.uCmdRspBuf,"\"Hour\":\""); //time_zone
  headLen= sprintf(data2charbuf,"%d",time_send.frame.hour);
  strcat(uCmdRspFrame.uCmdRspBuf,data2charbuf);
  strcat(uCmdRspFrame.uCmdRspBuf,"\",");
  
  strcat(uCmdRspFrame.uCmdRspBuf,"\"Min\":\""); //time_zone
  headLen= sprintf(data2charbuf,"%d",time_send.frame.min);
  strcat(uCmdRspFrame.uCmdRspBuf,data2charbuf);
  strcat(uCmdRspFrame.uCmdRspBuf,"\",");
  
  strcat(uCmdRspFrame.uCmdRspBuf,"\"Sec\":\""); //time_zone
  headLen= sprintf(data2charbuf,"%d",time_send.frame.sec);
  strcat(uCmdRspFrame.uCmdRspBuf,data2charbuf);
  strcat(uCmdRspFrame.uCmdRspBuf,"\",");
  
  strcat(uCmdRspFrame.uCmdRspBuf,"\"HCHO_V\":\""); //hcho_send
  headLen= sprintf(data2charbuf,"%d",hcho_send.frame.value);
  strcat(uCmdRspFrame.uCmdRspBuf,data2charbuf);
  strcat(uCmdRspFrame.uCmdRspBuf,"\",");
  
  strcat(uCmdRspFrame.uCmdRspBuf,"\"PM25_V\":\""); //pm25_send
  headLen= sprintf(data2charbuf,"%d",pm25_send.frame.value);
  strcat(uCmdRspFrame.uCmdRspBuf,data2charbuf);
  strcat(uCmdRspFrame.uCmdRspBuf,"\",");
  
  strcat(uCmdRspFrame.uCmdRspBuf,"\"Temp_V\":\""); //time_zone
  headLen= sprintf(data2charbuf,"%d",temp_value);
  strcat(uCmdRspFrame.uCmdRspBuf,data2charbuf);
  strcat(uCmdRspFrame.uCmdRspBuf,"\",");
  
  strcat(uCmdRspFrame.uCmdRspBuf,"\"Humi_V\":\""); //time_zone
  headLen= sprintf(data2charbuf,"%d",humi_value);
  strcat(uCmdRspFrame.uCmdRspBuf,data2charbuf);
  strcat(uCmdRspFrame.uCmdRspBuf,"\"}");
  strcat(uCmdRspFrame.uCmdRspBuf,"##");
  headLen = strlen(uCmdRspFrame.uCmdRspBuf);
  return headLen;
}

uint16 Json_paraset_pro(void)
{
  int8 data2charbuf[6];
  uint16 headLen=0;
  strcpy(uCmdRspFrame.uCmdRspBuf,"{\"Dev_ID\":\"");  //Éè±¸id
  strcat(uCmdRspFrame.uCmdRspBuf,DEV_ID);
  strcat(uCmdRspFrame.uCmdRspBuf,"\",");
  strcat(uCmdRspFrame.uCmdRspBuf,"\"Soft_Ver\":\"");  //¹Ì¼þ°æ±¾
  strcat(uCmdRspFrame.uCmdRspBuf,SOFT_VER);
  strcat(uCmdRspFrame.uCmdRspBuf,"\",");
  
  strcat(uCmdRspFrame.uCmdRspBuf,"\"CMD\":\""); //ÃüÁîÂðcmd
  headLen= sprintf(data2charbuf,"%d",cmd_send);
  strcat(uCmdRspFrame.uCmdRspBuf,data2charbuf);
  strcat(uCmdRspFrame.uCmdRspBuf,"\",");
  
  strcat(uCmdRspFrame.uCmdRspBuf,"\"STATUS\":\""); //×´Ì¬cmd
  headLen= sprintf(data2charbuf,"%d",status_send);
  strcat(uCmdRspFrame.uCmdRspBuf,data2charbuf);
  strcat(uCmdRspFrame.uCmdRspBuf,"\",");
  
  strcat(uCmdRspFrame.uCmdRspBuf,"\"Tim_Zone\":\"UTC+"); //time_zone
  headLen= sprintf(data2charbuf,"%d",time_send.frame.zone);
  strcat(uCmdRspFrame.uCmdRspBuf,data2charbuf);
  strcat(uCmdRspFrame.uCmdRspBuf,"\",");
  
  strcat(uCmdRspFrame.uCmdRspBuf,"\"Year\":\""); //time_zone
  headLen= sprintf(data2charbuf,"%d",time_send.frame.year);
  strcat(uCmdRspFrame.uCmdRspBuf,data2charbuf);
  strcat(uCmdRspFrame.uCmdRspBuf,"\",");
  
  strcat(uCmdRspFrame.uCmdRspBuf,"\"Mon\":\""); //time_zone
  headLen= sprintf(data2charbuf,"%d",time_send.frame.mon);
  strcat(uCmdRspFrame.uCmdRspBuf,data2charbuf);
  strcat(uCmdRspFrame.uCmdRspBuf,"\",");
  
  strcat(uCmdRspFrame.uCmdRspBuf,"\"Day\":\""); //time_zone
  headLen= sprintf(data2charbuf,"%d",time_send.frame.day);
  strcat(uCmdRspFrame.uCmdRspBuf,data2charbuf);
  strcat(uCmdRspFrame.uCmdRspBuf,"\",");
  
  strcat(uCmdRspFrame.uCmdRspBuf,"\"Hour\":\""); //time_zone
  headLen= sprintf(data2charbuf,"%d",time_send.frame.hour);
  strcat(uCmdRspFrame.uCmdRspBuf,data2charbuf);
  strcat(uCmdRspFrame.uCmdRspBuf,"\",");
  
  strcat(uCmdRspFrame.uCmdRspBuf,"\"Min\":\""); //time_zone
  headLen= sprintf(data2charbuf,"%d",time_send.frame.min);
  strcat(uCmdRspFrame.uCmdRspBuf,data2charbuf);
  strcat(uCmdRspFrame.uCmdRspBuf,"\",");
  
  strcat(uCmdRspFrame.uCmdRspBuf,"\"Sec\":\""); //time_zone
  headLen= sprintf(data2charbuf,"%d",time_send.frame.sec);
  strcat(uCmdRspFrame.uCmdRspBuf,data2charbuf);
  strcat(uCmdRspFrame.uCmdRspBuf,"\",");
  
  strcat(uCmdRspFrame.uCmdRspBuf,"\"HCHO_K1\":\""); //hcho_send
  headLen= sprintf(data2charbuf,"%d",hcho_send.frame.k1);
  strcat(uCmdRspFrame.uCmdRspBuf,data2charbuf);
  strcat(uCmdRspFrame.uCmdRspBuf,"\",");
  
  strcat(uCmdRspFrame.uCmdRspBuf,"\"HCHO_K2\":\""); //hcho_send
  headLen= sprintf(data2charbuf,"%d",hcho_send.frame.k2);
  strcat(uCmdRspFrame.uCmdRspBuf,data2charbuf);
  strcat(uCmdRspFrame.uCmdRspBuf,"\",");
  
  strcat(uCmdRspFrame.uCmdRspBuf,"\"HCHO_A\":\""); //hcho_send
  headLen= sprintf(data2charbuf,"%d",hcho_send.frame.a);
  strcat(uCmdRspFrame.uCmdRspBuf,data2charbuf);
  strcat(uCmdRspFrame.uCmdRspBuf,"\",");
  
  strcat(uCmdRspFrame.uCmdRspBuf,"\"PM25_K1\":\""); //pm25_send
  headLen= sprintf(data2charbuf,"%d",pm25_send.frame.k1);
  strcat(uCmdRspFrame.uCmdRspBuf,data2charbuf);
  strcat(uCmdRspFrame.uCmdRspBuf,"\",");
  
  strcat(uCmdRspFrame.uCmdRspBuf,"\"PM25_K2\":\""); //pm25_send
  headLen= sprintf(data2charbuf,"%d",pm25_send.frame.k2);
  strcat(uCmdRspFrame.uCmdRspBuf,data2charbuf);
  strcat(uCmdRspFrame.uCmdRspBuf,"\",");
  
  strcat(uCmdRspFrame.uCmdRspBuf,"\"PM25_A\":\""); //pm25_send
  headLen= sprintf(data2charbuf,"%d",pm25_send.frame.a);
  strcat(uCmdRspFrame.uCmdRspBuf,data2charbuf);
  strcat(uCmdRspFrame.uCmdRspBuf,"\",");
  
  strcat(uCmdRspFrame.uCmdRspBuf,"\"PM25_Ref\":\""); //pm25_send
  headLen= sprintf(data2charbuf,"%d",pm25_send.frame.Ref);
  strcat(uCmdRspFrame.uCmdRspBuf,data2charbuf);
  strcat(uCmdRspFrame.uCmdRspBuf,"\"}");
  strcat(uCmdRspFrame.uCmdRspBuf,"##");
  headLen = strlen(uCmdRspFrame.uCmdRspBuf);  
  return headLen;
}
uint16 Json_updata_pro(void)
{
  int8 data2charbuf[6];
  uint16 headLen=0;
  strcpy(uCmdRspFrame.uCmdRspBuf,"{\"Dev_ID\":\"");  //Éè±¸id
  strcat(uCmdRspFrame.uCmdRspBuf,DEV_ID);
  strcat(uCmdRspFrame.uCmdRspBuf,"\",");
  strcat(uCmdRspFrame.uCmdRspBuf,"\"Soft_Ver\":\"");  //¹Ì¼þ°æ±¾
  strcat(uCmdRspFrame.uCmdRspBuf,SOFT_VER);
  strcat(uCmdRspFrame.uCmdRspBuf,"\",");
  
  strcat(uCmdRspFrame.uCmdRspBuf,"\"CMD\":\""); //ÃüÁîÂðcmd
  headLen= sprintf(data2charbuf,"%d",cmd_send);
  strcat(uCmdRspFrame.uCmdRspBuf,data2charbuf);
  strcat(uCmdRspFrame.uCmdRspBuf,"\",");
  
  strcat(uCmdRspFrame.uCmdRspBuf,"\"STATUS\":\""); //×´Ì¬
  headLen= sprintf(data2charbuf,"%d",status_send);
  strcat(uCmdRspFrame.uCmdRspBuf,data2charbuf);
  strcat(uCmdRspFrame.uCmdRspBuf,"\",");
  
  strcat(uCmdRspFrame.uCmdRspBuf,"\"Dat_num\":\""); //
  headLen= sprintf(data2charbuf,"%d",Soft_upd_datnumb);
  strcat(uCmdRspFrame.uCmdRspBuf,data2charbuf);
  /*strcat(uCmdRspFrame.uCmdRspBuf,"\",");
  
  strcat(uCmdRspFrame.uCmdRspBuf,"\"Dat\":\""); //
  headLen= sprintf(data2charbuf,"%d",time_send.frame.year);
  strcat(uCmdRspFrame.uCmdRspBuf,data2charbuf);*/
  strcat(uCmdRspFrame.uCmdRspBuf,"\"}");
  strcat(uCmdRspFrame.uCmdRspBuf,"##");
  headLen = strlen(uCmdRspFrame.uCmdRspBuf);
    
  return headLen;
}