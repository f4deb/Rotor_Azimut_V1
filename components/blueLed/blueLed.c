#include <stdio.h>
#include "esp_log.h"

#include "../../../../esp-idf/components/esp_driver_gpio/include/driver/gpio.h"

#include "blueLed.h"

static const char *TAG_BLUE_LED = "BLUE_LED";
static uint8_t s_led_state = 0;

void configure_led(void){
    ESP_LOGI(TAG_BLUE_LED, "Example configured to blink GPIO LED!");
    gpio_reset_pin(BLINK_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
}

void blinkBlueLed(void){
    ESP_LOGI(TAG_BLUE_LED, "Turning the LED %s!", s_led_state == true ? "ON" : "OFF");
    /* Toggle the LED state */
    s_led_state = !s_led_state;
    /* Set the GPIO level according to the state (LOW or HIGH)*/
    gpio_set_level(BLINK_GPIO, s_led_state);
}

void setBlueLed(uint8_t ledStatus){
    ESP_LOGI(TAG_BLUE_LED, "Turning the LED %s!", ledStatus == true ? "ON" : "OFF");
    /* Toggle the LED state */
    s_led_state = ledStatus;
    /* Set the GPIO level according to the state (LOW or HIGH)*/
    gpio_set_level(BLINK_GPIO, s_led_state);
}

uint8_t getBlueLed(void){
    ESP_LOGI(TAG_BLUE_LED, "Retourn the LED Status %s!", s_led_state == true ? "ON" : "OFF");
    return s_led_state;
}