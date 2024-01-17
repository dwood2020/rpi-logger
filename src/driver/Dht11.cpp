/*
 * Copyright (C) 2024  David Woodward
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "Dht11.h"
#include <cstdio>


Dht11::Dht11(IDigitalReconfigurableIo& pin): DhtBase(pin) {
}

void Dht11::updateHumidity(const std::array<uint8_t, 5>& byteBuffer) {
    humidity = static_cast<float>(byteBuffer[0]);   // byte 1 is unused.
}

void Dht11::updateTemperature(const std::array<uint8_t, 5>& byteBuffer) {
    // NOTE: Other sources say that for DHT11 devices, both bytes 1 and 3 are unused.
    // This may be incorrect.
    float whole = static_cast<float>(byteBuffer[2]);
    float decimal = static_cast<float>(byteBuffer[3]);
    temperature = whole + (decimal / 10.0f);
}
