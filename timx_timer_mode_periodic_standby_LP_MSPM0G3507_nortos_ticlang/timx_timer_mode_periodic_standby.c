/*

 */

#include "ti_msp_dl_config.h"

/* ((32KHz / (32+1)) * 0.5s) = 45 - 1 = 495 due to N+1 ticks */
#define TIMER_500_MILLISECONDS_TICKS (495)
/* ((32KHz / (32+1)) * 0.05s) = 50 */
#define TIMER_50_MILLISECONDS_TICKS (50)

int main(void)
{
    SYSCFG_DL_init();

    NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
    DL_SYSCTL_enableSleepOnExit();

    DL_TimerG_startCounter(TIMER_0_INST);

    while (1) {
        __WFI();
    }
}

void TIMER_0_INST_IRQHandler(void)
{
    static uint32_t count = TIMER_500_MILLISECONDS_TICKS;
    switch (DL_TimerG_getPendingInterrupt(TIMER_0_INST)) {
        case DL_TIMER_IIDX_ZERO:
            /*
             * Counter stopped to avoid a conflict with the timer reading
             * the LOAD value while it's being set
             */
                DL_TimerG_stopCounter(TIMER_0_INST);

            /*
             * Count progressively gets smaller in 0.05 s increments until
             * reset with 0.5s
             */
                if (count > (TIMER_500_MILLISECONDS_TICKS / 5)) {
                    count = count - TIMER_50_MILLISECONDS_TICKS;
                } else {
                    count = TIMER_500_MILLISECONDS_TICKS;
                }

                DL_Timer_setLoadValue(TIMER_0_INST, count);
            /*
             * By default, this should load the new count value and count down
             * from there (CVAE = 0)
             */
                DL_TimerG_startCounter(TIMER_0_INST);

            DL_GPIO_togglePins(GPIO_LEDS_PORT,
                (GPIO_LEDS_USER_LED_1_PIN | GPIO_LEDS_USER_TEST_PIN));
            break;
        default:
            break;
    }
}
