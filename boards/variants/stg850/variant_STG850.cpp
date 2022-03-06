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
    PA_7,   // D4 - OUT5
    PB_0,   // D5 - OUT6
    PB_1,   // D6 - OUT7
    PB_2,   // D7 - OUT8
    PB_7,   // D8 - OUT9
    PA_8,   // D9 - LED
    PA_12,  // D10 - IN7
    PA_15,  // D11 - IN8
    PB_4,   // D12 - IN9
    PB_5,   // D13 - IN10
    PB_6,   // D14 - CAN-S
    PA_9,   // D15 - TTL-RS232-TX
    PA_10,  // D16 - TTL-RS232-RX
    PA_13,  // D17 - SWD
    PA_14,  // D18 - SWD
    PB_8,   // D19 - CAN-RX
    PB_9,   // D20 - CAN-TX
    PB_10,  // D21 - IrDA-TX
    PB_11,  // D22 - IrDA-RX
    PB_13,  // D23 - I2C-SCL
    PB_14,  // D24 - I2C-SDA
    PF_0,   // D25 - Q
    PF_1,   // D26 - Q
    PF_11,  // D27 - BOOT0
    PA_0,   // D28 - AIN1
    PA_1,   // D29 - AIN2
    PA_2,   // D30 - AIN3
    PA_3,   // D31 - AIN4
    PA_5,   // D32 - AIN5
    PA_6    // D33 - AIN6
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
    D28,  // A0 - IN1
    D29,  // A1 - IN2
    D30,  // A2 - IN3
    D31,  // A3 - IN4
    D32,  // A4 - IN5
    D33,  // A5 - IN6
};
