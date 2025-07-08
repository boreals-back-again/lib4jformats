/* 
Declares the File class, which all File types are derived from
Copyright 2025 Boreal | Licensed under BSD-3
*/

#ifndef FILE_H
#define FILE_H

#include "../IO/BinaryIO.h"

namespace l4jf::file {

	class File {
	public:
		File();
		virtual size_t GetSize() const = 0;
		virtual void Write(std::ostream& output) = 0;
	};
}

#endif // FILE_H
