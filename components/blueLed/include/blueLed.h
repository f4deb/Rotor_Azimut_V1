#ifndef BLUE_LED_H
#define BLUE_LED_H


#define BLUE_LED_GPIO CONFIG_BLUE_LED_GPIO

void configure_led(void);
void blinkBlueLed(void);
void setBlueLed(uint8_t ledStatus);
uint8_t getBlueLed(void);

#endif