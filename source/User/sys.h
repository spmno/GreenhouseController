#ifndef __SYS_H
#define __SYS_H	   

//us延时函数 
void delay_us(unsigned int us);
//ms延时函数
void delay_ms(unsigned int ms);
//外部8M,则得到72M的系统时钟	
void Stm32_Clock_Init(void);
#endif
