/*
 *******************************************************************************
 * Copyright (c) 2020-2021, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
    PC_13,  // D0 - OUT1
    PC_14,  // D1 - OUT2
    PC_15,  // D2 - OUT3
    PA_4,   // D3 - OUT4
    PA_5,   // D4 - OUT5
    PA_8,   // D5 - LED
    PA_12,  // D6 - IN4
    PA_15,  // D7 - IN5
    PB_6,   // D8 - CAN-S
    PA_9,   // D9 - TTL-RS232-TX
    PA_10,  // D10 - TTL-RS232-RX
    PA_13,  // D11 - SWD
    PA_14,  // D12 - SWD
    PB_8,   // D13 - CAN-RX
    PB_9,   // D14 - CAN-TX
    PB_10,  // D15 - IrDA-TX
    PB_11,  // D16 - IrDA-RX
    PB_13,  // D17 - I2C-SCL
    PB_14,  // D18 - I2C-SDA
    PF_0,   // D19 - Q
    PF_1,   // D20 - Q
    PF_11,  // D21 - BOOT0
    PA_0,   // D22 - AIN1
    PA_1,   // D23 - AIN2
    PA_2,   // D24 - AIN3
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
    D22,  // A0 - IN1
    D23,  // A1 - IN2
    D24,  // A2 - IN3
};
