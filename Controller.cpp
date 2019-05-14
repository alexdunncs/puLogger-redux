#include "Controller.h"

Controller::Controller(): sensors(nullptr), sensorsCount(0), heater(nullptr), humidifier(nullptr), buzzer(nullptr){
  
}
	
void Controller::defineBME280Sensors(uint8_t* addressArray, uint8_t sensorsCount) {
  //Serial.print("Defining ");
  //Serial.print(sensorsCount);
  //Serial.print(" BME280 sensors\n");
	this->sensorsCount = sensorsCount;
	delete this->sensors;
	this->sensors = new BME280Sensor[sensorsCount];
	for (int i = 0; i < sensorsCount; i++) {
		this->sensors[i] = BME280Sensor(addressArray[i]);
    //Serial.print("Defining sensor ");
    //Serial.print(i);
    //Serial.print(" with address ");
    //Serial.print(this->sensors[i].address);
    //Serial.print("\n");
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

