# esp-idf component
if(IDF_TARGET)
   idf_component_register(SRCS "lib/sensori2c.c" "lib/LSM303DLHC.c" "../rtci2c/lib/esp-idf.c"
                          INCLUDE_DIRS "include"
                          PRIV_INCLUDE_DIRS "lib" "include/sensori2c"
                          PRIV_REQUIRES "driver" "esp_timer")
   return()
endif()

cmake_minimum_required(VERSION 3.5)
set(project sensori2c)
project(${project} LANGUAGES C VERSION 1.3.0)

add_library(sensori2c STATIC lib/sensori2c.c lib.LSM303DLHC.c lib/linux.c)
target_include_directories(sensori2c PUBLIC include)
target_include_directories(sensori2c PRIVATE lib include/sensori2c)
target_compile_definitions(sensori2c PRIVATE SYS_DEBUG_ENABLE)
install(TARGETS sensori2c LIBRARY DESTINATION lib)
install(DIRECTORY include/sensori2c DESTINATION include)

add_subdirectory(example/linux)
