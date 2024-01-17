/*
 * Copyright (C) 2024  David Woodward
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once
#include <array>
#include <cstdint>
#include "driver/DhtBase.h"
#include "driver/IDigitalIo.h"


/**
 * DHT11 device driver class.
*/
class Dht11 : public DhtBase {
public:
    Dht11(IDigitalReconfigurableIo& pin);
    virtual ~Dht11() = default;

private:
    void updateHumidity(const std::array<uint8_t, 5>& byteBuffer) override;
    void updateTemperature(const std::array<uint8_t, 5>& byteBuffer) override;
};
