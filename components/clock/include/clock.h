#ifndef CLOCK_H
#define CLOCK_H

#define CLOCK_TASK_STACK_SIZE   3072

void initClock(void);

void clock_task(void *arg);

#endif