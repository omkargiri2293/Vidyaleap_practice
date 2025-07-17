/* Question_5

Problem Statement:
Timer is configured in upcounting mode.
It is upcounted every 100 msec.
Switch 1 is used to start the timer.
Switch 2 is used to capture the timer current value.
And the timer captured value is printed.

 NAME    - OMKAR GIRI
 ROLL_NO - BAMM-1U-06

 */


#include "ti_msp_dl_config.h"
#include <stdio.h>

#define LOAD_VALUE 100  // Timer load value for 100 ms timing

/*
 * Storage Variables
 */
static uint8_t rollVal = 0;
uint16_t rollOver = 0;
uint32_t capTime = 0;
uint32_t Time = 0;


int main(void)
{
    // System and peripheral initialization
    SYSCFG_DL_init();
    NVIC_EnableIRQ(CAPTURE_0_INST_INT_IRQN);
    DL_SYSCTL_enableSleepOnExit();
    printf("[INFO] System Initialized. Ready to start!\n");

    while (1)
    {
        if (DL_GPIO_readPins(GPIO_SWITCH_PORT, GPIO_SWITCH_SW_1_PIN))
        {
            while (DL_GPIO_readPins(GPIO_SWITCH_PORT, GPIO_SWITCH_SW_1_PIN));
            if (!DL_TimerG_isRunning(CAPTURE_0_INST))
            {
                rollOver = 0;
                rollVal = 0;
                DL_Timer_startCounter(CAPTURE_0_INST);

                printf("[INFO] Timer started!\n");
            }
        }
    }
}

/*
 * Timer Capture ISR
 */
void CAPTURE_0_INST_IRQHandler(void)
{
    switch (DL_Timer_getPendingInterrupt(CAPTURE_0_INST))
    {
        case DL_TIMER_IIDX_ZERO: // Timer overflow
            DL_Timer_clearInterruptStatus(CAPTURE_0_INST, DL_TIMER_IIDX_ZERO);
            rollVal++;
            rollOver = rollVal;
            printf("[ISR] Timer overflow detected! Rollover count: %u\n", rollOver);
            break;

        case DL_TIMER_IIDX_CC0_DN: // Capture event
            DL_Timer_clearInterruptStatus(CAPTURE_0_INST, DL_TIMER_IIDX_CC0_DN);
            capTime = DL_Timer_getCaptureCompareValue(CAPTURE_0_INST, DL_TIMER_CC_0_INDEX);
            Time = ( LOAD_VALUE * rollOver ) - capTime;  // Corrected time calculation

            printf("[ISR] Capture event detected: %u ms\n", Time);

            break;

        default:
            break;
    }
}
