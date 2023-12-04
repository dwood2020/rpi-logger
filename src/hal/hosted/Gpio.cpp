#include "Gpio.h"

bool hal::hosted::Gpio::init(void) {
    return true;
}

void hal::hosted::Gpio::cleanup(void) {}

void hal::hosted::Gpio::initInputPin(hal::PinNumber_t pinNumber) {}

void hal::hosted::Gpio::initOutputPin(hal::PinNumber_t pinNumber) {}

void hal::hosted::Gpio::setPinHigh(hal::PinNumber_t pinNumber) {}

void hal::hosted::Gpio::setPinLow(hal::PinNumber_t pinNumber) {}

hal::PinLevel hal::hosted::Gpio::getPinLevel(hal::PinNumber_t pinNumber) {
    return hal::PinLevel::Low;
}
