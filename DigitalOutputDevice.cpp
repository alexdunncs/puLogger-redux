#include "DigitalOutputDevice.h"


DigitalOutputDevice::DigitalOutputDevice(uint8_t pin) : pin(pin) {
	//Serial.print("Setting pin ");
  //Serial.print(pin);
  //Serial.print(" as OUTPUT.\n");
	pinMode(pin, OUTPUT);
}

void DigitalOutputDevice::activate() {
	digitalWrite(pin, 1);
}

void DigitalOutputDevice::deactivate() {
	digitalWrite(pin, 0);
}
