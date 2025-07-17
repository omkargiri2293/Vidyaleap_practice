/*

 * Timer is configured for PWM mode to control the brightness of an LED.

 * When SW1 is pressed, the duty cycle of the PWM increases up to 90%.

 * When SW2 is pressed, the duty cycle of the PWM decreases down to 10%.

 */



#include "ti_msp_dl_config.h"

#include <stdio.h>



#define MAX_DUTY_CYCLE 450  // Corresponds to 90% duty cycle

#define MIN_DUTY_CYCLE 50   // Corresponds to 10% duty cycle

#define DUTY_CYCLE_STEP 50  // Step size for increasing/decreasing duty cycle



uint16_t dutyCycle = MIN_DUTY_CYCLE;


int main(void)

{

    // Initialize system configuration

    SYSCFG_DL_init();



    // Enable sleep on exit from ISR

    DL_SYSCTL_enableSleepOnExit();



    // Start the PWM timer

    DL_TimerG_startCounter(PWM_0_INST);



    while (1)

    {

        // Check if SW1 is pressed (active high)

        if (DL_GPIO_readPins(GPIO_SWITCH_SW_1_PORT, GPIO_SWITCH_SW_1_PIN))

        {

    delay_cycles(1600000);



            // Wait for SW1 to be released

            while (DL_GPIO_readPins(GPIO_SWITCH_SW_1_PORT, GPIO_SWITCH_SW_1_PIN));



            // Increase duty cycle, ensuring it does not exceed MAX_DUTY_CYCLE

            if (dutyCycle <= (MAX_DUTY_CYCLE - DUTY_CYCLE_STEP))

            {

                dutyCycle += DUTY_CYCLE_STEP;

                printf("Duty cycle increased: %d\n", dutyCycle);

                DL_Timer_setCaptureCompareValue(PWM_0_INST, dutyCycle, DL_TIMER_CC_0_INDEX);

            }

        }



        // Check if SW2 is pressed (active low)

        if (!DL_GPIO_readPins(GPIO_SWITCH_SW_2_PORT, GPIO_SWITCH_SW_2_PIN))

        {

            delay_cycles(1600000);



            // Wait for SW2 to be released

            while (!DL_GPIO_readPins(GPIO_SWITCH_SW_2_PORT, GPIO_SWITCH_SW_2_PIN));



            // Decrease duty cycle, ensuring it does not go below MIN_DUTY_CYCLE

            if (dutyCycle >= (MIN_DUTY_CYCLE + DUTY_CYCLE_STEP))

            {

                dutyCycle -= DUTY_CYCLE_STEP;

                printf("Duty cycle decreased: %d\n", dutyCycle);

                DL_Timer_setCaptureCompareValue(PWM_0_INST, dutyCycle, DL_TIMER_CC_0_INDEX);

            }

        }



           }

}
