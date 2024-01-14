# ==============================================================================
# rpi-logger
# Temperature and humidity logger sofware based on the Raspberry Pi.
#
# Top-level CMakeLists file.
# ==============================================================================

cmake_minimum_required(VERSION 3.12)

project(rpi-logger
    VERSION 0.1
    DESCRIPTION "Temperature and humidity logger software based on the Raspberry Pi."
    LANGUAGES C CXX
)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(HOSTED OFF)

set(MAIN_TARGET ${CMAKE_PROJECT_NAME})
add_executable(${MAIN_TARGET})

add_subdirectory(src)
add_subdirectory(vendor)

# Add compile definitions.
if(HOSTED)
    target_compile_definitions(${MAIN_TARGET} PRIVATE "HOSTED=1")
else()
    target_compile_definitions(${MAIN_TARGET} PRIVATE "HOSTED=0")
endif()

# Link libraries.
if(NOT HOSTED)
    target_link_libraries(${MAIN_TARGET} PUBLIC lib::bcm2835)
endif()
target_link_libraries(${MAIN_TARGET} PUBLIC lib::json)
target_link_libraries(${MAIN_TARGET} PUBLIC lib::logging)


# Release packages.
set(RELEASE_DIR "${CMAKE_BINARY_DIR}/release")
install(DIRECTORY DESTINATION ${RELEASE_DIR})

install(TARGETS ${MAIN_TARGET} DESTINATION ${RELEASE_DIR})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/autostart/installStartService.sh DESTINATION ${RELEASE_DIR})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/autostart/removeStartService.sh DESTINATION ${RELEASE_DIR})
