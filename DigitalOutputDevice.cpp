#include "DigitalOutputDevice.h"


DigitalOutputDevice::DigitalOutputDevice(uint8_t pin) : pin(pin) {
	pinMode(pin, OUTPUT);
}

void DigitalOutputDevice::activate() {
	digitalWrite(pin, 1);
}

void DigitalOutputDevice::deactivate() {
	digitalWrite(pin, 0);
}
