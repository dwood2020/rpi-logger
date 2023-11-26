# ==============================================================================
# rpi-logger
# Temperature and humidity logger sofware based on the Raspberry Pi.
#
# Top-level CMakeLists file.
# ==============================================================================

cmake_minimum_required(VERSION 3.12)

project(rpi-logger
    VERSION 0.1
    DESCRIPTION "Temperature and humidity logger sofware based on the Raspberry Pi."
    LANGUAGES C CXX
)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(MAIN_TARGET ${CMAKE_PROJECT_NAME})
add_executable(${MAIN_TARGET})

add_subdirectory(src)
add_subdirectory(vendor)

target_link_libraries(${MAIN_TARGET} PUBLIC lib::bcm2835)