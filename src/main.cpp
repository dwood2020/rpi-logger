#include <iostream>
#include <chrono>
#include <thread>
#include "bcm2835.h"
#include "hal/Bcm2835Pin.h"


int main(void) {
    std::cout << "Hello rpi-logger!" << std::endl;

    // TODO: Write HAL/wrapper around GPIOs!
    if (!bcm2835_init()) {
        std::cout << "FAILED TO INIT BCM2835!!" << std::endl;
        return 1;
    }

    bcm2835_gpio_fsel(24, BCM2835_GPIO_FSEL_OUTP);

    Bcm2835OutputPin pin(24);

    for (int i = 0; i < 10; i++) {
        pin.setHigh();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        pin.setLow();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    bcm2835_close();
    return 0;
}
