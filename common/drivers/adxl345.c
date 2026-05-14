#include "adxl345.h"
#include "spi.h"
#include <stdint.h>
#include <stdbool.h>

void adxl345_init() {
    // setting 4 wire mode
    uint8_t value = adxl345_read_reg(DATA_FORMAT); 
    value &= ~(1 << SPI_BIT); 
    adxl345_write_reg(DATA_FORMAT, value);
    // starting measurement  
    value = adxl345_read_reg(POWER_CTL); 
    value |= (1 << MEASURE_BIT); 
    adxl345_write_reg(POWER_CTL, value); 
}

void adxl345_write_reg(uint8_t reg, uint8_t value) {
    uint8_t rw_mask = ~(0b1 << 7); // 0 at bit 7 = write
    uint8_t mb_mask = ~(0b1 << 6); // 0 at bit 6 = single byte
    uint8_t cmd_byte = reg & mb_mask & rw_mask; 
    uint8_t data_byte = value;
    adxl_cs_low(); 
    spi_transfer_byte(cmd_byte); 
    spi_transfer_byte(data_byte); 
    adxl_cs_high(); 
}

uint8_t adxl345_read_reg(uint8_t reg) {
    uint8_t ret_value;
    uint8_t rw_mask = (0b1 << 7); // 1 at bit 7 = read
    uint8_t mb_mask = ~(0b1 << 6); // 0 at bit 6 = single byte
    uint8_t cmd_byte = (reg & mb_mask) | rw_mask; 
    uint8_t dummy_byte = 0xFF;
    adxl_cs_low();
    ret_value = spi_transfer_byte(cmd_byte); 
    ret_value = spi_transfer_byte(dummy_byte); 
    adxl_cs_high();
    return ret_value;
}

void adxl345_read_multi(uint8_t start_reg, uint8_t *buffer, size_t len) {
    int i = 0;
    uint8_t rw_mask = (0b1 << 7); // 1 at bit 7 = read
    uint8_t mb_mask = (0b1 << 6); // 1 at bit 6 = multi byte
    uint8_t dummy_byte = 0xFF;
    adxl_cs_low();
    uint8_t cmd_byte = (start_reg | mb_mask) | rw_mask; 
    spi_transfer_byte(cmd_byte); 
    for (i = 0; i < len; i++) {
        buffer[i] = spi_transfer_byte(dummy_byte); 
    }
    adxl_cs_high();
}

bool adxl345_read_xyz(adxl345_sample_t *sample) {
    uint8_t accel_buffer[6];
    adxl345_read_multi(DATAX0, accel_buffer, 6); 
    uint16_t accel_x = (accel_buffer[1] << 8) | accel_buffer[0]; 
    uint16_t accel_y = (accel_buffer[3] << 8) | accel_buffer[2]; 
    uint16_t accel_z = (accel_buffer[5] << 8) | accel_buffer[4]; 
    sample->accel_x = (int16_t)accel_x; 
    sample->accel_y = (int16_t)accel_y;
    sample->accel_z = (int16_t)accel_z; 

    return true;
}