/*   Question_3

Problem statement:
When switch 1 is pressed, LED is turned on for 8 seconds and then turned off.
If during this time, if switch1 is pressed is pressed, this cycle is extended.

Implementation Guidelines:
Timer is configured to generate 10 msec interrupt.
All delays are derived from this timer inerrupt.

 NAME    - OMKAR GIRI
 ROLL_NO - BAMM-1U-06
 */


#include "ti_msp_dl_config.h"


#define LED_ON_TIME 8000
#define DEBOUNCE_TIME 50
volatile uint32_t led1_timer = 0;
volatile uint32_t sw1_debounce_counter = 0;
volatile uint8_t led1_active = 0;
volatile uint8_t sw1_pressed = 0;

int main(void) {

    SYSCFG_DL_init();
    NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
    DL_TimerA_startCounter(TIMER_0_INST);


    DL_GPIO_clearPins(GPIO_LED_PORT, GPIO_LED_LED_1_PIN);

    while (1) {

    }
}


void TIMER_0_INST_IRQHandler(void) {

    if (DL_TimerA_getPendingInterrupt(TIMER_0_INST) == DL_TIMERA_IIDX_ZERO) {
        DL_TimerA_clearInterruptStatus(TIMER_0_INST, DL_TIMERA_IIDX_ZERO);


        if (!DL_GPIO_readPins(GPIO_SW_1_PORT, GPIO_SW_1_PIN_1_PIN)) {
            if (sw1_debounce_counter < DEBOUNCE_TIME) {
                sw1_debounce_counter += 10;
            } else if (!sw1_pressed) {
                sw1_pressed = 1;
                led1_active = 1;
                led1_timer = LED_ON_TIME;
                DL_GPIO_setPins(GPIO_LED_PORT, GPIO_LED_LED_1_PIN);
            }
        } else {
            sw1_debounce_counter = 0;
            sw1_pressed = 0;
        }


        if (led1_active) {
            if (led1_timer > 0) {
                led1_timer -= 10;
            } else {
                led1_active = 0;
                DL_GPIO_clearPins(GPIO_LED_PORT, GPIO_LED_LED_1_PIN);
            }
        }
    }
}
