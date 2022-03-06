#pragma once

#include <pins_arduino.h>

// Pin definitions according to the description on the board.
// These are the same pin numbers as in the original Arduino core for the STG-820 board.
// See https://barth-elektronik.com/downloads/9022-0022-A.pdf
auto constexpr IN1 = A0;
auto constexpr IN2 = A1;
auto constexpr IN3 = A2;
auto constexpr IN4 = D6;
auto constexpr IN5 = D7;
auto constexpr OUT1 = D0;
auto constexpr OUT2 = D1;
auto constexpr OUT3 = D2;
auto constexpr OUT4 = D3;
auto constexpr OUT5 = D4;  // Analog.
