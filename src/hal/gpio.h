#pragma once

/**
 * Generic GPIO interface functions. 
 * These functions do not introduce any types. They solely represent the coupling 
 * layer tos the hardware-specific interface.
*/
namespace gpio {

    /**
     * Initialize the GPIO hardware layer.
     * \return \c True if successful, \c false else.
    */
    bool init(void);

    /**
     * Cleanup all resources used by the GPIO hardware layer.
    */
    void cleanup(void);

    /**
     * Initialize a pin as input pin.
     * \param pinNumber Pin number of pin to be init'd.
    */
    void initInputPin(unsigned int pinNumber);

    /**
     * Initialize a pin as output pin.
     * \param pinNumber Pin number of pin to be init'd.
    */
    void initOutputPin(unsigned int pinNumber);

    /**
     * Set an output pin HIGH.
     * \param pinNumber Pin number of pin to set.
    */
    void setPinHigh(unsigned int pinNumber);

    /**
     * Set an output pin LOW.
     * \param pinNumber Pin number of pin to set.
    */
    void setPinLow(unsigned int pinNumber);

    /**
     * Get an input pin's current level.
     * \param pinNumber Pin number of pin to set.
    */
    int getPinLevel(unsigned int pinNumber);
}
