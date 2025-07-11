#include <stdio.h>
#include <string.h>

#include "sensor.h"
#include "sensorInterface.h"

#include "sdkconfig.h"

#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_log.h"

#include "driver/i2c_master.h"


#include "../sensori2c/include/sensori2c/sensori2c.h"
#include "../uartCommand/include/uartCommand.h"
#include "../I2c/include/I2c.h"

#include "../../../../esp-idf/components/esp_driver_uart/include/driver/uart.h"

#define TAG "SENSOR"

#define SENSOR_LIBRARY_I2C_BUS_INIT 0

i2c_master_bus_handle_t I2cBusSensor;

//static i2c_master_bus_handle_t i2c_bus;
static i2c_lowlevel_config config = {0}; /* ensure initialize to zero */
//static struct sensorAGM m;
static int sensorRefreshDelay = CONFIG_SENSOR_PERIOD;

void gy511_init(){
    ESP_LOGI(TAG, "Initialize I2C bus");
    I2cBusSensor = getI2cBus ();
    config.bus = &I2cBusSensor;
}

void gy511_magneto_init(){



    sensori2c_context *ctx = sensori2c_init(SENSOR_DEVICE_GY511, DEVICE_I2C_ADDRESS, &config);



    /*
    i2c_cmd_handle_t cmd;

    uint8_t data[2] = {0x02, 0x00};

    cmd = i2c_cmd_link_create();
	ESP_ERROR_CHECK(i2c_master_start(cmd));
	ESP_ERROR_CHECK(i2c_master_write_byte(cmd, (MAGNETO_I2C << 1) | I2C_MASTER_WRITE, 1));
	i2c_master_write(cmd, data, sizeof(data), 1);
	ESP_ERROR_CHECK(i2c_master_stop(cmd)); 
	i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_PERIOD_MS);
	i2c_cmd_link_delete(cmd);
    */
}


void setSensorRefresh(int value){
    sensorRefreshDelay = value;
}

int getSensorRefresh(void){
    return sensorRefreshDelay;
}

void getMagX(void){
    
}

void initSensor(void){
    gy511_init();
    gy511_magneto_init();

   
}

void sensor_task(void *arg){
    
}