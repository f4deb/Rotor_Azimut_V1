 #pragma once

 #include <stdint.h>
 #include "esp_err.h"
 #include "driver/i2c_master.h"
 #include "../../../components/io_expander/include/esp_io_expander.h"
 
 #ifdef __cplusplus
 extern "C" {
 #endif
 
 /**
  * @brief Create a GY511 IO expander object
  *
  * @param[in]  i2c_bus    I2C bus handle. Obtained from `i2c_new_master_bus()`
  * @param[in]  dev_addr   I2C device address of chip. Can be `ESP_IO_EXPANDER_I2C_GY511_ADDRESS_XXX`.
  * @param[out] handle_ret Handle to created IO expander object
  *
  * @return
  *      - ESP_OK: Success, otherwise returns ESP_ERR_xxx
  */
 esp_err_t esp_io_expander_new_i2c_gy511(i2c_master_bus_handle_t i2c_bus, uint32_t dev_addr, esp_io_expander_handle_t *handle_ret);
 
 /**
  * @brief I2C address of the gy511
  *
  * The 8-bit address format is as follows:
  *
  *                (Slave Address)
  *     ┌─────────────────┷─────────────────┐
  *  ┌─────┐─────┐─────┐─────┐─────┐─────┐─────┐─────┐
  *  |  0  |  0  |  1  |  1  |  1  |  1  |  0  | R/W |
  *  └─────┘─────┘─────┘─────┘─────┘─────┘─────┘─────┘
  *     └────────┯────────┘     └─────┯──────┘
  *           (Fixed)        (Hareware Selectable)
  *
  * And the 7-bit slave address is the most important data for users.
  * For example, if a chip's A0,A1,A2 are connected to GND, it's 7-bit slave address is 0111000b(0x38).
  * Then users can use `ESP_IO_EXPANDER_I2C_GY511_ADDRESS_000` to init it.
  */
 #define ESP_IO_EXPANDER_I2C_GY511_ADDRESS_000    (0x1E) // magnetometer address

 
 
 #ifdef __cplusplus
 }
 #endif