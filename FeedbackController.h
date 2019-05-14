#ifndef FEEDBACKCONTROLLER
#define FEEDBACKCONTROLLER

#include <stdint.h>

typedef double (*input)();
typedef void (*output)(bool state);

class FeedbackController {
	input* inputs;
	output* outputs;

  double* latestSensorData;
	
	uint8_t inputCount;
	uint8_t outputCount;
	
	double upperBound;
	double lowerBound;
	double setpoint;
	
	bool inverselyProportional;
	bool pwmOutput;
	int controlPeriod;
	
	public:
	FeedbackController(bool inverselyProportional, bool pwmOutput, int controlPeriod);
	
	void setUpperBound(double upperBound);
	void setLowerBound(double lowerBound);
	void setSetpoint(double setpoint);
	
	void defineInputs(input* inputs, uint8_t inputCount);
	void defineOutputs(output* inputs, uint8_t outputCount);
	void poll();
	
	double getMaxValue();
	double getAvgValue();
	double getMinValue();
	
	private:
	
};

#endif
