#include "App.h"
#include <filesystem>
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

    this->outputPath = outputPath;
    Log::init(outputPath);

    if (!gpio->init()) {
        LOG_ERROR("Could not init GPIO device.");
        return false;
    }

    for (const SensorConfig cfg : config.getDht11Configs()) {
        if (pinNumberExists(cfg.pinNumber)) {
            LOG_WARN("Pin number %v already exists. Skipping.", cfg.pinNumber);
            continue;
        }

        auto pin = new DigitalReconfigurableIo(*gpio, cfg.pinNumber);
        sensorPins.push_back(pin);
        dht11Sensors.push_back(Dht11(*pin));
    }

    for (const SensorConfig cfg : config.getDht22Configs()) {
        if (pinNumberExists(cfg.pinNumber)) {
            LOG_WARN("Pin number %v already exists. Skipping.", cfg.pinNumber);
            continue;
        }

        auto pin = new DigitalReconfigurableIo(*gpio, cfg.pinNumber);
        sensorPins.push_back(pin);
        dht22Sensors.push_back(Dht22(*pin));
        LOG_INFO("Added DHT22 config: %v, %v", cfg.pinNumber, cfg.logName);
    }

    return true;
}

void App::run(void) {
}

bool App::pinNumberExists(hal::PinNumber_t pinNumber) {
    for (auto existingPin : sensorPins) {
        if (existingPin->getNumber() == pinNumber) {
            return true;
        }
    }
    return false;
}
