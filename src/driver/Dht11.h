#pragma once
#include <cstdint>
#include <array>
#include "driver/IDigitalIo.h"

/**
 * Driver class. Represents a DHT11 device.
*/
class Dht11 {
private:
    IDigitalReconfigurableIo* pin;
    uint64_t pollingBuffer = 0;

public:
    /**
     * Init a DHT11 device.
     * \param gpioPin The GPIO pin number the device uses as data pin.
     * NOTE: This parameter will change in future when a GPIO abstraction class is written!
    */
    Dht11(IDigitalReconfigurableIo& pin);
    virtual ~Dht11() = default;

    void poll(void);

private:
    void requestData(void);
    bool receiveDeltas(std::array<unsigned long, 41>& buffer);

};
