/*
 * Baremetal.c
 *
 *  Created on: 20-Mar-2025
 *      Author: omkar
 */


#include <Baremetal.h>

// Function to enable power to a specified GPIO port
void enablePort(GPIO_Regs* port) {
    port->GPRCM.PWREN = (GPIO_PWREN_KEY_UNLOCK_W | GPIO_PWREN_ENABLE_ENABLE);
}

// Configure a pin as a digital output
void digitalOutputConfig(GPIO_Regs* gpio, uint8_t led_pincm_idx, uint32_t PinNumber) {
    // Configure the pin control multiplexer for GPIO
    IOMUX->SECCFG.PINCM[led_pincm_idx] = (IOMUX_PINCM_PC_CONNECTED | 0x00000001);
    // Enable output for the specified pin
    gpio->DOE31_0 |= (1 << PinNumber);
}

// Set (turn ON) a GPIO pin
void setPins(GPIO_Regs* gpio, uint32_t pins) {
    gpio->DOUTSET31_0 = pins;
}

// Clear (turn OFF) a GPIO pin
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

// Read the state of GPIO pins
uint32_t readPins(GPIO_Regs* gpio, uint32_t pins) {
    return (gpio->DIN31_0 & pins);
}

// Initialize a digital input pin with specific configurations
void initDigitalInput(uint32_t pincmIndex,
    DL_GPIO_INVERSION inversion, DL_GPIO_RESISTOR internalResistor,
    DL_GPIO_HYSTERESIS hysteresis, DL_GPIO_WAKEUP wakeup) {

    // Configure the pin for input with various options
    IOMUX->SECCFG.PINCM[pincmIndex] =
        IOMUX_PINCM_INENA_ENABLE | IOMUX_PINCM_PC_CONNECTED |
        ((uint32_t) 0x00000001) | (uint32_t) inversion |
        (uint32_t) internalResistor | (uint32_t) hysteresis |
        (uint32_t) wakeup;
}

// Reset a GPIO module
void GPIO_reset(GPIO_Regs* gpio) {
    gpio->GPRCM.RSTCTL =
        (GPIO_RSTCTL_KEY_UNLOCK_W | GPIO_RSTCTL_RESETSTKYCLR_CLR |
         GPIO_RSTCTL_RESETASSERT_ASSERT);
}




// Enable an interrupt for a specific IRQ number
void EnableIRQ(IRQn_Type IRQn) {
    if ((int32_t)(IRQn) >= 0) {
        __COMPILER_BARRIER();
        NVIC->ISER[0U] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
        __COMPILER_BARRIER();
    }
}

// Set the polarity for upper GPIO pins
void setUpperPinsPolarity(GPIO_Regs* gpio, uint32_t polarity) {
    gpio->POLARITY31_16 |= polarity;
}

// Clear the interrupt status for specified GPIO pins
void clearInterruptStatus(GPIO_Regs* gpio, uint32_t pins) {
    gpio->CPU_INT.ICLR |= pins;
}

// Enable GPIO interrupts for specified pins
void enableInterrupt(GPIO_Regs* gpio, uint32_t pins) {
    gpio->CPU_INT.IMASK |= pins;
}

// Disable GPIO interrupts for specified pins
void disableInterrupt(GPIO_Regs* gpio, uint32_t pins) {
    gpio->CPU_INT.IMASK &= ~pins;
}

// Get the status of enabled GPIO interrupts
uint32_t getEnabledInterrupts(GPIO_Regs* gpio, uint32_t pins) {
    return (gpio->CPU_INT.IMASK & pins);
}

// Get the status of enabled and pending GPIO interrupts
uint32_t getEnabledInterruptStatus(GPIO_Regs* gpio, uint32_t pins) {
    return (gpio->CPU_INT.MIS & pins);
}

// Manually set a GPIO interrupt to be pending
void setInterrupt(GPIO_Regs* gpio, uint32_t pins) {
    gpio->CPU_INT.ISET = pins;
}

// Get the raw interrupt status (even if not enabled)
uint32_t getRawInterruptStatus(GPIO_Regs* gpio, uint32_t pins) {
    return (gpio->CPU_INT.RIS & pins);
}

// Get the highest priority pending GPIO interrupt
DL_GPIO_IIDX getPendingInterrupt(GPIO_Regs* gpio) {
    return (DL_GPIO_IIDX)(gpio->CPU_INT.IIDX);
}
