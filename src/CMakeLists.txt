# ==============================================================================
# rpi-logger
# Level: /src
# ==============================================================================

target_sources(${MAIN_TARGET} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/driver/Dht11.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/driver/Dht11.h"
)
