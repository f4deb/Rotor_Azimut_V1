#ifndef UART_COMMAND_H
#define UART_COMMAND_H

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "freertos/queue.h"

#define BUF_SIZE (1024)

#define COMMAND_TASK_STACK_SIZE    (CONFIG_COMMAND_TASK_STACK_SIZE)

#define COMMAND_TEST_TXD (CONFIG_COMMAND_UART_TXD)
#define COMMAND_TEST_RXD (CONFIG_COMMAND_UART_RXD)
#define COMMAND_TEST_RTS (UART_PIN_NO_CHANGE)
#define COMMAND_TEST_CTS (UART_PIN_NO_CHANGE)

#define COMMAND_UART_PORT_NUM      (CONFIG_COMMAND_UART_PORT_NUM)
#define COMMAND_UART_BAUD_RATE     (CONFIG_COMMAND_UART_BAUD_RATE)


void command_uart_task(void *arg);

QueueHandle_t getQueueUart2(void);

#endif