#pragma once
#include <cstdint>

struct Microseconds{ double value; };

struct Volt { double value; };

struct Rpm  { double value; };

struct Celsius {double value; };

struct Status {
    bool overtemp;
    bool overvoltage;
    bool random_fault;
};

struct Scaling {
    static constexpr double speed_rpm_per_count = 0.5;
    static constexpr double dc_volts_per_count = 800.0 / 4095.0;
    static constexpr double temp_c_per_count = 0.1;
    static constexpr double temp_c_offset = -50;
};

// enum class ParseError {
//   TooShort,
//   BadSync,
//   BadCrc
// };

struct Telemetry {
    Microseconds timestamp;
    Rpm speed;
    Volt dc_voltage;
    Celsius temperature;
    Status status;
};