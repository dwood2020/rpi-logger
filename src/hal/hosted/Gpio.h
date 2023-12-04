#pragma once
#include "hal/IGpio.h"

namespace hal::hosted {

    class Gpio : public hal::IGpio {
    public:
        Gpio() = default;
        ~Gpio() = default;

        bool init(void) override;
        void cleanup(void) override;
        void initInputPin(hal::PinNumber_t pinNumber) override;
        void initOutputPin(hal::PinNumber_t pinNumber) override;
        void setPinHigh(hal::PinNumber_t pinNumber) override;
        void setPinLow(hal::PinNumber_t pinNumber) override;
        hal::PinLevel getPinLevel(hal::PinNumber_t pinNumber) override;
    };
}
