#include "SenseInput.h"

SenseInput::SenseInput(): sensor(nullptr), parameterCode(0) {
  
}

SenseInput::SenseInput(Sensor* _sensor, char _parameterCode): sensor(_sensor), parameterCode(_parameterCode) {
 
}

double SenseInput::get() {
	return sensor->get(parameterCode);
}

char SenseInput::getParameterCode() {
  return parameterCode;
}
