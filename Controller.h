#ifndef CONTROLLER
#define CONTROLLER

#include <stdint.h>
#include "BME280Sensor.h"
#include "Heater.h"
#include "Humidifier.h"
#include "Buzzer.h"


class Controller {
public:
	BME280Sensor* sensors;
	uint8_t sensorsCount;
	Heater* heater;
	Humidifier* humidifier;
  Buzzer* buzzer;
	
public:
  Controller();
	void defineBME280Sensors(uint8_t* addressArray, uint8_t sensorsCount);
	void initialiseSensors();
	void defineHeater(uint8_t pin);
	void defineHumidifier(uint8_t pin);
	void defineBuzzer(uint8_t pin);

  void beep();
};

#endif
