#pragma once
#include <cstdint>

// Helper function to convert from byte to to unsigned 8-bit integer
inline std::uint8_t byte_value(const std::byte b)
{
    return std::to_integer<std::uint8_t>(b);
}

// Helper functions to convert from byte to eacho of the reading types 

inline std::uint8_t read_u8_le(const std::byte* b, size_t off){
    return byte_value(b[off]);
}

inline std::uint16_t read_u16_le(const std::byte* b, size_t off){
    return byte_value(b[off]);
}

inline std::uint32_t read_u32_le(const std::byte* b, size_t off){
    return byte_value(b[off]);
}

