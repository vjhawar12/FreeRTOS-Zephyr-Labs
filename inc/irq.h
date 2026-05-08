#ifndef IRQ_H
#define IRQ_H

extern volatile int tim2_isr_flag; 
void TIM2_IRQHandler(void);

#endif