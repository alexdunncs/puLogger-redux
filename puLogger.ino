#include "Wire.h"
#include "Controller.h"
#include "FeedbackController.h"

#include "config_nano.h"

const uint8_t SENSORCOUNT = 1;
uint8_t SENSORADDRESSES[SENSORCOUNT] = {0x77};
String SENSORNAMES[SENSORCOUNT] = {"sensor1"};
//uint8_t SENSORADDRESSES[SENSORCOUNT] = {0x76, 0x77};
//String SENSORNAMES[SENSORCOUNT] = {"sensor1", "sensor2"};

Controller* puLogger = nullptr;
FeedbackController* temperatureController = nullptr;
FeedbackController* humidityController = nullptr;

void setup() {
	Serial.begin(57600);
	Wire.begin();
	
	puLogger = new Controller();
	
	puLogger->defineBME280Sensors(SENSORADDRESSES, SENSORNAMES, SENSORCOUNT);
  puLogger->defineBuzzer(BUZZERPIN);
  puLogger->defineHumidifier(FANPIN);
  puLogger->defineHeater(HEATPIN);

  humidityController = new FeedbackController(false,false,200);
  humidityController->defineInputs(reinterpret_cast<Sensor**>(puLogger->sensors), SENSORCOUNT,'H');
//  DigitalOutputDevice* humidifier[1] = {puLogger->humidifier};
//  humidityController->setSetpoint(65.0);
//  humidityController->setHysteresis(2.5);
//  humidityController->setUpperBound(70.0);
//  humidityController->defineOutputs(humidifier, 1);
  
  temperatureController = new FeedbackController(false,false,200);
  temperatureController->defineInputs(reinterpret_cast<Sensor**>(puLogger->sensors), SENSORCOUNT,'T');
//  DigitalOutputDevice* heater[1] = {puLogger->heater};
//  temperatureController->setSetpoint(25.0);
//  temperatureController->defineOutputs(heater, 1);
}

void loop() { 
  humidityController->poll();
  temperatureController->poll();
  delay(1000);
  Serial.println("");
}
