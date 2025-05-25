/* 
Defines the Language class (and the keys inside), which implements the language data inside of LOCs.
Copyright 2025 Boreal | Licensed under LICENSE_TBD
*/

#include "Language.h"
#include <iostream>

namespace l4jf::loc {
	
	Language::Language(io::BinaryReader& reader, std::shared_ptr<Keys> keys) : keys(keys) {
		shouldReadByte = reader.Read<uint32_t>();	
		
		if(shouldReadByte) { 
			byte = reader.ReadByte();
		}
		
		code = reader.Read4JString();
		uint32_t stringsCount = reader.Read<uint32_t>();
		
		for(uint32_t i = 0; i < stringsCount; i++) {
			strings[ reader.Read4JString() ] = reader.Read4JString(); // segfaults if version != 0x2
		}
	}
	
	std::optional<std::string> Language::GetStringByIndex(size_t index) const {
		auto it = strings.find(keys->at(index));
		if(it != strings.end()) return it->second;
		return std::nullopt;
	}
	
	std::optional<std::string> Language::GetStringByKey(std::string key) const {
		auto it = strings.find(key);
		if(it != strings.end()) return it->second;
		return std::nullopt;
	}
	
	std::string Language::GetCode() const {
		return code;
	}
	
	std::unique_ptr<std::vector<std::string>> Language::GetStringsOrdered() const {
		std::vector<std::string> orderedStrings;
		orderedStrings.reserve(keys->size());
		
		for (const auto& key : *keys) {
			orderedStrings.push_back(strings.at(key));
		}
		
		return std::make_unique<Keys>(orderedStrings);
	}
	
	void Language::Write(io::BinaryWriter& writer) const {
		writer.Write<uint32_t>(shouldReadByte);
		if(shouldReadByte) writer.WriteByte(byte);
		
		writer.Write4JString(code);
		writer.Write<uint32_t>(strings.size());
		
		for (const auto& key : *keys) {
			writer.Write4JString(strings.at(key));
		}
	}
}
