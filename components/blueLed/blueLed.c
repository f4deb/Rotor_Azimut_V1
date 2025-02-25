#include <stdio.h>
#include "blueLed.h"

#include "sdkconfig.h"

#include "esp_event.h"
#include "esp_log.h"


#include "../../../../esp-idf/components/esp_driver_gpio/include/driver/gpio.h"


static const char *TAG_BLUE_LED = "BLUE_LED";
static uint8_t s_led_state = 0;

uint32_t timeBlink ;
uint32_t ratioBlink;

uint32_t getTimeBlink (void){
    return timeBlink;
}

uint32_t getRatioBlink (void){
    return ratioBlink;
}

void setTimeBlink (uint32_t value){
    timeBlink = value;
}

void setRatioBlink (uint32_t value){
    ratioBlink = value;
}

void configure_led(void){
    ESP_LOGI(TAG_BLUE_LED, "Blue Led configured to blink GPIO LED!");
    gpio_reset_pin(BLUE_LED_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLUE_LED_GPIO, GPIO_MODE_OUTPUT);

    setTimeBlink(CONFIG_BLUE_LED_PERIOD);
    setRatioBlink(CONFIG_BLUE_LED_RATIO);
}

void blinkBlueLed(uint32_t time, uint32_t ratio){
    //ESP_LOGI(TAG_BLUE_LED, "Turning the LED %s!", s_led_state == true ? "ON" : "OFF");
    /* Toggle the LED state */
    s_led_state = !s_led_state;
    /* Set the GPIO level according to the state (LOW or HIGH)*/
    gpio_set_level(BLUE_LED_GPIO, s_led_state);

    if (s_led_state) vTaskDelay(pdMS_TO_TICKS(time * ratio /100));
    else vTaskDelay(pdMS_TO_TICKS(time - (time * ratio /100)));
}

void setBlueLed(uint8_t ledStatus){
    ESP_LOGI(TAG_BLUE_LED, "Turning the LED %s!", ledStatus == true ? "ON" : "OFF");
    /* Toggle the LED state */
    s_led_state = ledStatus;
    /* Set the GPIO level according to the state (LOW or HIGH)*/
    gpio_set_level(BLUE_LED_GPIO, s_led_state);
}

uint8_t getBlueLed(void){
    ESP_LOGI(TAG_BLUE_LED, "Return the LED Status %s!", s_led_state == true ? "ON" : "OFF");
    return s_led_state;
}