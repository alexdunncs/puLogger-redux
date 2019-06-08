#ifndef SENSEINPUT
#define SENSEINPUT

#include "Sensor.h"

class SenseInput {
	Sensor* sensor;
	double calibrationOffset;
	char parameterCode;
	
public:
		SenseInput();
    SenseInput(Sensor* _sensor, char _parameterCode);
    SenseInput(Sensor* _sensor, double _calibrationOffset, char _parameterCode);
    double get();
    char getParameterCode();
    String getName();
};

#endif
