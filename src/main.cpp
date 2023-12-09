#include <iostream>
#include <chrono>
#include <thread>

#include "hal/IGpio.h"
#include "hal/bcm2835/Gpio.h"
#include "hal/hosted/Gpio.h"
#include "driver/IDigitalIo.h"
#include "driver/DigitalIo.h"
#include "driver/DhtBase.h"


int main(void) {
    std::cout << "Hello rpi-logger!" << std::endl;

#if HOSTED
    hal::hosted::Gpio gpio;
#else
    hal::bcm2835::Gpio gpio;
#endif /* HOSTED */
    
    if (!gpio.init()) {
        std::cout << "Failed to init GPIO!" << std::endl;
        return 1;
    }

    DigitalReconfigurableIo pin(gpio, 24);
    DhtBase dht11(pin);
    dht11.poll();


    // DigitalOutput pin(gpio, 24);
    // for (int i = 0; i < 10; i++) {
    //     pin.setHigh();
    //     std::this_thread::sleep_for(std::chrono::milliseconds(500));
    //     pin.setLow();
    //     std::this_thread::sleep_for(std::chrono::milliseconds(500));
    // }

    return 0;
}
