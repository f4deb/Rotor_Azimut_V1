idf_component_register(SRCS "I2c.c" "i2cInterface.c"
                    INCLUDE_DIRS "include"
                    "$ENV{IDF_PATH}/components/esp_driver_i2c/include"
                    "$ENV{IDF_PATH}/components/log/include"
                    "$ENV{IDF_PATH}/components/esp_event/include"
                    )
