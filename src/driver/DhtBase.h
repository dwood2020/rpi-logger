#pragma once
#include <cstdint>
#include <array>
#include <chrono>
#include "driver/IDigitalIo.h"

/**
 * Driver class. Represents a DHT11 device.
*/
class DhtBase {
private:
    IDigitalReconfigurableIo* pin;
    float humidity = 0.0f;
    float temperature = 0.0f;

public:
    /**
     * Init a DHT11 device.
     * \param pin The GPIO pin which the device is connected to.
    */
    DhtBase(IDigitalReconfigurableIo& pin);
    virtual ~DhtBase() = default;

    bool poll(void);
    float getHumidity(void) const;
    float getTemperature(void) const;

private:
    void requestData(void);
    bool waitForLevel(hal::PinLevel level, std::chrono::steady_clock::time_point* timePoint);
    bool receiveDeltas(std::array<unsigned long, 41>& buffer);
    void deltasToBits(const std::array<unsigned long, 41>& deltaBuffer, std::array<unsigned int, 41>& bitBuffer);
    void bitsToBytes(const std::array<unsigned int, 41>& bitBuffer, std::array<uint8_t, 5>& byteBuffer);
    bool doChecksum(const std::array<uint8_t, 5>& byteBuffer);
    void updateHumidity(const std::array<uint8_t, 5>& byteBuffer);
    void updateTemperature(const std::array<uint8_t, 5>& byteBuffer);

};
