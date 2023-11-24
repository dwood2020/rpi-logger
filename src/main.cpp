#include <iostream>
#include <chrono>
#include <thread>
#include "bcm2835.h"
#include "hal/gpio.h"



int main(void) {
    std::cout << "Hello rpi-logger!" << std::endl;

    if (!gpio::init()) {
        std::cout << "Failed to init GPIO!" << std::endl;
        return 1;
    }

    gpio::initOutputPin(24);

    for (int i = 0; i < 10; i++) {
        // pin.setHigh();
        gpio::setPinHigh(24);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        // pin.setLow();
        gpio::setPinLow(24);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    bcm2835_close();
    return 0;
}
