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
static struct sensorAGM m;
static int sensorRefreshDelay = CONFIG_SENSOR_PERIOD;



void setSensorRefresh(int value){
    sensorRefreshDelay = value;
}

int getSensorRefresh(void){
    return sensorRefreshDelay;
}

void getMagX(void){
    
}

void initSensor(void){

   
}

void sensor_task(void *arg){
    
}