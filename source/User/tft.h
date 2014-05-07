
#include	"Font.h"

#ifndef __TFT_H__
#define __TFT_H__

// 屏幕驱动类型
#define	TFT_DRIVER_ILI9326			(1)
//#define	TFT_DRIVER_ILI9327			(2)

// 初始化
void TFT_Initialize( void );

// 清屏
void TFT_ClearScreen( unsigned int uiColor );

// 矩形描画
void TFT_DrawRectangle(	unsigned int	uiStartX,
						unsigned int	uiEndX,
						unsigned int	uiStartY,
						unsigned int	uiEndY,
						unsigned int	uiColor	);

// 字符串描画
void TFT_DrawString(	unsigned int	uiOffsetX,
						unsigned int	uiOffsetY,
						unsigned char*	pucString,
						unsigned int	uiForeColor,
						unsigned int	uiBackColor,
						FontSizeEnum	enFontSize	);


#endif

