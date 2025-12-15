#pragma once
#include <cstdint>
#include <cstddef>
#include <vector>
#include "raw_frame.hpp"

std::vector<RawFrame> sweep_bytes(std::byte* p, size_t buffer_size);