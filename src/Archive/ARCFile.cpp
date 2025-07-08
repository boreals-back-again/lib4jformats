/* 
Defines the ARCFile class, which implements the ARC file type.
Documentation for this file type is available at:
https://team-lodestone.github.io/Documentation/LCE/File%20Types/ARC.html
Copyright 2025 Boreal | Licensed under BSD-3
*/

#include "ARCFile.h"
#include <algorithm>

namespace l4jf::arc {
	
	ARCFile::ARCFile(std::istream& stream) {
		io::BinaryReader reader(stream, Endianness::BigEndian);
		
		uint32_t fileCount = reader.Read<uint32_t>();
		files = std::vector<std::unique_ptr<file::InnerFile>>(fileCount);
		
		for(size_t i = 0; i < fileCount; i++) {
			std::string name = reader.Read4JString();
			uint32_t offset = reader.Read<uint32_t>();
			uint32_t size = reader.Read<uint32_t>();
			
			files[i] = std::make_unique<file::InnerFile>( file::InnerFile(name, reader.ReadBytes(offset, size)) );
		}
	}
	
	size_t ARCFile::GetSize() const {
		size_t size = 0;
		size += sizeof(GetFileCount());
		
		for(const auto& file : files) {
			size += file->GetSize();
			size += file->GetHeaderSize();
		}
		
		return size;
	}
	
	size_t ARCFile::GetHeaderSize() const {
		size_t size = 0;
		
		size += sizeof(GetFileCount()); // 4
		
		for(const auto& file : files) {
			size += file->GetHeaderSize();
		}
		
		return size;
	}
	
	void ARCFile::AddFile(std::unique_ptr<file::InnerFile>&& file) {
        this->files.push_back(std::move(file));
    }

    void ARCFile::RemoveFile(const uint32_t index) {
        if (index >= files.size()) return;
		files.erase(files.begin() + index);
    }
	
	// Calculate offset
	void ARCFile::Write(std::ostream& output) {
		io::BinaryWriter writer(output, Endianness::BigEndian);
		
		writer.Write<uint32_t>(GetFileCount());
		
		size_t currentOffset = GetHeaderSize();
		
		for(const auto& file : files) {
			writer.Write4JString(file->GetName());
			writer.Write<uint32_t>(currentOffset);
			writer.Write<uint32_t>(file->GetSize());
			
			currentOffset += file->GetSize();
		}
		
		for(auto& file : files) {
			file->Write(output);
		}
	}
}

