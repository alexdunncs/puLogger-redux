#include "Buzzer.h"

Buzzer::Buzzer(uint8_t pin): DigitalOutputDevice(pin, "BUZZER") {
  beep(); //self-test
}

Buzzer::Buzzer(uint8_t pin, String name): DigitalOutputDevice(pin, name) {
  beep(); //self-test
}

void Buzzer::beep() {
  activate();
  delay(40);
  deactivate();
}
