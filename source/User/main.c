
#include	"stm32f10x.h"
#include	"sys.h"

int main( void )
{
	Stm32_Clock_Init();//系统时钟设置
	RCC->APB2ENR |= 0x00000001; //开启afio时钟
//	AFIO->MAPR = (0x00FFFFFF & AFIO->MAPR)|0x04000000;          //关闭JTAG 
	RCC->APB2ENR|=0X0000001c;//先使能外设IO PORTa,b,c时钟


	while ( 1 )
	{
		// do something here
	}
	

}
