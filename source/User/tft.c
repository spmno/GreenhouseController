/*------------------------------------------------
                包含头文件
------------------------------------------------*/
#include "stm32f10x.h"
#include"Tft.h"
/*-----------------------------------------------------------------------
                           液晶端口定义
-----------------------------------------------------------------------*/
#define	TFT_WR	(1<<11)  //写数据控制线		PA11
#define	TFT_RS	(1<<12)  //数据/命令选择端口	PA12
#define	TFT_CS	(1<<13)  //片选端口  	    PB13
#define	TFT_RST	(1<<14)  //硬复位			PB14
//彩屏RD引脚接3.3V 悬空或者接5V可能导致不能正常工作


#define TFT_RS_SET(x)   GPIOA->ODR=(GPIOA->ODR&~TFT_RS)|(x ? TFT_RS:0)
#define TFT_CS_SET(x)   GPIOB->ODR=(GPIOB->ODR&~TFT_CS)|(x ? TFT_CS:0)													     
#define TFT_RST_SET(x)  GPIOB->ODR=(GPIOB->ODR&~TFT_RST)|(x ? TFT_RST:0)	
#define TFT_WR_SET(x)   GPIOA->ODR=(GPIOA->ODR&~TFT_WR)|(x ? TFT_WR:0)	
 

#define DATAOUT(x) GPIOA->ODR=(GPIOA->ODR&0xffffff00)|(x&0xff);//定义8位数据操作端口  
//unsigned char code pic[];
#define X_MAX 240
#define Y_MAX 400


/*------------------------------------------------
                写指令函数
------------------------------------------------*/
void LCD_Write_Command(unsigned char u)
{
  	
	TFT_CS_SET(0); 
	TFT_RS_SET(0);

	DATAOUT(u);
	TFT_WR_SET(0); 
	TFT_WR_SET(1);


	TFT_CS_SET(1); 
}

/*------------------------------------------------
                 写数据函数
------------------------------------------------*/
void LCD_Write_Data(unsigned char u)
{	
	TFT_CS_SET(0); 
	TFT_RS_SET(1);

	DATAOUT(u);
	TFT_WR_SET(0); 
	TFT_WR_SET(1);


	TFT_CS_SET(1); 
}

/*------------------------------------------------
              写16位数据函数
------------------------------------------------*/
void  Write_Data_U16(unsigned int y)
{
	unsigned char m,n;
	m=y>>8;
	n=y;
	LCD_Write_Data(m);
    LCD_Write_Data(n);

}

void WriteCom(unsigned char a,unsigned char b)
{
LCD_Write_Command(a);
LCD_Write_Command(b);
}

void WriteData(unsigned char a,unsigned char b)
{
LCD_Write_Data(a);
LCD_Write_Data(b);
}

/*------------------------------------------------
函数名称:LCD_DefineDispWindow
功    能:定义显示窗体
参    数:x0:  窗体中X坐标中较小者
	 x1:  窗体中X坐标中较大者
	 y0:  窗体中Y坐标中较小者
	 y1:  窗体中Y坐标中较大者 
返 回 值:无
------------------------------------------------*/
static void ILI9327_SetPos(unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1)
{
	WriteCom(0x00,0x2A);
	WriteData(x0>>8,x0);
	WriteData(x1>>8,x1);
	WriteCom(0x00,0x2B);
	WriteData(y0>>8,y0);
	WriteData(y1>>8,y1);
	WriteCom(0x00,0x2C);
}

static void ILI9326_SetPos(unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1)
{
	WriteCom(0x02,0x10);WriteData(x0>>8,x0);
	WriteCom(0x02,0x11);WriteData(x1>>8,x1);
	WriteCom(0x02,0x12);WriteData(y0>>8,y0);
	WriteCom(0x02,0x13);WriteData(y1>>8,y1);

	WriteCom(0x02,0x00);WriteData(0X00,0X00);
	WriteCom(0x02,0x01);WriteData(0X00,0X00);
	WriteCom(0x02,0x02);
}

