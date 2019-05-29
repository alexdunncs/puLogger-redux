#ifndef SENSOR
#define SENSOR

#include <Arduino.h>

class Sensor {
public:
  virtual double get(char parameter) = 0;
  virtual String getName() = 0;
};

#endif
