
#include	"key.h"
#include	"HumiTemp.h"

#ifndef	__Business_h__
#define	__Business_h__

typedef enum tagBusinessQuueueItemTypeEnum
{
	BusinessQuueueItemType_HumiTemp = 0,
	BusinessQuueueItemType_Key,

	BusinessQuueueItemType_Cnt,
	BusinessQuueueItemType_Invalid = BusinessQuueueItemType_Cnt

} BusinessQuueueItemTypeEnum;


typedef struct tagBusinessQueueItem_t
{
	BusinessQuueueItemTypeEnum		enItemType;

	union
	{
		HumiTempInfo_t		stHumiTemp;
		KeyTypeEnum			enKey;

	} u;

} BusinessQueueItem_t;


void Business_Entry( void *pvParameters );


#endif	/* __BusinessLogic_h__ */


