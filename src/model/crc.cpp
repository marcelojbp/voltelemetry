// #include <span>
// #include <cstddef>

// inline uint8_t crc8(std::span<const std::byte> bytes) { 

// }

// inline static bool crc_ok(std::span<const std::byte> frame16) {
//   uint8_t received = std::to_integer<uint8_t>(frame16[14]);
//   uint8_t computed = crc8(frame16.first(14));
//   return received == computed;
// }