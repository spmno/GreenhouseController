#ifndef _GREENHOUSE_REAL_TIME_CLOCK_H_
#define _GREENHOUSE_REAL_TIME_CLOCK_H_

typedef void (*CLOCK_TASK)();
int Real_Time_Clock_Init();
void Register_Real_Time_Task(CLOCK_TASK);

#endif
