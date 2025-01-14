/* Rotor Azimut V1

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_log.h"


#include "led_strip.h"
#include "rtci2c/rtci2c.h"


#include "../components/uartCommand/include/uartCommand.h"

#include "../components/blueLed/include/blueLed.h"

void init(){
    /* Configure the peripheral according to the LED type */
    configure_led();
}

void app_main(void){

    init();

    //UART ECHO Task
    xTaskCreate(echo_task, "uart_echo_task", ECHO_TASK_STACK_SIZE, NULL, 10, NULL);

    // Blink Task
    while (1) {
        blinkBlueLed();    
        vTaskDelay(CONFIG_BLUE_LED_PERIOD / portTICK_PERIOD_MS);
    }
}
