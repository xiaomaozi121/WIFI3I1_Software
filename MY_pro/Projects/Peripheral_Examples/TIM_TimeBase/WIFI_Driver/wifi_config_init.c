//;****************************************************
//;Company :  WIFI WIRELESS
//;File Name : wifi_CONFIG_INIT.c
//;Author :    Junhua
//;Create Data : 2014-03-15
//;Last Modified : 
//;Description : WIFI413 WIFI UART  DRIVER
//;Version : 1.0.1
//;****************************************************
#include "wifi_global.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/**
 * Global Variables
 */
/*=============================================================================*/
/**
 * @fn			int8 * wifi_bytes4ToAsciiDotAddr(uint8 *hexAddr, uint8 *strBuf)
 * @brief		Convert an uint8 4-Byte array to  . notation network address
 * @param[in]		uint8 *hexAddress, Address to convert
 * @param[in]		uint8 *strBuf, String Pointer to hold the Concatenated String
 * @param[out]		none
 * @return		char * destString, pointer to the string with the data
 */
/*=============================================================================*/
int8 * wifi_bytes4ToAsciiDotAddr(uint8 *hexAddr,uint8 *strBuf)
{
  uint8			i;							// loop counter
  uint8			ii;							// loop counter
  int8			cBuf[4];						// character buffer
  int8			*destString;

  strBuf[0] = 0;								// make  strcat think the array is empty
  for (i = 0; i < 3; i++){							// we are assuming IPV4, so 4 bytes
    // This will take care of the first 3 bytes
    // zero out the character buffer since we don't know how long the string will be
    for(ii = 0; ii < sizeof(cBuf); ii++) { cBuf[ii] = 0; }	
    sprintf ((char *)cBuf, "%d", (unsigned int)(((uint8*)hexAddr)[i]));
    destString =(int8 *) strcat((char *)strBuf,(char *) cBuf);
    destString = (int8 *)strcat((char *)strBuf,(char *) ".");
  }
  // take care of the last entry outside the loop, there is no . after the last octet
  // zero out the character buffer since we don't know how long the string will be
  for(ii = 0; ii < sizeof(cBuf); ii++) { cBuf[ii] = 0; }		
  sprintf ((char *)cBuf, "%d", (unsigned int)(((uint8*)hexAddr)[i]));
  destString = (int8 *) strcat((char *)strBuf,(char *) cBuf);
  return destString;
}
/*=============================================================================*/
/**
 * @fn			void wifi_asciiDotAddressTo4Bytes(uint8 *hexAddr, int8 *asciiDotAddress)
 * @brief		Convert an ASCII . notation network address to 4-byte hex address
 * @param[in]		int8 *asciiDotFormatAddress, source address to convert, must be a null terminated string
 * @param[out]		uint8 *hexAddr,	Output value is passed back in the 4-byte Hex Address
 * @return		none
 */
/*=============================================================================*/
void wifi_asciiDotAddressTo4Bytes(uint8 *hexAddr, int8 *asciiDotAddress, uint8 length)
{
  uint8			i;
  // loop counter
  uint8			cBufPos;													
  // which char in the ASCII representation
  uint8			byteNum;													
  // which byte in the 32BitHexAddress
   uint8			cBuf[4];													
  // character buffer

  byteNum = 0;
  cBufPos = 0;
  for (i = 0; i < length; i++) {
    // this will take care of the first 3 octets
    if (asciiDotAddress[i] == '.') 
		{										
	    // we are at the end of the address octet
      cBuf[cBufPos] = 0;													
      // terminate the string
      cBufPos = 0;														
      // reset for the next char
      hexAddr[byteNum++] = (uint8)atoi((char *)cBuf);								
      // convert the strint to an integer
    }
    else {
      cBuf[cBufPos++] = asciiDotAddress[i];
    }
  }
  // handle the last octet													
  // // we are at the end of the string with no .
  cBuf[cBufPos] = 0x00;														
  // terminate the string
  hexAddr[byteNum] = (uint8)atoi((char *)cBuf);

  // convert the strint to an integer
}


