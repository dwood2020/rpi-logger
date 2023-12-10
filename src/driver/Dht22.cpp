#include "Dht22.h"


Dht22::Dht22(IDigitalReconfigurableIo& pin): DhtBase(pin) {
}

void Dht22::updateHumidity(const std::array<uint8_t, 5>& byteBuffer) {
    float humidity = static_cast<float>((byteBuffer[0] << 8) + (byteBuffer[1]));
    humidity /= 10.0f;
    this->humidity = humidity;
}

void Dht22::updateTemperature(const std::array<uint8_t, 5>& byteBuffer) {
    float temperature = static_cast<float>(((byteBuffer[2] && 0x7Fu) << 8) + byteBuffer[3]);
    temperature /= 10.0f;
    int negative = byteBuffer[2] & 0x80u;
    if (negative == 1) {
        temperature = -temperature;
    }
    this->temperature = temperature;
}
