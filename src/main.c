#include "projdefs.h"
#include "platform.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdint.h>
#include "irq.h"

TaskHandle_t task_handle;

// void blinkLED(void* pvParams) {
//     int16_t *delay = (int16_t*)pvParams;
//     while (1) {
//         GPIOA->ODR ^= (1 << 5); // flipping PA5
//         vTaskDelay(pdMS_TO_TICKS(*delay)); 
//     }
// }

void low_priority_task(void* pvParams) {
    int16_t *delay = (int16_t*)pvParams;
    while (1) {
        uart_outstring("LOW\r\n");
        vTaskDelay(pdMS_TO_TICKS(*delay)); 
    }   
}

void high_priority_task(void* pvParams) {
    while (1) {
        if (tim2_isr_flag) {
            tim2_isr_flag = 0;
            uart_outstring("HIGH\r\n");
            xTaskNotify(task_handle, 0x01, eSetBits); 
        }
    }
}

int main(void) {
    // int16_t blink_led_delay = 500;
    int16_t low_priority_delay = 100;
    int8_t high_priority_delay = 50; 

    PLL_Init();
    led2_Init();
    uart_Init();
    timer2_init(high_priority_delay); 
    timer2_start();
    // xTaskCreate(blinkLED, "led blink", 256, (void*)&blink_led_delay, 5, NULL);
    xTaskCreate(low_priority_task, "low priority", 256, (void*)&low_priority_delay, 2, NULL);
    xTaskCreate(high_priority_task, "high priority", 256, NULL, 5, NULL);
    vTaskStartScheduler();
    while (1) {

    } 
}