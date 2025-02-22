#ifndef UART_COMMAND_H
#define UART_COMMAND_H

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "freertos/queue.h"

#define BUF_SIZE (1024)

#define COMMAND_TASK_STACK_SIZE    (CONFIG_COMMAND_TASK_STACK_SIZE)

void command_uart_task(void *arg);

QueueHandle_t getQueueUart2(void);

#endif