/*
 * BM.h
 *
 *  Created on: 04-Mar-2025
 *      Author: omkar
 */

#ifndef BM_H_
#define BM_H_

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
#endif /* BM_H_ */
