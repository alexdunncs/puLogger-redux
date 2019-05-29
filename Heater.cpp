#include "Heater.h"

Heater::Heater(uint8_t pin): DigitalOutputDevice(pin, "HEATER") {
  
}

Heater::Heater(uint8_t pin, String name): DigitalOutputDevice(pin, name) {
 
}
