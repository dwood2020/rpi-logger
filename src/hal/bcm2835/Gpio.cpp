/*
 * Copyright (C) 2024  David Woodward
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "Gpio.h"
#include "bcm2835.h"


hal::bcm2835::Gpio::Gpio() {
}

hal::bcm2835::Gpio::~Gpio() {
    cleanup();
}

bool hal::bcm2835::Gpio::init(void) {
    return bcm2835_init();
}

void hal::bcm2835::Gpio::cleanup(void) {
    bcm2835_close();
}

void hal::bcm2835::Gpio::initInputPin(PinNumber_t pinNumber) {
    bcm2835_gpio_fsel(static_cast<uint8_t>(pinNumber), BCM2835_GPIO_FSEL_INPT);
}

void hal::bcm2835::Gpio::initOutputPin(PinNumber_t pinNumber) {
    bcm2835_gpio_fsel(static_cast<uint8_t>(pinNumber), BCM2835_GPIO_FSEL_OUTP);
}

void hal::bcm2835::Gpio::setPinHigh(PinNumber_t pinNumber) {
    bcm2835_gpio_write(static_cast<uint8_t>(pinNumber), HIGH);
}

void hal::bcm2835::Gpio::setPinLow(PinNumber_t pinNumber) {
    bcm2835_gpio_write(static_cast<uint8_t>(pinNumber), LOW);
}

hal::PinLevel hal::bcm2835::Gpio::getPinLevel(PinNumber_t pinNumber) {
    uint8_t lev = bcm2835_gpio_lev(static_cast<uint8_t>(pinNumber));
    return (lev == HIGH) ? PinLevel::High : PinLevel::Low;
}
