#include <iostream>
#include <chrono>
#include <thread>
#include <memory>

#include "hal/IGpio.h"
#include "hal/bcm2835/Gpio.h"
#include "hal/hosted/Gpio.h"
#include "driver/IDigitalIo.h"
#include "driver/DigitalIo.h"
#include "driver/Dht11.h"
#include "driver/Dht22.h"

#include "application/csv/Writer.h"
#include "application/csv/Column.h"
#include "application/AppConfig.h"

int main(void) {
    std::cout << "Hello rpi-logger!" << std::endl;

#if HOSTED
    hal::hosted::Gpio gpio;
#else
    hal::bcm2835::Gpio gpio;
#endif /* HOSTED */

    if (!gpio.init()) {
        std::cout << "Failed to init GPIO!" << std::endl;
        return 1;
    }

    DigitalReconfigurableIo pin(gpio, 24);
    Dht22 sensor(pin);
    if (sensor.poll()) {
        std::cout << "Humidity: " << sensor.getHumidity() << " % RH\n";
        std::cout << "Temperature: " << sensor.getTemperature() << " °C" << std::endl;
    }
    else {
        std::cout << "Sensor polling failed. Last error: " << static_cast<int>(sensor.getLastError()) << std::endl;
    }

    // Testing CsvWriter
    // std::shared_ptr<csv::Column> col1 = std::make_shared<csv::Column>("TestColumn");
    // csv::Writer writer({col1}, ".");
    // writer.initialize();
    // col1->logValue(100);
    // writer.writeLine();
    // col1->logValue(200);
    // writer.writeLine();
    // col1->logValue(300);
    // writer.writeLine();

    // Test AppConfig
    AppConfig appConfig;
    try {
        appConfig.parse(std::filesystem::current_path());
    }catch (std::runtime_error& e) {
        std::cout << "Could not parse AppConfig: " << e.what() << std::endl;
        return -1;
    }
    std::cout << appConfig.toString() << std::endl;

    // DigitalOutput pin(gpio, 24);
    // for (int i = 0; i < 10; i++) {
    //     pin.setHigh();
    //     std::this_thread::sleep_for(std::chrono::milliseconds(500));
    //     pin.setLow();
    //     std::this_thread::sleep_for(std::chrono::milliseconds(500));
    // }

    return 0;
}
