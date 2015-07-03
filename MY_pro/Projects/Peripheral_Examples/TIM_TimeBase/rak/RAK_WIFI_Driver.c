//;****************************************************
//;Company :  WIFI WIRELESS
//;File Name : wifi_WIFI_DRIVER.c
//;Author :    Junhua
//;Create Data : 2014-03-15
//;Last Modified : 
//;Description : WIFI413 WIFI UART  DRIVER
//;Version : 1.0.1
//;****************************************************

#include "BSP_Driver.h"
#include "delay.h"
#include "date.h"

wifi_api wifi_strApi;



/* Set SOCKET CONFIG */
uint8   wifi_DEST_IP_ADDRESS[4]={192,168,1,102}; 
uint16  wifi_DEST_PORT=0;
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
   do{
        Reset_Target();			  //RESET WIFI413
	    while(read_flag == FALSE);
		read_flag = FALSE;       
    }while( strncmp((char *)uCmdRspFrame.uCmdRspBuf,"Welcome to WIFI413\r\n",19) != 0); 
	

   //读取模块的版本号
//	retval=wifi_query_fwversion();					
//	if(retval!=0)
//	{			 			  
//	  return retval;					
//    }
//	while(read_flag == FALSE);
//	read_flag = FALSE;
//	 
//   
//   //设置模块的功耗模式
//	do{
//		retval=wifi_set_pwrmode(wifi_POWER_LEVEL_0);	
//		if(retval!=0)
//		{			 			  
//			return retval;					
//		}
//		while(read_flag == FALSE);
//		read_flag = FALSE;       
//    }while(strncmp((char *)uCmdRspFrame.uCmdRspBuf,"OK",2) != 0);
//	 		
//读取用户配置
	wifi_init_struct(&wifi_strApi);

 if(wifi_AP_STATION_MODE==0)
  { 	    		
		//扫描指定的ssid
		//wifi_RESET_TIMER1;	  wifi_ascii
		do {														
				retval=wifi_ascii();
				if(retval!=0)
				{			 			  
					return retval;					
				}	
				while(read_flag == FALSE);
				read_flag = FALSE;
				//if(	wifi_INC_TIMER_1>10) break;			
		    }while( strncmp((char *)uCmdRspFrame.uCmdRspBuf,"OK",2) != 0);

		   //扫描的ssid
		do {														
				retval=wifi_scan_ap(&wifi_strApi.uScanFrame);
				if(retval!=0)
				{			 			  
					return retval;					
				}	
				while(read_flag == FALSE);
				read_flag = FALSE;
				if(	wifi_INC_TIMER_1>10) break;			
		    }while( strncmp((char *)uCmdRspFrame.scanResponse.scanframe.rspCode,"OK",2) != 0);			
		 	if(uCmdRspFrame.errorResponse.errorframe.errorCode== 0xFE)
			 {

			 }

		 //输入该ssid的密码
		do{
			retval=wifi_set_psk(&wifi_strApi.uJoinFrame);
				if(retval!=0)
				{			 			  
					return retval;					
					}				  
					while(read_flag == FALSE);
					read_flag = FALSE;      
			}while(strncmp((char *)uCmdRspFrame.uCmdRspBuf,"OK",2) != 0);


	 //Connect to the specified network
	 //wifi_RESET_TIMER1;
	 do {																 
			retval=wifi_connect_ap(&wifi_strApi.uJoinFrame);
			if(retval!=0)
				{			 			  
					return retval;					
				}				  
			while(read_flag == FALSE);
			read_flag = FALSE; 		
			if(	wifi_INC_TIMER_1>wifi_PRAR_ERROR_TIMEOUT)
					return uCmdRspFrame.errorResponse.errorframe.errorCode; 
		}while( strncmp((char *)uCmdRspFrame.mgmtResponse.mgmtframe.rspCode,"OK",2) != 0);
		if(uCmdRspFrame.errorResponse.errorframe.errorCode== 0xFD)
		{
		
		}
				
		//设置IP获取方式
				  //0: 动态配置  1：静态配置
		   if(wifi_IPDHCP_MODE_ENABLE==1)
		   {
		 	do {												
					retval=wifi_set_ipstatic(&wifi_strApi.uIpparamFrame);		  //IPstatic
					if(retval!=0)
					{			 			  
						return retval;					
					}	  
					while(read_flag == FALSE);
					read_flag = FALSE;
			}while( strncmp((char *)uCmdRspFrame.scanResponse.scanframe.rspCode,"OK",2) != 0);
		   }
		   else if(wifi_IPDHCP_MODE_ENABLE==0)
		  {
		 	wifi_strApi.uIpparamFrame.ipparamFrameSnd.dhcpMode=0;
		 	do {												
				  retval=wifi_set_ipdhcp(&wifi_strApi.uIpparamFrame);		  //IPdhcp	client
				  if(retval!=0)
					{			 			  
						return retval;					
					}	  
					while(read_flag == FALSE);
					read_flag = FALSE;
			}while( strncmp((char *)uCmdRspFrame.scanResponse.scanframe.rspCode,"OK",2) != 0);		
		  }						
}			

