/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
//文件名是dht11.c//正常
#include "dht11.h"


static unsigned char ReadValue(void);



/*数据线输出1*/

static BitStatus DHT11_DATA_Read(void)
{
	
		//GPIO_Init(GPIO_DHT11_PORT,DHT11_DATA,GPIO_MODE_IN_PU_NO_IT);
		return ((BitStatus)GPIO_ReadInputPin(GPIO_DHT11_PORT,DHT11_DATA));
}


#ifdef DHT11

/*读一个字节的数据*/
static unsigned char DHT11_ReadValue(void)
{
	unsigned char count, value = 0, i;
	status = OK; //设定标志为正常状态
	for(i = 8; i > 0; i--)
	{
//高位在先
		value <<= 1;
		count = 0;
//每一位数据前会有一个50us 的低电平时间.等待50us 低电平结束
	while(DHT11_DATA_Read()== 0 && count++ < NUMBER);
	if(count >= NUMBER)
		{
			status = ERROR; //设定错误标志
			return 0; //函数执行过程发生错误就退出函数
		}
  count=0;
	delay_us(8);
//延时30us 后检测数据线是否还是高电平
	if(DHT11_DATA_Read() != 0)
		{
//进入这里表示该位是1
			value++;
//等待剩余(约40us)的高电平结束
			while(DHT11_DATA_Read() != 0 && count++ < NUMBER)
			{
			}
	if(count >= NUMBER)
		{
			status = ERROR; //设定错误标志
			return 0;
		}
		}
	}
return (value);
}


//读温度和湿度函数，读一次的数据,共五字节，读出成功函数返回OK, 错误返回ERROR
 unsigned char DHT11_ReadTempAndHumi(void)
{
	BitStatus m;
	unsigned char i = 0, check_value = 0,count = 0;
	GPIO_Init(GPIO_DHT11_PORT,DHT11_DATA,GPIO_MODE_OUT_PP_HIGH_FAST);
	GPIO_WriteLow(GPIO_DHT11_PORT,DHT11_DATA);
 //	DHT11_DATA_Clear(); //拉低数据线大于18ms 发送开始信号
	Delay_Ms(20);//(19); //需大于18 毫秒	DHT11_Enable();
	//DHT11_DATA_Set();
	//GPIO_Init(GPIO_DHT11_PORT,DHT11_DATA,GPIO_MODE_OUT_PP_HIGH_FAST);
	GPIO_WriteHigh(GPIO_DHT11_PORT,DHT11_DATA);
	delay_us(5);
	GPIO_Init(GPIO_DHT11_PORT,DHT11_DATA,GPIO_MODE_IN_PU_NO_IT);
//	DHT11_DATA_Set(); //释放数据线,用于检测低电平的应答信号
//延时20-40us,等待一段时间后检测应答信号,应答信号是从机拉低数据线80us
	//delay_us(10);
	delay_us(1);
	if(DHT11_DATA_Read()!= 0) //检测应答信号,应答信号是低电平
	{
		//没应答信号  
		delay_us(1);
		return ERROR;
	}
	else
	{
//有应答信号
  count=0;
	while(DHT11_DATA_Read() == 0 && count++ < NUMBER*2); 
		if(count >= NUMBER) //检测计数器是否超过了设定的范围
		{
			//DHT11_DATA_Set();
			return ERROR; //读数据出错,退出函数
		}
	count = 0;
	//DHT11_DATA_Set();//释放数据线
	//GPIO_Init(GPIO_DHT11_PORT,DHT11_DATA,GPIO_MODE_IN_PU_NO_IT);
//应答信号后会有一个80us 的高电平，等待高电平结束
	while(DHT11_DATA_Read() != 0 && count++ < NUMBER);
	if(count >= NUMBER)
		{
		//DHT11_DATA_Set();
		return ERROR; //退出函数
		}
//读出湿.温度值
for(i = 0; i < SIZE; i++)
		{
		value_array[i] = DHT11_ReadValue();
		if(status == ERROR)//调用ReadValue()读数据出错会设定status 为ERROR
			{
				//DHT11_DATA_Set();
				return ERROR;
			}
//读出的最后一个值是校验值不需加上去
		if(i != SIZE - 1)
			{
//读出的五字节数据中的前四字节数据和等于第五字节数据表示成功
		check_value += value_array[i];
			}
		}//end for
//在没用发生函数调用失败时进行校验
	if(check_value == value_array[SIZE - 1])
		{
//将温湿度扩大10 倍方便分离出每一位
		//humi_value = value_array[0] * 10;
	//	temp_value = value_array[2] * 10;
		ts_pranus_MP_pro->Humi_V = value_array[0];
	  ts_pranus_MP_pro->Temp_V = value_array[2];
		//DHT11_DATA_Set();
		GPIO_Init(GPIO_DHT11_PORT,DHT11_DATA,GPIO_MODE_OUT_PP_HIGH_FAST);
		GPIO_WriteHigh(GPIO_DHT11_PORT,DHT11_DATA);
	//	DHT11_Disable();
		return OK; //正确的读出dht11 输出的数据
		}
		else
		{
//校验数据出错
		//DHT11_Disable();

		return ERROR;
		}
	}
}
#endif

