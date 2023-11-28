#include "Dht11.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <cmath>
#include <bitset>


Dht11::Dht11(IDigitalReconfigurableIo& pin): pin(&pin) {
}

void Dht11::poll(void) {
    requestData();

    bool levelIsOk = false;
    for (int t = 0; t < 200; t++) {
        std::this_thread::sleep_for(std::chrono::microseconds(1));
        if (pin->getLevel() == hal::PinLevel::Low) {
            levelIsOk = true;
            break;
        }
    }
    if (!levelIsOk) {
        std::cout << "Level is not OK (1)\n";
        return;
    }


    std::chrono::steady_clock::time_point tStart;
    std::chrono::steady_clock::time_point tEnd;
    unsigned long long deltaBuffer[41];

    for (int i = 0; i < 41; i++) {
        levelIsOk = false;
        for (int t = 0; t < 2000; t++) {
            if (pin->getLevel() == hal::PinLevel::High) {
                tStart = std::chrono::steady_clock::now();
                levelIsOk = true;
                break;
            }
        }
        if (!levelIsOk) {
            std::cout << "Level is not OK (2), i = " << i << "\n";
            return;
        }

        levelIsOk = false;
        int t = 0;
        for (t = 0; t < 200000; t++) {
            // std::this_thread::sleep_for(std::chrono::microseconds(1));
            if (pin->getLevel() == hal::PinLevel::Low) {
                tEnd = std::chrono::steady_clock::now();
                levelIsOk = true;
                // std::cout << "(3) t = " << t << "\n";
                break;
            }
        }
        if (!levelIsOk) {
            std::cout << "Level is not OK (3), t = " << t << "  i = " << i << "\n";
            return;
        }

        auto tDelta = std::chrono::duration_cast<std::chrono::microseconds>(tEnd - tStart);
        deltaBuffer[i] = tDelta.count();
    }


    // Translate deltas to bits
    int bitBuffer[41];
    for (int i = 0; i < 41; i++) {
        long long delta70 = std::labs(70 - deltaBuffer[i]);
        long long delta26 = std::labs(26 - deltaBuffer[i]);

        std::cout << "[" << i << "] delta: " << deltaBuffer[i] << "  delta70: " << delta70 << "  delta26: " << delta26 << std::endl;

        if (delta70 < delta26) {
            // 1
            bitBuffer[i] = 1;
        }
        else {
            // 0
            bitBuffer[i] = 0;
        }
    }

    std::cout << "bitBuffer: ";
    for (int i = 0; i < 41; i++) {
        std::cout << bitBuffer[i];
    }
    std::cout << std::endl;
}

void Dht11::requestData(void) {
    // Configure as output pin and pull down for 0.8-29ms.
    pin->configureAsOutput();
    pin->setLow();
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    pin->configureAsInput();
}
