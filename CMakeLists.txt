cmake_minimum_required(VERSION 3.10)
project(puLogger)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)
include_directories(../libraries/Arduino_Core)
include_directories(../libraries/)
include_directories("G:/Program Files (x86)/Arduino/hardware/arduino/avr/libraries")


add_executable(puLogger
        BME280Sensor.cpp
        BME280Sensor.h
        Controller.cpp
        Controller.h
        DigitalOutputDevice.cpp
        DigitalOutputDevice.h
        i2c-configuration.h
        puLogger.ino)
