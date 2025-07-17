
#include "BM.h"
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

uint32_t delay = 12800000;  // Initial delay (400ms)
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

    // Configure switches as input
    initDigitalInput(SW1_PINCM_IDX, DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
                     DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    initDigitalInput(SW2_PINCM_IDX, DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
                     DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    // Configure LED as output
    digitalOutputConfig(LED_PORT, LED_PINCM_IDX, 22);

    // Ensure LED is off initially
    clearPins(LED_PORT, LED_PIN);

    while (1) {
        // Toggle LED and wait for the delay duration
        togglePins(LED_PORT, LED_PIN);
        delay_cycles(delay);

        // Check SW1 (active-high) for increasing delay
        if (readPins(SW1_PORT, SW1_PIN)) {
            delay_cycles(5000);  // Simple debounce delay
            if (readPins(SW1_PORT, SW1_PIN)) {  // Confirm button press
                if (delay + step <= max_delay) {
                    delay += step;  // Increase delay by 100ms
                    printf("Delay increased: %lu cycles\n", delay);
                }
            }
        }

        // Check SW2 (active-low) for decreasing delay
        if (!readPins(SW2_PORT, SW2_PIN)) {
            delay_cycles(5000);  // Simple debounce delay
            if (!readPins(SW2_PORT, SW2_PIN)) {  // Confirm button press
                if (delay >= min_delay + step) {
                    delay -= step;  // Decrease delay by 100ms
                    printf("Delay decreased: %lu cycles\n", delay);
                }
            }
        }
    }
}



/*
 After power on, put on LED.
 Now press a button to toggle the LED i.e. when the button is pressed,
 if the LED is ON / OFF, it will be put OFF / ON.
 */
/*
  NAME- OMKAR GIRI
  Assignment 2
 */
/*
#include "BM.h"
#define LED_PORT       GPIOB
#define LED_PIN        0x00400000  // Bit mask for PB22
#define LED_PINCM_IDX  49          // PINCM index for PB22

#define SW_PORT        GPIOA
#define SW_PIN         0x00040000  // Bit mask for PA18
#define SW_PINCM_IDX   39          // PINCM index for PA18

void delay(uint32_t cycles) {
    while (cycles--) {
        __NOP();  // No operation, just loop for delay
    }
}

int main(void) {
    // Reset GPIO ports
    GPIO_reset(LED_PORT);
    GPIO_reset(SW_PORT);

    // Enable GPIO power
    enablePort(LED_PORT);
    enablePort(SW_PORT);

    // Configure switch as input
    initDigitalInput(SW_PINCM_IDX, DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_NONE,
                     DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    // Configure LED as output
    digitalOutputConfig(LED_PORT, LED_PINCM_IDX, 22);

    // Ensure LED is off initially
    clearPins(LED_PORT, LED_PIN);

    while (1) {
        if (!(readPins(SW_PORT, SW_PIN))) {  // Button press detected (active-low)
            delay_cycles(50000);  // Basic debounce delay
            if (!(readPins(SW_PORT, SW_PIN))) {  // Confirm button press
                togglePins(LED_PORT, LED_PIN);  // Toggle LED state
                while (!(readPins(SW_PORT, SW_PIN)));  // Wait until button is released
            }
        }
    }
}
*/

/*
 *
 After power on, blink the LED every 400 msec. After 5 blink cycles, increase the interval by 100 msec.
 Continue this till the blinking interval is 1200 msec.
 Thereafter reduce the blinking interval to 400 msec. Repeat these cycles. */
/*
/* NAME- OMKAR GIRI
 * Assignment 1
 */
/*
 *
 * #include "BM.h"
#define LED_PORT       GPIOB
#define LED_PIN        0x00400000  // Bit mask for PB22
#define LED_PINCM_IDX  49         // PINCM index for PB22

uint32_t delay = 12800000;  // Initial delay: 400ms
uint8_t blinkCount = 0;

int main(void) {
    // Enable GPIOB power
    enablePort(LED_PORT);


    // Configure pin
    digitalOutputConfig(LED_PORT,LED_PINCM_IDX,22);


    // Clear pin
    clearPins(LED_PORT, LED_PIN);

   // SET output
    setPins(LED_PORT, LED_PIN);

    delay_cycles(16);

    // Main loop
    while (1) {
        togglePins(LED_PORT, LED_PIN); // Toggle LED state
        delay_cycles(delay);

        blinkCount++;

        if (blinkCount == 5) {
            blinkCount = 0;
            delay += 3200000;  // Increase delay by 100ms

            if (delay > 38400000) {
                delay = 12800000;  // Reset delay to 400ms
            }
        }
    }
}
*/
