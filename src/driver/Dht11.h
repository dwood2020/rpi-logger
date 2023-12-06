#pragma once
#include <cstdint>
#include <array>
#include <chrono>
#include "driver/IDigitalIo.h"

/**
 * Driver class. Represents a DHT11 device.
*/
class Dht11 {
private:
    IDigitalReconfigurableIo* pin;

public:
    /**
     * Init a DHT11 device.
     * \param pin The GPIO pin which the device is connected to.
    */
    Dht11(IDigitalReconfigurableIo& pin);
    virtual ~Dht11() = default;

    void poll(void);

private:
    void requestData(void);
    bool receiveDeltas(std::array<unsigned long, 41>& buffer);
    void deltasToBits(const std::array<unsigned long, 41>& deltaBuffer, std::array<unsigned int, 41>& bitBuffer);
    void bitsToBytes(const std::array<unsigned int, 41>& bitBuffer, std::array<uint8_t, 5>& byteBuffer);
    bool doChecksum(const std::array<uint8_t, 5>& byteBuffer);

    bool waitForLevel(hal::PinLevel level, std::chrono::steady_clock::time_point* timePoint);

};
