#include <stdio.h>
#include "I2c.h"

#include "sdkconfig.h"

#include "esp_err.h"
#include "esp_log.h"

#include "driver/i2c_master.h"

//#include "../../managed_components/espressif__esp_io_expander/include/esp_io_expander.h"
#include "../../components/io_expander/include/esp_io_expander.h"
//#include "../../managed_components/espressif__esp_io_expander_ht8574/include/esp_io_expander_ht8574.h"
#include "../../components/io_expander_PCF8574/include/esp_io_expander_pcf8574.h"

#define I2C_ADDRESS         ESP_IO_EXPANDER_I2C_PCF8574_ADDRESS_000

static const char *TAG = "I2C : ";

static i2c_master_bus_handle_t i2c_bus; //static i2c_master_bus_handle_t i2c_handle = NULL;


i2c_master_bus_handle_t getI2cBus (void){
    return i2c_bus;
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

