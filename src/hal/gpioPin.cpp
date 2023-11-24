#include "gpioPin.h"
#include "gpio.h"


namespace gpio {

    Pin::Pin(PinType type, unsigned int number): type(type), number(number) {
        // Do nothing else here.
    }

    PinType Pin::getType(void) const {
        return type;
    }

    unsigned int Pin::getNumber(void) const {
        return number;
    }

    InputPin::InputPin(int number): Pin(PinType::Input, number) {
        gpio::initInputPin(this->number);
    }

    unsigned int InputPin::getLevel(void) const {
        return gpio::getPinLevel(this->number);
    }


    OutputPin::OutputPin(int number): Pin(PinType::Output, number) {
        gpio::initOutputPin(this->number);
    }

    void OutputPin::setLow(void) {
        gpio::setPinLow(this->number);
    }

    void OutputPin::setHigh(void) {
        gpio::setPinHigh(this->number);
    }

}  // namespace gpio
