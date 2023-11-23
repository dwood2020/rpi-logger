#include <iostream>
#include "bcm2835.h"


int main(void) {
    std::cout << "Hello rpi-logger!" << std::endl;

    // TODO: Write HAL/wrapper around GPIOs!
    if (!bcm2835_init()) {
        std::cout << "FAILED TO INIT BCM2835!!" << std::endl;
        return 1;
    }

    

    bcm2835_close();
    return 0;
}
