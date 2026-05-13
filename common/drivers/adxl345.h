#ifndef ADXL345_H
#define ADXL345_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct adxl345_sample_t {
    int16_t accel_x; 
    int16_t accel_y;
    int16_t accel_z;
} adxl345_sample_t;

uint8_t adxl345_read_reg(uint8_t reg); 
void adxl345_write_reg(uint8_t reg);
void adxl345_read_multi(uint8_t start_reg, uint8_t *buffer, size_t len);  
void adxl345_init(); 
bool adxl345_read_xyz(adxl345_sample_t *sample); 

#endif