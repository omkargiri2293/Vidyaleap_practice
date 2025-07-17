
/*
 There are 2 switches (SW1, SW2) and associated 2 LEDS (L1, L2).
  When SW1 is pressed, L1 is put off. After 800 msec, L1 is put on for 500 msec.
   Similarly, when SW2 is pressed, L2 is put off. After 400 msec, L2 is put on for 600 msec.
   You have to debounce SW1 & SW2.
 */


#include "Baremetal.h"
#include <stdio.h>

#define LED1_PORT       GPIOB
#define LED1_PIN        0x00400000  // Bit mask for PB22
#define LED1_PINCM_IDX  49          // PINCM index for PB22

#define SW1_PORT       GPIOA
#define SW1_PIN        0x00040000  // Bit mask for PA18
#define SW1_PINCM_IDX  39          // PINCM index for PA18

#define SW2_PORT       GPIOB
#define SW2_PIN        0x00200000  // Bit mask for PB21
#define SW2_PINCM_IDX  48          // PINCM index for PB21

#define LED2_PORT       GPIOB
#define LED2_PIN        0X04000000  // Bit mask for PB26
#define LED2_PINCM_IDX  56          // PINCM index for PB26



// Define delay values for LED blinking
#define DELAY_800_MS 25600000  // 800 ms
#define DELAY_500_MS 16000000  // 500 ms
#define DELAY_400_MS 12800000  // 400 ms
#define DELAY_600_MS 19200000  // 600 ms
#define DEBOUNCE_DELAY 1600000  // 50 ms debounce delay


    int main(void) {
    // Reset all GPIO ports
    GPIO_reset(LED1_PORT);
    GPIO_reset(SW1_PORT);
    GPIO_reset(SW2_PORT);

    // Enable GPIO power for all used ports
    enablePort(LED1_PORT);
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
    digitalOutputConfig(LED1_PORT, LED1_PINCM_IDX, 22);
    digitalOutputConfig(LED2_PORT, LED2_PINCM_IDX, 26);

    // Ensure LED is off initially
    clearPins(LED1_PORT, LED1_PIN);
    clearPins(LED2_PORT, LED2_PIN);



    setUpperPinsPolarity(SW1_PORT, DL_GPIO_PIN_18_EDGE_RISE_FALL  );
    setUpperPinsPolarity(SW2_PORT, DL_GPIO_PIN_21_EDGE_RISE_FALL  );
    // Enable interrupts for switches
    enableInterrupt(SW1_PORT, SW1_PIN);
    enableInterrupt(SW2_PORT, SW2_PIN);


    setPins(LED2_PORT, LED2_PIN);
    setPins(LED1_PORT, LED1_PIN);

    while (1) {

       }

}

    void GROUP1_IRQHandler(void) {
        uint32_t gpioA = getEnabledInterruptStatus(SW1_PORT, SW1_PIN);
        uint32_t gpioB = getEnabledInterruptStatus(SW2_PORT, SW2_PIN);

        // Check if SW1 is pressed (Increase delay)
        if ((gpioA & SW1_PIN) == SW1_PIN) {

               clearPins(LED1_PORT, LED1_PIN);
                       delay_cycles(DELAY_800_MS);

                       // Turn on LED 1
                       setPins(LED1_PORT, LED1_PIN);
                       delay_cycles(DELAY_500_MS);

                       // Turn off LED 1 again
                     clearPins(LED1_PORT, LED1_PIN);



            clearInterruptStatus(SW1_PORT, SW1_PIN);
        }

        // Check if SW2 is pressed (Decrease delay)
        if ((gpioB & SW2_PIN) == SW2_PIN) {


            // Turn off LED 2
            clearPins(LED2_PORT, LED2_PIN);
            delay_cycles(DELAY_400_MS);

            // Turn on LED 2
            setPins(LED2_PORT, LED2_PIN);
            delay_cycles(DELAY_600_MS);

            // Turn off LED 2 again
           clearPins(LED2_PORT, LED2_PIN);



            clearInterruptStatus(SW2_PORT, SW2_PIN);
        }
    }

