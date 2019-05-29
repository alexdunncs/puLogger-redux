#include "Humidifier.h"

Humidifier::Humidifier(uint8_t pin): DigitalOutputDevice(pin, "HUMIDIFIER") {
  
}

Humidifier::Humidifier(uint8_t pin, String name): DigitalOutputDevice(pin, name) {
 
}
