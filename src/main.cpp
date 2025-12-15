/* Here:
 * decide input path (default = data/raw/telemetry.bin)
 * create a parser/readers
 * run the decode + store + report pipeline
 * print a short summary / return exit code
 */

#include <iostream>
#include "io/byte_reader.hpp"

int main() {

  // read bytes
  ByteReader reader("data/raw/telemetry.bin");

  // parse frames
  // for now, just a placeholder—we'll print a fake output summary
  printf("________________________________________________________\n");
  printf("________________________________________________________\n");
  printf("Frames received: 1234\n");
  // printf("Frames dropped (CRC): 12\n");
  // printf("Frames dropped (sync): 3\n \n");
  //  printf("Speed: \n \t min: 0 rpm\n \t max: 5000 rpm \n");
  // printf("Voltage: \n \t min: 520 V \n \t max: 580 V \n\n");
  // printf("Temperature: \n \t max: 85 C \n\n");
  // printf("Warnings: \n \t Overvoltage events: 2 \n \t Overtemperature events:
  // "
  //        "1 \n\n");
  printf("________________________________________________________\n");
  printf("________________________________________________________\n");
  printf("Telemetry decoding completed");
}
