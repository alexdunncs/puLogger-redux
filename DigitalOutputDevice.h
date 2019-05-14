#ifndef DIGITALOUTPUTDEVICE
#define DIGITALOUTPUTDEVICE

#include <stdint.h>
#include <Arduino.h>

class DigitalOutputDevice {
protected:
	uint8_t pin;

public:
	DigitalOutputDevice(uint8_t pin);
 
  void controlOutput(bool state);
	void activate();
	void deactivate();
};

#endif