static void LCD_SetPos(unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1)
{
	#ifdef TFT_DRIVER_ILI9327
		ILI9327_SetPos( x0, x1, y0, y1 );
	#else /* TFT_DRIVER_ILI9326 */
		ILI9326_SetPos( x0, x1, y0, y1 );
	#endif
}

/*------------------------------------------------
             		清屏函数
------------------------------------------------*/
void TFT_ClearScreen( unsigned int uiColor )
{
 unsigned int i,j;
 LCD_SetPos(0,X_MAX-1,0,Y_MAX-1);//
 for (i=0;i<Y_MAX;i++)
	{
	
	   for (j=0;j<X_MAX;j++)
	       Write_Data_U16(uiColor);

	}
}

/*------------------------------------------------
                写字符串函数
------------------------------------------------*/
void TFT_DrawString(	unsigned int	uiOffsetX,
						unsigned int	uiOffsetY,
						unsigned char*	pucString,
						unsigned int	uiForeColor,
						unsigned int	uiBackColor,
						FontSizeEnum	enFontSize	)
{
	int				iLoop1 = 0;
	int				iLoop2 = 0;
	FontMaskInfo_t	stFontMaskInfo = { 0 };

	if ( !pucString )
	{
		return	;
	}

	while ( *pucString )
	{
		if ( FontRslt_Success == Font_GetMask(enFontSize, pucString, &stFontMaskInfo) )
		{

			LCD_SetPos( uiOffsetX,  uiOffsetX + stFontMaskInfo.ucWidth - 1, uiOffsetY, uiOffsetY + stFontMaskInfo.ucHeight - 1 );

			uiOffsetX += stFontMaskInfo.ucWidth;

			for ( iLoop1 = 0; iLoop1 < stFontMaskInfo.ucSize; ++iLoop1 )
			{		
				for ( iLoop2 = 0; iLoop2 < 8; ++iLoop2 )
				{
					if ( 0x80 == ((stFontMaskInfo.pucMask[iLoop1] << iLoop2) & 0x80) )
					{
						Write_Data_U16( uiForeColor );
					}
					else
					{
						Write_Data_U16( uiBackColor );
					}
				}
			}
		}

		if ( *pucString < 0x80 )
		{
			++pucString;
		}
		else
		{
			pucString += 2;
		}
	}

	return	;
}
/*------------------------------------------------
              指定区域显示指定RGB颜色
------------------------------------------------*/
void Show_RGB (unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1,unsigned int Color)
{
	unsigned int i,j;
	LCD_SetPos(x0,x1,y0,y1);
	for (i=y0;i<=y1;i++)
	{
	   for (j=x0;j<=x1;j++)
	       Write_Data_U16(Color);
	}
}

void TFT_DrawRectangle(	unsigned int	uiStartX,
						unsigned int	uiEndX,
						unsigned int	uiStartY,
						unsigned int	uiEndY,
						unsigned int	uiColor	)
{
	unsigned int	x, y;
	
	LCD_SetPos( uiStartX, uiEndX, uiStartY, uiEndY );

	for ( x = uiStartX; x <= uiEndX; ++x )
	{
		for ( y = uiStartY; y <= uiEndY; ++y )
		{
			Write_Data_U16( uiColor );
		}
	}

	return	;
}

/*------------------------------------------------
                显示彩条
------------------------------------------------*/
void show_colour_bar (void)//8条色彩

