#ifndef BLUE_LED_H
#define BLUE_LED_H


#define BLINK_GPIO CONFIG_BLINK_GPIO

void configure_led(void);
void blinkBlueLed(void);
void setBlueLed(uint8_t ledStatus);
uint8_t getBlueLed(void);

#endif