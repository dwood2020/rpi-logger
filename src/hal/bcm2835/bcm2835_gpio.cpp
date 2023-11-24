#include "../gpio.h"
#include <cstdint>
#include "bcm2835.h"


bool gpio::init(void) {
    return bcm2835_init();
}

void gpio::cleanup(void) {
    bcm2835_close();
}

void gpio::initInputPin(unsigned int pinNumber) {
    bcm2835_gpio_fsel(static_cast<uint8_t>(pinNumber), BCM2835_GPIO_FSEL_INPT);
}

void gpio::initOutputPin(unsigned int pinNumber) {
    bcm2835_gpio_fsel(static_cast<uint8_t>(pinNumber), BCM2835_GPIO_FSEL_OUTP);
}

void gpio::setPinHigh(unsigned int pinNumber) {
    bcm2835_gpio_write(static_cast<uint8_t>(pinNumber), HIGH);
}

void gpio::setPinLow(unsigned int pinNumber) {
    bcm2835_gpio_write(static_cast<uint8_t>(pinNumber), LOW);
}

int gpio::getPinLevel(unsigned int pinNumber) {
    uint8_t lev = bcm2835_gpio_lev(static_cast<uint8_t>(pinNumber));
    return (lev == HIGH) ? 1 : 0;
}
