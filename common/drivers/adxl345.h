#ifndef ADXL345_H
#define ADXL345_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

// device ID
#define DEVID 0xE5
// offset accceleration registers
#define OFSX 0x1E
#define OFSY 0x1F
#define OFSZ 0x20
// SPI configuration register
#define DATA_FORMAT 0x31
#define SPI_BIT 6
// acceleration data registers
// x-axis data 0
#define DATAX0 0x32
// x-axis data 1
#define DATAX1 0x33
// Y-axis data 0
#define DATAY0 0x34
// Y-axis data 1
#define DATAY1 0x35
// Z-axis data 0
#define DATAZ0 0x36
// Z-axis data 1
#define DATAZ1 0x37
// power register
#define POWER_CTL 0x2D
#define MEASURE_BIT 3

typedef struct adxl345_sample_t {
    int16_t accel_x; 
    int16_t accel_y;
    int16_t accel_z;
} adxl345_sample_t;

// pull cs low (motorola mode), send command byte, send dummy byte, return received byte
uint8_t adxl345_read_reg(uint8_t reg); 
// pull cs low, send command byte, send value byte, release cs
void adxl345_write_reg(uint8_t reg, uint8_t value);
void adxl345_read_multi(uint8_t start_reg, uint8_t *buffer, size_t len);  
void adxl345_init(); 
bool adxl345_read_xyz(adxl345_sample_t *sample); 

#endif

/* 
SPI: 

CS idles high (motorola)
MCU pulls CS low to initiate communication
To read: MCU sends command byte + dummy byte on MOSI and sensor sends on MISO
To write: MCU sends command byte + data byte on MOSI and sensor sends on MISO
MCU releases

*/