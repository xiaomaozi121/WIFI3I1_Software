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
#define	HOST		 		1	   	//����
#define DOORBELLS	 		2	   	//����
#define DOORMAGNETIC 		3	   	//�Ŵ�
#define HOST_PIR	 		4	   	//����������PIR
#define	SWITCH		 		5	   	//���ܲ���
#define	IP_CAMERA	 		6	   	//IP camera
#define	ANTI_LOST	 		7	   	//���߷���
#define	INTELLIGENCE_LED 	8 		//���ܵ���
#define CURTAIN		 		9	   	//Ļ��
#define SUB_EQUIPMENT 		10   	//���豸
#define	WIFI		 		11	   	//WiFi
#define TELECONTROLLER		12


//state
#define	ALL_DEPLOYMENT 		1	   	//ȫ������
#define	HOME_DEPLOYMENT    	2	   	//�ڼҲ���
#define	ALL_DISARM		  	3	   	//ȫ������
#define	HOME_DISARM	    	4	   	//�ڼҳ���
#define	MISOPERATION  		5	   	//�����
#define UNDERVOLTAGE		6		//Ƿѹ	
#define	ALARM				7		//����
#define	STATE				8		//״̬
#define	ERROR				9		//�쳣error
#define	OK					10		//����OK
#define	OPEN				11		//��
#define	CLOSE				12		//��
#define	WIFI_READ			13		//��
#define	WIFI_WRITE			14		//д�����ƣ�
#define	TMIE				15		//ʱ��
#define	LED_TWINKLE			16		//LED��˸
#define	CONFIGURE			17		//����
#define STUDY				18		//ѧϰ
#define	UPDATE				19		//����
#define	WEATHER				20		//����
#define	CUE					21		//��ʾ
#define	SELF_CHECK			22		//�Լ칦��

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
