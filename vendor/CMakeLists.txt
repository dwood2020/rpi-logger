# ==============================================================================
# rpi-logger
# Level: /vendor
# ==============================================================================

# bcm2835
set(LIB_BCM2835_TARGET bcm2835)
add_library(${LIB_BCM2835_TARGET} STATIC
    "bcm2835/src/bcm2835.c"
)
target_include_directories(${LIB_BCM2835_TARGET} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/bcm2835/src"
)


# Aliases
add_library(lib::bcm2835 ALIAS ${LIB_BCM2835_TARGET})
