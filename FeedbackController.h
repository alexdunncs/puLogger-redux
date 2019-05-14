#ifndef FEEDBACKCONTROLLER
#define FEEDBACKCONTROLLER

#include <stdint.h>
#include "Bound.h"
#include "BME280Sensor.h"
#include "DigitalOutputDevice.h"

typedef double (BME280Sensor::*sensorFunction)();
//typedef void (DigitalOutputDevice::*output)(bool state);

class FeedbackController {
	BME280Sensor* inputSensors;
  sensorFunction getter; 
	DigitalOutputDevice* outputDevices;

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
  
	
	void defineInputs(BME280Sensor* inputSensors, uint8_t inputCount, sensorFunction getter);
	void defineOutputs(DigitalOutputDevice* outputDevices, uint8_t outputCount);
	void poll();
  void controlOutputs();
	
	double getMaxValue();
	double getAvgValue();
	double getMinValue();
	
	private:
	
};

#endif
