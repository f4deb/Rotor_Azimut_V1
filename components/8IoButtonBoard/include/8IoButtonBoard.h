#ifndef IO_OUTPUT_BOARD
#define IO_OUTPUT_BOARD

void writeOutPut(int value);
int readInput(void);

void ioButtonBoard_task(void *arg);

#define IO_BUTTUN_BOARD_TASK_SIZE   3072

#endif
