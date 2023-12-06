#include "Dht11.h"
#include <thread>
#include <chrono>
#include <array>

#include <iostream>
#include <cstdio>


Dht11::Dht11(IDigitalReconfigurableIo& pin): pin(&pin) {
}

void Dht11::poll(void) {
    requestData();

    std::array<unsigned long, 41> deltaBuffer;
    if (!receiveDeltas(deltaBuffer)) {
        std::cout << "Receiving deltas failed" << std::endl;
        return;
    }

    std::array<unsigned int, 41> bitBuffer;
    deltasToBits(deltaBuffer, bitBuffer);

    std::array<uint8_t, 5> bytes;
    bitsToBytes(bitBuffer, bytes);

    if (doChecksum(bytes)) {
        std::cout << "checksum OK\n";
    }

    // TODO: DHT-11 humidity is just byte 0, ignore byte 1.
    // DHT-22 uses both bytes.
    // Temperature DHT-11: Just byte 2? Or Byte 2 (whole) and 3 (fraction)?
    // Temperature DHT-22: Uses Byte 2's uppermost bit to indicate sign.
    float humidity = (float) ((bytes[0] << 8) + (bytes[1]));
    humidity /= 10.0f;
    std::cout << "humidity: " << humidity << "%\n";

    float temperature = (float) (((bytes[2] && 0x7Fu) << 8) + bytes[3]);
    temperature /= 10.0f;
    int negative = bytes[2] & 0x80u;
    if (negative == 1) {
        temperature = -temperature;
    }
    std::cout << "temperature: " << temperature << "°C" << std::endl;

}


void Dht11::requestData(void) {
    // Configure as output pin and pull down for 0.8-29ms.
    pin->configureAsOutput();
    pin->setLow();
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    pin->configureAsInput();
}


bool Dht11::receiveDeltas(std::array<unsigned long, 41>& buffer) {
    std::chrono::steady_clock::time_point tStart;
    std::chrono::steady_clock::time_point tEnd;

    // Wait until sensor pulls line low.
    if (!waitForLevel(hal::PinLevel::Low, nullptr)) {
        std::cout << "Level is not OK (1)\n";
        return false;
    }

    // Get 40 data bits + the start sequence (which will always be read as 1).
    for (int i = 0; i < 41; i++) {
        if (!waitForLevel(hal::PinLevel::High, &tStart)) {
            std::cout << "Level is not OK (2), i = " << i << "\n";
            return false;
        }

        if (!waitForLevel(hal::PinLevel::Low, &tEnd)) {
            std::cout << "Level is not OK (3), i = " << i << "\n";
            return false;
        }

        auto tDelta = std::chrono::duration_cast<std::chrono::microseconds>(tEnd - tStart);
        buffer[i] = tDelta.count();
    }
    return true;
}


void Dht11::deltasToBits(const std::array<unsigned long, 41>& deltaBuffer, std::array<unsigned int, 41>& bitBuffer) {
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

void Dht11::bitsToBytes(const std::array<unsigned int, 41>& bitBuffer, std::array<uint8_t, 5>& byteBuffer) {
    for (int b = 0; b < 5; b++) {
        uint8_t byte = 0;
        for (int i = 0; i < 8; i++) {
            byte |= ((uint8_t)bitBuffer[1 + (8 * b) + i] << (7 - i));
        }
        printf("0x%02X ", byte);
        byteBuffer[b] = byte;
    }
    printf("\n");
}

bool Dht11::doChecksum(const std::array<uint8_t, 5>& byteBuffer) {
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

bool Dht11::waitForLevel(hal::PinLevel level, std::chrono::steady_clock::time_point* timePoint) {
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

