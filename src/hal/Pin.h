#pragma once
#include "Gpio.h"


/**
 * Generic pin types.
*/
enum class PinType {
    None = 0,
    Input,
    Output,
    Reserved    // This is to be extended here.
};


/**
 * Generic Pin base class.
*/
class Pin {
protected:
    PinType type = PinType::None;
    unsigned int number = 0;

    Pin(PinType type, unsigned int number): type(type), number(number) {}

public:
    virtual ~Pin() = default;

    PinType getType(void) const {
        return type;
    }
};


/**
 * Virtual input pin base class.
*/
class InputPin : public Pin {
public:
    InputPin(int number): Pin(PinType::Input, number) {}
    virtual ~InputPin() = default;

    virtual unsigned int getLevel(void) const = 0;
};


/**
 * Virtual output pin base class.
*/
class OutputPin : public Pin {
public:
    OutputPin(int number): Pin(PinType::Output, number) {}
    virtual ~OutputPin() = default;

    virtual void setLow(void) = 0;
    virtual void setHigh(void) = 0;
};
