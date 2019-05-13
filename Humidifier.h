#ifndef HUMIDIFIER
#define HUMIDIFIER

#include "DigitalOutputDevice.h"

class Humidifier: public DigitalOutputDevice {
public:
  Humidifier(uint8_t pin);
};

#endif
