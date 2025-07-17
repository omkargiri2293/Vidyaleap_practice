/*
 Problem Statement: Toggle the red and blue LEDS to give police light effect.

 NAME    - OMKAR GIRI
 ROLL_NO - BAMM-1U-06
 */

#include "ti_msp_dl_config.h"

int main(void)
{
    uint32_t DELAY = 12800000;

    SYSCFG_DL_init();


    while (1) {

        DL_GPIO_togglePins(GPIO_LED_PORT, GPIO_LED_LED_1_PIN);
        delay_cycles(DELAY);
        DL_GPIO_togglePins(GPIO_LEDS_PORT, GPIO_LEDS_LED_2_PIN);
        delay_cycles(DELAY);

    }
}
