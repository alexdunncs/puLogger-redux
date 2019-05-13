#include "Buzzer.h"

Buzzer::Buzzer(uint8_t pin): DigitalOutputDevice(pin) {
	beep(); //self-test
}

void Buzzer::beep() {
  activate();
  delay(40);
  deactivate();
}