{   unsigned char GAP=50;
	int V,H;
	LCD_SetPos(0,X_MAX-1,0,Y_MAX-1);

	for(H=0;H<X_MAX;H++)
	{
		for(V=0;V<GAP*1;V++)
		Write_Data_U16(0xf800);
	}

	for(H=0;H<X_MAX;H++)
	{
		for(V=GAP*1;V<GAP*2;V++)
		Write_Data_U16(0x07e0);
	}

	for(H=0;H<X_MAX;H++)
	{
		for(V=GAP*2;V<GAP*3;V++)
		Write_Data_U16(0x001f);
	}

	for(H=0;H<X_MAX;H++)
	{
		for(V=GAP*3;V<GAP*4;V++)
		Write_Data_U16(0xffe0);
	}

	for(H=0;H<X_MAX;H++)
	{
		for(V=GAP*4;V<GAP*5;V++)
		Write_Data_U16(0xf81f);
	}

	for(H=0;H<X_MAX;H++)
	{
		for(V=GAP*5;V<GAP*6;V++)
		Write_Data_U16(0x07ff);
	}

	for(H=0;H<X_MAX;H++)
	{
		for(V=GAP*6;V<GAP*7;V++)
		Write_Data_U16(0xffff);
	}

	for(H=0;H<X_MAX;H++)
	{
		for(V=GAP*7;V<GAP*8;V++)
		Write_Data_U16(0x0000);
	}

}
/*------------------------------------------------
             显示图片函数
------------------------------------------------*/
/*void show_photo(void)
{
	unsigned char j;
	unsigned int i;
	unsigned long s=0;

	LCD_SetPos(0,240,0,320);//320x240

	for (i=0;i<75;i++)
	{
	for (j=0;j<240;j++)
	Write_Data_U16(0xffff);
		
	}

	for (i=0;i<170;i++)
	{
	for (j=0;j<55;j++)
		Write_Data_U16(0xffff);

		for (j=0;j<130;j++)
		Write_Data_U16(pic[s++],pic[s++]);
		
		for (j=0;j<55;j++)
		Write_Data_U16(0xffff);
	}

    for (i=0;i<75;i++)
	{
	for (j=0;j<240;j++)
	Write_Data_U16(0xffff);
		
	}
}
*/


/*------------------------------------------------
                延时函数
------------------------------------------------*/
void delayms(unsigned int count)
{
    int i,j;                                                                                
    for(i=0;i<count;i++)                                                                    
       {
	     for(j=0;j<260;j++);
       }                                                                                     
}



/*------------------------------------------------
             	液晶初始化代码
------------------------------------------------*/

