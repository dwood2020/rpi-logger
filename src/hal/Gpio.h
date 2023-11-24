#pragma once


/**
 * Abstract GPIO interface base class.
*/
class Gpio {
public:
    Gpio() = default;
    virtual ~Gpio() = default;

    Gpio(const Gpio&) = delete;
    Gpio& operator=(const Gpio&) = delete;

    virtual bool init(void) = 0;

    virtual void registerInputPin(unsigned int pinNumber) = 0;
    virtual void registerOutputPin(unsigned int pinNumber) = 0;
};
