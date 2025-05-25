/* 
Defines the enum for little and big endianness, and the byteVector
Copyright 2025 Boreal | Licensed under LICENSE_TBD
*/

#ifndef TYPES_H
#define TYPES_H

#include <vector>
#include <array>
#include <cstdint>
#include <algorithm>

namespace l4jf { // Not in IO namespace.
	
	using ByteVector = std::vector<std::byte>;
	
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
