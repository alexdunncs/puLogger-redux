#ifndef FEEDBACKCONTROLLER
#define FEEDBACKCONTROLLER

#include <stdint.h>
#include "Bound.h"

typedef double (*input)();
typedef void (*output)(bool state);

class FeedbackController {
	input* inputs;
	output* outputs;

  double* latestSensorData;
	
	uint8_t inputCount;
	uint8_t outputCount;
	
	Bound upperBound;
	Bound lowerBound;
	double setpoint;
  double hysteresis;

  bool currentControlState;
	bool inverselyProportional;
	bool pwmOutput;
	int controlPeriod;
	
	public:
	FeedbackController(bool inverselyProportional, bool pwmOutput, int controlPeriod);
	
	void setUpperBound(double value);
	void setLowerBound(double value);
	void setSetpoint(double setpoint);
  void setHysteresis(double hysteresis);
  
	
	void defineInputs(input* inputs, uint8_t inputCount);
	void defineOutputs(output* inputs, uint8_t outputCount);
	void poll();
  void controlOutputs();
	
	double getMaxValue();
	double getAvgValue();
	double getMinValue();
	
	private:
	
};

#endif
