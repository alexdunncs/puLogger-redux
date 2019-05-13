#ifndef DIGITALOUTPUTDEVICE
#define DIGITALOUTPUTDEVICE

#include <stdint.h>
#include <Arduino.h>

class DigitalOutputDevice {
private:
	uint8_t pin;

public:
	DigitalOutputDevice(uint8_t pin);
	void activate();
	void deactivate();
};

#endif
