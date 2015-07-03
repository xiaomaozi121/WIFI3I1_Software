#ifndef _WIFICONFIG_H_
#define _WIFICONFIG_H_

/*==============================================*/
/**
 * Global Defines
 */
#define wifi_POWER_LEVEL_0		  0
#define wifi_POWER_LEVEL_1		  1
#define wifi_POWER_LEVEL_2		  2
#define wifi_POWER_LEVEL_3		  3


#define wifi_AP_STATION_MODE        1				  //0 station  1 AP	 2 ADHOC

#define wifi_SCAN_SSID			    "TP-LINK_2.4GHz"				   //@ null string ("") scans all ssids
#define wifi_CONNECT_SSID		    "TP-LINK_2.4GHz"			   //@ SSID to join to in 2.4GHz 
#define wifi_SCAN_CHANNEL		    0				              //@ 0 scans all channels	1-11

#define wifi_GET_SCAN_NUM		     3			   //@ 0 get scan result number

#define wifi_PSK				         "lthonway303550"                //"1234567890"			   //@ If we are using WPA2, this is the key
#define wifi_CREAT_CHANNEL		       9
/* Set AP  CONFIG */         	
#define wifi_CREAT_AP_ADHOC_SSID       "WIFI410_UART_TEST" 		  
#define wifi_AP_BRODCAST_ENABLE         0                           //  0: no hidden	 1:hidden

 /* Set IP  CONFIG */
#define wifi_IPDHCP_MODE_ENABLE			0	   			  // station 0:dhcp 1:static
#define wifi_IPSTATIC_IP_ADDRESS			"192.168.1.10"
#define wifi_IPSTATIC_GATEWAY			 "192.168.1.1"	
#define wifi_IPSTATIC_NETMASK			 "255.255.255.0"		
#define wifi_IPSTATIC_DNS1				  "0"
#define wifi_IPSTATIC_DNS2				  "0"

#define wifi_DOMAIN_NAME            "www.lthonway.com"                     //@ set the domain name for which dns is requested
    
#endif
