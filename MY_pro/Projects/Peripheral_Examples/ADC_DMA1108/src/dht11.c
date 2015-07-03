/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
//�ļ�����dht11.c//����
#include "dht11.h"


static unsigned char ReadValue(void);



/*���������1*/

static BitStatus DHT11_DATA_Read(void)
{
	
		//GPIO_Init(GPIO_DHT11_PORT,DHT11_DATA,GPIO_MODE_IN_PU_NO_IT);
		return ((BitStatus)GPIO_ReadInputPin(GPIO_DHT11_PORT,DHT11_DATA));
}


#ifdef DHT11

/*��һ���ֽڵ�����*/
static unsigned char DHT11_ReadValue(void)
{
	unsigned char count, value = 0, i;
	status = OK; //�趨��־Ϊ����״̬
	for(i = 8; i > 0; i--)
	{
//��λ����
		value <<= 1;
		count = 0;
//ÿһλ����ǰ����һ��50us �ĵ͵�ƽʱ��.�ȴ�50us �͵�ƽ����
	while(DHT11_DATA_Read()== 0 && count++ < NUMBER);
	if(count >= NUMBER)
		{
			status = ERROR; //�趨�����־
			return 0; //����ִ�й��̷���������˳�����
		}
  count=0;
	delay_us(8);
//��ʱ30us �����������Ƿ��Ǹߵ�ƽ
	if(DHT11_DATA_Read() != 0)
		{
//���������ʾ��λ��1
			value++;
//�ȴ�ʣ��(Լ40us)�ĸߵ�ƽ����
			while(DHT11_DATA_Read() != 0 && count++ < NUMBER)
			{
			}
	if(count >= NUMBER)
		{
			status = ERROR; //�趨�����־
			return 0;
		}
		}
	}
return (value);
}


//���¶Ⱥ�ʪ�Ⱥ�������һ�ε�����,�����ֽڣ������ɹ���������OK, ���󷵻�ERROR
 unsigned char DHT11_ReadTempAndHumi(void)
{
	BitStatus m;
	unsigned char i = 0, check_value = 0,count = 0;
	GPIO_Init(GPIO_DHT11_PORT,DHT11_DATA,GPIO_MODE_OUT_PP_HIGH_FAST);
	GPIO_WriteLow(GPIO_DHT11_PORT,DHT11_DATA);
 //	DHT11_DATA_Clear(); //���������ߴ���18ms ���Ϳ�ʼ�ź�
	Delay_Ms(20);//(19); //�����18 ����	DHT11_Enable();
	//DHT11_DATA_Set();
	//GPIO_Init(GPIO_DHT11_PORT,DHT11_DATA,GPIO_MODE_OUT_PP_HIGH_FAST);
	GPIO_WriteHigh(GPIO_DHT11_PORT,DHT11_DATA);
	delay_us(5);
	GPIO_Init(GPIO_DHT11_PORT,DHT11_DATA,GPIO_MODE_IN_PU_NO_IT);
//	DHT11_DATA_Set(); //�ͷ�������,���ڼ��͵�ƽ��Ӧ���ź�
//��ʱ20-40us,�ȴ�һ��ʱ�����Ӧ���ź�,Ӧ���ź��Ǵӻ�����������80us
	//delay_us(10);
	delay_us(1);
	if(DHT11_DATA_Read()!= 0) //���Ӧ���ź�,Ӧ���ź��ǵ͵�ƽ
	{
		//ûӦ���ź�  
		delay_us(1);
		return ERROR;
	}
	else
	{
//��Ӧ���ź�
  count=0;
	while(DHT11_DATA_Read() == 0 && count++ < NUMBER*2); 
		if(count >= NUMBER) //���������Ƿ񳬹����趨�ķ�Χ
		{
			//DHT11_DATA_Set();
			return ERROR; //�����ݳ���,�˳�����
		}
	count = 0;
	//DHT11_DATA_Set();//�ͷ�������
	//GPIO_Init(GPIO_DHT11_PORT,DHT11_DATA,GPIO_MODE_IN_PU_NO_IT);
//Ӧ���źź����һ��80us �ĸߵ�ƽ���ȴ��ߵ�ƽ����
	while(DHT11_DATA_Read() != 0 && count++ < NUMBER);
	if(count >= NUMBER)
		{
		//DHT11_DATA_Set();
		return ERROR; //�˳�����
		}
//����ʪ.�¶�ֵ
for(i = 0; i < SIZE; i++)
		{
		value_array[i] = DHT11_ReadValue();
		if(status == ERROR)//����ReadValue()�����ݳ�����趨status ΪERROR
			{
				//DHT11_DATA_Set();
				return ERROR;
			}
//���������һ��ֵ��У��ֵ�������ȥ
		if(i != SIZE - 1)
			{
//���������ֽ������е�ǰ���ֽ����ݺ͵��ڵ����ֽ����ݱ�ʾ�ɹ�
		check_value += value_array[i];
			}
		}//end for
//��û�÷�����������ʧ��ʱ����У��
	if(check_value == value_array[SIZE - 1])
		{
//����ʪ������10 ����������ÿһλ
		//humi_value = value_array[0] * 10;
	//	temp_value = value_array[2] * 10;
		ts_pranus_MP_pro->Humi_V = value_array[0];
	  ts_pranus_MP_pro->Temp_V = value_array[2];
		//DHT11_DATA_Set();
		GPIO_Init(GPIO_DHT11_PORT,DHT11_DATA,GPIO_MODE_OUT_PP_HIGH_FAST);
		GPIO_WriteHigh(GPIO_DHT11_PORT,DHT11_DATA);
	//	DHT11_Disable();
		return OK; //��ȷ�Ķ���dht11 ���������
		}
		else
		{
//У�����ݳ���
		//DHT11_Disable();

		return ERROR;
		}
	}
}
#endif

