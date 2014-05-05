
#ifndef	__Motor_H__
#define	__Motor_H__

void Motor_GPIO_Init( void );

void Delay(int nCount);

// 继电器置高电平 
void SetRelay( void );

// 继电器A置低电平
void ReSetRelayA( void );

// 继电器B置低电平
void ReSetRelayB( void );

void Motor_Entry( void *pvParameters );
#endif	/* __Motor_H__ */
