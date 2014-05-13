#ifndef _GREENHOUSE_LIGHT_COUNTER_H_
#define _GREENHOUSE_LIGHT_COUNTER_H_

typedef void (*LIGHT_COUNT_CALLBACK)(); 
int Light_Counter_Init();
void Register_Light_Count_CallBack(LIGHT_COUNT_CALLBACK function);

#endif
