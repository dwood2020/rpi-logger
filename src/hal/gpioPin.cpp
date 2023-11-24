#include "gpioPin.h"
#include "gpio.h"


namespace gpio {

    Pin::Pin(PinType type, unsigned int number): type(type), number(number) {
    }

    PinType Pin::getType(void) const {
        return type;
    }

    unsigned int InputPin::getLevel(void) const {
        return gpio::getPinLevel(this->number);
    }

    void OutputPin::setLow(void) {
        gpio::setPinLow(this->number);
    }

    void OutputPin::setHigh(void) {
        gpio::setPinHigh(this->number);
    }

}  // namespace gpio
