

#ifndef	__DHT11_H__
#define	__DHT11_H__

typedef enum tagDHT11RsltEnum
{
	DHT11_Success = 0,
	DHT11_Failure,

} DHT11Rslt;

DHT11Rslt DHT11_GetHumiTemp( u8* pu8Humi, u8* pu8Temp );


#endif	/* __DHT11_H__ */


