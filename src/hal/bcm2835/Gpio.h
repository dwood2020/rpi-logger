#include "hal/IGpio.h"


namespace hal::bcm2835 {

    class Gpio final : public hal::IGpio {
    public:
        Gpio();
        ~Gpio();

        bool init(void) override;
        void cleanup(void) override;

        void initInputPin(PinNumber_t pinNumber) override;
        void initOutputPin(PinNumber_t pinNumber) override;

        void setPinHigh(PinNumber_t pinNumber) override;
        void setPinLow(PinNumber_t pinNumber) override;
        hal::PinLevel getPinLevel(PinNumber_t pinNumber) override;
    };

}
