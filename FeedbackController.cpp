#include "FeedbackController.h"
#include <stdint.h>
#include <Arduino.h>

FeedbackController::FeedbackController(bool inverselyProportional, bool pwmOutput, int controlPeriod)
: inputSensors(nullptr), getter(nullptr), outputDevices(nullptr), latestSensorData(nullptr), inputCount(0), outputCount(0),
	upperBound(), lowerBound(), setpoint(0.0), hysteresis(0.0),
	currentControlState(false), inverselyProportional(inverselyProportional), pwmOutput(pwmOutput), controlPeriod(controlPeriod) {
    
}

void FeedbackController::setUpperBound(double value){
	this->upperBound = Bound(value);
	poll();
}

void FeedbackController::setLowerBound(double value){
	this->lowerBound = Bound(value);
	poll();
}
	
void FeedbackController::setSetpoint(double setpoint){
	this->setpoint = setpoint;
	poll();
}

void FeedbackController::setHysteresis(double hysteresis) {
  this->hysteresis = hysteresis;
  poll();
}

void FeedbackController::testOutput() {
  while(true){
    Serial.print("testing");
    for (int i = 0; i < outputCount; i++) {
    Serial.print("on");
      outputDevices[i]->controlOutput(true);
    }
    delay(2000);
    for (int i = 0; i < outputCount; i++) {
    Serial.print("off");
      outputDevices[i]->controlOutput(false);
    }
    delay(2000);
  }
}

void FeedbackController::defineInputs(BME280Sensor* inputSensors, uint8_t inputCount, sensorFunction getter){

 if (this->latestSensorData) {
   delete latestSensorData;
  }

  this->inputSensors = inputSensors;
	this->inputCount = inputCount;
  this->getter = getter;
  this->latestSensorData = new double [inputCount];
  
	for (int i = 0; i < inputCount; i++) {
    this->latestSensorData[i] = 0.0;
	}
}

void FeedbackController::defineOutputs(DigitalOutputDevice** deviceArray, uint8_t deviceArrayCount){
  if (outputDevices) {
    delete outputDevices; 
  }
  outputDevices = new DigitalOutputDevice* [deviceArrayCount];
  outputCount = deviceArrayCount;
  
  for (int i = 0; i < outputCount; i++) {
    outputDevices[i] = deviceArray[i];
    outputDevices[i]->controlOutput(currentControlState);
  }
}

void FeedbackController::poll(){
  for (int i = 0; i < inputCount; i++) {
    this->latestSensorData[i] = (inputSensors[i].*(((FeedbackController*)this)->FeedbackController::getter))();
  }

  controlOutputs();
}

void FeedbackController::controlOutputs() {
  bool controlState = currentControlState;

    //prepare to drive output based on average reading vs setpoint
  if (getAvgValue() < (this->setpoint - this->hysteresis)) {
    controlState = this->inverselyProportional ? false : true;
  }
  else if (getAvgValue() > (this->setpoint + this->hysteresis)) {
    controlState = this->inverselyProportional ? true : false;
  }

    //apply upper/lower bounds, giving priority to upper bound
  if (this->lowerBound.isSet && getMinValue() < this->lowerBound.value) {
    controlState = this->inverselyProportional ? false : true;
  }
  else if (this->upperBound.isSet && getMaxValue() > this->upperBound.value) {
    controlState = this->inverselyProportional ? true : false;
  }

  this->currentControlState = controlState;
  for (int i = 0; i < this->outputCount; i++) {
    outputDevices[i]->controlOutput(controlState);
  }
}

double FeedbackController::getMaxValue(){
  double maximum = 0.0;

	for (int i = 0; i < inputCount; i++) {
    if (i == 0) {
      maximum = this->latestSensorData[0];
    }
    else if (i == 1) {
      maximum = max(this->latestSensorData[0], this->latestSensorData[1]);
    }
    else {
      maximum = max(this->latestSensorData[i], maximum);
    }
  }
  
	return maximum;
}

double FeedbackController::getAvgValue(){
	double acc = 0.0;
  double average = 0.0;

  for (int i = 0; i < inputCount; i++) {
    acc += this->latestSensorData[i];
  }
  
  average = acc / double(inputCount);
  return average;
}

double FeedbackController::getMinValue(){
	double minimum = 0.0;

  for (int i = 0; i < inputCount; i++) {
    if (i == 0) {
      minimum = this->latestSensorData[0];
    }
    else if (i == 1) {
      minimum = min(this->latestSensorData[0], this->latestSensorData[1]);
    }
    else {
      minimum = min(this->latestSensorData[i], minimum);
    }
  }
  
  return minimum;
}
