
#include	"stm32f10x.h"

#ifndef	__HumiTemp_H__
#define	__HumiTemp_H__

typedef enum tagHumiTempRsltEnum
{
	HumiTempRslt_Success = 0,
	HumiTempRslt_Failure,

} HumiTempRsltEnum;

typedef struct tagHumiTempInfo_t
{
	u8	u8Humi;
	u8	u8Temp;

} HumiTempInfo_t;


HumiTempRsltEnum HT_GetHumiTemp( HumiTempInfo_t* pstHumiTempInfo );


#endif	/* __HumiTemp_H__ */


