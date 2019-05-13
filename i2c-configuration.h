#ifndef I2CCONFIG
#define I2CCONFIG

#include <stdint.h>

//// BME280 and I2C Setup

uint8_t osrs_t = 1;             //Temperature oversampling x 1
uint8_t osrs_p = 1;             //Pressure oversampling x 1
uint8_t osrs_h = 1;             //Humidity oversampling x 1
uint8_t mode = 3;               //Normal mode
uint8_t t_sb = 5;               //Tstandby 1000ms
uint8_t filter = 0;             //Filter off 
uint8_t spi3w_en = 0;           //3-wire SPI Disable

uint8_t ctrl_meas_reg = (osrs_t << 5) | (osrs_p << 2) | mode;
uint8_t config_reg = (t_sb << 5) | (filter << 2) | spi3w_en;
uint8_t ctrl_hum_reg = osrs_h;

#endif