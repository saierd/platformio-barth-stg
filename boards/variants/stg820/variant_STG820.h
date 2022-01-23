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
#pragma once

#define NUM_DIGITAL_PINS 25
#define NUM_ANALOG_INPUTS 3

// On-board LED pin number
#ifndef LED_BUILTIN
#define LED_BUILTIN 5
#endif

// I2C definitions
#ifndef PIN_WIRE_SDA
#define PIN_WIRE_SDA 18
#endif
#ifndef PIN_WIRE_SCL
#define PIN_WIRE_SCL 17
#endif

// Timer Definitions
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#ifndef TIMER_TONE
#define TIMER_TONE TIM6
#endif
#ifndef TIMER_SERVO
#define TIMER_SERVO TIM7
#endif

// UART Definitions
#ifndef SERIAL_UART_INSTANCE
#define SERIAL_UART_INSTANCE 1
#endif

// Default pin used for generic 'Serial' instance
// Mandatory for Firmata
#ifndef PIN_SERIAL_RX
#define PIN_SERIAL_RX 10
#endif
#ifndef PIN_SERIAL_TX
#define PIN_SERIAL_TX 9
#endif

// Extra HAL modules
#if !defined(HAL_DAC_MODULE_DISABLED)
#define HAL_DAC_MODULE_ENABLED
#endif

#if !defined(HAL_CAN_MODULE_DISABLED)
#define HAL_CAN_MODULE_ENABLED
#endif

/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus
// These serial port names are intended to allow libraries and architecture-neutral
// sketches to automatically default to the correct port name for a particular type
// of use.  For example, a GPS module would normally connect to SERIAL_PORT_HARDWARE_OPEN,
// the first hardware serial port whose RX/TX pins are not dedicated to another use.
//
// SERIAL_PORT_MONITOR        Port which normally prints to the Arduino Serial Monitor
//
// SERIAL_PORT_USBVIRTUAL     Port which is USB virtual serial
//
// SERIAL_PORT_LINUXBRIDGE    Port which connects to a Linux system via Bridge library
//
// SERIAL_PORT_HARDWARE       Hardware serial port, physical RX & TX pins.
//
// SERIAL_PORT_HARDWARE_OPEN  Hardware serial ports which are open for use.  Their RX & TX
//                            pins are NOT connected to anything by default.
#ifndef SERIAL_PORT_MONITOR
#define SERIAL_PORT_MONITOR Serial
#endif
#ifndef SERIAL_PORT_HARDWARE
#define SERIAL_PORT_HARDWARE Serial
#endif
#endif
