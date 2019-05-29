#ifndef DIGITALOUTPUTDEVICE
#define DIGITALOUTPUTDEVICE

#include <stdint.h>
#include <Arduino.h>

class DigitalOutputDevice {
protected:
	uint8_t pin;
  String name;

public:
	DigitalOutputDevice(uint8_t pin, String name);
 
  void controlOutput(bool state);
	void activate();
	void deactivate();
  String getName();
};

#endif
