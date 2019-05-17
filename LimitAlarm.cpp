#include "LimitAlarm.h"
#include <Arduino.h>

LimitAlarm::LimitAlarm(): lowLimit(Bound()), highLimit(Bound()) {
	
}

LimitAlarm::LimitAlarm(double _lowLimit, double _highLimit):  lowLimit(Bound(_lowLimit)), highLimit(Bound(_highLimit)) {
	
}

bool LimitAlarm::check(double min, double max) {
	bool inAlarm = true;
	if (activationTime == 0) {
		if ( (lowLimit.isSet && min < lowLimit.value) ||
				(highLimit.isSet && max > highLimit.value)) {
				activationTime = millis();
		}
		else {
			inAlarm = false;
		}
	}
	else {
		if ( (!lowLimit.isSet || min >= lowLimit.value) &&
				(!highLimit.isSet || max <= highLimit.value)) {
				activationTime = 0;
				inAlarm = false;
		}
	}
	
	if (activationTime - millis() < (unsigned long long int)timeout) {
		inAlarm = false;
	}
	
	return inAlarm;
}
