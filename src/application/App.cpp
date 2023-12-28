#include "App.h"
#include <chrono>
#include <cmath>
#include <filesystem>
#include <thread>
#include <vector>
#include "AppConfig.h"
#include "Log.h"


App::App(hal::IGpio& gpio): gpio(&gpio) {
}

App::~App() {
    for (auto pin : sensorPins) {
        delete pin;
    }
}

bool App::init(void) {
    Log::init(std::filesystem::current_path());

    AppConfig config;
    try {
        config.parse(std::filesystem::current_path());
    }
    catch (std::runtime_error& e) {
        LOG_ERROR("Could not parse '%v': %v", config.appConfigFileName, e.what());
        return false;
    }
    LOG_INFO("%v", config.toString());

    std::filesystem::path outputPath = std::filesystem::path(config.getCsvOutputDir());
    if (!std::filesystem::exists(outputPath)) {
        LOG_ERROR("Output directory '%v' does not exist. Check %v", config.getCsvOutputDir(), config.appConfigFileName);
        return false;
    }

    Log::init(outputPath);

    if (!gpio->init()) {
        LOG_ERROR("Could not init GPIO device.");
        return false;
    }

    csvWriter = std::make_unique<csv::Writer>(outputPath);

    for (const SensorConfig cfg : config.getDht11Configs()) {
        if (pinNumberExists(cfg.pinNumber)) {
            LOG_WARN("Pin number %v already exists. Skipping.", cfg.pinNumber);
            continue;
        }

        auto pin = new DigitalReconfigurableIo(*gpio, cfg.pinNumber);
        sensorPins.push_back(pin);
        auto columnHumidity = std::make_shared<csv::Column>(cfg.logNameHumidity);
        auto columnTemp = std::make_shared<csv::Column>(cfg.logNameTemp);
        dht11SensorPaths.emplace_back(std::make_unique<Dht11>(*pin), columnHumidity, columnTemp);
        csvWriter->addColumn(columnHumidity);
        csvWriter->addColumn(columnTemp);
        LOG_INFO("Added DHT11 config: pin %v, humidity log name '%v', temperature log name '%v'", 
            pin->getNumber(), columnHumidity->getName(), columnTemp->getName());
    }

    for (const SensorConfig cfg : config.getDht22Configs()) {
        if (pinNumberExists(cfg.pinNumber)) {
            LOG_WARN("Pin number %v already exists. Skipping.", cfg.pinNumber);
            continue;
        }

        auto pin = new DigitalReconfigurableIo(*gpio, cfg.pinNumber);
        sensorPins.push_back(pin);
        auto columnHumidity = std::make_shared<csv::Column>(cfg.logNameHumidity);
        auto columnTemp = std::make_shared<csv::Column>(cfg.logNameTemp);
        dht22SensorPaths.emplace_back(std::make_unique<Dht22>(*pin), columnHumidity, columnTemp);
        csvWriter->addColumn(columnHumidity);
        csvWriter->addColumn(columnTemp);
        LOG_INFO("Added DHT11 config: pin %v, humidity log name '%v', temperature log name '%v'", 
            pin->getNumber(), columnHumidity->getName(), columnTemp->getName());
    }

    logIntervalSec = std::chrono::seconds(config.getLogIntervalSec());
    testMode = config.getTestMode();

    return true;
}

void App::run(void) {
    if (testMode) {
        runTest();
        return;
    }

    // We use t0 as reference for every tIntervalEnd to prevent a drift.
    std::chrono::time_point t0 = std::chrono::steady_clock::now();
    unsigned long loopCount = 0;

    while (true) {
        loopCount++;
        std::chrono::time_point tIntervalEnd = t0 + logIntervalSec * loopCount;
        if (loopCount == std::numeric_limits<unsigned long>::max()) {
            // Reset t0 and do a "manual" wrap-around so that tIntervalEnd is never calculated with loopCount = 0.
            t0 = std::chrono::steady_clock::now();
            loopCount = 0;
        }

        // Do business
        LOG_INFO("DOING BUSINESS .....");
        for (const auto& dht11Path : dht11SensorPaths) {
            performReading(dht11Path);
        }
        for (const auto& dht22Path : dht22SensorPaths) {
            performReading(dht22Path);
        }

        std::chrono::time_point tEnd = std::chrono::steady_clock::now();
        if (tEnd > tIntervalEnd) {
            LOG_WARN("Measurement duration exceeds configured log interval.");
        }
        else {
            std::this_thread::sleep_until(tIntervalEnd);
        }
    }
}

