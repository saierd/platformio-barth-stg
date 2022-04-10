#pragma once

#include <cstdint>
#include <cstddef>

// Provides a simple interface for using the CAN bus. Most of the implementation was taken from the Barth samples in
// https://barth-elektronik.com/downloads/9045-0020-A.zip and ported to the newer HAL API.

namespace can {

enum Baudrate : int {
    Rate1m = 1,
    Rate500k = 2,
    Rate250k = 4,
    Rate125k = 8,
    Rate100k = 10,
    Rate50k = 20,
};

void init(Baudrate baudrate);
void set_baudrate(Baudrate baudrate);

void send(uint32_t id, uint8_t const* data, size_t size);

template <size_t N>
void send(uint32_t id, uint8_t const (&data)[N])
{
    send(id, data, N);
}

using ReceiveCallback = void (*)(uint32_t id, uint8_t const* data, size_t size);
void on_receive(ReceiveCallback callback);

}  // namespace can
