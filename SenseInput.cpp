#include "SenseInput.h"

SenseInput::SenseInput(): sensor(nullptr), parameterCode(0) {
  
}

SenseInput::SenseInput(Sensor* _sensor, char _parameterCode): sensor(_sensor), calibrationOffset(0.0), parameterCode(_parameterCode) {
 
}

SenseInput::SenseInput(Sensor* _sensor, double _calibrationOffset, char _parameterCode): sensor(_sensor), calibrationOffset(_calibrationOffset), parameterCode(_parameterCode) {
 
}

double SenseInput::get() {
	return (sensor->get(parameterCode) + calibrationOffset);
}

char SenseInput::getParameterCode() {
  return parameterCode;
}

String SenseInput::getName() {
  return sensor->getName();
}
