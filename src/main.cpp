/* Here:
 * decide input path (default = data/raw/telemetry.bin)
 * create a parser/readers
 * run the decode + store + report pipeline
 * print a short summary / return exit code
 */

#include <iostream>
#include "io/byte_reader.hpp"
#include "model/raw_frame.hpp"
#include "model/frame_parser.hpp"
#include "model/sweeper.hpp"
#include <cstddef>   // std::byte
#include <cstdint>   // uint8_t
#include <utility>   // std::to_integer
#include <vector>

int main() {
  // read bytes
  ByteReader reader{ "data/raw/telemetry.bin" };

  std::byte buffer[64]{ };
  std::size_t bytes_read{reader.read_some(buffer, 64)};
    
  printf("Read %zu bytes:\n", bytes_read);
    for (std::size_t i{0}; i < bytes_read; ++i) {
        std::uint8_t b = byte_value(buffer[i]);
        printf("%02x ", static_cast<unsigned int>(b));
    }

  
  std::vector<RawFrame> vec_decoded_frames = sweep_bytes(buffer, bytes_read);
  std::size_t n_frames = vec_decoded_frames.size();

  printf("\n");
  for (const auto& frame : vec_decoded_frames) {
    printf("Timestamp: %d, Speed: %d, Voltage: %d\n", 
         frame.timestamp, frame.speed, frame.dc_voltage);
  }

  // for now, just a placeholder—we'll print a fake output summary
  // printf("________________________________________________________\n");
  printf("Frames received: %zu \n", n_frames);
  // printf("Frames dropped (CRC): 12\n");
  // printf("Frames dropped (sync): 3\n \n");
  //  printf("Speed: \n \t min: 0 rpm\n \t max: 5000 rpm \n");
  // printf("Voltage: \n \t min: 520 V \n \t max: 580 V \n\n");
  // printf("Temperature: \n \t max: 85 C \n\n");
  // printf("Warnings: \n \t Overvoltage events: 2 \n \t Overtemperature events:
  // "
  //        "1 \n\n");
  printf("________________________________________________________\n");
  printf("Telemetry decoding completed");
}
