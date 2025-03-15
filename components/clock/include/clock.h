#ifndef CLOCK_H
#define CLOCK_H

#define CLOCK_TASK_STACK_SIZE   3072

void setSeconde(int);
void setMinute(int value);
void setHour(int value);
void setDay(int);
void setDayOfWeek(int);
void setMonth(int);
void setYear(int);

void setTime(int select, int value);

void initClock(void);

void clock_task(void *arg);

#endif