#pragma once


/**
 * Driver class. Represents a DHT11 device.
*/
class Dht11 {
public:
    /**
     * Init a DHT11 device.
     * \param gpioPin The GPIO pin number the device uses as data pin.
     * NOTE: This parameter will change in future when a GPIO abstraction class is written!
    */
    Dht11(int gpioPin);
    virtual ~Dht11() = default;
};
