/* Question_2
Problem Statement:
If switch1 is pressed scroll the LEDs left to right.
If switch 2 is pressed scroll the LEDs right to left.
Print number of times switches 1 & 2 are pressed.

Implementation Guidelines: There is no need to debounce the buttons.

 NAME    - OMKAR GIRI
 ROLL_NO - BAMM-1U-06
 */


#include "ti_msp_dl_config.h"
#include <stdio.h>

uint16_t sw1 = 0;
uint16_t sw2 = 0;
 uint32_t delay =  6400000;
int main(void)
{
    SYSCFG_DL_init();


    while (1) {


        if (DL_GPIO_readPins(GPIO_SWITCH_PORT, GPIO_SWITCH_SW_1_PIN)) {
            sw1++;
            printf("SW1 press : %u times \n", sw1);
            DL_GPIO_setPins(GPIO_LED_PORT, GPIO_LED_LED_1_PIN);
            delay_cycles(delay);
            DL_GPIO_setPins(GPIO_LEDS_PORT, GPIO_LEDS_LED_2_PIN);
            DL_GPIO_clearPins(GPIO_LED_PORT, GPIO_LED_LED_1_PIN);
            delay_cycles(delay);
            DL_GPIO_clearPins(GPIO_LEDS_PORT, GPIO_LEDS_LED_2_PIN);
        }
        delay_cycles(delay);
        if (!DL_GPIO_readPins(GPIO_SWITCHES_PORT, GPIO_SWITCHES_SW_2_PIN)) {
            sw2++;
                        printf("SW2 press : %u times \n", sw2);
                        DL_GPIO_setPins(GPIO_LEDS_PORT, GPIO_LEDS_LED_2_PIN);
                        delay_cycles(delay);
                        DL_GPIO_setPins(GPIO_LED_PORT, GPIO_LED_LED_1_PIN);
                        DL_GPIO_clearPins(GPIO_LEDS_PORT, GPIO_LEDS_LED_2_PIN);
                        delay_cycles(delay);
                        DL_GPIO_clearPins(GPIO_LED_PORT, GPIO_LED_LED_1_PIN);

                }
        delay_cycles(delay);



    }
}
