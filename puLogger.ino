#include "Wire.h"
#include "Controller.h"
#include "printf.h"
#include "FeedbackController.h"

const uint8_t SENSORCOUNT = 2;
uint8_t SENSORADDRESSES[SENSORCOUNT] = {0x77, 0x76};
const int BUZZERPIN = 2;
const int FANPIN = 5;
const int HEATPIN = 4;

int step = 0;
double simReadings[10] = {5.5,4.5,3.5,4.5,5.5,6.5,7.5,8.5,7.5,6.0};
//should result in off, off, on, on, on, off, off, off, off, off

double foo() {
  double reading = simReadings[step++];
  Serial.print("Read ");
  Serial.println(reading);
  return reading;
}

void bar(bool state) {
  Serial.println(state ? "on" : "off");
}

Controller* puLogger = nullptr;
FeedbackController* testController = nullptr;

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

  testController = new FeedbackController(false, false, 200);
  input inputs[1] = {foo};
  output outputs[1] = {bar};
  
  testController->defineInputs(inputs, 1);
  testController->defineOutputs(outputs, 1);
  
  testController->setSetpoint(5.0);
  testController->setHysteresis(1.0);
  
  Serial.println("ready to go");
  testController->poll();
}

void loop() { 
  if (step <= 10) {
    testController->poll();
  }
  delay(1000);
}
