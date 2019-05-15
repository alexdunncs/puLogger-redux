#include "BME280Sensor.h"
#include <Arduino.h>
#include "i2c-configuration.h"
#include "BME280.h"

BME280Sensor::BME280Sensor(): address(0), temperature(0), humidity(0), lastPolled(0){
  
}

BME280Sensor::BME280Sensor(uint8_t address): address(address), temperature(0), humidity(0), lastPolled(0){
  
}

void BME280Sensor::initialise() {
  //Serial.print("Initialising sensor ");
  //Serial.print(address);
  //Serial.print("\n"); //debug
  writeReg(0xF2, ctrl_hum_reg, address);
  writeReg(0xF4, ctrl_meas_reg, address);
  writeReg(0xF5, config_reg, address);
  pollSensor();
}

void BME280Sensor::pollSensor() {
  //Serial.print("Polling sensor ");
  //Serial.print(this->address);
  //Serial.print("\n"); //debug
	readTrim(address);
  readData(address);
  this->temperature = calibration_T(temp_raw) / 100.0;
  this->humidity = calibration_H(hum_raw) / 1024.0;
	lastPolled = millis();
}

double BME280Sensor::getTemperature() {
	if (millis() - lastPolled > 1000) {
		pollSensor();
	}
  //Serial.print("Temp is ");
  //Serial.print(temperature);
  //Serial.print("\n"); //debug
	return temperature;
}

double BME280Sensor::getHumidity() {
	if (millis() - lastPolled > 1000) {
		pollSensor();
	}
  //Serial.print("Humidity is ");
  //Serial.print(humidity);
  //Serial.print("\n"); //debug
	return humidity;
}


double BME280Sensor::get(char parameter) {
  switch(parameter) {
  case 'T':
    return getTemperature();
  case 'H':
    return getHumidity();
  }
  return 0.0;
}

