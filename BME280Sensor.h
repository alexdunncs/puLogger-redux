#ifndef BME280SENSOR
#define BME280SENSOR

#include <stdint.h>

class BME280Sensor {
public: //debug
	uint8_t address;
	double temperature;
	double humidity;
	long long unsigned int lastPolled;
	
public:
  BME280Sensor();
  BME280Sensor(uint8_t address);

  void initialise();
	void pollSensor();
	double getTemperature();
	double getHumidity();
};

#endif
