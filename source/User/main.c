
#include	"stm32f10x.h"
#include	"sys.h"
#include	"Business.h"
#include	"FreeRTOS.h"
#include	"task.h"
#include	"queue.h"
#include	"list.h"
#include	"portable.h"
#include	"freertosconfig.h"
#include	"tft.h"
#include	"key.h"
#include	"Motor.h"
#include	"HumiTemp.h"

int main( void )
{
	xQueueHandle xQueue;
	
	Stm32_Clock_Init();//系统时钟设置
	
	TFT_Initialize();
	Motor_GPIO_Init();
	
	xQueue = xQueueCreate( 10, sizeof( long ) );
	if( xQueue != NULL )
	{
		xTaskCreate( Business_Entry, "Business_Entry", 1000, (void*)xQueue, 1, NULL );
		xTaskCreate( Key_Entry, "Key_Entry", 1000, (void*)xQueue , 2 ,NULL );
		xTaskCreate( HumiTemp_Entry, "HumiTemp_Entry", 1000, (void*)xQueue, 3, NULL );
	}

	vTaskStartScheduler();
	
	while ( 1 )
	{

	}
	

}
