
#include	"FreeRTOS.h"
#include	"task.h"
#include	"queue.h"
#include	"list.h"
#include	"portable.h"
#include	"freertosconfig.h"

#include	"Business.h"
#include	"tft.h"


void BusinessLogic_Entry( void *pvParameters )
{
	xQueueHandle			hQueue = (xQueueHandle)pvParameters;

	BusinessQueueItem_t*	pstBusinessQueueItem = NULL;


	while( 1 )
	{
		xQueueReceive( hQueue, &pstBusinessQueueItem, portMAX_DELAY );

		if ( pstBusinessQueueItem != NULL )
		{

			free( pstBusinessQueueItem );
			pstBusinessQueueItem = NULL;
		}
		
	}
	

	



	
}