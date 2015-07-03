#ifndef _DEFINE_H_
#define _DEFINE_H_

/*typedef unsigned char	uint8_t
typedef char	int8_t 
typedef unsigned int	uint16_t 
typedef int		int16_t */


/*#define uint8_t	unsigned char
#define int8_t	char
#define uint16_t 	unsigned int
#define int16_t 	int*/

typedef struct 
{
	unsigned char id[4];
	unsigned char date[8];
	unsigned char pards;
	unsigned char type;
	unsigned char length;
	unsigned char date_length;
	unsigned char check_result;
	
} app_comd_analytical;


//pards
#define	APP			 		0	   	//APP
#define	HOST		 		1	   	//主机
#define DOORBELLS	 		2	   	//门铃
#define DOORMAGNETIC 		3	   	//门磁
#define HOST_PIR	 		4	   	//被动红外线PIR
#define	SWITCH		 		5	   	//智能插座
#define	IP_CAMERA	 		6	   	//IP camera
#define	ANTI_LOST	 		7	   	//无线防丢
#define	INTELLIGENCE_LED 	8 		//智能灯泡
#define CURTAIN		 		9	   	//幕帘
#define SUB_EQUIPMENT 		10   	//子设备
#define	WIFI		 		11	   	//WiFi
#define TELECONTROLLER		12


//state
#define	ALL_DEPLOYMENT 		1	   	//全部布防
#define	HOME_DEPLOYMENT    	2	   	//在家布防
#define	ALL_DISARM		  	3	   	//全部撒防
#define	HOME_DISARM	    	4	   	//在家撤防
#define	MISOPERATION  		5	   	//误操作
#define UNDERVOLTAGE		6		//欠压	
#define	ALARM				7		//报警
#define	STATE				8		//状态
#define	ERROR				9		//异常error
#define	OK					10		//正常OK
#define	OPEN				11		//开
#define	CLOSE				12		//关
#define	WIFI_READ			13		//读
#define	WIFI_WRITE			14		//写（控制）
#define	TMIE				15		//时间
#define	LED_TWINKLE			16		//LED闪烁
#define	CONFIGURE			17		//配置
#define STUDY				18		//学习
#define	UPDATE				19		//更新
#define	WEATHER				20		//天气
#define	CUE					21		//提示
#define	SELF_CHECK			22		//自检功能

//pards_num
#define DOORBELLS_NUM 				4
#define DOORMAGNETIC_NUM			8
#define SWITCH_NUM					12
#define ANTI_LOST_NUM				5
#define INTELLIGENCE_LED_NUM		6
#define CURTAIN_NUM					6
#define TELECONTROLLER_NUM			6


//pards_address
#define DOORBELLS_ADDR				0x00
#define DOORMAGNETIC_ADDR			0x14	//20
#define SWITCH_ADDR					0x3c
#define ANTI_LOST_ADDR				0x78
#define INTELLIGENCE_LED_ADDR		0x91
#define CURTAIN_ADDR				0xAF
#define TELECONTROLLER_ADDR			0xCD
#define HOST_PIR_ADDR				0xEB





#endif
