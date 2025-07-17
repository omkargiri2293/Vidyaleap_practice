/*
 * After power on, blink the LED after every 400 msec.
 * Now with each pressing of the button_1 the interval should increase by 100 msec.
 * If the button_2 is pressed, the interval should decrease by 100 msec.
 * The blinking interval should remain in 400 msec to 1200 msec range.
  NAME- OMKAR GIRI
 * Assignment 3
 */



#include "ti_msp_dl_config.h"

#define SYSTEM_CLOCK 32000000  // System clock frequency in Hz
#define MS_TO_CYCLES(ms) ((ms) * (SYSTEM_CLOCK / 1000))  // Convert ms to clock cycles

#define MIN_DELAY MS_TO_CYCLES(400)  // 400 ms
#define MAX_DELAY MS_TO_CYCLES(1200)  // 1200 ms
#define STEP_DELAY MS_TO_CYCLES(100)  // 100 ms
#define DEBOUNCE_DELAY MS_TO_CYCLES(50)  // 50 ms debounce

void debounce_delay(void)
{
    delay_cycles(DEBOUNCE_DELAY);
}

int main(void)
{
    uint32_t DELAY = MIN_DELAY;  // Start with the minimum delay

    SYSCFG_DL_init();  // Initialize system configuration
    DL_GPIO_setPins(GPIO_LEDS_PORT, GPIO_LEDS_USER_LED_1_PIN);  // Turn on the LED

    while (1)
    {
        // Check if button 1 is pressed to increase delay
        if (DL_GPIO_readPins(GPIO_SWITCHES_PORT, GPIO_SWITCHES_PIN_1_PIN))
        {
            DELAY += STEP_DELAY;
            if (DELAY > MAX_DELAY)
            {
                DELAY = MAX_DELAY;  // Cap at maximum delay
            }
            debounce_delay();
        }

        // Check if button 2 is pressed to decrease delay
        if (!DL_GPIO_readPins(GPIO_SWITCHES_2_PORT, GPIO_SWITCHES_2_PIN_2_PIN))
        {
            DELAY -= STEP_DELAY;
            if (DELAY < MIN_DELAY)
            {
                DELAY = MIN_DELAY;  // Cap at minimum delay
            }
            debounce_delay();
        }

        // Blink the LED
        DL_GPIO_togglePins(GPIO_LEDS_PORT, GPIO_LEDS_USER_LED_1_PIN);

        // Wait for the current delay interval
        delay_cycles(DELAY);
    }
}
