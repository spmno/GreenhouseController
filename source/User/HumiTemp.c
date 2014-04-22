
#include	"stm32f10x.h"
#include	"HumiTemp.h"
#include	"Business.h"
#include	"Dht11.h"

#include	"FreeRTOS.h"
#include	"task.h"
#include	"queue.h"
#include	"list.h"
#include	"portable.h"
#include	"freertosconfig.h"


void HumiTemp_Entry( void *pvParameters )
{
	xQueueHandle			xQueue = (xQueueHandle)pvParameters;

	BusinessQueueItem_t*	pstBusinessQueueItem = NULL;

	portTickType	xLastWakeTime = xTaskGetTickCount();

	while ( 1 )
	{
		u8	u8Humi = 0;
		u8	u8Temp = 0;
		
		if ( DHT11_Success == DHT11_GetHumiTemp(&u8Humi, &u8Temp) )
		{
			pstBusinessQueueItem = (BusinessQueueItem_t*)malloc( sizeof(BusinessQueueItem_t) );

			if ( pstBusinessQueueItem != NULL )
			{
				pstBusinessQueueItem->enItemType = BusinessQuueueItemType_HumiTemp;
				pstBusinessQueueItem->u.stHumiTemp.u8Humi = u8Humi;
				pstBusinessQueueItem->u.stHumiTemp.u8Temp = u8Temp;

				xQueueSend( xQueue, &pstBusinessQueueItem, 5000 / portTICK_RATE_MS );
			}
		}
	
		vTaskDelayUntil( &xLastWakeTime, ( 5000 / portTICK_RATE_MS ) );
	}

	return	;
}

