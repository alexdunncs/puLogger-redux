#ifndef FEEDBACKCONTROLLER
#define FEEDBACKCONTROLLER

#include <stdint.h>
#include "Bound.h"
#include "Sensor.h"
#include "SenseInput.h"
#include "DigitalOutputDevice.h"

class FeedbackController {
  public://debug
	SenseInput* inputs;
	DigitalOutputDevice** outputDevices;

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

  void testInput();
  void testOutput();
	
	void defineInputs(Sensor** sensorArray, uint8_t sensorArrayCount, char parameterCode);
	void defineOutputs(DigitalOutputDevice** outputDevices, uint8_t outputCount);
	void poll();
  void controlOutputs();
	
	double getMaxValue();
	double getAvgValue();
	double getMinValue();
	
	private:
	
};

#endif
