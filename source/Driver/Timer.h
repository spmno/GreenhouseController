#ifndef	__GREENHOUSE_TIMER_H__
#define	__GREENHOUSE_TIMER_H__

typedef void (*TIMER_TASK)();
int Start_Timer(TIMER_TASK task, int second);
void Stop_Timer();

#endif

