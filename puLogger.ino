#include "Wire.h"
#include "Controller.h"
#include "printf.h"
#include "FeedbackController.h"

const uint8_t SENSORCOUNT = 2;
uint8_t SENSORADDRESSES[SENSORCOUNT] = {0x77, 0x76};
const int BUZZERPIN = 4; //2;
const int FANPIN = 5;
const int HEATPIN = 4;

double foo() {
  Serial.println("foo");
  return 5.0;
}

double bar() {
  Serial.println("bar");
  return 10.0;
}

double foobar() {
  Serial.println("foobar");
  return 100.0;
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
  input inputs[3] = {foo, bar, foobar};
  testController->defineInputs(inputs, 3);
  testController->poll();
  Serial.println(testController->getMinValue());
  Serial.println(testController->getAvgValue());
  Serial.println(testController->getMaxValue());
  
}

void loop() { 
  delay(10000);
}
