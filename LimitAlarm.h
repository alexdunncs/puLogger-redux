#ifndef LIMITALARM
#define LIMITALARM

#include "Bound.h"

class LimitAlarm {
	Bound lowLimit;
	Bound highLimit;
	unsigned int timeout;
	unsigned long long int activationTime;
	
public:
  LimitAlarm();
	LimitAlarm(double _lowLimit, double _highLimit);
	bool check(double min, double max);
};

#endif