#ifdef DHT22

/*读一个字节的数据*/
static unsigned char DHT11_ReadValue(void)
{
	unsigned char count, value = 0, i;
	status = OK; //设定标志为正常状态
	for(i = 8; i > 0; i--)
	{
//高位在先
		value <<= 1;
		count = 0;
//每一位数据前会有一个50us 的低电平时间.等待50us 低电平结束
	while(DHT11_DATA_Read()== 0 && count++ < NUMBER);
	if(count >= NUMBER)
		{
			status = ERROR; //设定错误标志
			return 0; //函数执行过程发生错误就退出函数
		}
  count=0;
	delay_us(8);
//延时30us 后检测数据线是否还是高电平
	if(DHT11_DATA_Read() != 0)
		{
//进入这里表示该位是1
			value++;
//等待剩余(约40us)的高电平结束
			while(DHT11_DATA_Read() != 0 && count++ < NUMBER)
			{
			}
	if(count >= NUMBER)
		{
			status = ERROR; //设定错误标志
			return 0;
		}
		}
	}
return (value);
}


//读温度和湿度函数，读一次的数据,共五字节，读出成功函数返回OK, 错误返回ERROR
 unsigned char DHT11_ReadTempAndHumi(void)
{
	BitStatus m;
	unsigned char i = 0, check_value = 0,count = 0;
	GPIO_Init(GPIO_DHT11_PORT,DHT11_DATA,GPIO_MODE_OUT_PP_HIGH_FAST);
	GPIO_WriteLow(GPIO_DHT11_PORT,DHT11_DATA);
 //	DHT11_DATA_Clear(); //拉低数据线大于18ms 发送开始信号
	Delay_Ms(19); //需大于18 毫秒	DHT11_Enable();
	//DHT11_DATA_Set();
	//GPIO_Init(GPIO_DHT11_PORT,DHT11_DATA,GPIO_MODE_OUT_PP_HIGH_FAST);
	GPIO_WriteHigh(GPIO_DHT11_PORT,DHT11_DATA);
	delay_us(5);
	GPIO_Init(GPIO_DHT11_PORT,DHT11_DATA,GPIO_MODE_IN_PU_NO_IT);
//	DHT11_DATA_Set(); //释放数据线,用于检测低电平的应答信号
//延时20-40us,等待一段时间后检测应答信号,应答信号是从机拉低数据线80us
	//delay_us(10);
	delay_us(1);
	if(DHT11_DATA_Read()!= 0) //检测应答信号,应答信号是低电平
	{
		//没应答信号  
		delay_us(1);
		return ERROR;
	}
	else
	{
//有应答信号
  count=0;
	while(DHT11_DATA_Read() == 0 && count++ < NUMBER*2); 
		if(count >= NUMBER) //检测计数器是否超过了设定的范围
		{
			//DHT11_DATA_Set();
			return ERROR; //读数据出错,退出函数
		}
	count = 0;
	//DHT11_DATA_Set();//释放数据线
	//GPIO_Init(GPIO_DHT11_PORT,DHT11_DATA,GPIO_MODE_IN_PU_NO_IT);
//应答信号后会有一个80us 的高电平，等待高电平结束
	while(DHT11_DATA_Read() != 0 && count++ < NUMBER);
	if(count >= NUMBER)
		{
		//DHT11_DATA_Set();
		return ERROR; //退出函数
		}
//读出湿.温度值
for(i = 0; i < SIZE; i++)
		{
		value_array[i] = DHT11_ReadValue();
		if(status == ERROR)//调用ReadValue()读数据出错会设定status 为ERROR
			{
				//DHT11_DATA_Set();
				return ERROR;
			}
//读出的最后一个值是校验值不需加上去
		if(i != SIZE - 1)
			{
//读出的五字节数据中的前四字节数据和等于第五字节数据表示成功
		check_value += value_array[i];
			}
		}//end for
//在没用发生函数调用失败时进行校验
	if(check_value == value_array[SIZE - 1])
		{
//将温湿度扩大10 倍方便分离出每一位
		//humi_value = value_array[0] * 10;
	//	temp_value = value_array[2] * 10;
		//ts_pranus_MP_pro->Humi_V = value_array[0];
	  //ts_pranus_MP_pro->Temp_V = value_array[2];
		//DHT11_DATA_Set();
		ts_pranus_MP_pro->Humi_V = (value_array[0]*256+value_array[1])/10;  //正常
	  ts_pranus_MP_pro->Temp_V = (value_array[2]*256+value_array[3])/10;   //正常
		//ts_pranus_MP_pro->Humi_V = (value_array[2]*256+value_array[3])/10; //传感器调试
		//ts_pranus_MP_pro->Temp_V = (value_array[0]*256+value_array[1])/10;;//传感器调试
		GPIO_Init(GPIO_DHT11_PORT,DHT11_DATA,GPIO_MODE_OUT_PP_HIGH_FAST);
		GPIO_WriteHigh(GPIO_DHT11_PORT,DHT11_DATA);
	//	DHT11_Disable();
		return OK; //正确的读出dht11 输出的数据
		}
		else
		{
//校验数据出错
		//DHT11_Disable();

		return ERROR;
		}
	}
}
#endif
/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/