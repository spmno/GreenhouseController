#include "InterFlash.h"

#define FLASH_PAGE_SIZE    ((uint16_t)0x400) //页大小1K
#define WRITE_START_ADDR   ((uint32_t)0x08009000)//起始地址 
#define WRITE_END_ADDR      ((uint32_t)0x0800C000)//结束地址

static u32 CurrentFlashPosition = WRITE_START_ADDR;

int Inter_Flash_Init()
{
	
	return 0;
}


void Inter_Flash_Write_Data(uint32_t addr , uint8_t *p , uint16_t Byte_Num)  
{  
	uint32_t HalfWord;  
	Byte_Num = Byte_Num/2;  
	FLASH_Unlock();  
	FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);  
	FLASH_ErasePage(addr);  
	while(Byte_Num --)  
	{  
			HalfWord=*(p++);  
			HalfWord|=*(p++)<<8;  
			FLASH_ProgramHalfWord(addr, HalfWord);  
			addr += 2;  
	}  
	FLASH_Lock();  
}  

void Inter_Flash_Write_Temperature(u16 TimeStamp, u16 Temperature)
{
	FLASH_Unlock();  
	FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);  
	FLASH_ErasePage(CurrentFlashPosition);  
	FLASH_ProgramHalfWord(CurrentFlashPosition, TimeStamp);
	CurrentFlashPosition += 2;
	FLASH_ProgramHalfWord(CurrentFlashPosition, Temperature);
	FLASH_Lock();
}
