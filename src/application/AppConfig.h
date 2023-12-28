#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include <iostream>
#include "hal/IGpio.h"


class SensorConfig {
public:
    const hal::PinNumber_t pinNumber;
    const std::string logNameHumidity;
    const std::string logNameTemp;

    SensorConfig(hal::PinNumber_t pinNumber, const std::string& logNameHumidity, const std::string& logNameTemp): 
        pinNumber(pinNumber), logNameHumidity(logNameHumidity), logNameTemp(logNameTemp) {}

    inline friend std::ostream& operator<< (std::ostream& os, const SensorConfig& inst) {
        return  os << "{ pinNumber: " << inst.pinNumber << ", logNameHumidity: " << inst.logNameHumidity 
        << ", logNameTemperature: " << inst.logNameTemp << " }";
    }
};


class AppConfig {
private:
    std::vector<SensorConfig> dht11Configs{};
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

    const std::vector<SensorConfig>& getDht11Configs(void) const;
    const std::vector<SensorConfig>& getDht22Configs(void) const;
    int getLogIntervalSec(void) const;
    std::string getCsvOutputDir(void) const;
    bool getTestMode(void) const;
};
