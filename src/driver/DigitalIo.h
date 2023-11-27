#pragma once
#include "hal/IGpio.h"


/**
 * Concrete base class for all IO subclasses.
*/
class DigitalIoBase {
protected:
    hal::IGpio* gpioDevice;
    hal::PinNumber_t pinNumber;

public:
    DigitalIoBase(hal::IGpio& gpio, hal::PinNumber_t pinNumber);
    virtual ~DigitalIoBase() = default;

    hal::PinNumber_t getNumber(void) const;
};



class IDigitalInput {
public:
    virtual ~IDigitalInput() = default;

    virtual hal::PinLevel getLevel(void) = 0;
};


class DigitalInput: IDigitalInput, DigitalIoBase {
public:
    DigitalInput(hal::IGpio& gpio, hal::PinNumber_t pinNumber);
    virtual ~DigitalInput() = default;

    hal::PinLevel getLevel(void) override;
};


class IDigitalOutput {
public:
    virtual ~IDigitalOutput() = default;

    virtual void setLow(void) = 0;
    virtual void setHigh(void) = 0;
};


class DigitalOutput: IDigitalOutput, DigitalIoBase {
public:
    DigitalOutput(hal::IGpio& gpio, hal::PinNumber_t pinNumber);
    virtual ~DigitalOutput() = default;

    void setLow(void) override;
    void setHigh(void) override;
};


// TODO: DigitalReconfigurableIo 
