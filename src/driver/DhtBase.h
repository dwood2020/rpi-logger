#pragma once
#include <cstdint>
#include <array>
#include <chrono>
#include "driver/IDigitalIo.h"


/**
 * DHT11/DHT22 Error conditions.
*/
enum class DhtError : int {
    None = 0,
    LevelTimeout1 = 1,
    LevelTimeout2 = 2,
    LevelTimeout3 = 3,
    LevelTimeout4 = 4,
    LevelTimeout5 = 5,
    ChecksumIncorrect = 6
};

/**
 * DHT11/DHT22 driver base class.
 * Contains all the device read logic except humidity and temperature decoding.
 * As this differs between DHT11 and DHT22 devices, it must be implemented separately.
 * 
 * TODO: Use buffers of length 40!
*/
class DhtBase {
protected:
    IDigitalReconfigurableIo* pin;
    float humidity = 0.0f;
    float temperature = 0.0f;
    DhtError lastError = DhtError::None;

public:
    /**
     * Init a DHT device.
     * \param pin The GPIO pin which the device is connected to.
    */
    DhtBase(IDigitalReconfigurableIo& pin);
    virtual ~DhtBase() = default;

    /**
     * Poll device, i.e. perform a sensor read.
     * \return \c True if successful; \c False if an error occurred.
     * Call \c getLastError() to retrieve the error code in the latter case.
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

    /**
     * \return Last error. Is refreshed on every \c poll() call.
    */
    DhtError getLastError(void) const;

private:
    void requestData(void);
    bool waitForLevel(hal::PinLevel level, std::chrono::steady_clock::time_point* timePoint);
    bool receiveDeltas(std::array<unsigned long, 40>& buffer);
    void deltasToBits(const std::array<unsigned long, 40>& deltaBuffer, std::array<unsigned int, 40>& bitBuffer);
    void bitsToBytes(const std::array<unsigned int, 40>& bitBuffer, std::array<uint8_t, 5>& byteBuffer);
    bool doChecksum(const std::array<uint8_t, 5>& byteBuffer);

    virtual void updateHumidity(const std::array<uint8_t, 5>& byteBuffer) = 0;
    virtual void updateTemperature(const std::array<uint8_t, 5>& byteBuffer) = 0;

};
