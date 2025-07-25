/*
 * Baremetal.h
 *
 *  Created on: 22-Mar-2025
 *      Author: omkar
 */

#ifndef LIB_BAREMETAL_H_
#define LIB_BAREMETAL_H_



#include <stdint.h>
#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>

// Function Prototypes

/**
 * @brief Enables power to the specified GPIO port.
 * @param gpioPort Pointer to the GPIO register structure.
 */
void enablePort(GPIO_Regs* gpioPort);

/**
 * @brief Configures a pin as a digital output.
 * @param gpioPort Pointer to the GPIO register structure.
 * @param pinCMIndex Pin configuration index.
 * @param pinNumber GPIO pin number.
 */
void digitalOutputConfig(GPIO_Regs* gpioPort, uint8_t pinCMIndex, uint32_t pinNumber);

/**
 * @brief Sets a GPIO pin (turns it ON).
 * @param gpioPort Pointer to the GPIO register structure.
 * @param pins Bitmask of the pins to set.
 */
void setPins(GPIO_Regs* gpioPort, uint32_t pins);

/**
 * @brief Clears a GPIO pin (turns it OFF).
 * @param gpioPort Pointer to the GPIO register structure.
 * @param pins Bitmask of the pins to clear.
 */
void clearPins(GPIO_Regs* gpioPort, uint32_t pins);

/**
 * @brief Toggles a GPIO pin.
 * @param gpioPort Pointer to the GPIO register structure.
 * @param pins Bitmask of the pins to toggle.
 */
void togglePins(GPIO_Regs* gpioPort, uint32_t pins);

/**
 * @brief Reads the state of a GPIO pin.
 * @param gpioPort Pointer to the GPIO register structure.
 * @param pins Bitmask of the pins to read.
 * @return uint32_t State of the specified pins.
 */
uint32_t readPins(GPIO_Regs* gpioPort, uint32_t pins);

/**
 * @brief Configures a pin as a digital input with optional features.
 * @param pinCMIndex Pin configuration index.
 * @param inversion Enable or disable signal inversion.
 * @param internalResistor Configure pull-up, pull-down, or none.
 * @param hysteresis Enable or disable input hysteresis.
 * @param wakeup Configure wakeup functionality.
 */
void initDigitalInput(uint32_t pinCMIndex,
                      DL_GPIO_INVERSION inversion,
                      DL_GPIO_RESISTOR internalResistor,
                      DL_GPIO_HYSTERESIS hysteresis,
                      DL_GPIO_WAKEUP wakeup);

/**
 * @brief Resets a GPIO port.
 * @param gpioPort Pointer to the GPIO register structure.
 */
void GPIO_reset(GPIO_Regs* gpioPort);

/**
 * @brief Enables an interrupt for a specific IRQ.
 * @param IRQn Device specific interrupt number.
 */
void EnableIRQ(IRQn_Type IRQn);

/**
 * @brief Sets the polarity for upper GPIO pins.
 * @param gpioPort Pointer to the GPIO register structure.
 * @param polarity Polarity configuration bitmask.
 */
void setUpperPinsPolarity(GPIO_Regs* gpioPort, uint32_t polarity);

/**
 * @brief Clears the interrupt status of specified GPIO pins.
 * @param gpioPort Pointer to the GPIO register structure.
 * @param pins Bitmask of pins whose interrupt status should be cleared.
 */
void clearInterruptStatus(GPIO_Regs* gpioPort, uint32_t pins);

/**
 * @brief Enables interrupts on specified GPIO pins.
 * @param gpioPort Pointer to the GPIO register structure.
 * @param pins Bitmask of pins to enable interrupts for.
 */
void enableInterrupt(GPIO_Regs* gpioPort, uint32_t pins);

/**
 * @brief Disables interrupts on specified GPIO pins.
 * @param gpioPort Pointer to the GPIO register structure.
 * @param pins Bitmask of pins to disable interrupts for.
 */
void disableInterrupt(GPIO_Regs* gpioPort, uint32_t pins);

/**
 * @brief Gets the enabled interrupt status of GPIO pins.
 * @param gpioPort Pointer to the GPIO register structure.
 * @param pins Bitmask of pins to check.
 * @return uint32_t Bitmask of enabled interrupts.
 */
uint32_t getEnabledInterruptStatus(GPIO_Regs* gpioPort, uint32_t pins);

/**
 * @brief Checks which GPIO interrupts are enabled.
 * @param gpioPort Pointer to the GPIO register structure.
 * @param pins Bitmask of pins to check.
 * @return uint32_t Bitmask of enabled interrupts.
 */
uint32_t getEnabledInterrupts(GPIO_Regs* gpioPort, uint32_t pins);

/**
 * @brief Sets a GPIO interrupt as pending.
 * @param gpioPort Pointer to the GPIO register structure.
 * @param pins Bitmask of pins to set interrupt for.
 */
void setInterrupt(GPIO_Regs* gpioPort, uint32_t pins);

/**
 * @brief Gets the raw interrupt status of GPIO pins.
 * @param gpioPort Pointer to the GPIO register structure.
 * @param pins Bitmask of pins to check.
 * @return uint32_t Bitmask of raw interrupt status.
 */
uint32_t getRawInterruptStatus(GPIO_Regs* gpioPort, uint32_t pins);

/**
 * @brief Gets the highest priority pending GPIO interrupt.
 * @param gpioPort Pointer to the GPIO register structure.
 * @return DL_GPIO_IIDX The highest priority pending interrupt.
 */
DL_GPIO_IIDX getPendingInterrupt(GPIO_Regs* gpioPort);

#endif /* LIB_BAREMETAL_H_ */
