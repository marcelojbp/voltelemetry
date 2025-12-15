#include "raw_frame.hpp"
#include "frame_parser.hpp"
#include <cstddef>

RawFrame decode_frame(std::byte* p, size_t off){
    RawFrame frame{};
    frame.sync_word = read_u16_le(p, off);
    frame.timestamp = read_u32_le(p, off + 2);
    frame.speed =  read_u16_le(p, off + 6);
    frame.dc_voltage = read_u16_le(p, off + 8);
    frame.temperature = read_u16_le(p, off + 10);
    frame.status_flags = read_u8_le(p, off + 13);
    frame.crc = read_u8_le(p, off + 14);
    // the last 2 bytes (out of 16) are left zeroed.
    
    return frame;
}