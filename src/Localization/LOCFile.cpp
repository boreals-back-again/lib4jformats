/* 
Defines the LOCFile class, which implements the LOC file type.
Documentation for this file type is available at:
https://team-lodestone.github.io/Documentation/LCE/File%20Types/LOC.html
Copyright 2025 Boreal | Licensed under LICENSE_TBD
*/

#include "LOCFile.h"
#include <iostream>

#include "../IO/Conversion.h"

namespace l4jf::loc {

	LOCFile::LOCFile(std::istream& input) {
		io::BinaryReader reader(input, Endianness::BigEndian);
		
		version = reader.Read<uint32_t>();
		uint32_t languageCount = reader.Read<uint32_t>();

		// Key Table
		if(version == 0x2) {
			useUniqueIds = (reader.ReadByte() > 0);
			uint32_t keyCount =  reader.Read<uint32_t>();
			
			keys.resize(keyCount);	
			
			for(auto& key : keys) {
				key = useUniqueIds ? 
				io::ToHexString<uint32_t>(reader.Read<uint32_t>()) 
				: reader.Read4JString();
			}		
		}		
		
		languages.resize(languageCount);
		
		// Languages Table
		for(uint32_t i = 0; i < languageCount; i++) {
			std::string code = reader.Read4JString();	
			uint32_t length = reader.Read<uint32_t>();
			
			Language lang;
			
			lang.code = code;
			lang.bytesLength = length;
			
			languages[i] = lang;
		}
		
		// Strings table
		for(auto& language : languages) {
			language.shouldReadByte = reader.Read<uint32_t>();
			
			if(language.shouldReadByte) {
				language.byte = reader.ReadByte();
			}
			
			std::string code = reader.Read4JString();
			uint32_t stringsCount = reader.Read<uint32_t>();
			
			for(int i = 0; i < stringsCount; i++) {
				strings[keys[i]][code] = reader.Read4JString();
			}
		}
	}
	
	void LOCFile::Write(std::ostream& output) const {
		io::BinaryWriter writer(output, Endianness::BigEndian);
		
		writer.Write<uint32_t>(version);
		writer.Write<uint32_t>(languages.size());
		
		// Write Key Table
		if(version == 0x2) {
			writer.Write<uint8_t>(useUniqueIds);
			writer.Write<uint32_t>(keys.size());
			
			for(const auto& key : keys) {
				useUniqueIds ? 
				writer.Write<uint32_t>(io::FromHexString<uint32_t>(key))
				: writer.Write4JString(key);
			}
		}
		
		for(const auto& language : languages) {		
			writer.Write4JString(language.code);
			writer.Write<uint32_t>(language.bytesLength);
		}
		
		for(const auto& language : languages) {
			writer.Write<uint32_t>(language.shouldReadByte);
			if(language.shouldReadByte) writer.WriteByte(language.byte);
			
			writer.Write4JString(language.code);
			writer.Write<uint32_t>(strings.size());
			
			for(uint32_t i = 0; i < strings.size(); i++) {
				writer.Write4JString( strings.at(keys[i]).at(language.code) );
			}
		}
	}
	
	std::optional<std::map<std::string, std::string>> LOCFile::GetString(const std::string& key) {
		auto it = strings.find(key);
		if (it != strings.end()) {
			return it->second;
		}
		
		return std::nullopt;
	}
	
	void LOCFile::SetString(const std::string& key, const std::string& value) {
		for(const auto& language : languages) {
			strings[key][language.code] = value;
		}
	}
}
