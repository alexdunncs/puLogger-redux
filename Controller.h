#ifndef CONTROLLER
#define CONTROLLER

#include <stdint.h>
#include "BME280Sensor.h"
#include "Heater.h"
#include "Humidifier.h"


class Controller {
public:
	BME280Sensor* sensors;
	uint8_t sensorsCount;
	Heater* heater;
	Humidifier* humidifier;
	
public:
  Controller();
	void defineBME280Sensors(uint8_t* addressArray, uint8_t sensorsCount);
	void initialiseSensors();
	void addHeater(uint8_t pin);
	void addHumidifier(uint8_t pin);
	void addBuzzer(uint8_t pin);
};

#endif
