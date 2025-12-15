# This file sources some random data for us to handle with the program
# To generate the data, just call python3 tools/gen_telemetry.py in the terminal 
#!/usr/bin/env python3
import struct
import random
import math

SYNC = 0xA55A
FRAME_FMT_NOCRC = "<H I h H h B"
FRAME_FMT_FULL  = "<H I h H h B B H"
RESERVED = 0

def clamp(x, lo, hi):
    return lo if x < lo else hi if x > hi else x

def crc8_simple(payload_bytes):
    return sum(payload_bytes) & 0xFF

def rpm_to_raw(rpm):
    return int(round(2.0 * rpm))

def volts_to_raw(volts):
    raw = int(round(volts * 4095.0 / 800.0))
    return clamp(raw, 0, 4095)

def celsius_to_raw(temp_c):
    raw = int(round(10.0 * (temp_c + 50.0)))
    return clamp(raw, -32768, 32767)

def speed_profile(t):
    if t < 10.0:
        return 1500.0 * (t / 10.0)
    if t < 40.0:
        return 1500.0
    if t < 60.0:
        return 1500.0 * (1.0 - (t - 40.0) / 20.0)
    return 0.0

def dc_voltage_profile(speed, t):
    base = 560.0
    droop = 30.0 * (speed / 1500.0)
    ripple = 2.0 * math.sin(2.0 * math.pi * 2.0 * t)
    noise = random.gauss(0.0, 1.5)
    return base - droop + ripple + noise

def temp_profile(speed, t, prev):
    ambient = 30.0
    target = ambient + 60.0 * (speed / 1500.0)
    tau = 12.0
    dt = 0.01
    temp = prev + (dt / tau) * (target - prev)
    if 5.0 < t < 12.0:
        temp += 0.8 * math.exp(-0.5 * ((t - 8.0) / 1.2) ** 2)
    temp += random.gauss(0.0, 0.08)
    return temp

def status_flags(speed, volts, temp):
    flags = 0
    if temp > 85.0:
        flags |= 1 << 0
    if volts > 650.0:
        flags |= 1 << 1
    if random.random() < 0.0008:
        flags |= 1 << 2
    return flags

def write_stream(path="data/raw/telemetry.bin"):
    random.seed(42)
    duration_s = 60.0
    sample_period_ms = 10
    n_samples = int(duration_s * 1000 / sample_period_ms)
    t_us = 0
    dt_us = sample_period_ms * 1000
    temp_c = 30.0

    with open(path, "wb") as f:
        for i in range(n_samples):
            t_s = t_us / 1e6
            speed = clamp(speed_profile(t_s) + random.gauss(0.0, 3.0), -50.0, 2000.0)
            volts = dc_voltage_profile(speed, t_s)
            if abs(t_s - 52.0) < 1e-6:
                volts = 900.0
            temp_c = temp_profile(speed, t_s, temp_c)
            if 23.0 <= t_s <= 23.2:
                t_us += dt_us
                continue

            speed_raw = clamp(rpm_to_raw(speed), -32768, 32767)
            dc_raw = volts_to_raw(volts)
            temp_raw = celsius_to_raw(temp_c)
            status = status_flags(speed, volts, temp_c)

            payload = struct.pack(FRAME_FMT_NOCRC, SYNC, t_us, speed_raw, dc_raw, temp_raw, status)
            crc = crc8_simple(payload)
            frame = struct.pack(FRAME_FMT_FULL, SYNC, t_us, speed_raw, dc_raw, temp_raw, status, crc, RESERVED)

            f.write(frame)
            t_us += dt_us

    print(f"Wrote {path}")

if __name__ == "__main__":
    write_stream()
