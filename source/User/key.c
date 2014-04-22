
#include	"stm32f10x.h"
#include	"key.h"
#include	"Business.h"

#include	"FreeRTOS.h"
#include	"task.h"
#include	"queue.h"
#include	"list.h"
#include	"portable.h"
#include	"freertosconfig.h"


#define	Get_Key1_Up()		(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0))
#define	Get_Key2_Up()		(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1))
#define	Get_Key3_Up()		(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10))
#define	Get_Key4_Up()		(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12))
#define	Get_Key5_Up()		(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9))
#define	Get_Key6_Up()		(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8))
#define	Get_Key7_Up()		(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7))
#define	Get_Key8_Up()		(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6))

void Key_Init( void )
{
	GPIO_InitTypeDef	GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_10 | GPIO_Pin_12 | GPIO_Pin_9 | GPIO_Pin_8 | GPIO_Pin_7 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;

	GPIO_Init( GPIOB, &GPIO_InitStructure );

	return	;
}

KeyTypeEnum Key_Scan( void )
{
	KeyTypeEnum	enKeyType = KeyType_Invalid;

	if( !Get_Key1_Up() )  // 检测是否按下
	{
		delay_ms( 10 );	//去抖

		if( !Get_Key1_Up() )
		{
			while( !Get_Key1_Up() );	//等待按键释放，如果不释放按键一直等待此处不能执行其他程序，长按键不能使用这种程序

			delay_ms( 10 );	//释放按键去抖

			if( Get_Key1_Up() )	//检测完全释放后执行按键操作
			{
				enKeyType = KeyType_1;
			}
		}
	}

	if( !Get_Key2_Up() )  // 检测是否按下
	{
		delay_ms( 10 );	//去抖

		if( !Get_Key2_Up() )
		{
			while( !Get_Key2_Up() );	//等待按键释放，如果不释放按键一直等待此处不能执行其他程序，长按键不能使用这种程序

			delay_ms( 10 );	//释放按键去抖

			if( Get_Key2_Up() )	//检测完全释放后执行按键操作
			{
				enKeyType = KeyType_2;
			}
		}
	}

	if( !Get_Key3_Up() )  // 检测是否按下
	{
		delay_ms( 10 );	//去抖

		if( !Get_Key3_Up() )
		{
			while( !Get_Key3_Up() );	//等待按键释放，如果不释放按键一直等待此处不能执行其他程序，长按键不能使用这种程序

			delay_ms( 10 );	//释放按键去抖

			if( Get_Key3_Up() )	//检测完全释放后执行按键操作
			{
				enKeyType = KeyType_3;
			}
		}
	}

	if( !Get_Key4_Up() )  // 检测是否按下
	{
		delay_ms( 10 );	//去抖

		if( !Get_Key4_Up() )
		{
			while( !Get_Key4_Up() );	//等待按键释放，如果不释放按键一直等待此处不能执行其他程序，长按键不能使用这种程序

			delay_ms( 10 );	//释放按键去抖

			if( Get_Key4_Up() )	//检测完全释放后执行按键操作
			{
				enKeyType = KeyType_4;
			}
		}
	}

	if( !Get_Key5_Up() )  // 检测是否按下
	{
		delay_ms( 10 );	//去抖

		if( !Get_Key5_Up() )
		{
			while( !Get_Key5_Up() );	//等待按键释放，如果不释放按键一直等待此处不能执行其他程序，长按键不能使用这种程序

			delay_ms( 10 );	//释放按键去抖

			if( Get_Key5_Up() )	//检测完全释放后执行按键操作
			{
				enKeyType = KeyType_5;
			}
		}
	}

	if( !Get_Key6_Up() )  // 检测是否按下
	{
		delay_ms( 10 );	//去抖

		if( !Get_Key6_Up() )
		{
			while( !Get_Key6_Up() );	//等待按键释放，如果不释放按键一直等待此处不能执行其他程序，长按键不能使用这种程序

			delay_ms( 10 );	//释放按键去抖

			if( Get_Key6_Up() )	//检测完全释放后执行按键操作
			{
				enKeyType = KeyType_6;
			}
		}
	}

	if( !Get_Key7_Up() )  // 检测是否按下
	{
		delay_ms( 10 );	//去抖

		if( !Get_Key7_Up() )
		{
			while( !Get_Key7_Up() );	//等待按键释放，如果不释放按键一直等待此处不能执行其他程序，长按键不能使用这种程序

			delay_ms( 10 );	//释放按键去抖

			if( Get_Key7_Up() )	//检测完全释放后执行按键操作
			{
				enKeyType = KeyType_7;
			}
		}
	}

	if( !Get_Key8_Up() )  // 检测是否按下
	{
		delay_ms( 10 );	//去抖

		if( !Get_Key8_Up() )
		{
			while( !Get_Key8_Up() );	//等待按键释放，如果不释放按键一直等待此处不能执行其他程序，长按键不能使用这种程序

			delay_ms( 10 );	//释放按键去抖

			if( Get_Key8_Up() )	//检测完全释放后执行按键操作
			{
				enKeyType = KeyType_8;
			}
		}
	}

	return	enKeyType;
}

void Key_Entry( void *pvParameters )
{
	xQueueHandle			xQueue = (xQueueHandle)pvParameters;

	BusinessQueueItem_t*	pstBusinessQueueItem = NULL;

	portTickType	xLastWakeTime = xTaskGetTickCount();

	Key_Init();
	
	while ( 1 )
	{
		KeyTypeEnum	enKeyType = Key_Scan();

		if ( enKeyType != KeyType_Invalid )
		{
			pstBusinessQueueItem = (BusinessQueueItem_t*)malloc( sizeof(BusinessQueueItem_t) );

			if ( pstBusinessQueueItem != NULL )
			{
				pstBusinessQueueItem->enItemType = BusinessQuueueItemType_Key;
				pstBusinessQueueItem->u.enKey = enKeyType;

				xQueueSend( xQueue, &pstBusinessQueueItem, 5000 / portTICK_RATE_MS );
			}
		}
	
		vTaskDelayUntil( &xLastWakeTime, ( 50 / portTICK_RATE_MS ) );
	}

	return	;
}

