#ifndef BME280SENSOR
#define BME280SENSOR

#include "Sensor.h"
#include <stdint.h>
#include <Arduino.h>

class BME280Sensor: public Sensor{
public: //debug
  String name;
	uint8_t address;
	double temperature;
	double humidity;
	long long unsigned int lastPolled;
	
public:
  BME280Sensor();
  BME280Sensor(uint8_t address, String name);

  void initialise();
	void pollSensor();
  String getName();
	double getTemperature();
	double getHumidity();
  double get(char parameter);

private:
  unsigned long int hum_raw,temp_raw,pres_raw;
  signed long int t_fine;

  uint16_t dig_T1;
  int16_t dig_T2;
  int16_t dig_T3;
  uint16_t dig_P1;
  int16_t dig_P2;
  int16_t dig_P3;
  int16_t dig_P4;
  int16_t dig_P5;
  int16_t dig_P6;
  int16_t dig_P7;
  int16_t dig_P8;
  int16_t dig_P9;
  int8_t  dig_H1;
  int16_t dig_H2;
  int8_t  dig_H3;
  int16_t dig_H4;
  int16_t dig_H5;
  int8_t  dig_H6;

  void readTrim(uint8_t address);
  void writeReg(uint8_t reg_address, uint8_t data, uint8_t sensorAddress);
  void readData(uint8_t sensorAddress);
  signed long int calibration_T(signed long int adc_T);
  unsigned long int calibration_P(signed long int adc_P);
  unsigned long int calibration_H(signed long int adc_H);
  
  
  
};

#endif
