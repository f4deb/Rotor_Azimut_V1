/* Main */

#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/uart.h"
#include "driver/gpio.h"

#include "sdkconfig.h"

#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_dev.h"
#include "esp_lcd_panel_ssd1306.h"

#include "esp_err.h"
#include "esp_log.h"
#include "esp_console.h"
#include "esp_vfs_fat.h"

#include "esp_lvgl_port.h"

#include "argtable3/argtable3.h"
#include "driver/i2c_master.h"

#include "led_strip.h"
#include "rtci2c/rtci2c.h"
#include "lvgl.h"


#include "../components/uartCommand/include/uartCommand.h"
#include "../components/blueLed/include/blueLed.h"
#include "../components/clock/include/clock.h"
#include "../components/interface/include/interface.h"
#include "../components/charUtils/include/charUtils.h"
#include "../components/Oled/include/Oled.h"
#include "../components/I2c/include/I2c.h"
#include "../components/8IoButtonBoard/include/8IoButtonBoard.h"


static const char *TAG_MAIN = "Main : ";

void init(){

    /* Configure the peripheral according to the LED type */
    configure_led();

    I2cBusInit();  
    i2c_dev_pcf8574_init();

    oled();

    initClock();

    //UART COMMAND Task
    xTaskCreate(command_uart_task, 
                "uart_command_task", 
                COMMAND_TASK_STACK_SIZE, 
                NULL,
                1, 
                NULL);

    // CLOCK Task
    xTaskCreate(clock_task,
                "clock_task",
                CLOCK_TASK_STACK_SIZE,
                NULL, 
                4, 
                NULL);

    // IOBUTTONBOARD TASK
    xTaskCreate(ioButtonBoard_task,
                "IO BUTTON BOARD task",
                IO_BUTTUN_BOARD_TASK_SIZE,
                NULL, 
                3, 
                NULL);               
              
    // INTERFACE TASK
    xTaskCreate(interface_task,
                "interface_task",
                INTERFACE_TASK_STACK_SIZE,
                NULL,
                2,
                NULL);
}

void app_main(void){
    init();
    
    //   Blink Task
    while (1) {
        blinkBlueLed(getTimeBlink(), getRatioBlink());    
    }

}