static void ILI9326_Initialize( void )
{
	TFT_RST_SET(0);
	delayms(20);
	TFT_RST_SET(1);
	delayms(200);
	// Synchronization after reset
	WriteCom(0x06,0x06);WriteData(0X00,0X00);
	delayms(100);
	WriteCom(0x00,0x07);WriteData(0X00,0X01);
	delayms(5);
	WriteCom(0x01,0x10);WriteData(0X00,0X01);
	delayms(5);
	WriteCom(0x01,0x00);WriteData(0X17,0XB0);
	WriteCom(0x01,0x01);WriteData(0X01,0X47);
	WriteCom(0x01,0x02);WriteData(0X01,0X9D);
	WriteCom(0x01,0x03);WriteData(0X36,0X00);
	WriteCom(0x02,0x81);WriteData(0X00,0X10);
	delayms(5);
	WriteCom(0x01,0x02);WriteData(0X01,0XBD);
	delayms(5);
	WriteCom(0x00,0x00);WriteData(0X00,0X00);
	WriteCom(0x00,0x01);WriteData(0X01,0X00);
	WriteCom(0x00,0x02);WriteData(0X01,0X00);
	WriteCom(0x00,0x03);WriteData(0X10,0XB0);
	WriteCom(0x00,0x06);WriteData(0X00,0X00);
	WriteCom(0x00,0x08);WriteData(0X02,0X02);

	WriteCom(0x00,0x09);WriteData(0X00,0X01);
	WriteCom(0x00,0x0B);WriteData(0X00,0X10);
	WriteCom(0x00,0x0C);WriteData(0X00,0X00);
	WriteCom(0x00,0x0F);WriteData(0X00,0X00);
	WriteCom(0x00,0x07);WriteData(0X00,0X01);

	WriteCom(0x00,0x10);WriteData(0X00,0X11);
	WriteCom(0x00,0x11);WriteData(0X03,0X01);
	WriteCom(0x00,0x12);WriteData(0X03,0X00);
	WriteCom(0x00,0x20);WriteData(0X02,0X1E);
	WriteCom(0x00,0x21);WriteData(0X02,0X02);

	WriteCom(0x00,0x90);WriteData(0X08,0X00);
	WriteCom(0x00,0x92);WriteData(0X00,0X00);
	WriteCom(0x01,0x00);WriteData(0X12,0XB0);
	delayms(10);
	WriteCom(0x01,0x01);WriteData(0X01,0X47);
	delayms(10);
	WriteCom(0x01,0x02);WriteData(0X01,0XBE);
	delayms(10);
	WriteCom(0x01,0x03);WriteData(0X2B,0X00);
	delayms(10);
	WriteCom(0x01,0x07);WriteData(0X00,0X00);
	delayms(10);
	WriteCom(0x01,0x10);WriteData(0X00,0X01);
	delayms(10);
	WriteCom(0x02,0x10);WriteData(0X00,0X00);
	WriteCom(0x02,0x11);WriteData(0X00,0XEF);
	WriteCom(0x02,0x12);WriteData(0X00,0X00);
	WriteCom(0x02,0x13);WriteData(0X01,0X8F);
	WriteCom(0x02,0x00);WriteData(0X00,0X00);

	WriteCom(0x02,0x01);WriteData(0X00,0X00);
	WriteCom(0x02,0x80);WriteData(0X00,0X00);
	WriteCom(0x02,0x81);WriteData(0X00,0X07);
	WriteCom(0x02,0x82);WriteData(0X00,0X00);
	delayms(10);
	WriteCom(0x03,0x00);WriteData(0X01,0X01);
	WriteCom(0x03,0x01);WriteData(0X09,0X29);
	WriteCom(0x03,0x02);WriteData(0X0F,0X2C);
	WriteCom(0x03,0x03);WriteData(0X2C,0X0F);
	WriteCom(0x03,0x04);WriteData(0X29,0X09);
	WriteCom(0x03,0x05);WriteData(0X01,0X01);
	WriteCom(0x03,0x06);WriteData(0X19,0X04);
	WriteCom(0x03,0x07);WriteData(0X04,0X19);
	WriteCom(0x03,0x08);WriteData(0X06,0X05);

	WriteCom(0x03,0x09);WriteData(0X04,0X03);
	WriteCom(0x03,0x0A);WriteData(0X0E,0X06);
	WriteCom(0x03,0x0B);WriteData(0X0E,0X00);
	WriteCom(0x03,0x0C);WriteData(0X00,0X0E);
	WriteCom(0x03,0x0D);WriteData(0X06,0X0E);
	WriteCom(0x03,0x0E);WriteData(0X03,0X04);
	WriteCom(0x03,0x0F);WriteData(0X05,0X06);
	WriteCom(0x04,0x00);WriteData(0X35,0X00);
	WriteCom(0x04,0x01);WriteData(0X00,0X01);

	WriteCom(0x04,0x04);WriteData(0X00,0X00);
	WriteCom(0x05,0x00);WriteData(0X00,0X00);
	WriteCom(0x05,0x01);WriteData(0X00,0X00);
	WriteCom(0x05,0x02);WriteData(0X00,0X00);
	WriteCom(0x05,0x03);WriteData(0X00,0X00);
	WriteCom(0x05,0x04);WriteData(0X00,0X00);
	WriteCom(0x05,0x05);WriteData(0X00,0X00);
	WriteCom(0x06,0x00);WriteData(0X00,0X00);
	WriteCom(0x06,0x06);WriteData(0X00,0X00);
	WriteCom(0x06,0xF0);WriteData(0X00,0X00);
	WriteCom(0x07,0xF0);WriteData(0X54,0X20);
	WriteCom(0x07,0xF3);WriteData(0X28,0X0F);
	WriteCom(0x07,0xF4);WriteData(0X00,0X22);
	WriteCom(0x07,0xF5);WriteData(0X00,0X01);
	WriteCom(0x07,0xF0);WriteData(0X00,0X00);
	WriteCom(0x00,0x07);WriteData(0X01,0X73);
	delayms(5);
	WriteCom(0x00,0x07);WriteData(0X00,0X61);
	delayms(5);
	WriteCom(0x00,0x07);WriteData(0X01,0X73);
	delayms(500);
	WriteCom(0x02,0x02);		
}

