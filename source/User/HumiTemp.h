
#include	"stm32f10x.h"

#ifndef	__HumiTemp_H__
#define	__HumiTemp_H__

typedef struct tagHumiTempInfo_t
{
	u8	u8Humi;
	u8	u8Temp;

} HumiTempInfo_t;

void HumiTemp_Entry( void *pvParameters );

#endif	/* __HumiTemp_H__ */


