#pragma once
#include <filesystem>
#include <list>
#include <vector>
#include "AppConfig.h"
#include "hal/IGpio.h"
#include "driver/DigitalIo.h"
#include "driver/Dht11.h"
#include "driver/Dht22.h"


/**
 * Represents the app instance.
*/
class App final {
private:
    hal::IGpio* gpio;
    std::list<DigitalReconfigurableIo> sensorPins;
    std::vector<Dht11> dht11Sensors;
    std::vector<Dht22> dht22Sensors;
    int logIntervalSec = 0;
    std::filesystem::path outputPath;

public:
    App(hal::IGpio& gpio);
    ~App() = default;

    bool init(void);
    void run(void);
};
