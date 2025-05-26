/* 
Defines conversion functions, which don't need to be in a class.
Copyright 2025 Boreal | Licensed under LICENSE_TBD
*/

#ifndef CONVERSION_H
#define CONVERSION_H

#include <cstdint>
#include <string>

namespace l4jf::io {

	std::string UIntToHexString(uint32_t input);
	uint32_t HexStringToUInt(const std::string& str);

}

#endif //CONVERSION_H
