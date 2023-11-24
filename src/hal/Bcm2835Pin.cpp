#include "Bcm2835Pin.h"
#include "bcm2835.h"


Bcm2835InputPin::Bcm2835InputPin(unsigned int number): InputPin(number) {}

Bcm2835OutputPin::Bcm2835OutputPin(unsigned int number): OutputPin(number) {}


void Bcm2835OutputPin::setLow(void) {
    bcm2835_gpio_write(this->number, LOW);
}

void Bcm2835OutputPin::setHigh(void) {
    bcm2835_gpio_write(this->number, HIGH);
}
