#include "Wire.h"
#include "Controller.h"
#include "printf.h"

const uint8_t SENSORCOUNT = 2;
uint8_t SENSORADDRESSES[SENSORCOUNT] = {0x77, 0x76};

Controller* puLogger = nullptr;

void setup() {
	Serial.begin(57600);
	Wire.begin();
  printf_begin();
	
	puLogger = new Controller();
	
	puLogger->defineBME280Sensors(SENSORADDRESSES, SENSORCOUNT);
	puLogger->initialiseSensors();
}

void loop() {
	puLogger->sensors[0].getTemperature();
	puLogger->sensors[0].getHumidity();
	puLogger->sensors[1].getTemperature(); 
  puLogger->sensors[1].getHumidity();	
  Serial.print("\n");
	delay(5000);
}
