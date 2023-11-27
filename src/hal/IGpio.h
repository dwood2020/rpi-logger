#pragma once


namespace hal {

    /**
     * Pin number type.
    */
    using PinNumber_t = unsigned int;

    /**
     * GPIO pin state.
    */
    enum class PinLevel {
        Low = 0,
        High = 1
    };

    /**
     * Generic GPIO interface.
     * See also this SO answer: https://stackoverflow.com/a/55013604/15864221.
    */
    class IGpio {
    public:
        IGpio() = default;
        virtual ~IGpio() = default;

        IGpio(const IGpio&) = delete;
        IGpio& operator=(const IGpio&) = delete;

        /**
         * Initialize the GPIO hardware layer.
         * \return \c True if successful, \c false else.
        */
        virtual bool init(void) = 0;

        /**
         * Cleanup all resources used by the GPIO interface.
        */
        virtual void cleanup(void) = 0;

        /**
         * Initialize a pin as input pin.
         * \param pinNumber Pin number of pin to be init'd.
        */
        virtual void initInputPin(PinNumber_t pinNumber) = 0;

        /**
         * Initialize a pin as output pin.
         * \param pinNumber Pin number of pin to be init'd.
        */
        virtual void initOutputPin(PinNumber_t pinNumber) = 0;

        /**
         * Set an output pin HIGH.
         * \param pinNumber Pin number of pin to set.
        */
        virtual void setPinHigh(PinNumber_t pinNumber) = 0;

        /**
         * Set an output pin LOW.
         * \param pinNumber Pin number of pin to set.
        */
        virtual void setPinLow(PinNumber_t pinNumber) = 0;

        /**
         * Get an input pin's current level.
         * \param pinNumber Pin number of pin.
         * \return Pin level.
        */
        virtual PinLevel getPinLevel(PinNumber_t pinNumber) = 0;
    };
}
