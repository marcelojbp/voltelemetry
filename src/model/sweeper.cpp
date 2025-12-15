#include <cstddef>
#include <vector>
#include "raw_frame.hpp"

std::vector<RawFrame> sweep_bytes(std::byte* p, size_t buffer_size){
    std::vector<RawFrame> frames;
    for (size_t i = 0; i < buffer_size; ++i) {
        if (p[i] == std::byte{0x5a} && p[i + 1] == std::byte{0xa5}) {
            frames.push_back(decode_frame(p, i));
        }
    }
    return frames;
}