/*
 * Time interval between two events is measured using a timer in capture mode.
 * Press SW1 to start the timer.
 * The constraint is that the time interval should be less than 8 seconds.
 */

#include "ti_msp_dl_config.h"
#include <stdio.h>

#define LOAD_VALUE 8000  // Timer load value (for known clock source)

/*
 * Storage Variables
 */
static uint8_t rollVal = 0;
uint16_t rollOver = 0;
bool capStatus = false;
uint32_t capTime = 0;

int main(void)
{
    // System and peripheral initialization
    SYSCFG_DL_init();
    NVIC_EnableIRQ(CAPTURE_0_INST_INT_IRQN);
    DL_SYSCTL_enableSleepOnExit();
    printf("[INFO] System Initialized. Ready to start!\n");

    while (1)
    {
        // Check if SW1 is pressed to start the timer
        if (DL_GPIO_readPins(GPIO_SWITCH_PORT, GPIO_SWITCH_SW_1_PIN))
        {
            while (DL_GPIO_readPins(GPIO_SWITCH_PORT, GPIO_SWITCH_SW_1_PIN)); // Wait for release

            if (!DL_TimerG_isRunning(CAPTURE_0_INST))
            {
                rollOver = 0;  // Reset rollover counter
                DL_Timer_startCounter(CAPTURE_0_INST);
                DL_GPIO_setPins(GPIO_LED_PORT, GPIO_LED_LED_1_PIN);
                printf(" Timer started!\n");
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
        case DL_TIMER_IIDX_CC0_DN:
            DL_Timer_clearInterruptStatus(CAPTURE_0_INST, DL_TIMER_IIDX_CC0_DN);
            capStatus = true;
            capTime = DL_Timer_getCaptureCompareValue(CAPTURE_0_INST, DL_TIMER_CC_0_INDEX);
            capTime = LOAD_VALUE - capTime;  // Calculate time interval

            printf("[ISR] Capture event detected: %u ms\n", capTime);
            DL_GPIO_clearPins(GPIO_LED_PORT, GPIO_LED_LED_1_PIN);
            break;

        case DL_TIMER_IIDX_ZERO:
            DL_Timer_clearInterruptStatus(CAPTURE_0_INST, DL_TIMER_IIDX_ZERO);
            rollVal++;
            rollOver = rollVal;
            printf("[ISR] Timer overflow detected! Rollover count: %u\n", rollOver);
            break;

        default:
            break;
    }
}
