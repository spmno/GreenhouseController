#include "stm32f10x.h"

#define uint unsigned int
#define uchar unsigned char

#define CLOCK 72/8 //时钟=72M

/*------------------------------------------------------------
                         us延时函数 
------------------------------------------------------------*/
void delay_us(unsigned int us)
{
	u8 n;		    
	while(us--)for(n=0;n<CLOCK;n++); 	 
}

/*------------------------------------------------------------
                         ms延时函数
------------------------------------------------------------*/
void delay_ms(unsigned int ms)
{
	while(ms--)delay_us(1000);	 
}

/*------------------------------------------------------------
                      把所有时钟寄存器复位
------------------------------------------------------------*/
void RCC_DeInit(void)
{									   
	RCC->APB2RSTR = 0x00000000;//外设复位			 
	RCC->APB1RSTR = 0x00000000;   	  
  	RCC->AHBENR = 0x00000014;  //flash时钟,闪存时钟使能.DMA时钟关闭	  
  	RCC->APB2ENR = 0x00000000; //外设时钟关闭.			   
  	RCC->APB1ENR = 0x00000000;   
	RCC->CR |= 0x00000001;     //使能内部高速时钟HSION	 															 
	RCC->CFGR &= 0xF8FF0000;   //复位SW[1:0],HPRE[3:0],PPRE1[2:0],PPRE2[2:0],ADCPRE[1:0],MCO[2:0]					 
	RCC->CR &= 0xFEF6FFFF;     //复位HSEON,CSSON,PLLON
	RCC->CR &= 0xFFFBFFFF;     //复位HSEBYP	   	  
	RCC->CFGR &= 0xFF80FFFF;   //复位PLLSRC, PLLXTPRE, PLLMUL[3:0] and USBPRE 
	RCC->CIR = 0x00000000;     //关闭所有中断
}


/*------------------------------------------------------------
                  外部8M,则得到72M的系统时钟
------------------------------------------------------------*/	
void Stm32_Clock_Init(void)
{
	ErrorStatus HSEStartUpStatus; 

	RCC_DeInit();

	RCC_HSEConfig(RCC_HSE_ON);

	HSEStartUpStatus = RCC_WaitForHSEStartUp();
	
	if (HSEStartUpStatus == SUCCESS) {

		RCC_HCLKConfig(RCC_SYSCLK_Div1);

		RCC_PCLK2Config(RCC_HCLK_Div1);

		RCC_PCLK1Config(RCC_HCLK_Div2);

		FLASH_SetLatency(FLASH_Latency_2);

		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

		RCC_PLLCmd(ENABLE);

		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

		while(RCC_GetSYSCLKSource() != 0x08);
	}
}