void App::runTest(void) {
    LOG_INFO("Running in test mode.");

    if (dht11SensorPaths.empty()) {
        LOG_INFO("No DHT11 sensors configured.");
    }
    else {
        for (const auto& dht11path : dht11SensorPaths) {
            testSensorPath(dht11path);
        }
    }

    if (dht22SensorPaths.empty()) {
        LOG_INFO("No DHT22 sensors configured.");
    }
    else {
        for (const auto& dht22Path: dht22SensorPaths) {
            testSensorPath(dht22Path);
        }
    }
}

void App::testSensorPath(const DhtSensorPath& sensorPath) {
    int failedReadings = 0;
    std::vector<DhtSensorReading> readings;
    readings.reserve(10);

    for (int i = 0; i < 10; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        if (sensorPath.sensor->poll()) {
            DhtSensorReading reading(sensorPath.sensor->getHumidity(), sensorPath.sensor->getTemperature());
            readings.push_back(reading);
        }
        else {
            LOG_ERROR("Sensor path '%v', '%v' reading #%v failed. Error code %v", 
                sensorPath.columnHumidity->getName(), sensorPath.columnTemp->getName(), i, 
                static_cast<int>(sensorPath.sensor->getLastError()));
            failedReadings++;
        }
    }

    if (failedReadings == 10) {
        LOG_INFO("All readings failed for '%v', '%v'.", sensorPath.columnHumidity->getName(), sensorPath.columnTemp->getName());
        return;
    }

    DhtSensorReading averageReading;
    for (int i = 0; i < (10 - failedReadings); i++) {
        averageReading.humidity += readings[i].humidity;
        averageReading.temperature += readings[i].temperature;
    }
    averageReading.humidity = std::roundf((averageReading.humidity / static_cast<float>(10 - failedReadings)) * 100.0f) / 100.0f;
    averageReading.temperature = std::roundf((averageReading.temperature/ static_cast<float>(10 - failedReadings)) * 100.0f) / 100.0f;

    LOG_INFO("Average reading of %v successful attempts: Humidity %v % RH, Temperature %v °C", 
        (10 - failedReadings), averageReading.humidity, averageReading.temperature);
}

void App::performReading(const DhtSensorPath& sensorPath) {
    std::vector<DhtSensorReading> readings;
    readings.reserve(3);
    int successfulReadings = 0;

    for (int i = 0; i < 10; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        if (sensorPath.sensor->poll()) {
            DhtSensorReading reading(sensorPath.sensor->getHumidity(), sensorPath.sensor->getTemperature());
            readings.push_back(reading);
            successfulReadings++;
        }
        if (successfulReadings == 3) {
            break;
        }
    }

    if (successfulReadings == 0) {
        sensorPath.columnHumidity->logNA();
        sensorPath.columnTemp->logNA();
        return;
    }

    DhtSensorReading averageReading;
    for (int i = 0; i < successfulReadings; i++) {
        averageReading.humidity += readings[i].humidity;
        averageReading.temperature += readings[i].temperature;
    }
    averageReading.humidity = std::roundf((averageReading.humidity / static_cast<float>(successfulReadings)) * 100.0f) / 100.0f;
    averageReading.temperature = std::roundf((averageReading.temperature/ static_cast<float>(successfulReadings)) * 100.0f) / 100.0f;

    sensorPath.columnHumidity->logValue(averageReading.humidity);
    sensorPath.columnTemp->logValue(averageReading.temperature);
}

bool App::pinNumberExists(hal::PinNumber_t pinNumber) {
    for (auto existingPin : sensorPins) {
        if (existingPin->getNumber() == pinNumber) {
            return true;
        }
    }
    return false;
}
