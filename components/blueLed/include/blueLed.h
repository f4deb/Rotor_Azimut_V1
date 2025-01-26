#ifndef BLUE_LED_H
#define BLUE_LED_H


#define BLUE_LED_GPIO CONFIG_BLUE_LED_GPIO

uint32_t getTimeBlink (void);
uint32_t getRatioBlink (void);
void setTimeBlink (uint32_t value);
void setRatioBlink (uint32_t value);

void configure_led(void);
void blinkBlueLed(uint32_t time, uint32_t ratio);
void setBlueLed(uint8_t ledStatus);
uint8_t getBlueLed(void);

#endif