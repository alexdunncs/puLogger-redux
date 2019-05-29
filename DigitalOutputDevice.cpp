#include "DigitalOutputDevice.h"


DigitalOutputDevice::DigitalOutputDevice(uint8_t pin, String name) : pin(pin), name(name) {
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

String DigitalOutputDevice::getName() {
  return name;
}
