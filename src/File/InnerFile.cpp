/* 
Defines the InnerFile class, which is responsible holding the files in a File
Copyright 2025 Boreal | Licensed under LICENSE_TBD
*/

#include "InnerFile.h"
#include "../IO/BinaryIO.h"
#include <iostream>

namespace l4jf::file {
	
	size_t InnerFile::GetHeaderSize() const {
		return sizeof(uint16_t) + name.size() 
		+ sizeof(uint32_t) // size 
		+ sizeof(uint32_t); // data
	}
	
	void InnerFile::Write(std::ostream& output) {
		io::BinaryWriter writer(output, Endianness::BigEndian);
		writer.WriteBytes(*data);
	}
}
