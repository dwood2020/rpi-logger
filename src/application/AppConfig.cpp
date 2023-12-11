#include "AppConfig.h"
#include <filesystem>
#include <fstream>
#include "nlohmann/json.hpp"


void AppConfig::parse(std::filesystem::path configFileDir) {
    std::filesystem::path filepath = configFileDir;
    if (!std::filesystem::is_directory(filepath)) {
        filepath = filepath.parent_path();
    }
    filepath.append(appConfigFileName);

    std::ifstream f(filepath);
    if (!f.good()) {
        throw std::runtime_error("Could not read config file");
    }
    nlohmann::json cfgData = nlohmann::json::parse(f);

    if (cfgData.contains("logIntervalSec")) {
        this->logIntervalSec = cfgData["logIntervalSec"];
    }
    if (cfgData.contains("dht11Pins")) {
        auto dht11Pins = cfgData["dht11Pins"];
        if (dht11Pins.is_array()) {
            for (const auto& pin : dht11Pins) {
                this->dht11Pins.push_back(pin);
            }
        }
    }
    if (cfgData.contains("dht22Pins")) {
        auto dht22Pins = cfgData["dht22Pins"];
        if (dht22Pins.is_array()) {
            for (const auto& pin : dht22Pins) {
                this->dht22Pins.push_back(pin);
            }
        }
    }
}

const std::vector<hal::PinNumber_t>& AppConfig::getDht11Pins(void) const {
    return dht11Pins;
}

const std::vector<hal::PinNumber_t>& AppConfig::getDht22Pins(void) const {
    return dht22Pins;
}

int AppConfig::getLogIntervalSec(void) const {
    return logIntervalSec;
}

std::string AppConfig::getCsvOutputDir(void) const {
    return std::move(csvOutputDir);
}
