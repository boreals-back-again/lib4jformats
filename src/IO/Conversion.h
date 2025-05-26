/* 
Defines conversion functions, which don't need to be in a class.
Copyright 2025 Boreal | Licensed under LICENSE_TBD
*/

#ifndef CONVERSION_H
#define CONVERSION_H

#include <sstream>
#include <iomanip>

namespace l4jf::io {
	
	template <typename T>
	std::string ToHexString(T input) {
		std::stringstream stream;
		stream << std::setfill('0') << std::setw(sizeof(T) * 2) << std::hex << input;
		return stream.str();
	}
	
	template <typename T>
	T FromHexString(const std::string& str) {
		return static_cast<T>(std::stoul(str, nullptr, sizeof(T) * 4));
	}

}

#endif
