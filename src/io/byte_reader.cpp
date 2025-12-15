#include "byte_reader.hpp"
#include <stdexcept>

// We use a constructor with a member initializer list
ByteReader::ByteReader(const std::string& path) : file_{path, std::ios::binary} {
        if(!file_) {
            // throw std::runtime_error("\n Failed to open file:" + path);
             throw std::runtime_error("\n Failed to open file: " + path );
             
        }   
    }
std::size_t ByteReader::read_some(std::byte* buffer, std::size_t buffer_size) {
    // we treat memory as raw bytes not chars
    file_.read(reinterpret_cast<char*>(buffer),  //read expects chars --> reintepret
            static_cast<std::streamsize>(buffer_size)); //safe type conversion

    return static_cast<std::size_t>(file_.gcount());
}

bool ByteReader::eof() const
{
    return file_.eof(); 
}
