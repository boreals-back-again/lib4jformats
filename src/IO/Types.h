/* 
Defines the enum for little and big endianness, and the byteVector
Copyright 2025 Boreal | Licensed under BSD-3
*/

#ifndef TYPES_H
#define TYPES_H

#include <vector>
#include <array>
#include <cstdint>
#include <algorithm>

namespace l4jf { // Not in IO namespace.
	
	using ByteVector = std::vector<uint8_t>;
	
	enum class Endianness {
		LittleEndian,
		BigEndian
	};
	
	#ifdef BR_BIG_ENDIAN
		const Endianness SystemEndian = Endianness::BigEndian;
	#else
		const Endianness SystemEndian = Endianness::LittleEndian;
	#endif
}

#endif //TYPES_H
