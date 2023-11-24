#pragma once


namespace gpio {

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

        Pin(PinType type, unsigned int number);

    public:
        virtual ~Pin() = default;

        /**
         * Get this pin's type.
         * \return Pin type (see generic pin types).
        */
        PinType getType(void) const;

        /**
         * Get this pin's number.
         * \return Pin number.
        */
        unsigned int getNumber(void) const;
    };


    /**
     * Virtual input pin base class.
    */
    class InputPin : public Pin {
    public:
        /**
         * Constructor.
         * \param number This pin's pin number.
         * TODO: Pin is currently initialized here. This may have to change, check! Maybe unsafe?
        */
        InputPin(int number);
        virtual ~InputPin() = default;

        /**
         * Get the current pin level. 
         * \return Pin level (1 = high, 0 = low).
        */
        virtual unsigned int getLevel(void) const;
    };


    /**
     * Virtual output pin base class.
    */
    class OutputPin : public Pin {
    public:
        /**
         * Constructor.
         * \param number This pin's pin number.
         * TODO: Pin is currently initialized here. This may have to change, check! Maybe unsafe?
        */
        OutputPin(int number);
        virtual ~OutputPin() = default;

        /**
         * Set pin level low.
        */
        virtual void setLow(void);

        /**
         * Set pin level high.
        */
        virtual void setHigh(void);
    };

}

