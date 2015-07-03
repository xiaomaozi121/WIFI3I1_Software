/*
 * This file is part of libemqtt.
 *
 * libemqtt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libemqtt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with libemqtt.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 *
 * Created by Vicente Ruiz Rodr√≠guez
 * Copyright 2012 Vicente Ruiz Rodr√≠guez <vruiz2.0@gmail.com>. All rights reserved.
 *
 */

#include "libemqtt.h"
//#include "BSP_Driver.h"
#include "userBSP.h"
#include "wifi_uart_api.h"

#include <stdio.h>
#include <string.h>
//#include <unistd.h>




#define RCVBUFSIZE 100
uint8_t packet_buffer[RCVBUFSIZE];

char packet1_buffer[5];
int keepalive = 30;
mqtt_broker_handle_t broker;

unsigned char socket_id;

extern int8   wifi_server_ip[15]; 
uint8_t send_packet(uint8_t socket_info, const void* buf, unsigned int count)
{
	//∑¢ÀÕ ˝æ›
	do{
			retval=wifi_Send_mqtt_data(socket_info,(char *)wifi_server_ip,count,(uint8 *)buf);
			if(retval!=0)
			{			 			  
				return retval;					
			}				  
			while(read_flag == FALSE);
			read_flag = FALSE;      
		}while(strncmp((char *)uCmdRspFrame.uCmdRspBuf,"OK",2) != 0);
		return 0;
}

uint8_t read_packet(void)
{
	uint8_t i;
	uint8_t num;

	if(strncmp((char *)uCmdRspFrame.uCmdRspBuf,"OK",2) == 0)
	{
		num = 0;
		i = 0;
		while(num < 3)
		{
			if(uCmdRspFrame.uCmdRspBuf[i++] == ',')
			{
				num++;
			}
		}
		packet1_buffer[0] = uCmdRspFrame.uCmdRspBuf[i++];
		i++;
		packet1_buffer[1] = uCmdRspFrame.uCmdRspBuf[i++] + 0x30;
		packet1_buffer[2] = uCmdRspFrame.uCmdRspBuf[i++] + 0x30;
		packet1_buffer[3] = uCmdRspFrame.uCmdRspBuf[i++] + 0x30;
		packet1_buffer[4] = uCmdRspFrame.uCmdRspBuf[i++] + 0x30;
		USART_OUT(USART2,packet1_buffer,5);
		return 0;
	}
	return 1;
}

int init_socket(mqtt_broker_handle_t* broker, int keepalive)
{
	int flag = 1;

	socket_id = wifi_connect_server();
	if(socket_id >= 8)
	{
		return -1;
	}
	
	// MQTT stuffs
	mqtt_set_alive(broker, keepalive);
	broker->socket_info = socket_id;
	//broker->send = send_packet;

	return 0;
}

void init_mqtt(void)
{
	mqtt_init(&broker, "client-id1");
	mqtt_init_auth(&broker, "aleph201409", "al2014eph");
	init_socket(&broker, keepalive);

	// >>>>> CONNECT
	mqtt_connect(&broker);
	read_packet();
}


