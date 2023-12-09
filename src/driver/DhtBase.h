#pragma once
#include <cstdint>
#include <array>
#include <chrono>
#include "driver/IDigitalIo.h"

/**
 * DHT11/DHT22 driver base class.
 * Contains all the device read logic except humidity and temperature decoding.
 * As this differs between DHT11 and DHT22 devices, it must be implemented separately.
*/
class DhtBase {
protected:
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

    /**
     * Poll device, i.e. perform a sensor read.
     * \return \c True if successful; \c False if an error occurred.
    */
    bool poll(void);

    /**
     * \return Last read relative humidity value in %.
    */
    float getHumidity(void) const;

    /**
     * \return Last read temperature value in °C.
    */
    float getTemperature(void) const;

private:
    void requestData(void);
    bool waitForLevel(hal::PinLevel level, std::chrono::steady_clock::time_point* timePoint);
    bool receiveDeltas(std::array<unsigned long, 41>& buffer);
    void deltasToBits(const std::array<unsigned long, 41>& deltaBuffer, std::array<unsigned int, 41>& bitBuffer);
    void bitsToBytes(const std::array<unsigned int, 41>& bitBuffer, std::array<uint8_t, 5>& byteBuffer);
    bool doChecksum(const std::array<uint8_t, 5>& byteBuffer);

    virtual void updateHumidity(const std::array<uint8_t, 5>& byteBuffer) = 0;
    virtual void updateTemperature(const std::array<uint8_t, 5>& byteBuffer) = 0;

};
