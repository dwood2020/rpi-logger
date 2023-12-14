#include "AppConfig.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include "nlohmann/json.hpp"
#include "Log.h"


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
        auto dht22Configs = cfgData["dht22Pins"];
        if (dht22Configs.is_array()) {
            for (const auto& cfg : dht22Configs) {

                if (cfg.contains("pinNumber") && cfg.contains("logName")) {
                    LOG_INFO("pinNumber: %v", cfg["pinNumber"]);
                    LOG_INFO("logName: %v", cfg["logName"]);
                    SensorConfig cfgInstance(static_cast<hal::PinNumber_t>(cfg["pinNumber"]), std::string(cfg["logName"]));
                    this->dht22Configs.push_back(cfgInstance);
                }
            }
        }
    }
    if (cfgData.contains("testMode")) {
        this->testMode = cfgData["testMode"];
    }
}

std::string AppConfig::toString(void) const {
    std::stringstream ss;
    ss << "AppConfig:\n";
    ss << "\tlogIntervalSec: " << logIntervalSec << "\n";
    ss << "\tcsvOutputDir: " << csvOutputDir << "\n";
    ss << "\tdht11Pins: [";
    if (!dht11Pins.empty()) {
        for (int i = 0; i < (dht11Pins.size() - 1); i++) {
            ss << dht11Pins[i] << ", ";
        }
        ss << dht11Pins.back();
    }
    ss << "]\n";

    ss << "\tdht22Pins: [";
    if (!dht22Configs.empty()) {
        for (int i = 0; i < (dht22Configs.size() - 1); i++) {
            ss << dht22Configs[i] << ", ";
        }
        ss << dht22Configs.back();
    }
    ss << "]\n";
    ss << "\ttestMode: " << ((testMode) ? "true" : "false") << "\n";
    return ss.str();
}


const std::vector<hal::PinNumber_t>& AppConfig::getDht11Pins(void) const {
    return dht11Pins;
}

const std::vector<SensorConfig>& AppConfig::getDht22Configs(void) const {
    return dht22Configs;
}

int AppConfig::getLogIntervalSec(void) const {
    return logIntervalSec;
}

std::string AppConfig::getCsvOutputDir(void) const {
    return std::move(csvOutputDir);
}

bool AppConfig::getTestMode(void) const {
    return testMode;
}
