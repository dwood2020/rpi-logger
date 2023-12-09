#include "Dht11.h"
#include <cstdio>


Dht11::Dht11(IDigitalReconfigurableIo& pin): DhtBase(pin) {
}

void Dht11::updateHumidity(const std::array<uint8_t, 5>& byteBuffer) {
    for (int i = 0; i < 5; i++) {
        printf("0x%02X ");
    }
    printf("\n");
}

void Dht11::updateTemperature(const std::array<uint8_t, 5>& byteBuffer) {
}
