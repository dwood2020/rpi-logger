#include <iostream>
#include <chrono>
#include <thread>

#include "hal/IGpio.h"
#include "hal/bcm2835/Gpio.h"
#include "hal/hosted/Gpio.h"
#include "driver/IDigitalIo.h"
#include "driver/DigitalIo.h"
#include "driver/Dht11.h"
#include "driver/Dht22.h"


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
    Dht22 sensor(pin);
    if (sensor.poll()) {
        std::cout << "Humidity: " << sensor.getHumidity() << " % r.H.\n";
        std::cout << "Temperature: " << sensor.getTemperature() << " °C" << std::endl;
    }
    else {
        std::cout << "Sensor polling failed. Last error: " << static_cast<int>(sensor.getLastError()) << std::endl;
    }


    // DigitalOutput pin(gpio, 24);
    // for (int i = 0; i < 10; i++) {
    //     pin.setHigh();
    //     std::this_thread::sleep_for(std::chrono::milliseconds(500));
    //     pin.setLow();
    //     std::this_thread::sleep_for(std::chrono::milliseconds(500));
    // }

    return 0;
}
