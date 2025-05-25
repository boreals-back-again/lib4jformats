/* 
Declares the ARCFile class, which implements the ARC file type.
Documentation for this file type is available at:
https://team-lodestone.github.io/Documentation/LCE/File%20Types/ARC.html
Copyright 2025 Boreal | Licensed under LICENSE_TBD
*/

#ifndef ARCHIVE_H
#define ARCHIVE_H
#include "../File/InnerFile.h"
#include "../IO/BinaryIO.h"

#include <map>

namespace l4jf::arc {
		
	class ARCFile {
	public:
		ARCFile(std::istream& stream);
		uint32_t GetFileCount() const { return files.size(); } 
		size_t GetSize() const;
		size_t GetHeaderSize() const;
		
		void AddFile(std::unique_ptr<file::InnerFile>&& file);
		void RemoveFile(uint32_t index);
		
		void Write(std::ostream& output);
	private: 		
		std::vector<std::unique_ptr<file::InnerFile>> files;
	};
}

#endif //ARCHIVE_H
