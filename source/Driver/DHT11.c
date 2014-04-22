
#include	"stm32f10x.h"
#include	"DHT11.h"
#include	"sys.h"

#define	DHT_GPIO_Port				(GPIOB)
#define	DHT_GPIO_Pin				(GPIO_Pin_5)
#define	DHT_GPIO_Speed				(GPIO_Speed_50MHz)

void DHT_Out_Mode( void )
{
	GPIO_InitTypeDef	GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = DHT_GPIO_Pin;
	GPIO_InitStructure.GPIO_Speed = DHT_GPIO_Speed;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;	// 开漏输出

	GPIO_Init( DHT_GPIO_Port, &GPIO_InitStructure );

	return	;
}

void DHT_Input_Mode( void )
{
	GPIO_InitTypeDef	GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = DHT_GPIO_Pin;
	GPIO_InitStructure.GPIO_Speed = DHT_GPIO_Speed;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	// 浮空输入

	GPIO_Init( DHT_GPIO_Port, &GPIO_InitStructure );

	return	;
}

// 向DHT11写入一个读取数据的引导码
void DHT11_WriteStart( void )
{
	DHT_Out_Mode();
	GPIO_SetBits( DHT_GPIO_Port, DHT_GPIO_Pin );
	GPIO_ResetBits( DHT_GPIO_Port, DHT_GPIO_Pin );
	delay_ms( 25 );		// 主机至少拉低18ms
	GPIO_SetBits( DHT_GPIO_Port, DHT_GPIO_Pin );
	delay_us( 30 );		// 主机拉高20-40ms		
}

// 从DHT11中读取到一个字节
u8 DHT11_ReadByte( void )
{
	u8	u8Byte = 0;

	u8	u8Loop = 0;
	u8	u8TimeLen = 0;

	for( u8Loop = 0; u8Loop < 8; ++u8Loop )
	{
		u8Byte <<= 1;

		while( 0 == GPIO_ReadInputDataBit(DHT_GPIO_Port, DHT_GPIO_Pin) );	// 等待变高电平

		while( 1 == GPIO_ReadInputDataBit(DHT_GPIO_Port, DHT_GPIO_Pin) )	// 计算高电平时长
		{
			delay_us(1);
			++u8TimeLen;
		}

		if( u8TimeLen >= 30 )	// 超过30us确认为1
		{
			u8Byte |= 0x01;
		}

		u8TimeLen = 0;
	}

	return	u8Byte;
}

DHT11Rslt DHT11_GetHumiTemp( u8* pu8Humi, u8* pu8Temp )
{
	DHT11Rslt	enRslt = DHT11_Failure;

	u8	u8HumiH = 0;
	u8	u8HumiL = 0;
	u8	u8TempH = 0;
	u8	u8TempL = 0;
	u8	u8CkSum = 0;

	u8	u8Loop = 0;

	for ( ; u8Loop < 5; ++u8Loop )
	{
		DHT11_WriteStart();	// 写入一个读取数据的引导码

		DHT_Input_Mode();	// 设置端口为输入状态

		if ( 0 == GPIO_ReadInputDataBit(DHT_GPIO_Port, DHT_GPIO_Pin) )
		{
			while( 0 == GPIO_ReadInputDataBit(DHT_GPIO_Port, DHT_GPIO_Pin) );	// DHT响应信号40-50us

			while( 1 == GPIO_ReadInputDataBit(DHT_GPIO_Port, DHT_GPIO_Pin) );	// DHT拉高40-50us

			
			u8HumiH = DHT11_ReadByte();	// 湿度整数
			u8HumiL = DHT11_ReadByte();	// 湿度小数
			u8TempH = DHT11_ReadByte();	// 温度整数
			u8TempL = DHT11_ReadByte();	// 温度小数
			u8CkSum = DHT11_ReadByte();	// 校验和

			DHT_Out_Mode();
			GPIO_SetBits( DHT_GPIO_Port, DHT_GPIO_Pin );

			if ( u8HumiH + u8HumiL + u8TempH + u8TempL == u8CkSum )
			{
				enRslt = DHT11_Success;
			}

			break;
		}

		delay_us(100);	// DHT11一次通讯时间最大3ms，主机连续采样间隔建议不小于100ms。
	}

	if ( (DHT11_Success == enRslt) && pu8Humi )
	{
		*pu8Humi = u8HumiH;
	}

	if ( (DHT11_Success == enRslt) && pu8Temp )
	{
		*pu8Temp = u8TempH;
	}

	return	enRslt;
}

