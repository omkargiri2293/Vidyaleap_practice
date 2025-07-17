/*Timer_Assignment_2
 *
 * Timer is configured to generate 10 msec interrupt.
 *All delays are derived from this timer interrupt. After power on, both LEDs are OFF.
 *When SW1 is pressed, LED1 blinks at 0.5 Hz frequency.
 *When SW2 is pressed, LED2 blinks at 1 Hz frequency.
*/


#include "ti_msp_dl_config.h"

// Define toggle intervals in milliseconds for blinking
#define LED1_TOGGLE_INTERVAL 1000 // 1000 ms / (2 * 0.5) = 1000 ms
#define LED2_TOGGLE_INTERVAL 500  // 1000 ms / (2 * 1.0) = 500 ms
#define DEBOUNCE_TIME 50          // 50 ms debounce time

volatile uint32_t led1_counter = 0;
volatile uint32_t led2_counter = 0;
volatile uint32_t sw1_debounce_counter = 0;
volatile uint32_t sw2_debounce_counter = 0;
volatile uint8_t led1_enabled = 1;  // Initially, LED1 is OFF
volatile uint8_t led2_enabled = 0;  // Initially, LED2 is OFF
volatile uint8_t sw1_pressed = 0;
volatile uint8_t sw2_pressed = 0;

int main(void) {
    // Initialize system and enable timer interrupt
    SYSCFG_DL_init();
    NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
    DL_TimerA_startCounter(TIMER_0_INST);

    // Ensure LEDs are OFF at startup
    DL_GPIO_clearPins(GPIO_LED_PORT, GPIO_LED_LED_1_PIN);
    DL_GPIO_clearPins(GPIO_LEDS_PORT, GPIO_LEDS_LED_2_PIN);

    while (1) {
        // Main loop does nothing; everything is handled by Timer ISR
    }
}

// Timer Interrupt Service Routine (ISR)
void TIMER_0_INST_IRQHandler(void) {
    // Check if timer interrupt occurred
    if (DL_TimerA_getPendingInterrupt(TIMER_0_INST) == DL_TIMERA_IIDX_ZERO) {
        DL_TimerA_clearInterruptStatus(TIMER_0_INST, DL_TIMERA_IIDX_ZERO); // Clear interrupt

        // Handle SW1 press (Debounce and Toggle Logic)
        if (!DL_GPIO_readPins(GPIO_SW_1_PORT, GPIO_SW_1_PIN_1_PIN)) { // Active low
            if (sw1_debounce_counter < DEBOUNCE_TIME) {
                sw1_debounce_counter += 10;
            } else if (!sw1_pressed) {
                sw1_pressed = 1;
                led1_enabled = !led1_enabled; // Toggle LED1 blinking state

                if (!led1_enabled) {
                    DL_GPIO_clearPins(GPIO_LED_PORT, GPIO_LED_LED_1_PIN); // Keep LED OFF
                } else {
                    led1_counter = 0; // Reset counter if starting blinking
                }
            }
        } else {
            sw1_debounce_counter = 0;
            sw1_pressed = 0;
        }

        // Handle SW2 press (Debounce and Toggle Logic)
        if (!DL_GPIO_readPins(GPIO_SW_2_PORT, GPIO_SW_2_PIN_2_PIN)) { // Active low
            if (sw2_debounce_counter < DEBOUNCE_TIME) {
                sw2_debounce_counter += 10;
            } else if (!sw2_pressed) {
                sw2_pressed = 1;
                led2_enabled = !led2_enabled; // Toggle LED2 blinking state

                if (!led2_enabled) {
                    DL_GPIO_clearPins(GPIO_LEDS_PORT, GPIO_LEDS_LED_2_PIN); // Keep LED OFF
                } else {
                    led2_counter = 0; // Reset counter if starting blinking
                }
            }
        } else {
            sw2_debounce_counter = 0;
            sw2_pressed = 0;
        }

        // Handle LED1 blinking ONLY if enabled
        if (led1_enabled) {
            led1_counter += 10;
            if (led1_counter >= LED1_TOGGLE_INTERVAL) {
                DL_GPIO_togglePins(GPIO_LED_PORT, GPIO_LED_LED_1_PIN);
                led1_counter = 0;
            }
        }

        // Handle LED2 blinking ONLY if enabled
        if (led2_enabled) {
            led2_counter += 10;
            if (led2_counter >= LED2_TOGGLE_INTERVAL) {
                DL_GPIO_togglePins(GPIO_LEDS_PORT, GPIO_LEDS_LED_2_PIN);
                led2_counter = 0;
            }
        }
    }
}
