/*Timer_Assignment_3
 *
 *Timer is configured to generate monoshot.
 *When SW1 is pressed, the timer is triggered.
 *It generates a delay of 8 seconds. And when timer is running, LED is put ON.
 */

#include "ti_msp_dl_config.h"

int main(void)
{
    SYSCFG_DL_init();
    NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);

    while (1) {
        // Start the timer when SW1 is pressed
        if (DL_GPIO_readPins(GPIO_SWITCH_PORT, GPIO_SWITCH_SW_1_PIN)) {
            // Turn ON LED
            DL_GPIO_setPins(GPIO_LED_PORT, GPIO_LED_LED_1_PIN);

            // Start the pre-configured one-shot timer (8 sec)
            DL_TimerA_startCounter(TIMER_0_INST);

            // Wait for button release (simple debounce)
            while (DL_GPIO_readPins(GPIO_SWITCH_PORT, GPIO_SWITCH_SW_1_PIN));
        }
    }

    return 0;  // Added return statement
}

// Timer ISR - Executes when 8 sec timer expires
void TIMER_0_INST_IRQHandler(void)
{
    if (DL_TimerG_getPendingInterrupt(TIMER_0_INST) == DL_TIMER_IIDX_ZERO) {
        DL_TimerG_clearInterruptStatus(TIMER_0_INST, DL_TIMER_IIDX_ZERO);

        // Turn OFF the LED after 8 seconds
        DL_GPIO_clearPins(GPIO_LED_PORT, GPIO_LED_LED_1_PIN);
    }
}