else if(wifi_AP_STATION_MODE==1)

	{
			
		//设置AP或ADHCO网络	的信道
		do{
				retval=wifi_set_channel(&wifi_strApi.uApAdhocFrame);
				if(retval!=0)
				{			 			  
					return retval;					
				}				  
				while(read_flag == FALSE);
				read_flag = FALSE;      
			}while(strncmp((char *)uCmdRspFrame.uCmdRspBuf,"OK",2) != 0);
				
		//设置AP或ADHCO网络	的密码
		do{
				retval=wifi_set_psk(&wifi_strApi.uJoinFrame);
				if(retval!=0)
				{			 			  
					return retval;					
					}				  
					while(read_flag == FALSE);
					read_flag = FALSE;      
			}while(strncmp((char *)uCmdRspFrame.uCmdRspBuf,"OK",2) != 0);		
		
		//创建AP或ADHCO网络
		wifi_RESET_TIMER1;
		do{
				retval=wifi_creat_apadhoc(&wifi_strApi.uApAdhocFrame);
				if(retval!=0)
				{			 			  
					return retval;					
				}
				while(read_flag == FALSE);
				read_flag = FALSE;  
				if(	wifi_INC_TIMER_1>wifi_PRAR_ERROR_TIMEOUT)return uCmdRspFrame.errorResponse.errorframe.errorCode;
			}while(strncmp((char *)uCmdRspFrame.uCmdRspBuf,"OK",2) != 0);	
		
		//设置本地静态IP							
		do{
				retval=wifi_set_ipstatic(&wifi_strApi.uIpparamFrame);		  //IPstatic 
				if(retval!=0)
				{			 			  
					return retval;					
				}	  
				while(read_flag == FALSE);
				read_flag = FALSE;   
			}while(strncmp((char *)uCmdRspFrame.uCmdRspBuf,"OK",2) != 0);
				
		////AP模式  设置DHCP SERVER参数
	
			do{
					wifi_strApi.uIpparamFrame.ipparamFrameSnd.dhcpMode=1;
					retval=wifi_set_ipdhcp(&wifi_strApi.uIpparamFrame);		  //IPdhcp  sever
					if(retval!=0)
					{			 			  
						return retval;					
					}	  
					while(read_flag == FALSE);
					read_flag = FALSE;  
				}while(strncmp((char *)uCmdRspFrame.uCmdRspBuf,"OK",2) != 0);
	


		//查询连接状态
		do{
				retval=wifi_query_con_status();  //
				if(retval!=0)
				{			 			  
					return retval;					
				}									
				while(read_flag == FALSE);
				read_flag = FALSE;   
			}while(strncmp((char *)uCmdRspFrame.uCmdRspBuf,"OK",2) != 0);
			
			
	 
  }

	//建立本地socket
	do {
		delay_us(5000);
		retval=wifi_open_socket(wifi_LOCAL_PORT,wifi_DEST_PORT,1,wifi_DEST_IP_ADDRESS);  //0:TCP 1:LTCP 2:UDP 3:LUDP  
		while(read_flag == FALSE);
		read_flag = FALSE;
	   }while( strncmp((char *)uCmdRspFrame.socketFrameRcv.socketframe.rspCode,"OK",2) != 0);	
//	  TCP_server_socket_num=uCmdRspFrame.socketFrameRcv.socketOkframe.socketDescriptordata;

	//查询模块的IP配置信息
	retval=wifi_query_ipconfig();
    if(retval!=0)
	{			 			  
	  return retval;					
    }	  
    while(read_flag == FALSE);
    read_flag = FALSE;

	if( strncmp((char *)uCmdRspFrame.ipconfigResponse.ipconfigframe.rspCode,"OK",2) == 0)
	{
	  memcpy((char *)wifi_strApi.macAddress,uCmdRspFrame.ipconfigResponse.ipconfigframe.macAddr,6);		//保存MAC地址
	  memcpy((char *)wifi_strApi.uIpparamFrame.ipparamFrameSnd.ipaddr,uCmdRspFrame.ipconfigResponse.ipconfigframe.ipAddr,4);
	}	
	//wifi_connect_server();
	init_mqtt();	
	return retval; 
}

uint8 wifi_connect_server(void)
{
	strcpy((char *)&wifi_strApi.uDnsFrame.dnsFrameSnd.DomainName,wifi_SERVER);
	do {														
			retval=wifi_query_dns(&wifi_strApi.uDnsFrame);
			if(retval!=0)
			{			 			  
				return retval;					
			}	
			while(read_flag == FALSE);
			read_flag = FALSE;
			//if(	wifi_INC_TIMER_1>10) break;			
	    }while( strncmp((char *)uCmdRspFrame.uCmdRspBuf,"OK",2) != 0);

	  wifi_readAsciiDotAddress(wifi_server_ip,(int8 *)uCmdRspFrame.uCmdRspBuf);

	  do {														
			retval=wifi_open__tcp_socket((char *)wifi_server_ip);
			if(retval!=0)
			{			 			  
				return retval;					
			}	
			while(read_flag == FALSE);
			read_flag = FALSE;
			//if(	wifi_INC_TIMER_1>10) break;			
	    }while( strncmp((char *)uCmdRspFrame.uCmdRspBuf,"OK",2) != 0);
		if(strncmp((char *)uCmdRspFrame.uCmdRspBuf,"OK",2) == 0)
		{
			return uCmdRspFrame.uCmdRspBuf[2];
		}
		else
		{
			return 0x08;
		}
	  
}

