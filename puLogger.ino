#include "Wire.h"
#include "Controller.h"
#include "printf.h"
#include "FeedbackController.h"

const uint8_t SENSORCOUNT = 2;
uint8_t SENSORADDRESSES[SENSORCOUNT] = {0x77, 0x76};
const int BUZZERPIN = 2;
const int FANPIN = 5;
const int HEATPIN = 4;

Controller* puLogger = nullptr;
FeedbackController* temperatureController = nullptr;
FeedbackController* humidityController = nullptr;

void setup() {
	Serial.begin(57600);
	Wire.begin();
  printf_begin();
	
	puLogger = new Controller();
	
	puLogger->defineBME280Sensors(SENSORADDRESSES, SENSORCOUNT);
	puLogger->initialiseSensors();
  puLogger->defineBuzzer(BUZZERPIN);
  puLogger->defineHumidifier(FANPIN);
  puLogger->defineHeater(HEATPIN);

  BME280Sensor* humiditySensors = puLogger->sensors;
  humidityController->defineInputs(humiditySensors, 1, &BME280Sensor::getHumidity);
  
  DigitalOutputDevice humidifier[1] = {puLogger->humidifier};
  humidityController = new FeedbackController(false,false,200);
  humidityController->setSetpoint(70.0);
  humidityController->setHysteresis(0.0);
  humidityController->defineOutputs(humidifier, 1);
  

  Serial.println("ready to go");
  humidityController->poll();
}

void loop() { 
  humidityController->poll();
  delay(1000);
}
