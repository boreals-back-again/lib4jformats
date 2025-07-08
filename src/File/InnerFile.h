/* 
Declares the InnerFile class, which is responsible holding the files in a File
Copyright 2025 Boreal | Licensed under BSD-3
*/

#ifndef INNERFILE_H
#define INNERFILE_H
#include "File.h"
#include "../IO/Types.h"
#include <memory>

namespace l4jf::file {
	
	class InnerFile {
	public:
		InnerFile() = default;
		InnerFile(std::string _name, std::unique_ptr<ByteVector> _data) 
			: name(_name), data(std::move(_data)) {}

		std::string GetName() const { return name; }
		size_t GetSize() const { return data->size(); }
		size_t GetHeaderSize() const;
		
		void Write(std::ostream& output);
	private:
		std::string name;
		std::unique_ptr<ByteVector> data;
	};
}
#endif // INNERFILE_H
