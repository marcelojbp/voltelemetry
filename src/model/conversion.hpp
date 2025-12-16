#include <cstdint>
#include "telemetry.hpp"
#include "raw_frame.hpp"

static Status decode_status(uint8_t flags);

Telemetry to_physical(const RawFrame& ref);