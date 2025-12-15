#pragma once
#include <cstddef>
#include <fstream>
#include <string>

struct ByteReader {
	public:
		explicit ByteReader(const std::string& path);

		std::size_t read_some(std::byte* buffer, std::size_t buffer_size);
	
	bool eof() const; //End of file function

	private:
	std::ifstream file_;
};
