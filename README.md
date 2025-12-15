# Drive Telemetry Frame Decoder

This project simulates and decodes binary telemetry frames similar to those
used during industrial drive commissioning.

## Overview
- Python script generates realistic binary telemetry (`telemetry.bin`)
- C++ code parses, validates, scales, and analyzes the data
- Focus: correctness, ownership, lifetime safety, and type-safe physical units

## Frame format (16 bytes, little-endian)
| Field | Size | Description |
|------|------|-------------|
| Sync word | 2 | 0xA55A |
| Timestamp | 4 | microseconds |
| Speed | 2 | raw counts |
| DC voltage | 2 | raw ADC |
| Temperature | 2 | raw ADC |
| Status | 1 | bitfield |
| CRC | 1 | checksum |
| Reserved | 2 | padding |

## Generate data
```bash
python3 tools/gen_telemetry.py
```

## Build (later)
CMakeLists.txt is provided as a placeholder.
