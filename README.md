# rpi-logger
Temperature and humidity logger sofware based on the Raspberry Pi.    

Description TBD.    

#### Useful references:
- [Raspberry Pi GPIO Pinout](https://pinout.xyz/)
- [DHT11/DHT22 custom protocol implementation](https://www.iot-programmer.com/index.php/books/22-raspberry-pi-and-the-iot-in-c/chapters-raspberry-pi-and-the-iot-in-c/41-raspberry-pi-and-the-iot-in-c-a-custom-protocol-the-dht11-dht22)

## How to build
Currently, this project can only be built directly on the target platform (the Raspberry Pi).

```
mkdir build
cd build
cmake -G "Unix Makefiles" ..
cmake --build .
```

## Third-party dependencies
- [Broadcom BCM 2835 library](http://www.airspayce.com/mikem/bcm2835/) (**GPLv3!!**)
