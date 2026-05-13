#ifndef SPI_H
#define SPI_H

#include <stdint.h>
#include <stdlib.h>

// enable clocks, configure pins, set SPI mode
void spi_init(void);
// send one byte and return the received byte
uint8_t spi_transfer_byte(uint8_t tx); 
// transfer multiple bytes
void spi_transfer(uint8_t *tx, uint8_t *rx, size_t len); 
// drive cs low
void adxl_cs_low(void);
// drive cs high 
void adxl_cs_high(void); 

#endif

/* 
Using SPI2 on APB1 bus
CPHA = 1
CPOL = 1

CS: PB6
MOSI: PB15
MISO: PB14
SCK: PB13


1.Select the BR[2:0] bits to define the serial clock baud rate (see SPI_CR1 register).
2.Select the CPOL and CPHA bits to define one of the four relationships between the
data transfer and the serial clock (see Figure 194). This step is not required when the
TI mode is selected.
3.Set the DFF bit to define 8- or 16-bit data frame format
4.Configure the LSBFIRST bit in the SPI_CR1 register to define the frame format. This
step is not required when the TI mode is selected.
5.If the NSS pin is required in input mode, in hardware mode, connect the NSS pin to a
high-level signal during the complete byte transmit sequence. In NSS software mode,
set the SSM and SSI bits in the SPI_CR1 register. If the NSS pin is required in output
mode, the SSOE bit only should be set. This step is not required when the TI mode is
selected.
6.Set the FRF bit in SPI_CR2 to select the TI protocol for serial communications.
7.The MSTR and SPE bits must be set (they remain set only if the NSS pin is connected
to a high-level signal).
In this configuration the MOSI pin is a data output and the MISO pin is a data input.
Transmit sequence
The transmit sequence begins when a byte is written in the Tx Buffer.
The data byte is parallel-loaded into the shift register (from the internal bus) during the first
bit transmission and then shifted out serially to the MOSI pin MSB first or LSB first
depending on the LSBFIRST bit in the SPI_CR1 register. The TXE flag is set on the transfer
of data from the Tx Buffer to the shift register and an interrupt is generated if the TXEIE bit in
the SPI_CR2 register is set.

*/ 