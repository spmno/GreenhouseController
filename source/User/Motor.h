
#ifndef	__Motor_H__
#define	__Motor_H__

void Motor_GPIO_Init( void );

void Delay(int nCount);

// 继电器A置高电平 
void SetRelayA( void );

// 继电器B置高电平 
void SetRelayB( void );

// 继电器A置低电平
void ReSetRelayA( void );

// 继电器B置低电平
void ReSetRelayB( void );

void SetRelay( void );

void ReSetRelay( void );


void Motor_Entry( void *pvParameters );
#endif	/* __Motor_H__ */
