/* 
Defines the BinaryReader class (and relevant functions), which is used to deserialize the implemented files.
Copyright 2025 Boreal | Licensed under BSD-3
*/

#include "BinaryIO.h"
#include <algorithm>
#include <array>
#include <chrono>
#include <iostream>

namespace l4jf::io {
	
	BinaryReader::BinaryReader(std::istream &_stream, Endianness _endian) : stream(_stream), endian(_endian) {}
	
	uint8_t BinaryReader::ReadByte() {
		char ch;
		stream.get(ch);
		return static_cast<uint8_t>(ch);
	}
	
	std::string BinaryReader::ReadUTF8(size_t length) {
		std::string buffer(length, '\0');
		stream.read(&buffer[0], length);
		return buffer;
	}
	
	std::string BinaryReader::Read4JString() {
		uint16_t length = Read<uint16_t>();
		return ReadUTF8(length);
	}
	
	std::unique_ptr<ByteVector> BinaryReader::ReadBytes(int64_t offset, size_t size) {
		auto origin = stream.tellg();
		ByteVector vec(size);

		if(offset != origin) stream.seekg(offset);
		stream.read(reinterpret_cast<char*>(vec.data()), size);
		if(offset != origin) stream.seekg(origin);
		
		return std::make_unique<ByteVector>(vec);
	}
	
}
