#ifndef IRQ_H
#define IRQ_H

#define tim2_isr periodic_timer_isr
#define tim3_isr oneshot_timer_isr

void TIM2_IRQHandler(); 
void tim2_isr(); 
void TIM3_IRQHandler();
void tim3_isr();

#endif