#include "FeedbackController.h"
#include <stdint.h>
#include <Arduino.h>

FeedbackController::FeedbackController(bool inverselyProportional, bool pwmOutput, int controlPeriod)
: inputs(nullptr), outputs(nullptr), latestSensorData(nullptr), inputCount(0), outputCount(0),
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

void FeedbackController::defineInputs(input* inputs, uint8_t inputCount){

	if (this->inputs) {
		delete this->inputs;
	}

 if (this->latestSensorData) {
   delete latestSensorData;
  }
  
	this->inputCount = inputCount;
	(*this).inputs = new input [inputCount];
  this->latestSensorData = new double [inputCount];
  
	for (int i = 0; i < inputCount; i++) {
		this->inputs[i] = inputs[i];
    this->latestSensorData[i] = 0.0;
	}
}

void FeedbackController::defineOutputs(output* outputs, uint8_t outputCount){
	if (this->outputs) {
    delete this->outputs;
  }
  
  this->outputCount = outputCount;
  (*this).outputs = new output [outputCount];
  for (int i = 0; i < outputCount; i++) {
    this->outputs[i] = outputs[i];
    outputs[i](this->currentControlState);
  }
}

void FeedbackController::poll(){
  for (int i = 0; i < inputCount; i++) {
    this->latestSensorData[i] = inputs[i]();
  }

  controlOutputs();
}

void FeedbackController::controlOutputs() {
  bool controlState = currentControlState;
  Serial.print("Heat is currently ");
  Serial.println(currentControlState ? "on" : "off");

    //prepare to drive output based on average reading vs setpoint
  if (getAvgValue() < (this->setpoint - this->hysteresis)) {
    Serial.println("Temp low, turn on heat");
    controlState = this->inverselyProportional ? false : true;
  }
  else if (getAvgValue() > (this->setpoint + this->hysteresis)) {
    Serial.println("Temp high, turn off heat");
    controlState = this->inverselyProportional ? true : false;
  }

    //apply upper/lower bounds, giving priority to upper bound
  if (this->lowerBound.isSet && getMinValue() < this->lowerBound.value) {
    Serial.println("Applying lower bound");
    controlState = this->inverselyProportional ? false : true;
  }
  else if (this->upperBound.isSet && getMaxValue() > this->upperBound.value) {
    Serial.println("Applying upper bound");
    controlState = this->inverselyProportional ? true : false;
  }

  this->currentControlState = controlState;
  for (int i = 0; i < this->outputCount; i++) {
    outputs[i](controlState);
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
