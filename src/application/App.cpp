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
        auto column = std::make_shared<csv::Column>(cfg.logName);
        dht11SensorPaths.emplace_back(std::make_unique<Dht11>(*pin), column);
        csvWriter->addColumn(column);
        LOG_INFO("Added DHT11 config: pin %v, log name '%v'", pin->getNumber(), column->getName());
    }

    for (const SensorConfig cfg : config.getDht22Configs()) {
        if (pinNumberExists(cfg.pinNumber)) {
            LOG_WARN("Pin number %v already exists. Skipping.", cfg.pinNumber);
            continue;
        }

        auto pin = new DigitalReconfigurableIo(*gpio, cfg.pinNumber);
        sensorPins.push_back(pin);
        auto column = std::make_shared<csv::Column>(cfg.logName);
        dht22SensorPaths.emplace_back(std::make_unique<Dht22>(*pin), column);
        csvWriter->addColumn(column);
        LOG_INFO("Added DHT22 config: pin %v, log name '%v'", pin->getNumber(), column->getName());
    }

    testMode = config.getTestMode();

    return true;
}

void App::run(void) {
    if (testMode) {
        runTest();
        return;
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
            LOG_ERROR("Sensor path '%v' reading #%v failed. Error code %v", 
                sensorPath.column->getName(), i, static_cast<int>(sensorPath.sensor->getLastError()));
            failedReadings++;
        }
    }

    if (failedReadings == 10) {
        LOG_INFO("All readings failed for '%v'.", sensorPath.column->getName());
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

bool App::pinNumberExists(hal::PinNumber_t pinNumber) {
    for (auto existingPin : sensorPins) {
        if (existingPin->getNumber() == pinNumber) {
            return true;
        }
    }
    return false;
}
