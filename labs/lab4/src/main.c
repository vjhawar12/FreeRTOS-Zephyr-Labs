#include "irq.h"
#include "projdefs.h"
#include "platform.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdint.h>
#include "stdio.h"
#include "semphr.h"

#define PERIOD_1S_CYCLES 8084000

SemaphoreHandle_t binary_semphr; 

void tim2_isr() {
    BaseType_t higher_priority_awoken = pdFALSE;
    xSemaphoreGiveFromISR(binary_semphr, &higher_priority_awoken);
    portYIELD_FROM_ISR(higher_priority_awoken);  
}   

void task(void* pvParams) {
    char buffer[64];
    while (1) {
        xSemaphoreTake(binary_semphr, portMAX_DELAY);
        snprintf(buffer, sizeof(buffer), "[%u ms] Waking up ...\r\n", xTaskGetTickCount());  
        uart_outstring(buffer); 
    }
}

int main(void) {
    PLL_Init();
    led2_Init();
    uart_Init();
    timer2_init(5000); 
    binary_semphr = xSemaphoreCreateBinary();
    xTaskCreate(task, "dummy task", 256, NULL, 2, NULL);
    timer2_start();
    vTaskStartScheduler();
    while (1) {

    } 
}