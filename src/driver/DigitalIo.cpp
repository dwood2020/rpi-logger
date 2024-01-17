/*
 * Copyright (C) 2024  David Woodward
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "DigitalIo.h"


DigitalIoBase::DigitalIoBase(hal::IGpio& gpio, hal::PinNumber_t pinNumber): gpioDevice(&gpio), pinNumber(pinNumber) {
}

hal::PinNumber_t DigitalIoBase::getNumber(void) const {
    return pinNumber;
}


DigitalInput::DigitalInput(hal::IGpio& gpio, hal::PinNumber_t pinNumber): DigitalIoBase(gpio, pinNumber) {
    gpioDevice->initInputPin(this->pinNumber);
}

hal::PinLevel DigitalInput::getLevel(void) {
    return gpioDevice->getPinLevel(pinNumber);
}


DigitalOutput::DigitalOutput(hal::IGpio& gpio, hal::PinNumber_t pinNumber): DigitalIoBase(gpio, pinNumber) {
    gpioDevice->initOutputPin(this->pinNumber);
}

void DigitalOutput::setLow(void) {
    gpioDevice->setPinLow(pinNumber);
}

void DigitalOutput::setHigh(void) {
    gpioDevice->setPinHigh(pinNumber);
}


DigitalReconfigurableIo::DigitalReconfigurableIo(hal::IGpio& gpio, hal::PinNumber_t pinNumber): DigitalIoBase(gpio, pinNumber) {
}

hal::PinLevel DigitalReconfigurableIo::getLevel(void) {
    return gpioDevice->getPinLevel(pinNumber);
}

void DigitalReconfigurableIo::setLow(void) {
    gpioDevice->setPinLow(pinNumber);
}

void DigitalReconfigurableIo::setHigh(void) {
    gpioDevice->setPinHigh(pinNumber);
}

void DigitalReconfigurableIo::configureAsInput(void) {
    gpioDevice->initInputPin(pinNumber);
}

void DigitalReconfigurableIo::configureAsOutput(void) {
    gpioDevice->initOutputPin(pinNumber);
}
