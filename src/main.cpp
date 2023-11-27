#include <iostream>
#include <chrono>
#include <thread>
// #include "driver/Dht11.h"
#include "hal/IGpio.h"
#include "hal/bcm2835/Gpio.h"
#include "driver/IDigitalIo.h"
#include "driver/DigitalIo.h"


int main(void) {
    std::cout << "Hello rpi-logger!" << std::endl;

    hal::bcm2835::Gpio gpio;
    if (!gpio.init()) {
        std::cout << "Failed to init GPIO!" << std::endl;
        return 1;
    }

    // gpio.initOutputPin(24);
    // for (int i = 0; i < 10; i++) {
    //     gpio.setPinHigh(24);
    //     std::this_thread::sleep_for(std::chrono::milliseconds(500));
    //     gpio.setPinLow(24);
    //     std::this_thread::sleep_for(std::chrono::milliseconds(500));
    // }

    DigitalOutput pin(gpio, 24);
    for (int i = 0; i < 10; i++) {
        pin.setHigh();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        pin.setLow();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    // gpio::cleanup();
    return 0;
}
