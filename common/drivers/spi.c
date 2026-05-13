#include "spi.h"
#include "stm32f401xe.h"
#include <stdint.h>

/* 

–Configure the desired I/O as an alternate function in the GPIOx_MODER register
–Select the type, pull-up/pull-down and output speed via the GPIOx_OTYPER,
GPIOx_PUPDR and GPIOx_OSPEEDR registers, respectively
–Connect the I/O to the desired AFx in the GPIOx_AFRL or GPIOx_AFRH register


*/

void spi_init() {
    RCC->AHB1ENR |= (1U << 1); // enable clock for PORT B
    RCC->APB1ENR |= (1U << 14); // enable clock for SPI2
    GPIOB->MODER &= ~(0b11 << 26);
    GPIOB->MODER &= ~(0b11 << 28);
    GPIOB->MODER &= ~(0b11 << 30);
    GPIOB->MODER &= ~(0b11 << 12);
    GPIOB->MODER |= (0b10 << 26); // alternate function SPI2_SCK (PB13)
    GPIOB->MODER |= (0b10 << 28); // alternate function SPI2_MISO (Pb14)
    GPIOB->MODER |= (0b10 << 30); // alternate function SPI2_MOSI (PB15)
    GPIOB->MODER |= (0b01 << 12); // General purpose SPI2_CS (PB6)
    GPIOB->AFR[1] &= ~(0xF << 20);  
    GPIOB->AFR[1] &= ~(0xF << 24); 
    GPIOB->AFR[1] &= ~(0xF << 28); 
    GPIOB->AFR[1] |= (0x5 << 20);  
    GPIOB->AFR[1] |= (0x5 << 24); 
    GPIOB->AFR[1] |= (0x5 << 28); 
    SPI2->CR1 = 0;
    SPI2->CR1 |= (0b1 << 9); // software controls internal NSS behaviour
    SPI2->CR1 |= (0b1 << 8); // internal slave select 
    SPI2->CR1 |= (0b1 << 0); // CPHA
    SPI2->CR1 |= (0b1 << 1); // CPOL
    SPI2->CR1 |= (0b1 << 2); // master
    SPI2->CR1 &= ~(0b1 << 11); // 8 bit data
    SPI2->CR1 &= ~(0b1 << 7); // MSB first
    SPI2->CR1 |= (0b101 << 3); // setting to 40.21 Mhz / 64 = 628 Khz
    SPI2->CR2 = 0;
    SPI2->CR2 &= ~(0b1 << 4);  
    SPI2->CR1 |= (0b1 << 6);
    adxl_cs_high(); 
}

void adxl_cs_low() {
    GPIOB->ODR &= ~(1 << 6); 
}

void adxl_cs_high() {
    GPIOB->ODR |= (1 << 6); 
}

uint8_t spi_transfer_byte(uint8_t tx) {
    while ((SPI2->SR & (0b1 << 1)) == 0) {} // tx buffer not empty
    *((volatile uint8_t*)&SPI2->DR) = tx; // performing an 8-bit write 
    while ((SPI2->SR & (0b1 << 0)) == 0) {} // rx buffer empty
    return *((volatile uint8_t*)&SPI2->DR); // performing an 8-bit read
}

void spi_transfer(uint8_t *tx, uint8_t *rx, size_t len) {
    int i = 0;
    for (i = 0; i < len; i++) {
        while ((SPI2->SR & (0b1 << 1)) == 0) {} // tx buffer not empty
        *((volatile uint8_t*)&SPI2->DR) = tx[i]; // performing an 8-bit write 
        while ((SPI2->SR & (0b1 << 0)) == 0) {} // rx buffer empty
        rx[i] = *((uint8_t*)&SPI2->DR); // performing an 8-bit read
    }
}

