#pragma once
#include <cstdint>
#include <cstddef>

struct RawFrame {
   std::uint16_t sync_word;
   std::uint32_t timestamp;
   std::int16_t speed;
   std::uint16_t dc_voltage;
   std::int16_t temperature;
   std::uint8_t status_flags;
   std::uint8_t crc;
};

RawFrame decode_frame(std::byte* p, size_t off);