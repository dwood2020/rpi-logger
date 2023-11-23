#include <iostream>
#include "bcm2835.h"


static constexpr int outPin = RPI_GPIO_P1_18;   // GPIO 24

int main(void) {
    std::cout << "Hello rpi-logger!" << std::endl;

    if (!bcm2835_init()) {
        std::cout << "FAILED TO INIT BCM2835!!" << std::endl;
        return 1;
    }

    bcm2835_gpio_fsel(outPin, BCM2835_GPIO_FSEL_OUTP);

    for (int i = 0; i < 100; i++) {
        bcm2835_gpio_write(outPin, HIGH);
        std::cout << ":" << std::flush;
        bcm2835_delay(500);
        bcm2835_gpio_write(outPin, LOW);
        std::cout << "." << std::flush;
        bcm2835_delay(500);
    }
    std::cout << std::endl;

    bcm2835_close();
    return 0;
}
