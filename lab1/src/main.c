#include "projdefs.h"
#include "platform.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdint.h>

void low_priority_task(void* pvParams) {
    int16_t *delay = (int16_t*)pvParams;
    while (1) {
        uart_outstring("LOW\r\n");
        vTaskDelay(pdMS_TO_TICKS(*delay)); 
    }   
}

void med_priority_task(void* pvParams) {
    int16_t *delay = (int16_t*)pvParams;
    while (1) {
        uart_outstring("MED\r\n");
        vTaskDelay(pdMS_TO_TICKS(*delay)); 
    }   
}

void high_priority_task(void* pvParams) {
    int16_t *delay = (int16_t*)pvParams;
    while (1) {
        uart_outstring("HIGH\r\n");
        vTaskDelay(pdMS_TO_TICKS(*delay)); 
    }
}

int main(void) {
    int16_t low_priority_delay = 300;
    int16_t med_priority_delay = 200;
    int16_t high_priority_delay = 100; 

    PLL_Init();
    led2_Init();
    uart_Init();
    xTaskCreate(low_priority_task, "low priority", 256, (void*)&low_priority_delay, 2, NULL);
    xTaskCreate(med_priority_task, "med priority", 256, (void*)&med_priority_delay, 4, NULL);
    xTaskCreate(high_priority_task, "high priority", 256, (void*)&high_priority_delay, 6, NULL);
    vTaskStartScheduler();
    while (1) {

    } 
}