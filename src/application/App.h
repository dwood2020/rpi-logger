/*
 * Copyright (C) 2024  David Woodward
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

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
    std::shared_ptr<csv::Column> columnHumidity;
    std::shared_ptr<csv::Column> columnTemp;

    DhtSensorPath(std::unique_ptr<DhtBase> sensor, std::shared_ptr<csv::Column> columnHumidity, std::shared_ptr<csv::Column> columnTemp): 
        sensor(std::move(sensor)), columnHumidity(columnHumidity), columnTemp(columnTemp) {}
    DhtSensorPath(DhtSensorPath&& other) noexcept: 
        sensor(std::move(other.sensor)), columnHumidity(std::move(other.columnHumidity)), columnTemp(std::move(other.columnTemp)) {}
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
