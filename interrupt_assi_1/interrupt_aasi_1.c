/*
 * 1. After power on, blink the LED after every 400 msec.
 *  Now with each pressing of the button_1 the interval should increase by 100 msec. If the button_2 is pressed,
 *  the interval should decrease by 100 msec.
 *  The blinking interval should remain in 400 msec to 1200 msec range.
 *
 *  Name- OMKAR GIRI
 *  Roll no: BAMM-1U-06
 */

#include "ti_msp_dl_config.h"

volatile uint32_t blinkInterval = 400;

void delay_ms(uint32_t ms) {
    for (volatile uint32_t i = 0; i < ms * 3200; i++) {
        __NOP();
    }
}

int main(void) {
    SYSCFG_DL_init();


    NVIC_EnableIRQ(GPIO_SWITCHES_GPIOA_INT_IRQN);
    NVIC_EnableIRQ(GPIO_SWITCHES_GPIOB_INT_IRQN);


    DL_GPIO_writePins(GPIO_LEDS_PORT, GPIO_LEDS_USER_LED_1_PIN);

    while (1) {
        DL_GPIO_togglePins(GPIO_LEDS_PORT, GPIO_LEDS_USER_LED_1_PIN);
        delay_ms(blinkInterval);
    }
}

void GROUP1_IRQHandler(void) {


    uint32_t gpioA = DL_GPIO_getEnabledInterruptStatus(GPIOA,
        GPIO_SWITCHES_USER_SWITCH_1_PIN);
    uint32_t gpioB = DL_GPIO_getEnabledInterruptStatus(GPIOB,
            GPIO_SWITCHES_USER_SWITCH_2_PIN);


    if ((gpioA & GPIO_SWITCHES_USER_SWITCH_1_PIN) == GPIO_SWITCHES_USER_SWITCH_1_PIN) {
        if (blinkInterval < 1200) {
            blinkInterval += 100;
        }
        DL_GPIO_clearInterruptStatus(GPIOA, GPIO_SWITCHES_USER_SWITCH_1_PIN);
    }


    if ((gpioB & GPIO_SWITCHES_USER_SWITCH_2_PIN) == GPIO_SWITCHES_USER_SWITCH_2_PIN) {
        if (blinkInterval > 400) {
            blinkInterval -= 100;
        }
        DL_GPIO_clearInterruptStatus(GPIOB, GPIO_SWITCHES_USER_SWITCH_2_PIN);
    }
}
