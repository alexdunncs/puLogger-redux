#ifndef BUZZER
#define BUZZER

#include "DigitalOutputDevice.h"

class Buzzer: public DigitalOutputDevice {
public:
	Buzzer(uint8_t pin);
  Buzzer(uint8_t pin, String name);

	void beep();
  void longBeep();
  
};

#endif
