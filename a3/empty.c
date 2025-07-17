/*
 * After power on, blink the LED after every 400 msec.
 * Now with each pressing of the button_1 the interval should increase by 100 msec.
 * If the button_2 is pressed, the interval should decrease by 100 msec.
 * The blinking interval should remain in 400 msec to 1200 msec range.
  NAME- OMKAR GIRI
 * Assignment 3
 */



#include "ti_msp_dl_config.h"

#define MIN_DELAY 12800000  // 400 ms in terms of clock cycles
#define MAX_DELAY 38400000  // 1200 ms in terms of clock cycles
#define STEP_DELAY 3200000  // 100 ms in terms of clock cycles

int main(void)
{
    uint32_t DELAY = MIN_DELAY;  // Start with the minimum delay

    // Initialize the system configuration
    SYSCFG_DL_init();

    // Turn on the LED initially
    DL_GPIO_setPins(GPIO_LEDS_PORT, GPIO_LEDS_USER_LED_1_PIN);

    while (1)
    {
        // Check if button 1 is pressed to increase delay
        if (DL_GPIO_readPins(GPIO_SWITCHES_PORT, GPIO_SWITCHES_PIN_1_PIN))
        {
            DELAY += STEP_DELAY;
            if (DELAY > MAX_DELAY)
            {
                DELAY = MAX_DELAY; // Cap the delay at the maximum
            }
            delay_cycles(640000); // Debounce delay
        }

        // Check if button 2 is pressed to decrease delay
        if (DL_GPIO_readPins(GPIO_SWITCHES_PORT, GPIO_SWITCHES_PIN_2_PIN))
        {
            DELAY -= STEP_DELAY;
            if (DELAY < MIN_DELAY)
            {
                DELAY = MIN_DELAY; // Cap the delay at the minimum
            }
            delay_cycles(640000); // Debounce delay
        }

        // Blink the LED
        DL_GPIO_togglePins(GPIO_LEDS_PORT, GPIO_LEDS_USER_LED_1_PIN);

        // Wait for the current delay interval
        delay_cycles(DELAY);
    }
}
