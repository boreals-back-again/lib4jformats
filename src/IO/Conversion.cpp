/* 
Declares conversion functions, which don't need to be in a class.
Copyright 2025 Boreal | Licensed under LICENSE_TBD
*/

#include "Conversion.h"

#include <sstream>
#include <iomanip>

namespace l4jf::io {

	std::string UIntToHexString(uint32_t input) {
		std::stringstream stream;
		stream << std::setfill('0') << std::setw(sizeof(uint32_t) * 2) << std::hex << input;
		return stream.str();
	}
	
	uint32_t HexStringToUInt(const std::string& str) {
		return static_cast<uint32_t>(std::stoul(str, nullptr, 16));
	}
	
}
