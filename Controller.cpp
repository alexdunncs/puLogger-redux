#include "Controller.h"

Controller::Controller(): sensors(nullptr), sensorsCount(0), heater(nullptr), humidifier(nullptr), buzzer(nullptr){
  
}
	
void Controller::defineBME280Sensors(uint8_t* addressArray, uint8_t sensorsCount) {
	this->sensorsCount = sensorsCount;
	delete this->sensors;
	this->sensors = new BME280Sensor[sensorsCount];
	for (int i = 0; i < sensorsCount; i++) {
		this->sensors[i] = BME280Sensor(addressArray[i]);
	}
}

void Controller::initialiseSensors() {
	for (int i = 0; i < sensorsCount; i++) {
    sensors[i].initialise();
	}
}

void Controller::defineHeater(uint8_t pin) {
	if (heater) {
    delete heater;
  }
  heater = new Heater(pin);
}

void Controller::defineHumidifier(uint8_t pin) {
	if (humidifier) {
    delete humidifier;
  }
  humidifier = new Humidifier(pin);
}

void Controller::defineBuzzer(uint8_t pin) {
	if (buzzer) {
    delete buzzer;
	}
  buzzer = new Buzzer(pin);
}

void Controller::beep() {
  if (buzzer) {
    buzzer->beep();
  }
}

