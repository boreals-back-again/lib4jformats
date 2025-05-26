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
			
			keys.resize(keyCount);	
			
			for(auto& key : keys) {
				key = useUniqueIds ? 
				io::UIntToHexString(reader.Read<uint32_t>()) 
				: reader.Read4JString();
			}		
		}		
		
		// Languages Table
		for(uint32_t i = 0; i < languageCount; i++) {
			std::string code = reader.Read4JString();	
			uint32_t length = reader.Read<uint32_t>();
			
			// create a new blank language to have data filled later
			languages[code] = Language();
			
			languages[code].bytesLength = length;
		}
		
		// Strings table
		for(auto& language : languages) {
			Language& langData = language.second;
			langData.shouldReadByte = reader.Read<uint32_t>();
			
			if(langData.shouldReadByte) {
				langData.byte = reader.ReadByte();
			}
			
			reader.Read4JString(); // language code has already been set
			uint32_t stringsCount = reader.Read<uint32_t>();
			
			for(int i = 0; i < stringsCount; i++) {
				langData.strings[ keys[i] ] = reader.Read4JString();
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
				writer.Write<uint32_t>(io::HexStringToUInt(key))
				: writer.Write4JString(key);
			}
		}
		
		for(const auto& language : languages) {		
			writer.Write4JString(language.first);
			writer.Write<uint32_t>(language.second.bytesLength);
		}
		
		for(const auto& language : languages) {
			const Language& langData = language.second; 
			
			writer.Write<uint32_t>(langData.shouldReadByte);
			if(langData.shouldReadByte) writer.WriteByte(langData.byte);
			
			writer.Write4JString(language.first);
			
			writer.Write<uint32_t>(langData.strings.size());
			
			for(uint32_t i = 0; i < langData.strings.size(); i++) {
				writer.Write4JString( langData.strings.at(keys[i]) );
			}
		}
	}
	
}
