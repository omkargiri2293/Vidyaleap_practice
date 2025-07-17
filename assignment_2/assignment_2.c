/*
 After power on, put on LED.
 Now press a button to toggle the LED i.e. when the button is pressed,
 if the LED is ON / OFF, it will be put OFF / ON.
 */
/*
  NAME- OMKAR GIRI
  Assignment 2
 */
#include "ti_msp_dl_config.h"

uint32_t delay = 640000; // Delay for debounce
int main(void)
{
    // Initialize the system configuration
    SYSCFG_DL_init();

    // Set the LED pin to ON after power-on
    DL_GPIO_setPins(GPIO_LED_PORT, GPIO_LED_USER_LED_1_PIN);

    // Infinite loop to check button state
    while (1) {
        // Check if the button is pressed (active low)
        if (!DL_GPIO_readPins(GPIO_SWITCH_PORT, GPIO_SWITCH_PIN_1_PIN)) {
            // Toggle the LED state
            DL_GPIO_togglePins(GPIO_LED_PORT, GPIO_LED_USER_LED_1_PIN);

            // Delay for debounce
            delay_cycles(delay);

            // Wait until the button is released
            while (!DL_GPIO_readPins(GPIO_SWITCH_PORT, GPIO_SWITCH_PIN_1_PIN));
        }
    }
}
