#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include "hal/IGpio.h"


class AppConfig {
private:
    std::vector<hal::PinNumber_t> dht11Pins{};
    std::vector<hal::PinNumber_t> dht22Pins{};
    int logIntervalSec = 60;
    std::string csvOutputDir;

public:
    static constexpr auto appConfigFileName = "rpiLoggerConfig.json";

    AppConfig() = default;
    virtual ~AppConfig() = default;

    void parse(std::filesystem::path configFileDir);
    std::string toString(void) const;

    const std::vector<hal::PinNumber_t>& getDht11Pins(void) const;
    const std::vector<hal::PinNumber_t>& getDht22Pins(void) const;
    int getLogIntervalSec(void) const;
    std::string getCsvOutputDir(void) const;
};
