#include "DigitalOutputDevice.h"


DigitalOutputDevice::DigitalOutputDevice(uint8_t pin) : pin(pin) {
	pinMode(pin, OUTPUT);
}

void DigitalOutputDevice::controlOutput(bool state) {
  digitalWrite(pin, state ? 1 : 0);
}

void DigitalOutputDevice::activate() {
	controlOutput(true);
}

void DigitalOutputDevice::deactivate() {
	controlOutput(false);
}

