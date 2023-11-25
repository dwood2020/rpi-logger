#include "Dht11.h"
#include <thread>
#include <chrono>
#include "bcm2835.h"


Dht11::Dht11(gpio::OutputPin& pin): pin(pin) {
}

void Dht11::poll(void) {
    // Get data.
    // Pull down for 1ms.
    pin.setLow();
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    gpio::InputPin pinInp(pin.getNumber());

    for (unsigned int i = 0; i < 200; i++) {
        
    }

}

