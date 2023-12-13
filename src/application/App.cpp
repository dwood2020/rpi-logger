#include "App.h"
#include <filesystem>
#include "AppConfig.h"
#include "Log.h"


App::App(hal::IGpio& gpio): gpio(&gpio) {
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

    for (const hal::PinNumber_t pin : config.getDht11Pins()) {
        // TODO: Check if pin number is already given
        sensorPins.push_back(DigitalReconfigurableIo(*gpio, pin));  // TODO: This causes compiler error. Uses copy-constructor.
        // TODO: Continue here - Maybe use smart pointers? Is probably better than this
        dht11Sensors.push_back(Dht11(sensorPins.back()));
    }


    return true;
}

void App::run(void) {
}
