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
			useUniqueIds = (reader.ReadByte() > static_cast<std::byte>(0));
			uint32_t keyCount =  reader.Read<uint32_t>();
			
			keys = std::make_shared<Keys>(keyCount);	
			
			for(auto& key : *keys) {
				key = useUniqueIds ? 
				io::UIntToHexString(reader.Read<uint32_t>()) 
				: reader.Read4JString();
			}			
		}		
		
		// Languages Table
		for(uint32_t i = 0; i < languageCount; i++) {
			std::string code = reader.Read4JString();	
			uint32_t id = reader.Read<uint32_t>();
		
			langIds[code] = id;
		}
		
		// Strings table
		for(uint32_t i = 0; i < languageCount; i++) {
			Language lang(reader, keys);
			
			languages.emplace(lang.GetCode(), lang);
		}
	}
	
	void LOCFile::Write(std::ostream& output) const {
		io::BinaryWriter writer(output, Endianness::BigEndian);
		
		writer.Write<uint32_t>(version);
		writer.Write<uint32_t>(languages.size());
		
		// Write Key Table
		if(version == 0x2) {
			writer.Write<uint8_t>(useUniqueIds);
			writer.Write<uint32_t>(keys->size());
			
			for(const auto& key : *keys) {
				useUniqueIds ? 
				writer.Write<uint32_t>(io::HexStringToUInt(key))
				: writer.Write4JString(key);
			}
		}
		
		// Write Lang Ids
		for(const auto& langId : langIds) {
			writer.Write4JString(langId.first);
			writer.Write<uint32_t>(langId.second);
		} 
		
		// Write Language Tables
		for(const auto& language : languages) {
			language.second.Write(writer);
		}
	}
	
}
