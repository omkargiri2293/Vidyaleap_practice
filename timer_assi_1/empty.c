/*Timer_Assignment_1
 *
 * Timer is configured to generate 10 msec interrupt.
 *All delays are derived from this timer interrupt. After power on, LED blinks at 1 Hz.
 *When SW1 is pressed, blinking frequency reduces at 0.1 Hz step to 2 Hz.
 *When SW2 is pressed, blinking frequency increases at 0.1 Hz step to 0.5 Hz.
*/



#include "ti_msp_dl_config.h"
//interrupt is 10ms
#define INITIAL_PERIOD_MS 100  // Start with 1 Hz (1000ms period)
#define MAX_PERIOD_MS 200 //  2 Hz (500ms period)
#define MIN_PERIOD_MS 50  // 0.5 Hz (2000ms period)
#define STEP_MS 10  // Change step for frequency adjustment

volatile uint32_t toggle_count = INITIAL_PERIOD_MS ;

int main(void)
{
    SYSCFG_DL_init();
    NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);

    DL_TimerG_startCounter(TIMER_0_INST);

    while (1) {
        // Check SW1 - Increase frequency (reduce period)
        if (DL_GPIO_readPins(GPIO_SW_1_PORT, GPIO_SW_1_PIN_1_PIN)) {
            if (toggle_count > (MIN_PERIOD_MS )) {
                toggle_count -= (STEP_MS );
            }
            while (DL_GPIO_readPins(GPIO_SW_1_PORT, GPIO_SW_1_PIN_1_PIN)); // Wait for release (simple debounce)
        }

        // Check SW2 - Decrease frequency (increase period)
        if (!DL_GPIO_readPins(GPIO_SW_2_PORT, GPIO_SW_2_PIN_2_PIN)) {
            if (toggle_count < (MAX_PERIOD_MS )) {
                toggle_count += (STEP_MS );
            }
            while (!DL_GPIO_readPins(GPIO_SW_2_PORT, GPIO_SW_2_PIN_2_PIN)); // Wait for release (simple debounce)
        }
    }
}

void TIMER_0_INST_IRQHandler(void)
{
    static uint32_t tick_count = 0;

    if (DL_TimerG_getPendingInterrupt(TIMER_0_INST) == DL_TIMER_IIDX_ZERO) {
        DL_TimerG_clearInterruptStatus(TIMER_0_INST, DL_TIMER_IIDX_ZERO);

        tick_count++;
        if (tick_count >= toggle_count) {
            tick_count = 0;
            DL_GPIO_togglePins(GPIO_LEDS_PORT, GPIO_LEDS_USER_LED_1_PIN);
        }
    }
}
