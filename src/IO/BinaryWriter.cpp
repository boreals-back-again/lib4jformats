/* 
Defines the BinaryWriter class, which is used to serialize the implemented files.
Copyright 2025 Boreal | Licensed under LICENSE_TBD
*/

#include "BinaryIO.h"
#include <algorithm>

namespace l4jf::io {
	
	void BinaryWriter::WriteByte(std::byte byte) {
		stream.put(static_cast<char>(byte));
	}
	
	void BinaryWriter::WriteBytes(const ByteVector& input) {
 		stream.write(reinterpret_cast<const char*>(input.data()), input.size());
	}
	
	void BinaryWriter::WriteUTF8(std::string input) {
		stream << input;
	}
	
	void BinaryWriter::Write4JString(std::string input) {
		Write<uint16_t>(input.size());
		WriteUTF8(input);
	}
}
