#include <Arduino.h>

#include "can.h"

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
}

void on_receive(uint32_t id, uint8_t const* data, size_t size)
{
    digitalToggle(LED_BUILTIN);
}

void loop()
{
    can::on_receive(on_receive);
    can::init(can::Baudrate::Rate250k);

    int counter = 0;
    while (true) {
        uint8_t data[] = {counter};
        can::send(0x234, data);

        delay(1000);

        counter++;
    }
}
