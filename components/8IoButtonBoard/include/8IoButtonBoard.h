#ifndef IO_OUTPUT_BOARD
#define IO_OUTPUT_BOARD

void i2c_dev_pcf8574_init(void);

void i2c_dev_pcf8574_deinit(void);

void writeOutPutPin(int pin, int value);

void write8OutPutPin(int value);   

esp_err_t readInputPin(int pin);

void ioButtonBoard_task(void *arg);

#define IO_BUTTUN_BOARD_TASK_SIZE   3072

#endif
