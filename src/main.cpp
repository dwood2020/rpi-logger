#include <iostream>
#include <chrono>
#include <thread>
#include "hal/gpio.h"
#include "hal/gpioPin.h"
#include "driver/Dht11.h"


int main(void) {
    std::cout << "Hello rpi-logger!" << std::endl;

    if (!gpio::init()) {
        std::cout << "Failed to init GPIO!" << std::endl;
        return 1;
    }

    gpio::OutputPin pin(12);
    Dht11 dht11(pin);
    dht11.poll();

    // gpio::OutputPin pin(24);
    // for (int i = 0; i < 10; i++) {
    //     pin.setHigh();
    //     std::this_thread::sleep_for(std::chrono::milliseconds(500));
    //     pin.setLow();
    //     std::this_thread::sleep_for(std::chrono::milliseconds(500));
    // }

    gpio::cleanup();
    return 0;
}