/*=============================================================================*/
/**
 * @fn			void wifi_asciiDotAddressTo4Bytes(uint8 *hexAddr, int8 *asciiDotAddress)
 * @brief		Convert an ASCII . notation network address to 4-byte hex address
 * @param[in]		int8 *asciiDotFormatAddress, source address to convert, must be a null terminated string
 * @param[out]		uint8 *hexAddr,	Output value is passed back in the 4-byte Hex Address
 * @return		none
 */
/*=============================================================================*/
void wifi_readAsciiDotAddress(int8 *WriteAddr, int8 *ReadAsciiDotAddress)
{
  uint8			i,j;
  // loop counter
  int8			cBufPos;													
  i = 0;
  j = 0;
  while('=' != ReadAsciiDotAddress[j++]);
  cBufPos = ReadAsciiDotAddress[j];
  while('\r' != cBufPos)
  {
  	WriteAddr[i] = ReadAsciiDotAddress[j + i];
	i++;
	cBufPos = ReadAsciiDotAddress[j + i];
  }
  WriteAddr[i] = 0;
}

/*=============================================================================*/
/**
 * @fn          int16 wifi_init_struct(rsi_api *ptrStrApi)
 * @brief       Initialize the global parameter structure
 * @param[in]   rsi_api *ptrStrApi, pointer to the global parameter structure
 * @param[out]  none
 * @return      status
 *	        0  = SUCCESS
 * @description	This function is used to initialize the global parameter structure with parameters
 * 		used to configure the Wi-Fi module.
 * 
 * @prerequisite rsi_sys_init should be done successfully. 		
 */
/*=============================================================================*/
uint16 wifi_init_struct(wifi_api *ptrStrApi)
{
	//ptrStrApi->powerMode =wifi_POWER_LEVEL_0;
	
	/* Scan Parameters */
   	/*ptrStrApi->uScanFrame.scanFrameSnd.channel = wifi_SCAN_CHANNEL;
	strcpy((char *)&ptrStrApi->uScanFrame.scanFrameSnd.ssid,wifi_SCAN_SSID);*/
	
	/* Join Parameters */ //securityType ;
	/*strcpy((char *)&ptrStrApi->uJoinFrame.joinFrameSnd.psk,  wifi_PSK);
	strcpy((char *)&ptrStrApi->uJoinFrame.joinFrameSnd.ssid, wifi_CONNECT_SSID);*/

	/* Ap Parameters */
	/*ptrStrApi->uApAdhocFrame.apAdhocFrameSnd.ibssApChannel = wifi_CREAT_CHANNEL;
	strcpy((char *)&ptrStrApi->uApAdhocFrame.apAdhocFrameSnd.ssid, wifi_CREAT_AP_ADHOC_SSID);
	ptrStrApi->uApAdhocFrame.apAdhocFrameSnd.apMode = wifi_AP_BRODCAST_ENABLE;*/

	/* IP Parameters */
	ptrStrApi->uIpparamFrame.ipparamFrameSnd.dhcpMode = wifi_IPDHCP_MODE_ENABLE;
	wifi_asciiDotAddressTo4Bytes((uint8 *)&ptrStrApi->uIpparamFrame.ipparamFrameSnd.ipaddr, (int8 *)wifi_IPSTATIC_IP_ADDRESS,sizeof(wifi_IPSTATIC_IP_ADDRESS));
	wifi_asciiDotAddressTo4Bytes((uint8 *)&ptrStrApi->uIpparamFrame.ipparamFrameSnd.netmask, (int8 *)wifi_IPSTATIC_NETMASK,sizeof(wifi_IPSTATIC_NETMASK));
	wifi_asciiDotAddressTo4Bytes((uint8 *)&ptrStrApi->uIpparamFrame.ipparamFrameSnd.gateway, (int8 *)wifi_IPSTATIC_GATEWAY,sizeof(wifi_IPSTATIC_GATEWAY));
	wifi_asciiDotAddressTo4Bytes((uint8 *)&ptrStrApi->uIpparamFrame.ipparamFrameSnd.dnssvr1, (int8 *)wifi_IPSTATIC_DNS1,sizeof(wifi_IPSTATIC_DNS1));
	wifi_asciiDotAddressTo4Bytes((uint8 *)&ptrStrApi->uIpparamFrame.ipparamFrameSnd.dnssvr2, (int8 *)wifi_IPSTATIC_DNS2,sizeof(wifi_IPSTATIC_DNS2));

	return 0;
}
