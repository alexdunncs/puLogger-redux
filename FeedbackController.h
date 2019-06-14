#ifndef FEEDBACKCONTROLLER
#define FEEDBACKCONTROLLER

#include <stdint.h>
#include "Bound.h"
#include "Sensor.h"
#include "SenseInput.h"
#include "DigitalOutputDevice.h"
#include "Buzzer.h"

class FeedbackController {
  public://debug
	SenseInput* inputs;
	DigitalOutputDevice** outputDevices;
  Buzzer* buzzer;
  

  double* latestSensorData;
	
	uint8_t inputCount;
	uint8_t outputCount;
	
	Bound upperBound;
	Bound lowerBound;
	double setpoint;
  double hysteresis;
  Bound alarmUpperThreshold;
  Bound alarmLowerThreshold;
  unsigned long gracePeriodMillis;
  bool activeAlarm;
  unsigned long inAlarmStateSince;

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
  void setAlarm(double lowLimit, double highLimit, unsigned long gracePeriodMillis);
  void removeAlarm();

  void testInput();
  void testOutput();
	
  void defineInputs(Sensor** sensorArray, uint8_t sensorArrayCount, char parameterCode);
  void defineInputs(Sensor** sensorArray, double* calibrationOffsetArray, uint8_t sensorArrayCount, char parameterCode);
	void defineOutputs(DigitalOutputDevice** outputDevices, uint8_t outputCount);
  void defineBuzzer(Buzzer* buzzer);

  bool existingAlarmState();
  void soundAlarm();
	void updateAlarmState(bool valueOutOfBounds);
	void poll();
  void controlOutputs();
	
	double getMaxValue();
	double getAvgValue();
	double getMinValue();
	
	private:
	
};

#endif
