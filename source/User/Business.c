
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
#define		Redcolor	 0xf800

#define  defaultLestTemp  (18)
#define  defaultMostTemp	(25)	
#define  defaultLestLimitTemp  (0)
#define  defaultMostLimitTemp	(40)	
#define  defaultElectricMachineTime (120)
#define  defaultElectricMachineMostTime (600)
#define  defaultElectricMachineLesastTime (120)
#define  ElectricMachineTimeStep (30)
#define  defaultElectricLine	(1)

typedef enum tagEmCurAdjustItem
{
	Em_Item_LeastTemp = 1,
	Em_Item_MostTemp = 2,
	Em_Item_Count = Em_Item_MostTemp,
	Em_Item_Invilid,

} EmCurAdjustItem;

static   EmCurAdjustItem  m_CurAdjustItem = Em_Item_Invilid; 

static  int m_uiCurLeastTemp = defaultLestTemp;
static  int  m_uiCurMostTemp = defaultMostTemp;
static  int  m_uiElectricMachineTime = defaultElectricMachineTime;
static  int  m_uiElectricLine = defaultElectricLine;




void RefurbishRegularScreen(void)
{
		TFT_DrawString(20,40,"电机转动时间:",forecolor,backcolor ,TftFontSize_16x16);
		TFT_DrawString(88,80,"室内温度",forecolor,backcolor,TftFontSize_16x16);
		TFT_DrawString(28,160,"温度上限",forecolor,backcolor,TftFontSize_16x16);
		TFT_DrawString(148,160,"温度下限",forecolor,backcolor,TftFontSize_16x16);
		TFT_DrawString(28,230,"第几路",forecolor,backcolor,TftFontSize_16x16);
		TFT_DrawString(148,230,"当前时间",forecolor,backcolor,TftFontSize_16x16);
}

void RefurbishElectricTime(int iTime)
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

void RefurbishCurTemp(int iCurTemp)
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

void RefurbishMostHightTemp(int iHTemp)
{

		unsigned char str[3];
		if(iHTemp>=10)
		{
				str[0]  =  iHTemp/10+48;
				str[1]  =  iHTemp%10+48;
		}
		else
		{
				str[0]  =  iHTemp+48;
				str[1]  =  ' ';
		}

		str[2]  =  ' ';
			if(m_CurAdjustItem == Em_Item_MostTemp)
		{
			TFT_DrawString(28,200,str,Redcolor,backcolor,TftFontSize_16x16);
		}
		else
		{
			TFT_DrawString(28,200,str,forecolor,backcolor,TftFontSize_16x16);
		}
		

}
void RefurbishMostLowTemp(int iLTemp)
{
		unsigned char str[3];
		if(iLTemp>=10)
		{
				str[0]  =  iLTemp/10+48;
				str[1]  =  iLTemp%10+48;
		}
		else
		{
				str[0]  =  iLTemp+48;
				str[1]  =  ' ';
		}
		
		str[2]  =  ' ';
		if(m_CurAdjustItem == Em_Item_LeastTemp)
		{
			TFT_DrawString(148,200,str,Redcolor,backcolor,TftFontSize_16x16);
		}
		else
		{
			TFT_DrawString(148,200,str,forecolor,backcolor,TftFontSize_16x16);
		}
	

}

void RefurbishLine(int iline)
{
		unsigned char str[3];

		str[0] = iline+48;
		str[1]  =  ' ';
		str[2]  =  ' ';
		
		TFT_DrawString(28,260,str,forecolor,backcolor,TftFontSize_16x16);

}
void   dealBtnAdd ()
{
	if (m_CurAdjustItem == Em_Item_LeastTemp)
	{
		if(m_uiCurLeastTemp >= m_uiCurMostTemp)
		{
			return;
		}
			m_uiCurLeastTemp++;
		RefurbishMostLowTemp(m_uiCurLeastTemp);
	}
	else if (m_CurAdjustItem == Em_Item_MostTemp)
	{
		if(m_uiCurMostTemp >= defaultMostLimitTemp)
		{
			return;
		}
			m_uiCurMostTemp++;
		RefurbishMostHightTemp(m_uiCurMostTemp);
	}
}

