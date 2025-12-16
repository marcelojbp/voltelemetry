#include <iostream>
#include <cstddef>   // std::byte
#include <cstdint>   // uint8_t
#include <utility>   // std::to_integer
#include <vector>

#include "io/byte_reader.hpp"
#include "model/raw_frame.hpp"
#include "model/frame_parser.hpp"
#include "model/sweeper.hpp"
#include "model/conversion.hpp"
#include "model/telemetry.hpp"

int main() {
  // read bytes
  ByteReader reader{ "data/raw/telemetry.bin" };
  std::byte buffer[64]{ };
  std::size_t bytes_read{reader.read_some(buffer, 64)};
    
  // printf("Read %zu bytes:\n", bytes_read);
  //   for (std::size_t i{0}; i < bytes_read; ++i) {
  //       std::uint8_t b = byte_value(buffer[i]);
  //       printf("%02x ", static_cast<unsigned int>(b));
  //   }

  std::vector<RawFrame> vec_decoded_frames = sweep_bytes(buffer, bytes_read);
  std::size_t n_frames = vec_decoded_frames.size();

  

  // for (const auto& frame : vec_decoded_frames) {
  //   printf("Timestamp: %d, Speed: %d, Voltage: %d\n", 
  //        frame.timestamp, frame.speed, frame.dc_voltage);
  // }
std::vector<Telemetry> telemetry_data; //Is there a nice way to initialise this ?!
  telemetry_data.resize(n_frames);

// Printing the output
printf("____________________________________________________________________________\n");
printf("Frames received: %zu \n", n_frames);
  for(std::size_t i = 0; i < n_frames; i++) {
    Telemetry physical_data = to_physical(vec_decoded_frames[i]);
    telemetry_data[i] = physical_data;
        printf("Frame %zu || Timestamp: %lf mu-s | Speed: %lf rpm | Voltage: %lf  V | \n", 
         i+1, (physical_data.timestamp).value, (physical_data.speed).value, (physical_data.dc_voltage).value);
  }
  printf("____________________________________________________________________________\n");
  printf("Telemetry decoding completed");
}
