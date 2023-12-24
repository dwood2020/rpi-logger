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


struct DhtSensorPath {
    std::unique_ptr<DhtBase> sensor;
    std::shared_ptr<csv::Column> column;

    DhtSensorPath(std::unique_ptr<DhtBase> sensor, std::shared_ptr<csv::Column> column): sensor(std::move(sensor)), column(column) {}
    DhtSensorPath(DhtSensorPath&& other) noexcept: sensor(std::move(other.sensor)), column(std::move(other.column)) {}
};


struct DhtSensorReading {
    float humidity = 0.0f;
    float temperature = 0.0f;

    DhtSensorReading() = default;
    DhtSensorReading(float humidity, float temperature): humidity(humidity), temperature(temperature) {}
};


/**
 * Represents the app instance.
*/
class App final {
private:
    hal::IGpio* gpio;
    std::list<DigitalReconfigurableIo*> sensorPins;
    std::vector<DhtSensorPath> dht11SensorPaths;
    std::vector<DhtSensorPath> dht22SensorPaths;
    std::unique_ptr<csv::Writer> csvWriter;
    std::chrono::seconds logIntervalSec = std::chrono::seconds(0);
    bool testMode = false;

public:
    App(hal::IGpio& gpio);
    ~App();

    bool init(void);
    void run(void);

private:
    void runTest(void);
    void testSensorPath(const DhtSensorPath& sensorPath);
    void performReading(const DhtSensorPath& sensorPath);
    bool pinNumberExists(hal::PinNumber_t pinNumber);
};
