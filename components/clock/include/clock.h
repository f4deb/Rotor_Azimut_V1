#ifndef CLOCK_H
#define CLOCK_H

/* The following definitions may change, based on the ESP device,
   RTC device configuration, and wiring between them. */
   #define ESP_I2C_PORT I2C_NUM_0
   #define ESP_I2C_SDA  GPIO_NUM_21
   #define ESP_I2C_SCL  GPIO_NUM_22
   #define DEVICE_I2C_ADDRESS 0 /* let the library figure it out */

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

void setClockRefresh(int value);


void initClock(void);

void clock_task(void *arg);

#endif