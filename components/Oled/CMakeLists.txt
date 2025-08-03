idf_component_register(SRCS "Oled.c" "../I2c/I2c.c" "OledInterface.c"
                    INCLUDE_DIRS "include"
                    "../../components/I2c/include"
                    
                    "/home/f4deb/RotorV1A/managed_components/espressif__esp_lvgl_port/include"
                    "/home/f4deb/RotorV1A/managed_components/lvgl__lvgl"

                    "$ENV{IDF_PATH}/components/esp_driver_i2c/include"
                    "$ENV{IDF_PATH}/components/nvs_flash/include"
                    "$ENV{IDF_PATH}/components/log/include"
                    "$ENV{IDF_PATH}/components/esp_event/include"
                    "$ENV{IDF_PATH}/components/esp_partition/include"
                    "$ENV{IDF_PATH}/components/esp_driver_spi/include"
                    "$ENV{IDF_PATH}/components/esp_lcd/include"
                    )