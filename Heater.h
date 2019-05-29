#ifndef HEATER
#define HEATER

#include "DigitalOutputDevice.h"

class Heater: public DigitalOutputDevice {
public:
  Heater(uint8_t pin);
  Heater(uint8_t pin, String name);
};

#endif
