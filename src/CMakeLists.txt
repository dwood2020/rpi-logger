# ==============================================================================
# rpi-logger
# Level: /src
# ==============================================================================

target_sources(${MAIN_TARGET} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/driver/Dht11.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/driver/Dht11.h"

    "${CMAKE_CURRENT_SOURCE_DIR}/hal/gpio.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/hal/gpioPin.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/hal/gpioPin.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/hal/bcm2835/bcm2835_gpio.cpp"
)

target_include_directories(${MAIN_TARGET} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
)
