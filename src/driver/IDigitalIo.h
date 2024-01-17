/*
 * Copyright (C) 2024  David Woodward
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once
#include "hal/IGpio.h"


/**
 * Digital (GPIO) input interface.
*/
class IDigitalInput {
public:
    IDigitalInput() = default;
    virtual ~IDigitalInput() = default;

    IDigitalInput(const IDigitalInput&) = delete;
    IDigitalInput& operator=(const IDigitalInput&) = delete;

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
    IDigitalOutput() = default;
    virtual ~IDigitalOutput() = default;

    IDigitalOutput(const IDigitalOutput&) = delete;
    IDigitalOutput& operator=(const IDigitalOutput&) = delete;

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
    IDigitalReconfigurableIo() = default;
    virtual ~IDigitalReconfigurableIo() = default;

    IDigitalReconfigurableIo(const IDigitalReconfigurableIo&) = delete;
    IDigitalReconfigurableIo& operator=(const IDigitalReconfigurableIo&) = delete;

    /**
     * Configure this digital I/O as input.
    */
    virtual void configureAsInput(void) = 0;

    /**
     * Configure this digital I/O as output.
    */
    virtual void configureAsOutput(void) = 0;
};
