#pragma once
#include "Pin.h"


class Bcm2835InputPin final : public InputPin {
    Bcm2835InputPin(unsigned int number);
    ~Bcm2835InputPin() = default;
};


class Bcm2835OutputPin final : public OutputPin {
public:
    Bcm2835OutputPin(unsigned int number);
    ~Bcm2835OutputPin() = default;

    void setLow(void) override;
    void setHigh(void) override;
};
