
#ifndef	__Motor_H__
#define	__Motor_H__

void Motor_GPIO_Init( void );

// 设置延时周期，单位为ms，如果不调用此函数，延时周期默认1S
void Delay(int nCount);

// 继电器置高电平 
void SetRelay( void );

// 继电器A置低电平
void ReSetRelayA( void );

// 继电器B置低电平
void ReSetRelayB( void );

void Motor_Entry( void *pvParameters );
#endif	/* __Motor_H__ */
