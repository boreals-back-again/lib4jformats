/* 
Declares the Language class (and the keys inside), which implements the language data inside of LOCs.
Copyright 2025 Boreal | Licensed under LICENSE_TBD
*/

#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <unordered_map>
#include <memory>
#include <optional>
#include "../IO/BinaryIO.h"

namespace l4jf::loc {
	
	using Keys = std::vector<std::string>;
	
	class Language {
	public:
		Language(io::BinaryReader& reader, std::shared_ptr<Keys> keys);
		
		void Write(io::BinaryWriter& writer) const;
		
		std::optional<std::string> GetStringByIndex(size_t index) const;
		std::optional<std::string> GetStringByKey(std::string key) const;
		std::unique_ptr<std::vector<std::string>> GetStringsOrdered() const;
		
		std::string GetCode() const;
	private:
		uint32_t shouldReadByte;
		std::byte byte{}; // if !shouldReadByte, this is null.
		
		std::string code;
		
		std::unordered_map<std::string, std::string> strings;
		std::shared_ptr<Keys> keys;
	};
	
}

#endif //LANGUAGE_H
