# rpi-logger
Temperature and humidity logging software for the Raspberry Pi.    
Intended to be used with DHT-11 or DHT-22 temperature and humidity sensors.    

For a release history list, see [RELEASE_HISTORY.md](RELEASE_HISTORY.md).

## Installation
- Move the release directory to your preferred installation location and rename.
- From that exact same location, run
    ```
    chmod +x installStartService.sh
    sudo ./installStartService.sh
    ```
- Adapt `rpiLoggerConfig.json` as required.

## Usage
Multiple DHT-11 and DHT-22 sensors are supported and the logger is configurable to a certain extent via a JSON configuration file.
Logging interval, CSV output directory and "sensor paths" are configurable.
A sensor path refers to a GPIO input pin number + 2 CSV column names.
The input pin is connected to the sensor's data line and the CSV column names are labels to the output humidity and temperature values.

### Example:
The configuration file must be named `rpiLoggerConfig.json` and must reside next to the executable.
For an example case with a single DHT-22 sensor connected to GPIO pin 24 (physical 18), the configuration file has the 
following structure:
```json
{
    "logIntervalSec": 60,
    "csvOutputDir": ".",
    "dht11Configs": [],
    "dht22Configs": [
        {
            "pinNumber": 24,
            "logNameHumidity": "sensor1_humidity",
            "logNameTemperature": "sensor1_temp"
        }
    ],
    "testMode": false
}
```
whereas
- `logIntervalSec` is the logging interval in seconds
- `csvOutputDir` is the relative output directory for the CSV and logfiles
- `dht11Configs` is a list of DHT-11 sensor path configurations with 
    - `pinNumber` the GPIO pin number connected to the sonsor's "data" pin
    - `logNameHumidity` the column name for logging the humidity value 
    - `logNameTemperature` the same for the temperature value
- `dht22Configs` is a list of DHT-22 sensor path configurations
- `testMode` if set to `true`, the application enters a test mode which does not write CSVs but prints verbose outputs for sensor 
connection testing.

### Useful references:
- [Raspberry Pi GPIO Pinout](https://pinout.xyz/)
- [DHT11/DHT22 custom protocol implementation](https://www.iot-programmer.com/index.php/books/22-raspberry-pi-and-the-iot-in-c/chapters-raspberry-pi-and-the-iot-in-c/41-raspberry-pi-and-the-iot-in-c-a-custom-protocol-the-dht11-dht22)

## How to build
This project can either be built on the target platform (a Raspberry Pi, tested on the models 4, 3B+) or on any other host platform with a 
C++20 compiler.    
To build on a Raspberry Pi, run
```
mkdir build
cd build
cmake -G "Unix Makefiles" ..
cmake --build .
```

To build on a host platform, run
```
mkdir build
cd build
cmake -G <preferred generator, e.g. Ninja> .. -DHOSTED=ON
cmake --build .
```

## How to create a release
```
mkdir build 
cd build
cmake -G <preferred generator> -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
cmake --install . --config Release
```
The release files are bundled in a directory `release`.

## Third-party dependencies
- [Broadcom BCM 2835 library](http://www.airspayce.com/mikem/bcm2835/) (**GPLv3**)
- [Easylogging++ library](https://github.com/abumq/easyloggingpp) (MIT)
- [JSON for Modern C++](https://json.nlohmann.me/) (MIT)

### Note on licensing
This software includes the GPLv3-licensed BCM 2835 library and must therefore 
itself be licensed under GPLv3, see [LICENSE.txt](LICENSE.txt).    
To follow common practises, a short licensing information block is included at 
the top of every source file.