void   dealBtnReduce ()
{
	if (m_CurAdjustItem == Em_Item_LeastTemp)
	{
		if(m_uiCurLeastTemp <= defaultLestLimitTemp)
		{
			return;
		}
		m_uiCurLeastTemp--;
		RefurbishMostLowTemp(m_uiCurLeastTemp);
	}
	else if (m_CurAdjustItem == Em_Item_MostTemp)
	{
		if(m_uiCurMostTemp <= m_uiCurLeastTemp)
		{
			return;
		}
		m_uiCurMostTemp--;
		RefurbishMostHightTemp(m_uiCurMostTemp);
	}
}

void dealBtnElectricMachineTime ()
{
	m_uiElectricMachineTime +=ElectricMachineTimeStep;
	if (m_uiElectricMachineTime > defaultElectricMachineMostTime)
	{
		m_uiElectricMachineTime = defaultElectricMachineLesastTime;
	}	
	RefurbishElectricTime(m_uiElectricMachineTime);
}

void dealBtnSwitchLine()
{
	if (m_uiElectricLine == 1)
	{
		m_uiElectricLine = 2;
	}
	else if (m_uiElectricLine == 2)
	{
		m_uiElectricLine = 1;
	}
	RefurbishLine(m_uiElectricLine);
}

void dealBtnAjustTempUpperLimit()
{
	m_CurAdjustItem = Em_Item_MostTemp;
	RefurbishMostHightTemp(m_uiCurMostTemp);
	RefurbishMostLowTemp(m_uiCurLeastTemp);
}

void dealBtnAjustTempLowerLimit()
{
	m_CurAdjustItem = Em_Item_LeastTemp;
	RefurbishMostHightTemp(m_uiCurMostTemp);
	RefurbishMostLowTemp(m_uiCurLeastTemp);
}

void RefurbishTempBackColor()
{
	m_CurAdjustItem = Em_Item_Invilid;
	RefurbishMostHightTemp(m_uiCurMostTemp);
	RefurbishMostLowTemp(m_uiCurLeastTemp);
}

void Business_Entry( void *pvParameters )
{

	
	portBASE_TYPE xStatus ;
	
	xQueueHandle			hQueue = (xQueueHandle)pvParameters;

	BusinessQueueItem_t*	pstBusinessQueueItem = NULL;

	
		RefurbishRegularScreen();
		RefurbishElectricTime(m_uiElectricMachineTime);
		RefurbishMostHightTemp(m_uiCurMostTemp);
		RefurbishMostLowTemp(m_uiCurLeastTemp);
		RefurbishLine(m_uiElectricLine);

	while( 1 )
	{
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
					switch(pstBusinessQueueItem->u.enKey)
					{
						case KeyType_1:
							dealBtnElectricMachineTime();
							RefurbishTempBackColor();
						break;
						
						case KeyType_2:
							dealBtnAjustTempUpperLimit();
						break;
						
						case KeyType_3:
							dealBtnAjustTempLowerLimit();
						break;
						
						case KeyType_4:
							/*----关机键---*/
							RefurbishTempBackColor();
						break;
						
						case KeyType_5:
							dealBtnSwitchLine();
							RefurbishTempBackColor();
						break;
						
						case KeyType_6:
							/*----调整时间---*/
							RefurbishTempBackColor();
						break;
						
						case KeyType_7:
							dealBtnAdd();
						break;
						
						case KeyType_8:
							dealBtnReduce();
						break;
						
						default:
							
						break;
					}
			}
		}	

		if ( pstBusinessQueueItem != NULL )
		{

			free( pstBusinessQueueItem );
			pstBusinessQueueItem = NULL;
		}
		
	}
	

	



	
}