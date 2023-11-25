#pragma once
#include <cstdint>
#include "hal/gpioPin.h"


/**
 * Driver class. Represents a DHT11 device.
*/
class Dht11 {
private:
    gpio::OutputPin& pin;
    uint64_t pollingBuffer = 0;

public:
    /**
     * Init a DHT11 device.
     * \param gpioPin The GPIO pin number the device uses as data pin.
     * NOTE: This parameter will change in future when a GPIO abstraction class is written!
    */
    Dht11(gpio::OutputPin& pin);
    virtual ~Dht11() = default;

    void poll(void);

private:
    void getData(void);

};