static void ILI9327_Initialize( void )
{
	// VCI=2.80V
	//************* Reset LCD Driver ****************//
	TFT_RST_SET(1);
	delayms(1); // delaymsms 1ms
	TFT_RST_SET(0);
	delayms(10); // delaymsms 10ms // This delaymsms time is necessary
	TFT_RST_SET(1);
	delayms(50); // delaymsms 50 ms
	 // Synchronization after reset//////////
	////////////////////////////////////////////
	LCD_Write_Command(0x11); //Exit Sleep
	delayms(100);
	LCD_Write_Command(0xD1);
	LCD_Write_Data (0x00);
	LCD_Write_Data (0x71);
	LCD_Write_Data (0x19);
	LCD_Write_Command(0xD0);
	LCD_Write_Data (0x07);
	LCD_Write_Data (0x01);
	LCD_Write_Data (0x08);
	LCD_Write_Command(0x36);
	LCD_Write_Data (0x48);
	LCD_Write_Command(0x3A);
	LCD_Write_Data (0x05);
	LCD_Write_Command(0xC1);
	LCD_Write_Data (0x10);
	LCD_Write_Data (0x10);
	LCD_Write_Data (0x02);
	LCD_Write_Data (0x02);
	LCD_Write_Command(0xC0); //Set Default Gamma
	LCD_Write_Data (0x00);
	LCD_Write_Data (0x35);
	LCD_Write_Data (0x00);
	LCD_Write_Data (0x00);
	LCD_Write_Data (0x01);
	LCD_Write_Data (0x02);
	LCD_Write_Command(0xC5); //Set frame rate
	LCD_Write_Data (0x04);
	LCD_Write_Command(0xD2); //power setting
	LCD_Write_Data (0x01);
	LCD_Write_Data (0x44);
	LCD_Write_Command(0xC8); //Set Gamma
	LCD_Write_Data (0x04);
	LCD_Write_Data (0x67);
	LCD_Write_Data (0x35);
	LCD_Write_Data (0x04);
	LCD_Write_Data (0x08);
	LCD_Write_Data (0x06);
	LCD_Write_Data (0x24);
	LCD_Write_Data (0x01);
	LCD_Write_Data (0x37);
	LCD_Write_Data (0x40);
	LCD_Write_Data (0x03);
	LCD_Write_Data (0x10);
	LCD_Write_Data (0x08);
	LCD_Write_Data (0x80);
	LCD_Write_Data (0x00);
	LCD_Write_Command(0x2A); 
	LCD_Write_Data (0x00);
	LCD_Write_Data (0x00);
	LCD_Write_Data (X_MAX>>8);
	LCD_Write_Data (X_MAX);
	LCD_Write_Command(0x2B); 
	LCD_Write_Data (0x00);
	LCD_Write_Data (0x00);
	LCD_Write_Data (Y_MAX>>8);
	LCD_Write_Data (Y_MAX);
	LCD_Write_Command(0x29); //display on      
	LCD_Write_Command(0x2C); //display on
	delayms(100);
}

void TFT_Initialize(void)
{ 
  RCC->APB2ENR|=0X0000001C;//先使能外设IO PORTA,B,C时钟
	
	GPIOA->CRL=0X33333333; //PA0-7 推挽输出
	GPIOA->CRH=0X33333333; //PA8-15 推挽输出
	//GPIOA->ODR|=0X00FF;//全部输出高
	GPIOB->CRH=0X33333333; //PB8-15 推挽输出
	//GPIOB->ODR|=0X00FF;//全部输出高
	/*GPIOB->CRL&=0X000FFFFF;//PB5-7 推挽输出
	GPIOB->CRL|=0X33300000;
	GPIOB->CRH&=0XFFFFFFF0;//PB8   推挽输出
	GPIOB->CRH|=0X00000003;
	GPIOB->ODR|=0X01E0;//5-8 输出高

	GPIOC->CRL&=0XFF00FFFF;//PC4,5 推挽输出
	GPIOC->CRL|=0X00330000;
	GPIOC->ODR|=0X0030;//4,5 输出高	 */

	#ifdef TFT_DRIVER_ILI9327
		ILI9327_Initialize();
	#else /* TFT_DRIVER_ILI9326 */
		ILI9326_Initialize();
	#endif

	return	;
}

