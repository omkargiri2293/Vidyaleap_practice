/*
 * 2. There are 2 switches (SW1, SW2) and associated 2 LEDS (L1, L2).
 * When SW1 is pressed, L1 is put off. After 800 msec, L1 is put on for 500 msec.
 * Similarly, when SW2 ispressed, L2 is put off. After 400 msec, L2 is put on for 600 msec. 
 * You have to debounce SW1 & SW2.
 *
 *  Name- OMKAR GIRI
 *  Roll no: BAMM-1U-06
 */


#include "ti_msp_dl_config.h"

#define DEBOUNCE_DELAY 50 // Debounce delay in milliseconds

volatile uint8_t sw1_flag = 0; // Flag for SW1
volatile uint8_t sw2_flag = 0; // Flag for SW2

void delay_ms(uint32_t ms) {
    for (volatile uint32_t i = 0; i < ms * 3200; i++) {
        __NOP(); // Simple delay loop
    }
}

  int main(void) {
    SYSCFG_DL_init();

    /* Enable Interrupt for both GPIOA and GPIOB ports */
    NVIC_EnableIRQ(GPIO_SWITCHES_GPIOA_INT_IRQN);
    NVIC_EnableIRQ(GPIO_SWITCHES_GPIOB_INT_IRQN);

    /* Initial LED states: Both LEDs are ON */
    DL_GPIO_setPins(GPIO_LEDS_PORT,GPIO_LEDS_USER_LED_2_PIN);
    DL_GPIO_clearPins(GPIO_LED_PORT, GPIO_LED_USER_LED_1_PIN);
    while (1) {
        // Handle SW1 logic if interrupt is triggered
        if (sw1_flag) {
            sw1_flag = 0; // Reset flag

            // Turn off LED L1
            DL_GPIO_setPins(GPIO_LED_PORT, GPIO_LED_USER_LED_1_PIN);

            // Wait 800 ms, then turn it on for 500 ms
            delay_ms(800);
            DL_GPIO_clearPins(GPIO_LED_PORT, GPIO_LED_USER_LED_1_PIN);
            delay_ms(500);
            DL_GPIO_setPins(GPIO_LED_PORT, GPIO_LED_USER_LED_1_PIN);
        }

        // Handle SW2 logic if interrupt is triggered
        if (sw2_flag) {
            sw2_flag = 0; // Reset flag

            // Turn off LED L2
            DL_GPIO_clearPins(GPIO_LEDS_PORT, GPIO_LEDS_USER_LED_2_PIN);

            // Wait 400 ms, then turn it on for 600 ms
            delay_ms(400);
            DL_GPIO_setPins(GPIO_LEDS_PORT, GPIO_LEDS_USER_LED_2_PIN);
            delay_ms(600);
            DL_GPIO_clearPins(GPIO_LEDS_PORT, GPIO_LEDS_USER_LED_2_PIN);
        }

        // Enter low-power mode until the next interrupt
        __WFI(); // Wait for interrupt
    }
}

void GROUP1_IRQHandler(void) {
    /*
     * Get the pending interrupt for the GPIOA and GPIOB ports
     */
    uint32_t gpioA = DL_GPIO_getEnabledInterruptStatus(GPIOA, GPIO_SWITCHES_USER_SWITCH_1_PIN);
    uint32_t gpioB = DL_GPIO_getEnabledInterruptStatus(GPIOB, GPIO_SWITCHES_USER_SWITCH_2_PIN);

    /* Check SW1 */
    if ((gpioA & GPIO_SWITCHES_USER_SWITCH_1_PIN) == GPIO_SWITCHES_USER_SWITCH_1_PIN) {
        delay_ms(DEBOUNCE_DELAY); // Debounce delay
        if (DL_GPIO_readPins(GPIOA, GPIO_SWITCHES_USER_SWITCH_1_PIN) == 0) {
            sw1_flag = 1; // Set SW1 flag
        }
        DL_GPIO_clearInterruptStatus(GPIOA, GPIO_SWITCHES_USER_SWITCH_1_PIN);
    }

    /* Check SW2 */
    if ((gpioB & GPIO_SWITCHES_USER_SWITCH_2_PIN) == GPIO_SWITCHES_USER_SWITCH_2_PIN) {
        delay_ms(DEBOUNCE_DELAY); // Debounce delay
        if (DL_GPIO_readPins(GPIOB, GPIO_SWITCHES_USER_SWITCH_2_PIN) == 0) {
            sw2_flag = 1; // Set SW2 flag
        }
        DL_GPIO_clearInterruptStatus(GPIOB, GPIO_SWITCHES_USER_SWITCH_2_PIN);
    }
}
