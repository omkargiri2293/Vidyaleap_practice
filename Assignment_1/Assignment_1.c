
/*
 After power on, blink the LED every 400 msec. After 5 blink cycles, increase the interval by 100 msec.
 Continue this till the blinking interval is 1200 msec.
 Thereafter reduce the blinking interval to 400 msec. Repeat these cycles. */
/*
/* NAME- OMKAR GIRI
 * Assignment 1
 */

#include "ti_msp_dl_config.h"

/* Constants for LED blinking behavior */
#define INITIAL_DELAY   (12800000)           // Initial delay (400 ms for 32 MHz clock)
#define DELAY_INCREMENT (3200000)           // Increment (100 ms for 32 MHz clock)
#define MAX_DELAY       (38400000)          // Maximum delay (1200 ms for 32 MHz clock)
#define MIN_DELAY       (12800000)          // Minimum delay (400 ms for 32 MHz clock)
#define BLINK_CYCLES    5                   // Number of cycles before adjusting delay

int main(void) {
    /* Initialize GPIO for LED control */
    SYSCFG_DL_init() ;

    uint32_t delay = INITIAL_DELAY;         // Current delay in cycles
    uint8_t blink_count = 0;                // Blink cycle counter
    bool increasing = true;                 // Track delay direction

    while (1) {
        // Toggle the LED
        DL_GPIO_togglePins(GPIO_LEDS_PORT, GPIO_LEDS_USER_LED_1_PIN);

        // Wait for the current delay
        delay_cycles(delay);

        // Increment blink cycle count
        blink_count++;

        // Adjust delay after 5 cycles
        if (blink_count >= BLINK_CYCLES) {
            blink_count = 0; // Reset the blink cycle count

            if (increasing) {
                delay += DELAY_INCREMENT; // Increase delay
                if (delay >= MAX_DELAY) {
                    delay = MAX_DELAY;    // Cap delay at maximum
                    increasing = false;   // Reverse to decreasing
                }
            } else {
                delay -= DELAY_INCREMENT; // Decrease delay
                if (delay <= MIN_DELAY) {
                    delay = MIN_DELAY;    // Cap delay at minimum
                    increasing = true;    // Reverse to increasing
                }
            }
        }
    }
}
