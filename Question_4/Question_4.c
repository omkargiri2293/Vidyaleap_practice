/*
Problem Statement:
A timer is configured in PWM mode.
A LED is used to indicate the ON time of the PWM timer.
Switch 1 is used to increase the ON time.
Switch 2 is used to decrease the ON time.

Implementation Guidelines: The timer ON time will vary within certain range.

 NAME    - OMKAR GIRI
 ROLL_NO - BAMM-1U-06

 */


#include "ti_msp_dl_config.h"


#define MAX_DUTY_CYCLE 900
#define MIN_DUTY_CYCLE 100
#define DUTY_CYCLE_STEP 100

volatile uint16_t dutyCycle = MIN_DUTY_CYCLE;

int main(void) {
    SYSCFG_DL_init();

    DL_TimerG_startCounter(PWM_0_INST);

    while (1) {
        if (DL_GPIO_readPins(GPIO_SWITCH_SW_1_PORT, GPIO_SWITCH_SW_1_PIN)) {
            while (DL_GPIO_readPins(GPIO_SWITCH_SW_1_PORT, GPIO_SWITCH_SW_1_PIN));

            if (dutyCycle <= (MAX_DUTY_CYCLE - DUTY_CYCLE_STEP)) {
                dutyCycle += DUTY_CYCLE_STEP;
                DL_Timer_setCaptureCompareValue(PWM_0_INST, dutyCycle, DL_TIMER_CC_0_INDEX);
            }
        }

        if (!DL_GPIO_readPins(GPIO_SWITCH_SW_2_PORT, GPIO_SWITCH_SW_2_PIN)) {
            while (!DL_GPIO_readPins(GPIO_SWITCH_SW_2_PORT, GPIO_SWITCH_SW_2_PIN));

            if (dutyCycle >= (MIN_DUTY_CYCLE + DUTY_CYCLE_STEP)) {
                dutyCycle -= DUTY_CYCLE_STEP;
                DL_Timer_setCaptureCompareValue(PWM_0_INST, dutyCycle, DL_TIMER_CC_0_INDEX);
            }
        }
    }
}
