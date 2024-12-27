//---------------------------------------------------------------------------
#include <stddef.h>
#include <stdint.h>
//---------------------------------------------------------------------------
#include "crc32c.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
uint32_t crc32c::calc(const wchar_t* buffer, size_t length, uint32_t crc)
{
    crc = ~crc;
    while (length--) {
        crc ^= *buffer++;
        for (auto k = 0; k < 8; k++) {
            crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
        }
    }
    return ~crc;
}
//---------------------------------------------------------------------------
uint32_t crc32c::calc(const std::vector<unsigned char> buffer, uint32_t crc)
{
    crc = ~crc;
    for (auto byte : buffer) {
        crc ^= byte;
        for (auto k = 0; k < 8; k++) {
            crc = crc & 1 ? (crc >> 1) ^ POLY : crc >> 1;
        }
    }
    return ~crc;
}
//---------------------------------------------------------------------------
