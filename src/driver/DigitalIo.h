/*
 * Copyright (C) 2024  David Woodward
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once
#include "IDigitalIo.h"
#include "hal/IGpio.h"


/**
 * Concrete base class for all IO subclasses.
 * TODO: How to make this thread-safe: Hold ptr to a new GpioController instead of hal::IGpio.
 * Controller owns mutexes, ask controller first before each read/write.
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


class DigitalInput: public IDigitalInput, public DigitalIoBase {
public:
    DigitalInput(hal::IGpio& gpio, hal::PinNumber_t pinNumber);
    virtual ~DigitalInput() = default;

    hal::PinLevel getLevel(void) override;
};


class DigitalOutput: public IDigitalOutput, public DigitalIoBase {
public:
    DigitalOutput(hal::IGpio& gpio, hal::PinNumber_t pinNumber);
    virtual ~DigitalOutput() = default;

    void setLow(void) override;
    void setHigh(void) override;
};


class DigitalReconfigurableIo : public IDigitalReconfigurableIo, public DigitalIoBase {
public:
    DigitalReconfigurableIo(hal::IGpio& gpio, hal::PinNumber_t pinNumber);
    virtual ~DigitalReconfigurableIo() = default;

    hal::PinLevel getLevel(void) override;

    void setLow(void) override;
    void setHigh(void) override;

    void configureAsInput(void) override;
    void configureAsOutput(void) override;
};
