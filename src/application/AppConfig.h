#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include <iostream>
#include "hal/IGpio.h"


class SensorConfig {
public:
    const hal::PinNumber_t pinNumber;
    const std::string logName;

    SensorConfig(hal::PinNumber_t pinNumber, const std::string& logName): pinNumber(pinNumber), logName(logName) {}

    inline friend std::ostream& operator<< (std::ostream& os, const SensorConfig& inst) {
        return  os << "{" << inst.pinNumber << ", " << inst.logName << "}";
    }
};


class AppConfig {
private:
    std::vector<hal::PinNumber_t> dht11Pins{};
    std::vector<SensorConfig> dht22Configs{};
    int logIntervalSec = 60;
    std::string csvOutputDir;
    bool testMode = true;

public:
    static constexpr auto appConfigFileName = "rpiLoggerConfig.json";

    AppConfig() = default;
    virtual ~AppConfig() = default;

    void parse(std::filesystem::path configFileDir);
    std::string toString(void) const;

    const std::vector<hal::PinNumber_t>& getDht11Pins(void) const;
    const std::vector<SensorConfig>& getDht22Configs(void) const;
    int getLogIntervalSec(void) const;
    std::string getCsvOutputDir(void) const;
    bool getTestMode(void) const;
};
