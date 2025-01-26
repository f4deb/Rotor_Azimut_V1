/* Rotor Azimut V1

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/uart.h"
#include "driver/gpio.h"

#include "sdkconfig.h"

#include "esp_log.h"
#include "esp_console.h"
#include "esp_vfs_fat.h"

#include "argtable3/argtable3.h"
#include "driver/i2c_master.h"

#include "led_strip.h"
#include "rtci2c/rtci2c.h"

#include "../components/uartCommand/include/uartCommand.h"
#include "../components/blueLed/include/blueLed.h"
#include "../components/clock/include/clock.h"
#include "../components/interface/include/interface.h"

void init(){
    /* Configure the peripheral according to the LED type */
    configure_led();
    
    initClock();
}

void app_main(void){

    init();

    //UART ECHO Task
    xTaskCreate(echo_task, "uart_echo_task", ECHO_TASK_STACK_SIZE, NULL, 10, NULL);

    // CLOCK Task
    xTaskCreate(clock_task, "clock_task", CLOCK_TASK_STACK_SIZE, NULL, 11, NULL);

    // INTERFACE Task
    xTaskCreate(interface_task, "Interface_task", INTERFACE_TASK_STACK_SIZE, NULL, 12, NULL);

    //   Blink Task
    while (1) {
        blinkBlueLed(getTimeBlink(), getRatioBlink());    
    }
}
