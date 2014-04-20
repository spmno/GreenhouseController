

#ifndef __TFT_H__
#define __TFT_H__

// 字体大小
typedef enum tagTftFontSizeEnum
{
	TftFontSize_16x16 = 0,

	TftFontSize_Cnt,
	TftFontSize_Invalid = TftFontSize_Cnt,

} TftFontSizeEnum;

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
						TftFontSizeEnum	enFontSize	);


#endif