#ifdef DHT22

/*��һ���ֽڵ�����*/
static unsigned char DHT11_ReadValue(void)
{
	unsigned char count, value = 0, i;
	status = OK; //�趨��־Ϊ����״̬
	for(i = 8; i > 0; i--)
	{
//��λ����
		value <<= 1;
		count = 0;
//ÿһλ����ǰ����һ��50us �ĵ͵�ƽʱ��.�ȴ�50us �͵�ƽ����
	while(DHT11_DATA_Read()== 0 && count++ < NUMBER);
	if(count >= NUMBER)
		{
			status = ERROR; //�趨�����־
			return 0; //����ִ�й��̷���������˳�����
		}
  count=0;
	delay_us(8);
//��ʱ30us �����������Ƿ��Ǹߵ�ƽ
	if(DHT11_DATA_Read() != 0)
		{
//���������ʾ��λ��1
			value++;
//�ȴ�ʣ��(Լ40us)�ĸߵ�ƽ����
			while(DHT11_DATA_Read() != 0 && count++ < NUMBER)
			{
			}
	if(count >= NUMBER)
		{
			status = ERROR; //�趨�����־
			return 0;
		}
		}
	}
return (value);
}


//���¶Ⱥ�ʪ�Ⱥ�������һ�ε�����,�����ֽڣ������ɹ���������OK, ���󷵻�ERROR
 unsigned char DHT11_ReadTempAndHumi(void)
{
	BitStatus m;
	unsigned char i = 0, check_value = 0,count = 0;
	GPIO_Init(GPIO_DHT11_PORT,DHT11_DATA,GPIO_MODE_OUT_PP_HIGH_FAST);
	GPIO_WriteLow(GPIO_DHT11_PORT,DHT11_DATA);
 //	DHT11_DATA_Clear(); //���������ߴ���18ms ���Ϳ�ʼ�ź�
	Delay_Ms(19); //�����18 ����	DHT11_Enable();
	//DHT11_DATA_Set();
	//GPIO_Init(GPIO_DHT11_PORT,DHT11_DATA,GPIO_MODE_OUT_PP_HIGH_FAST);
	GPIO_WriteHigh(GPIO_DHT11_PORT,DHT11_DATA);
	delay_us(5);
	GPIO_Init(GPIO_DHT11_PORT,DHT11_DATA,GPIO_MODE_IN_PU_NO_IT);
//	DHT11_DATA_Set(); //�ͷ�������,���ڼ��͵�ƽ��Ӧ���ź�
//��ʱ20-40us,�ȴ�һ��ʱ�����Ӧ���ź�,Ӧ���ź��Ǵӻ�����������80us
	//delay_us(10);
	delay_us(1);
	if(DHT11_DATA_Read()!= 0) //���Ӧ���ź�,Ӧ���ź��ǵ͵�ƽ
	{
		//ûӦ���ź�  
		delay_us(1);
		return ERROR;
	}
	else
	{
//��Ӧ���ź�
  count=0;
	while(DHT11_DATA_Read() == 0 && count++ < NUMBER*2); 
		if(count >= NUMBER) //���������Ƿ񳬹����趨�ķ�Χ
		{
			//DHT11_DATA_Set();
			return ERROR; //�����ݳ���,�˳�����
		}
	count = 0;
	//DHT11_DATA_Set();//�ͷ�������
	//GPIO_Init(GPIO_DHT11_PORT,DHT11_DATA,GPIO_MODE_IN_PU_NO_IT);
//Ӧ���źź����һ��80us �ĸߵ�ƽ���ȴ��ߵ�ƽ����
	while(DHT11_DATA_Read() != 0 && count++ < NUMBER);
	if(count >= NUMBER)
		{
		//DHT11_DATA_Set();
		return ERROR; //�˳�����
		}
//����ʪ.�¶�ֵ
for(i = 0; i < SIZE; i++)
		{
		value_array[i] = DHT11_ReadValue();
		if(status == ERROR)//����ReadValue()�����ݳ�����趨status ΪERROR
			{
				//DHT11_DATA_Set();
				return ERROR;
			}
//���������һ��ֵ��У��ֵ�������ȥ
		if(i != SIZE - 1)
			{
//���������ֽ������е�ǰ���ֽ����ݺ͵��ڵ����ֽ����ݱ�ʾ�ɹ�
		check_value += value_array[i];
			}
		}//end for
//��û�÷�����������ʧ��ʱ����У��
	if(check_value == value_array[SIZE - 1])
		{
//����ʪ������10 ����������ÿһλ
		//humi_value = value_array[0] * 10;
	//	temp_value = value_array[2] * 10;
		//ts_pranus_MP_pro->Humi_V = value_array[0];
	  //ts_pranus_MP_pro->Temp_V = value_array[2];
		//DHT11_DATA_Set();
		ts_pranus_MP_pro->Humi_V = (value_array[0]*256+value_array[1])/10;  //����
	  ts_pranus_MP_pro->Temp_V = (value_array[2]*256+value_array[3])/10;   //����
		//ts_pranus_MP_pro->Humi_V = (value_array[2]*256+value_array[3])/10; //����������
		//ts_pranus_MP_pro->Temp_V = (value_array[0]*256+value_array[1])/10;;//����������
		GPIO_Init(GPIO_DHT11_PORT,DHT11_DATA,GPIO_MODE_OUT_PP_HIGH_FAST);
		GPIO_WriteHigh(GPIO_DHT11_PORT,DHT11_DATA);
	//	DHT11_Disable();
		return OK; //��ȷ�Ķ���dht11 ���������
		}
		else
		{
//У�����ݳ���
		//DHT11_Disable();

		return ERROR;
		}
	}
}
#endif
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/