/* 
Defines the templated BinaryReader::Read and BinaryWriter::Write functions.
Copyright 2025 Boreal | Licensed under LICENSE_TBD
*/

#ifndef BINARYIO_T_H
#define BINARYIO_T_H

#include <sstream>
#include <iomanip>

namespace l4jf::io {

	template <typename T>
	T BinaryReader::Read() {
		// checks
		static_assert(std::is_trivially_copyable_v<T>, "Needs a trivially copyable type");
		static_assert( sizeof(T) != 2 || sizeof(T) != 4 || sizeof(T) != 8, "need 16, 32, or 64 bits for bswap" );
		
		std::array<std::byte, sizeof(T)> array;
		stream.read(reinterpret_cast<char*>(array.data()), sizeof(T));
		
		if(endian != SystemEndian) std::reverse(array.begin(), array.end());
		
		T temp;
		std::memcpy(&temp, array.data(), sizeof(T));	

		return temp;
	}
	
	template <typename T>
	void BinaryWriter::Write(const T v) {
		static_assert(std::is_trivially_copyable_v<T>, "Needs a trivially copyable type");

		std::array<std::byte, sizeof(T)> array;
		std::memcpy(array.data(), &v, sizeof(T));

		if (endian != SystemEndian)
			std::reverse(array.begin(), array.end());

		stream.write(reinterpret_cast<char*>(array.data()), sizeof(T));
	}
	
}

#endif // BINARYIO_T_H
