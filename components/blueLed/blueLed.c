#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


#include "esp_log.h"

#include <esp_types.h>

#include "soc/soc_caps.h"



#include "blueLed.h"
#include "../../../../esp-idf/components/esp_driver_gpio/include/driver/gpio.h"



void configure_led(void)
{
    ESP_LOGI(TAG_BLUE_LED, "Example configured to blink GPIO LED!");
    gpio_reset_pin(BLINK_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
}


void blink_led(void)
{
    /* Set the GPIO level according to the state (LOW or HIGH)*/
    gpio_set_level(BLINK_GPIO, 1);
}