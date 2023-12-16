#pragma once
#include <filesystem>
#include <list>
#include <memory>
#include <vector>
#include "AppConfig.h"
#include "hal/IGpio.h"
#include "driver/DigitalIo.h"
#include "driver/Dht11.h"
#include "driver/Dht22.h"
#include "application/csv/Column.h"
#include "application/csv/Writer.h"


struct Dht11SensorPath {
    Dht11 sensor;
    std::shared_ptr<csv::Column> column;

    Dht11SensorPath(const Dht11& sensor, std::shared_ptr<csv::Column> column): sensor(sensor), column(column) {}
};


struct Dht22SensorPath {
    Dht22 sensor;
    std::shared_ptr<csv::Column> column;

    Dht22SensorPath(const Dht22& sensor, std::shared_ptr<csv::Column> column): sensor(sensor), column(column) {}
};


/**
 * Represents the app instance.
*/
class App final {
private:
    hal::IGpio* gpio;
    std::list<DigitalReconfigurableIo*> sensorPins;
    std::vector<Dht11SensorPath> dht11SensorPaths;
    std::vector<Dht22SensorPath> dht22SensorPaths;
    int logIntervalSec = 0;
    std::unique_ptr<csv::Writer> csvWriter;

public:
    App(hal::IGpio& gpio);
    ~App();

    bool init(void);
    void run(void);

private:
    bool pinNumberExists(hal::PinNumber_t pinNumber);
};
