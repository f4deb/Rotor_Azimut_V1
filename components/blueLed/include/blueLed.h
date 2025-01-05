
#define BLINK_GPIO CONFIG_BLINK_GPIO

static uint8_t s_led_state = 0;


static const char *TAG_BLUE_LED = "BLUE_LED";

void configure_led(void);

void blink_led(void);

