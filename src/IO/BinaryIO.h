/* 
Declares the BinaryReader and Writer classes (and relevant functions), which are used to serialize and deserialize the implemented files.
Copyright 2025 Boreal | Licensed under BSD-3
*/

#ifndef BINARYIO_H
#define BINARYIO_H

#include "../lib4jformats.h"
#include "Types.h"

#include <array>
#include <vector>
#include <cstddef>
#include <cstring>
#include <stdexcept>
#include <algorithm>
#include <string>
#include <fstream>
#include <memory>

#include <iostream>

namespace l4jf::io {
	
	class BinaryReader {
	private: 
		std::istream &stream;
		Endianness endian;
	public:
		BinaryReader(std::istream& _stream, Endianness _endian);
		
		template <typename T>
		T Read();

		uint8_t ReadByte();
		std::unique_ptr<ByteVector> ReadBytes(int64_t offset, size_t size);
		std::string ReadUTF8(size_t length);
		std::string Read4JString();
	};
	
	class BinaryWriter {
	private: 
		std::ostream &stream;
		Endianness endian;
	public:
		BinaryWriter(std::ostream &_stream, Endianness _endian) : stream(_stream), endian(_endian) {}
		
		template <typename T>
		void Write(const T v);
		
		void WriteUTF8(std::string input);
		void WriteBytes(const ByteVector& input);
		void Write4JString(std::string input);
		void WriteByte(uint8_t byte);
	};
}

#include "BinaryIO.t.h"

#endif //BINARYIO_H
