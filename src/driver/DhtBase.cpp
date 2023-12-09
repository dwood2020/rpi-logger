#include "DhtBase.h"
#include <thread>
#include <chrono>
#include <array>

#include <iostream>
#include <cstdio>


DhtBase::DhtBase(IDigitalReconfigurableIo& pin): pin(&pin) {
}

bool DhtBase::poll(void) {
    requestData();

    std::array<unsigned long, 41> deltaBuffer;
    if (!receiveDeltas(deltaBuffer)) {
        return false;
    }

    std::array<unsigned int, 41> bitBuffer;
    deltasToBits(deltaBuffer, bitBuffer);

    std::array<uint8_t, 5> bytes;
    bitsToBytes(bitBuffer, bytes);

    if (!doChecksum(bytes)) {
        lastError = DhtError::ChecksumIncorrect;
        return false;
    }

    // DHT-11 humidity is just byte 0, ignore byte 1.
    // DHT-22 uses both bytes.
    // Temperature DHT-11: Just byte 2? Or Byte 2 (whole) and 3 (fraction)?
    // Temperature DHT-22: Uses Byte 2's uppermost bit to indicate sign.
    updateHumidity(bytes);
    updateTemperature(bytes);

    lastError = DhtError::None;
    return true;

}

float DhtBase::getHumidity(void) const {
    return humidity;
}

float DhtBase::getTemperature(void) const {
    return temperature;
}

DhtError DhtBase::getLastError(void) const {
    return lastError;
}

void DhtBase::requestData(void) {
    // Configure as output pin and pull down for 0.8-29ms.
    pin->configureAsOutput();
    pin->setLow();
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    pin->configureAsInput();
}

bool DhtBase::waitForLevel(hal::PinLevel level, std::chrono::steady_clock::time_point* timePoint) {
    bool success = false;
    for (unsigned int i = 0; i < 10000; i++) {
        if (pin->getLevel() == level) {
            success = true;
            break;
        }
    }
    if (timePoint != nullptr) {
        *timePoint = std::chrono::steady_clock::now();
    }
    return success;
}

bool DhtBase::receiveDeltas(std::array<unsigned long, 41>& buffer) {
    std::chrono::steady_clock::time_point tStart;
    std::chrono::steady_clock::time_point tEnd;

    // Wait until sensor pulls line low.
    if (!waitForLevel(hal::PinLevel::Low, nullptr)) {
        lastError = DhtError::LevelTimeout1;
        return false;
    }

    // Get 40 data bits + the start sequence (which will always be read as 1).
    for (int i = 0; i < 41; i++) {
        if (!waitForLevel(hal::PinLevel::High, &tStart)) {
            lastError = DhtError::LevelTimeout2;
            return false;
        }

        if (!waitForLevel(hal::PinLevel::Low, &tEnd)) {
            lastError = DhtError::LevelTimeout3;
            return false;
        }

        auto tDelta = std::chrono::duration_cast<std::chrono::microseconds>(tEnd - tStart);
        buffer[i] = tDelta.count();
    }
    return true;
}


void DhtBase::deltasToBits(const std::array<unsigned long, 41>& deltaBuffer, std::array<unsigned int, 41>& bitBuffer) {
    // Translate high level time deltas to bits:
    // 70us high = 1, 24-26us high = 0.
    for (int i = 0; i < 41; i++) {
        unsigned long delta70 = std::labs(70 - deltaBuffer[i]);
        unsigned long delta26 = std::labs(26 - deltaBuffer[i]);

        if (delta70 < delta26) {
            // 1
            bitBuffer[i] = 1;
        }
        else {
            // 0
            bitBuffer[i] = 0;
        }
    }
}

void DhtBase::bitsToBytes(const std::array<unsigned int, 41>& bitBuffer, std::array<uint8_t, 5>& byteBuffer) {
    for (int b = 0; b < 5; b++) {
        uint8_t byte = 0;
        for (int i = 0; i < 8; i++) {
            byte |= ((uint8_t)bitBuffer[1 + (8 * b) + i] << (7 - i));
        }
        byteBuffer[b] = byte;
    }
}

bool DhtBase::doChecksum(const std::array<uint8_t, 5>& byteBuffer) {
    // Checksum is sum of bytes 0-4 capped to 1 byte.
    unsigned int checksum = 0;
    for (int i = 0; i < 4; i++) {
        checksum += byteBuffer[i];
    }
    checksum &= 0xFFu;
    if (checksum == static_cast<unsigned int>(byteBuffer[4])) {
        return true;
    }
    return false;
}
