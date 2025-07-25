/*
 * 1. After power on, blink the LED after every 400 msec.
 *  Now with each pressing of the button_1 the interval should increase by 100 msec. If the button_2 is pressed,
 *  the interval should decrease by 100 msec.
 *  The blinking interval should remain in 400 msec to 1200 msec range.
 *
 *  Name- OMKAR GIRI
 *  Roll no: BAMM-1U-06
 */

#include "Baremetal.h"
#include <stdio.h>

#define LED_PORT       GPIOB
#define LED_PIN        0x00400000  // Bit mask for PB22
#define LED_PINCM_IDX  49          // PINCM index for PB22

#define SW1_PORT       GPIOA
#define SW1_PIN        0x00040000  // Bit mask for PA18
#define SW1_PINCM_IDX  39          // PINCM index for PA18

#define SW2_PORT       GPIOB
#define SW2_PIN        0x00200000  // Bit mask for PB21
#define SW2_PINCM_IDX  48          // PINCM index for PB21

uint32_t delay = 12800000;  // 400ms
const uint32_t min_delay = 12800000;  // 400ms
const uint32_t max_delay = 38400000;  // 1200ms
const uint32_t step = 3200000;        // 100ms

    int main(void) {
    // Reset all GPIO ports
    GPIO_reset(LED_PORT);
    GPIO_reset(SW1_PORT);
    GPIO_reset(SW2_PORT);

    // Enable GPIO power for all used ports
    enablePort(LED_PORT);
    enablePort(SW1_PORT);
    enablePort(SW2_PORT);

    EnableIRQ(GPIOA_INT_IRQn); // Enable IRQ for handling GPIOA interrupts
        EnableIRQ(GPIOB_INT_IRQn); // Enable IRQ for handling GPIOB interrupts


    // Configure switches as input
    initDigitalInput(SW1_PINCM_IDX, DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
                     DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    initDigitalInput(SW2_PINCM_IDX, DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
                     DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    // Configure LED as output
    digitalOutputConfig(LED_PORT, LED_PINCM_IDX, 22);

    // Ensure LED is off initially
    clearPins(LED_PORT, LED_PIN);


    setUpperPinsPolarity(SW1_PORT, DL_GPIO_PIN_18_EDGE_RISE_FALL  );
    setUpperPinsPolarity(SW2_PORT, DL_GPIO_PIN_21_EDGE_RISE_FALL  );
    // Enable interrupts for switches
    enableInterrupt(SW1_PORT, SW1_PIN);
    enableInterrupt(SW2_PORT, SW2_PIN);



    while (1) {
           togglePins(LED_PORT, LED_PIN);
           delay_cycles(delay);
       }

}

    void GROUP1_IRQHandler(void) {
        uint32_t gpioA = getEnabledInterruptStatus(SW1_PORT, SW1_PIN);
        uint32_t gpioB = getEnabledInterruptStatus(SW2_PORT, SW2_PIN);

        // Check if SW1 is pressed (Increase delay)
        if ((gpioA & SW1_PIN) == SW1_PIN) {
            if (delay + step <= max_delay) {
                delay += step; // Increase delay by 100ms
                printf("Button 1 pressed. Delay increased to %u cycles (%.1f ms).\n", delay, (float)delay / 32000);
            }
            clearInterruptStatus(SW1_PORT, SW1_PIN);
        }

        // Check if SW2 is pressed (Decrease delay)
        if ((gpioB & SW2_PIN) == SW2_PIN) {
            if (delay >= min_delay + step) {
                delay -= step; // Decrease delay by 100ms
                printf("Button 2 pressed. Delay decreased to %u cycles (%.1f ms).\n", delay, (float)delay / 32000);
            }
            clearInterruptStatus(SW2_PORT, SW2_PIN);
        }
    }
