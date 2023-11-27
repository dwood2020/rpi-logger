#include "Dht11.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <cmath>
#include <bitset>


Dht11::Dht11(IDigitalReconfigurableIo& pin): pin(&pin) {
}

void Dht11::poll(void) {
    getData();

    for (int t = 0; t < 2000; t++) {
        if (pin->getLevel() == hal::PinLevel::Low) {
            break;
        }
    }

    std::chrono::steady_clock::time_point tStart;
    std::chrono::steady_clock::time_point tEnd;
    int buffer[41];

    for (int i = 0; i < 41; i++) {
        for (int t = 0; t < 2000; t++) {
            if (pin->getLevel() == hal::PinLevel::High) {
                tStart = std::chrono::steady_clock::now();
                break;
            }
        }

        for (int t = 0; t < 2000; t++) {
            if (pin->getLevel() == hal::PinLevel::Low) {
                tEnd = std::chrono::steady_clock::now();
                break;
            }
        }

        auto tDelta = std::chrono::duration_cast<std::chrono::microseconds>(tEnd - tStart);
        long long deltaUs = tDelta.count();

        long long delta70 = std::labs(70 - deltaUs);
        long long delta26 = std::labs(26 - deltaUs);
        if (delta70 < delta26) {
            // 1
            buffer[i] = 1;
        }
        else {
            // 0
            buffer[i] = 0;
        }

    }

    std::bitset<64> bufferBits(buffer);
    std::cout << "bufferBits: " << bufferBits << std::endl;
}

void Dht11::getData(void) {
    // Configure as output pin and pull down for 0.8-29ms.
    pin->configureAsOutput();
    pin->setLow();
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    pin->configureAsInput();
}
