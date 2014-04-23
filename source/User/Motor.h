
#ifndef	__Motor_H__
#define	__Motor_H__

void Motor_GPIO_Init( void );

void SetRelay( void );

void ReSetRelay( void );

void Motor_Entry( void *pvParameters );
#endif	/* __Motor_H__ */
