# ==============================================================================
# rpi-logger
# Level: /src
# ==============================================================================

target_sources(${MAIN_TARGET} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/hal/IGpio.h"

    "${CMAKE_CURRENT_SOURCE_DIR}/driver/IDigitalIo.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/driver/DigitalIo.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/driver/DigitalIo.h"

    "${CMAKE_CURRENT_SOURCE_DIR}/driver/DhtBase.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/driver/DhtBase.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/driver/Dht11.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/driver/Dht11.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/driver/Dht22.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/driver/Dht22.h"

    "${CMAKE_CURRENT_SOURCE_DIR}/application/csv/Column.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/application/csv/Column.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/application/csv/Writer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/application/csv/Writer.h"

    "${CMAKE_CURRENT_SOURCE_DIR}/application/App.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/application/App.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/application/AppConfig.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/application/AppConfig.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/application/Log.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/application/Log.h"
)

# Further platform sources will be added here.
if(NOT HOSTED)
    target_sources(${MAIN_TARGET} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/hal/bcm2835/Gpio.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/hal/bcm2835/Gpio.h"
    )
else()
    target_sources(${MAIN_TARGET} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/hal/hosted/Gpio.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/hal/hosted/Gpio.h"
    )
endif()

target_include_directories(${MAIN_TARGET} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
)
