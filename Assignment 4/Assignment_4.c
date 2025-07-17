/*4. There are 2 switches (SW1, SW2) and associated 2 LEDS (L1, L2). When SW1 is pressed, L1 is put off. After 800 msec, L1 is put on for 500 msec.
  Similarly, when SW2 is pressed, L2 is put off. After 400 msec, L2 is put on for 600 msec.You have to debounce SW1 & SW2.
  */

/*
 * name- OMKAR GIRI
 * Assignment 4
 */
/* There are 2 switches (SW1, SW2) and associated 2 LEDS (L1, L2). When SW1 is pressed, L1 is put off. After 800 msec, L1 is put on for 500 msec.
   Similarly, when SW2 is pressed, L2 is put off. After 400 msec, L2 is put on for 600 msec.
*/
/* There are 2 switches (SW1, SW2) and associated 2 LEDS (L1, L2). When SW1 is pressed, L1 is put off. After 800 msec, L1 is put on for 500 msec.
   Similarly, when SW2 is pressed, L2 is put off. After 400 msec, L2 is put on for 600 msec.
*/
#include "ti_msp_dl_config.h"


void delay_ms(uint32_t ms)
{
    uint32_t cycles_per_ms = 32000; // For a 32 MHz clock
    delay_cycles(ms * cycles_per_ms);
}

int main(void)
{
    SYSCFG_DL_init();

    // Initialize LEDs as OFF
    DL_GPIO_clearPins(GPIO_LEDS_USER_LED_1_PORT, GPIO_LEDS_USER_LED_1_LED_1_PIN); // L1 ON initially
    DL_GPIO_setPins(GPIO_LEDS_USER_LED_2_PORT, GPIO_LEDS_USER_LED_2_LED_2_PIN); // L2 ON initially

    while (1)
    {
        // SW1 (active-high) pressed
        if (DL_GPIO_readPins(GPIO_SWITCHES_1_PORT, GPIO_SWITCHES_1_PIN_1_PIN))
        {
            delay_ms(50); // Debounce delay
            if (DL_GPIO_readPins(GPIO_SWITCHES_1_PORT, GPIO_SWITCHES_1_PIN_1_PIN))
            {
                DL_GPIO_setPins(GPIO_LEDS_USER_LED_1_PORT, GPIO_LEDS_USER_LED_1_LED_1_PIN);
                delay_ms(800); // Wait for 800 ms
                DL_GPIO_clearPins(GPIO_LEDS_USER_LED_1_PORT, GPIO_LEDS_USER_LED_1_LED_1_PIN);
                delay_ms(500); // Keep L1 ON for 500 ms
            }
        }

        //  SW2 (active-low) pressed
        if (!DL_GPIO_readPins(GPIO_SWITCHES_2_PORT, GPIO_SWITCHES_2_PIN_2_PIN))
        {
            delay_ms(50); // Debounce delay
            if (!DL_GPIO_readPins(GPIO_SWITCHES_2_PORT, GPIO_SWITCHES_2_PIN_2_PIN))
            {
                DL_GPIO_clearPins(GPIO_LEDS_USER_LED_2_PORT, GPIO_LEDS_USER_LED_2_LED_2_PIN);
                delay_ms(400); // Wait for 400 ms
                DL_GPIO_setPins(GPIO_LEDS_USER_LED_2_PORT, GPIO_LEDS_USER_LED_2_LED_2_PIN);
                delay_ms(500); // Keep L2 ON for 600 ms
            }
        }
    }
}
