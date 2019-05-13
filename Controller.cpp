#include "Controller.h"

Controller::Controller(): sensors(nullptr), sensorsCount(0), heater(nullptr), humidifier(nullptr){
  
}
	
void Controller::defineBME280Sensors(uint8_t* addressArray, uint8_t sensorsCount) {
  Serial.print("Defining ");
  Serial.print(sensorsCount);
  Serial.print(" BME280 sensors\n");
	this->sensorsCount = sensorsCount;
	delete this->sensors;
	this->sensors = new BME280Sensor[sensorsCount];
	for (int i = 0; i < sensorsCount; i++) {
		this->sensors[i] = BME280Sensor(addressArray[i]);
    Serial.print("Defining sensor ");
    Serial.print(i);
    Serial.print(" with address ");
    Serial.print(this->sensors[i].address);
    Serial.print("\n");
	}
}

void Controller::initialiseSensors() {
	for (int i = 0; i < sensorsCount; i++) {
    sensors[i].initialise();
	}
}

void Controller::addHeater(uint8_t pin) {
	
}

void Controller::addHumidifier(uint8_t pin) {
	
}

void Controller::addBuzzer(uint8_t pin) {
	
}
