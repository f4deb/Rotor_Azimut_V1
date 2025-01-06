#ifndef UART_COMMAND_H
#define UART_COMMAND_H

#define ECHO_TASK_STACK_SIZE    (CONFIG_EXAMPLE_TASK_STACK_SIZE)

void echo_task(void *arg);

#endif