#ifndef SENSEINPUT
#define SENSEINPUT

#include "Sensor.h"

class SenseInput {
	Sensor* sensor;
	char parameterCode;
	
public:
		SenseInput();
    SenseInput(Sensor* _sensor, char _parameterCode);
    double get();
};

#endif
