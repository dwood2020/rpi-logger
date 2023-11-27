#pragma once
#include "hal/IGpio.h"


/**
 * Digital (GPIO) input interface.
*/
class IDigitalInput {
public:
    virtual ~IDigitalInput() = default;

    /**
     * Get voltage level of this input.
     * \return Pin level (Low or high).
    */
    virtual hal::PinLevel getLevel(void) = 0;
};


/**
 * Digital (GPIO) output interface.
*/
class IDigitalOutput {
public:
    virtual ~IDigitalOutput() = default;

    /**
     * Set this output's voltage level low.
    */
    virtual void setLow(void) = 0;

    /**
     * Set this output's voltage level high.
    */
    virtual void setHigh(void) = 0;
};


/**
 * Digital (GPIO) input/output with reconfigurable direction (in/out) interface.
*/
class IDigitalReconfigurableIo: public IDigitalInput, public IDigitalOutput {
public:
    virtual ~IDigitalReconfigurableIo() = default;

    /**
     * Configure this digital I/O as input.
    */
    virtual void configureAsInput(void) = 0;

    /**
     * Configure this digital I/O as output.
    */
    virtual void configureAsOutput(void) = 0;
};
