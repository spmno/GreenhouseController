
#ifndef	__KEY_H__
#define	__KEY_H__

typedef enum tagKeyTypeEnum
{
	KeyType_1 = 0,
	KeyType_2,
	KeyType_3,
	KeyType_4,
	KeyType_5,
	KeyType_6,
	KeyType_7,
	KeyType_8,

	KeyType_Cnt,
	KeyType_Invalid = KeyType_Cnt,

} KeyTypeEnum;



void Key_Init( void );
KeyTypeEnum Key_Scan( void );

#endif	/* __KEY_H__ */
