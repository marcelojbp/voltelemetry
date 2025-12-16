#include <cstdint>
#include "telemetry.hpp"
#include "raw_frame.hpp"

static Status decode_status(uint8_t flags) {
    return{
        .overtemp = (flags & (1u << 0)) != 0,  // if bit 0 is set 1; zero otherwise
        .overvoltage = (flags & (1u <<1)) != 0, // if bit 1 is set 1; zero otherwise
        .random_fault = (flags & (1u<<2)) != 0, // if bit 2 is set 1; zero otherwise
    }; //we store the results in Status.[property]
}

Telemetry to_physical(const RawFrame& ref) { 
    return Telemetry{
        .timestamp = Microseconds{static_cast<double>(ref.timestamp)} ,
        .speed = Rpm{ref.speed * Scaling::speed_rpm_per_count},
        .dc_voltage = Volt{ref.dc_voltage * Scaling::dc_volts_per_count},
        .temperature = Celsius{ref.temperature * Scaling::temp_c_per_count - Scaling::temp_c_offset},
        .status = decode_status(ref.status_flags),
    };
}