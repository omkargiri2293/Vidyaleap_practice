#include "BM.h"

// Enable power to the specified GPIO port
void enablePort(GPIO_Regs* port) {
    port->GPRCM.PWREN = (GPIO_PWREN_KEY_UNLOCK_W | GPIO_PWREN_ENABLE_ENABLE);
}

// Configure a pin as a digital output
void digitalOutputConfig(GPIO_Regs* gpio,uint8_t led_pincm_idx, uint32_t PinNumber) {
    IOMUX->SECCFG.PINCM[led_pincm_idx] = (IOMUX_PINCM_PC_CONNECTED | 0x00000001);
    gpio->DOE31_0 |= (1<< PinNumber);
}

// Set a GPIO pin (turn ON)
void setPins(GPIO_Regs* gpio, uint32_t pins) {
    gpio->DOUTSET31_0 = pins;
}

// Clear a GPIO pin (turn OFF)
void clearPins(GPIO_Regs* gpio, uint32_t pins) {
    gpio->DOUTCLR31_0 = pins;
}

// Toggle a GPIO pin
void togglePins(GPIO_Regs* gpio, uint32_t pins) {
    gpio->DOUTTGL31_0 = pins;
}

// Reset a GPIO port
void PORT_reset(GPIO_Regs* gpio) {
    gpio->GPRCM.RSTCTL = (GPIO_RSTCTL_KEY_UNLOCK_W | GPIO_RSTCTL_RESETSTKYCLR_CLR |
                           GPIO_RSTCTL_RESETASSERT_ASSERT);
}



uint32_t readPins(GPIO_Regs* gpio, uint32_t pins)
{
    return (gpio->DIN31_0 & pins);
}




/*
    Wakeup enabled
    DL_GPIO_WAKEUP_ENABLE = IOMUX_PINCM_WUEN_ENABLE,
    Wakeup disabled
    DL_GPIO_WAKEUP_DISABLE = IOMUX_PINCM_WUEN_DISABLE,
     Wakeup when pin changes to 0
    DL_GPIO_WAKEUP_ON_0 = (IOMUX_PINCM_WUEN_ENABLE | IOMUX_PINCM_WCOMP_MATCH0),
    Wakeup when pin changes to 1
    DL_GPIO_WAKEUP_ON_1 = (IOMUX_PINCM_WUEN_ENABLE | IOMUX_PINCM_WCOMP_MATCH1),

 */


/*
  DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
         DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE
 */


void initDigitalInput(uint32_t pincmIndex,
    DL_GPIO_INVERSION inversion, DL_GPIO_RESISTOR internalResistor,
    DL_GPIO_HYSTERESIS hysteresis, DL_GPIO_WAKEUP wakeup)
{
    /* GPIO functionality is always a pin function of 0x00000001 */
    IOMUX->SECCFG.PINCM[pincmIndex] =
        IOMUX_PINCM_INENA_ENABLE | IOMUX_PINCM_PC_CONNECTED |
        ((uint32_t) 0x00000001) | (uint32_t) inversion |
        (uint32_t) internalResistor | (uint32_t) hysteresis |
        (uint32_t) wakeup;
}


void GPIO_reset(GPIO_Regs* gpio)
{
    gpio->GPRCM.RSTCTL =
        (GPIO_RSTCTL_KEY_UNLOCK_W | GPIO_RSTCTL_RESETSTKYCLR_CLR |
            GPIO_RSTCTL_RESETASSERT_ASSERT);
}
