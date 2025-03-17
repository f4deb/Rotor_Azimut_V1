#ifndef CLOCK_H
#define CLOCK_H

#define CLOCK_TASK_STACK_SIZE   3072

void setSeconde(int value);
void setMinute(int value);
void setHour(int value);
void setDay(int value);
void setDayOfWeek(int value);
void setMonth(int value);
void setYear(int value);

int getSeconde(void);
int getMinute(void);
int getHour(void);
int getDay(void);
int getDayOfWeek(void);
int getMonth(void);
int getYear(void);

void readClock(void);

void getTime(void);
void setTime(int select, int value);

void initClock(void);

void clock_task(void *arg);

#endif