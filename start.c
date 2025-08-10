#include "FreeRTOS.h"
#include "task.h"

static void vTask1(void *pvParameters){
    volatile int a = 0;
    while(1){
        a++;
    };
}
static void vTask2(void *pvParameters){
    volatile int b = 0;
    while(1){
        b++;
    };
}

extern uint32_t _sdata; //Start of .data in RAM
extern uint32_t _edata; // End of .data in RAM
extern uint32_t _sidata; //Start of .data in flash
extern uint32_t _sbss; //Start of .bss
extern uint32_t _ebss; //End of .bss


void start(){
    BaseType_t xReturn;

    //Initilaize .data section (copy from flash to RAM)
    uint32_t *src = &_sidata; //source = flash
    uint32_t *dst = &_sdata; //destination = RAM
    while (dst <&_edata) {
        *dst++ = *src++;  //copy word and increment pointers
    }

    //Initialize .bss section (Zero out)
    dst = &_sbss;
    while (dst < &_ebss) {
        *dst++ = 0; //zero word and increment pointer
    }

    xReturn = xTaskCreate(vTask1, "T1", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xReturn = xTaskCreate(vTask2, "T2", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    // vTaskStartScheduler();
    xPortStartScheduler();
    return;

}
