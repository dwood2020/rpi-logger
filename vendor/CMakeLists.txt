# ==============================================================================
# rpi-logger
# Level: /vendor
# ==============================================================================

# bcm2835
if (NOT HOSTED)
    set(LIB_BCM2835_TARGET bcm2835)
    add_library(${LIB_BCM2835_TARGET} STATIC
        "bcm2835/src/bcm2835.c"
    )
    target_include_directories(${LIB_BCM2835_TARGET} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/bcm2835/src"
    )
endif()


# nlohmann/json
set(LIB_JSON_TARGET json)
add_library(${LIB_JSON_TARGET} INTERFACE)
target_include_directories(${LIB_JSON_TARGET} INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/json/single_include"
)

# Aliases
if(NOT HOSTED)
    add_library(lib::bcm2835 ALIAS ${LIB_BCM2835_TARGET})
endif()
add_library(lib::json ALIAS ${LIB_JSON_TARGET})
