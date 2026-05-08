#ifndef PLATFORM_H
#define PLATFORM_H
#include "stdint.h"

void led2_Init(void);
void uart_Init(void);
void PLL_Init(void);
void timer2_init(uint16_t reload);
void timer2_start(void);
void uart_outchar(char c);
void uart_outstring(const char* str);
void uart_test(void);

#endif