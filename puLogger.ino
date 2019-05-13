#include "Wire.h"
#include "Controller.h"
#include "printf.h"

const uint8_t SENSORCOUNT = 2;
uint8_t SENSORADDRESSES[SENSORCOUNT] = {0x77, 0x76};
const int BUZZERPIN = 2;
const int FANPIN = 5;
const int HEATPIN = 4;


Controller* puLogger = nullptr;

void setup() {
	Serial.begin(57600);
	Wire.begin();
  printf_begin();
	
	puLogger = new Controller();
	
	puLogger->defineBME280Sensors(SENSORADDRESSES, SENSORCOUNT);
	puLogger->initialiseSensors();
  puLogger->defineBuzzer(BUZZERPIN);
}

void loop() { 
  puLogger->beep();
	delay(5000);
}
