#include "Dht11.h"

Dht11::Dht11(IDigitalReconfigurableIo& pin): DhtBase(pin) {
}

void Dht11::updateHumidity(const std::array<uint8_t, 5>& byteBuffer) {
}

void Dht11::updateTemperature(const std::array<uint8_t, 5>& byteBuffer) {
}
