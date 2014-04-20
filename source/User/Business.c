
#include	"FreeRTOS.h"
#include	"task.h"
#include	"queue.h"
#include	"list.h"
#include	"portable.h"
#include	"freertosconfig.h"

#include	"Business.h"
#include	"tft.h"

/*------------------------------------------------
             		宏值定义
------------------------------------------------*/
#define   forecolor  0x0000
#define   backcolor  0xffff

void RefurbishRegularScreen(void)
{
		TFT_DrawString(20,40,"电机转动时间:",forecolor,backcolor ,TftFontSize_16x16);
		TFT_DrawString(88,80,"室内温度",forecolor,backcolor,TftFontSize_16x16);
		TFT_DrawString(28,160,"温度上限",forecolor,backcolor,TftFontSize_16x16);
		TFT_DrawString(148,160,"温度下限",forecolor,backcolor,TftFontSize_16x16);
		TFT_DrawString(28,230,"第几路",forecolor,backcolor,TftFontSize_16x16);
		TFT_DrawString(148,230,"当前时间",forecolor,backcolor,TftFontSize_16x16);
}

void RefurbishElectricTime(unsigned int iTime)
{
		unsigned char str[3];
	
		if(iTime >= 100)
		{
			str[0]  =  iTime/100+48;
			str[1]  =  (iTime/10)%10+48;
			str[2]  =  iTime%10+48;
		}
		else if(iTime>=10 && iTime<100)
		{
				str[0]  =  iTime/10+48;
				str[1]  =  iTime%10+48;
		}
		else if(iTime<10)
		{
				str[0]  =  iTime+48;
		}
		
		TFT_DrawString(150,40,str,forecolor,backcolor,TftFontSize_16x16);

}

void RefurbishCurTemp(unsigned int iCurTemp)
{
		unsigned char str[2];
		if(iCurTemp>=10)
		{
				str[0]  =  iCurTemp/10+48;
				str[1]  =  iCurTemp%10+48;
		}
		else
		{
				str[0]  =  iCurTemp+48;
		}

		
		TFT_DrawString(100,120,str,forecolor,backcolor,TftFontSize_16x16);

}

void RefurbishMostHightTemp(unsigned int iHTemp)
{
		unsigned char str[2];
		if(iHTemp>=10)
		{
				str[0]  =  iHTemp/10+48;
				str[1]  =  iHTemp%10+48;
		}
		else
		{
				str[0]  =  iHTemp+48;
		}

		
		TFT_DrawString(28,200,str,forecolor,backcolor,TftFontSize_16x16);

}
void RefurbishMostLowTemp(unsigned int iLTemp)
{
		unsigned char str[2];
		if(iLTemp>=10)
		{
				str[0]  =  iLTemp/10+48;
				str[1]  =  iLTemp%10+48;
		}
		else
		{
				str[0]  =  iLTemp+48;
		}

		
		TFT_DrawString(148,200,str,forecolor,backcolor,TftFontSize_16x16);

}
void RefurbishElectricCurTime(unsigned int iCurTime)
{
	
		unsigned char str[3];
		if(iCurTime >= 100)
		{
			str[0]  =  iCurTime/100+48;
			str[1]  =  (iCurTime/10)%10+48;
			str[2]  =  iCurTime%10+48;
		}
		else if(iCurTime>=10 && iCurTime<100)
		{
				str[0]  =  iCurTime/10+48;
				str[1]  =  iCurTime%10+48;
		}
		else if(iCurTime<10)
		{
				str[0]  =  iCurTime+48;
		}
		
		TFT_DrawString(148,260,str,forecolor,backcolor,TftFontSize_16x16);

}
void RefurbishLine(unsigned int iline)
{
		unsigned char str[2];

		str[0] = iline+48;
		
		TFT_DrawString(28,260,str,forecolor,backcolor,TftFontSize_16x16);

}

void Business_Entry( void *pvParameters )
{

	
	portBASE_TYPE xStatus ;
	
	xQueueHandle			hQueue = (xQueueHandle)pvParameters;

	BusinessQueueItem_t*	pstBusinessQueueItem = NULL;

	


	while( 1 )
	{
		RefurbishRegularScreen();
		xStatus = xQueueReceive( hQueue, &pstBusinessQueueItem, portMAX_DELAY );
		
		if( xStatus == pdPASS )
		{
			if(pstBusinessQueueItem->enItemType == BusinessQuueueItemType_HumiTemp)
			{
				RefurbishCurTemp(pstBusinessQueueItem->u.stHumiTemp.u8Temp);
				/*----还可以在这里刷新湿度----*/
			}
			else if(pstBusinessQueueItem->enItemType == BusinessQuueueItemType_Key)
			{
					/*----按键处理----*/
			}
		}	

		if ( pstBusinessQueueItem != NULL )
		{

			free( pstBusinessQueueItem );
			pstBusinessQueueItem = NULL;
		}
		
	}
	

	



	
}