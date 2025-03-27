#include <stdio.h>
#include "I2c.h"

#include "sdkconfig.h"

#include "esp_err.h"
#include "esp_log.h"

#include "driver/i2c_master.h"

#include "../../managed_components/espressif__esp_io_expander/include/esp_io_expander.h"
#include "../../managed_components/espressif__esp_io_expander_ht8574/include/esp_io_expander_ht8574.h"


#define I2C_ADDRESS         ESP_IO_EXPANDER_I2C_HT8574_ADDRESS_000


static const char *TAG = "I2C : ";

static i2c_master_bus_handle_t i2c_bus; //static i2c_master_bus_handle_t i2c_handle = NULL;
static esp_io_expander_handle_t io_expander = NULL;


#define TEST_OUTPUT_PINS    (IO_EXPANDER_PIN_NUM_0 | IO_EXPANDER_PIN_NUM_1)
#define TEST_INPUT_PINS     (IO_EXPANDER_PIN_NUM_2 | IO_EXPANDER_PIN_NUM_3)


void i2c_dev_ht8574_init(void)
{
    esp_err_t ret = esp_io_expander_new_i2c_ht8574(i2c_bus, I2C_ADDRESS, &io_expander);
    if (ESP_OK !=  ret){
        ESP_LOGE(TAG, "HT8574 create returned error");
    }
    else if (ESP_OK ==  ret){
        ESP_LOGI(TAG, "HT8574 create returned succed");
    }
}

void i2c_dev_ht8574_deinit(void)
{
    esp_err_t ret = esp_io_expander_del(io_expander);
    if (ESP_OK !=  ret){
        ESP_LOGE(TAG, "HT8574 delete returned error");
    }
    else if (ESP_OK ==  ret){
        ESP_LOGI(TAG, "HT8574 delete returned succed");
    }
}

i2c_master_bus_handle_t getI2cBus (void){
    return i2c_bus;
}

void pcf8574(void){
    esp_err_t ret;
    /* Test output level function */
    ret = esp_io_expander_set_dir(io_expander, TEST_OUTPUT_PINS, IO_EXPANDER_OUTPUT);

    ESP_LOGI(TAG, "Set level to 1");
    ret = esp_io_expander_set_level(io_expander, TEST_OUTPUT_PINS, 1);




}


void I2cBusInit(void){
    
    ESP_LOGI(TAG, "Initialize I2C bus");
    i2c_master_bus_config_t bus_cfg = {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .i2c_port = ESP_I2C_PORT,
        .sda_io_num = ESP_I2C_SDA,
        .scl_io_num = ESP_I2C_SCL,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };

    if(i2c_new_master_bus(&bus_cfg, &i2c_bus) != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to initialize I2C bus");
    }
}

