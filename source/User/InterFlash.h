#ifndef _GREENHOUSE_INTER_FLASH_H_
#define _GREENHOUSE_INTER_FLASH_H_
#include <stm32f10x.h>

int Inter_Flash_Init();
void Inter_Flash_Write_Data(uint32_t addr , uint8_t *p , uint16_t Byte_Num);
void Inter_Flash_Write_Temperature(u16 TimeStamp, u16 Temperature);

#endif
