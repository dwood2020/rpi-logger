# ==============================================================================
# rpi-logger
# Level: /src
# ==============================================================================

target_sources(${MAIN_TARGET} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/driver/Dht11.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/driver/Dht11.h"

    "${CMAKE_CURRENT_SOURCE_DIR}/hal/Gpio.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/hal/Pin.h"

    "${CMAKE_CURRENT_SOURCE_DIR}/hal/Bcm2835Pin.cpp"
)

target_include_directories(${MAIN_TARGET} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
)
