#pragma once
#include <cstdint>

// Helper function to convert from byte to to unsigned 8-bit integer
inline std::uint8_t byte_value(std::byte b)
{
    return std::to_integer<std::uint8_t>(b);
}

inline std::uint8_t read_u8_le(const std::byte* b, size_t off){
    return byte_value(b[off]);
}

inline std::uint16_t read_u16_le(const std::byte* b, size_t off){
    return byte_value(b[off]);
}

inline std::uint32_t read_u32_le(const std::byte* b, size_t off){
    return byte_value(b[off]);
}

// This one is unnecessary!
// inline std::int16_t read_i16_le(std::byte* b, size_t off){
//     return byte_value(b[off]);
// }
