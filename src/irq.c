#include "irq.h"
#include "stm32f401xe.h"

volatile int tim2_isr_flag = 0;

void TIM2_IRQHandler(void) {
    tim2_isr_flag = 1; 
    TIM2->SR &= ~(1 << 0); 
}