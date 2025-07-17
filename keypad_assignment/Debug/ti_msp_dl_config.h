/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X
#define CONFIG_MSPM0G3507

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)


#define CPUCLK_FREQ                                                     32000000




/* Port definition for Pin Group GPIO_PORT_C */
#define GPIO_PORT_C_PORT                                                 (GPIOB)

/* Defines for PIN_9: GPIOB.22 with pinCMx 50 on package pin 21 */
#define GPIO_PORT_C_PIN_9_PIN                                   (DL_GPIO_PIN_22)
#define GPIO_PORT_C_PIN_9_IOMUX                                  (IOMUX_PINCM50)
/* Port definition for Pin Group GPIO_PORT_B */
#define GPIO_PORT_B_PORT                                                 (GPIOB)

/* Defines for PIN_0: GPIOB.8 with pinCMx 25 on package pin 60 */
#define GPIO_PORT_B_PIN_0_PIN                                    (DL_GPIO_PIN_8)
#define GPIO_PORT_B_PIN_0_IOMUX                                  (IOMUX_PINCM25)
/* Defines for PIN_1: GPIOB.7 with pinCMx 24 on package pin 59 */
#define GPIO_PORT_B_PIN_1_PIN                                    (DL_GPIO_PIN_7)
#define GPIO_PORT_B_PIN_1_IOMUX                                  (IOMUX_PINCM24)
/* Defines for PIN_2: GPIOB.6 with pinCMx 23 on package pin 58 */
#define GPIO_PORT_B_PIN_2_PIN                                    (DL_GPIO_PIN_6)
#define GPIO_PORT_B_PIN_2_IOMUX                                  (IOMUX_PINCM23)
/* Defines for PIN_3: GPIOB.0 with pinCMx 12 on package pin 47 */
#define GPIO_PORT_B_PIN_3_PIN                                    (DL_GPIO_PIN_0)
#define GPIO_PORT_B_PIN_3_IOMUX                                  (IOMUX_PINCM12)
/* Defines for PIN_4: GPIOB.16 with pinCMx 33 on package pin 4 */
#define GPIO_PORT_B_PIN_4_PIN                                   (DL_GPIO_PIN_16)
#define GPIO_PORT_B_PIN_4_IOMUX                                  (IOMUX_PINCM33)
/* Port definition for Pin Group GPIO_PORT_A */
#define GPIO_PORT_A_PORT                                                 (GPIOA)

/* Defines for PIN_5: GPIOA.8 with pinCMx 19 on package pin 54 */
#define GPIO_PORT_A_PIN_5_PIN                                    (DL_GPIO_PIN_8)
#define GPIO_PORT_A_PIN_5_IOMUX                                  (IOMUX_PINCM19)
/* Defines for PIN_6: GPIOA.12 with pinCMx 34 on package pin 5 */
#define GPIO_PORT_A_PIN_6_PIN                                   (DL_GPIO_PIN_12)
#define GPIO_PORT_A_PIN_6_IOMUX                                  (IOMUX_PINCM34)
/* Defines for PIN_7: GPIOA.31 with pinCMx 6 on package pin 39 */
#define GPIO_PORT_A_PIN_7_PIN                                   (DL_GPIO_PIN_31)
#define GPIO_PORT_A_PIN_7_IOMUX                                   (IOMUX_PINCM6)
/* Defines for PIN_8: GPIOA.13 with pinCMx 35 on package pin 6 */
#define GPIO_PORT_A_PIN_8_PIN                                   (DL_GPIO_PIN_13)
#define GPIO_PORT_A_PIN_8_IOMUX                                  (IOMUX_PINCM35)

/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);



#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
