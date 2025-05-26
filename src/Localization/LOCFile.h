/* 
Declares the LOCFile class, which implements the LOC file type.
Documentation for this file type is available at:
https://team-lodestone.github.io/Documentation/LCE/File%20Types/LOC.html
Copyright 2025 Boreal | Licensed under LICENSE_TBD
*/

#ifndef LOCFILE_H
#define LOCFILE_H

#include "../IO/BinaryIO.h"

#include <unordered_map>
#include <vector>
#include <memory>

#ifdef USE_JSON
#include <nlohmann/json.hpp>
#endif // USE_JSON

namespace l4jf::loc {
	
	// This struct is Plain Old Data. we want to recreate the file exactly, so those five
	// bytes must be preserved.
	struct Language {
		// in the Languages table, this is stored after the name of the language.
		uint32_t bytesLength;
		
		uint32_t shouldReadByte;
		uint8_t byte{};
		std::unordered_map<std::string, std::string> strings; // key, value
	};
	
	using Languages = std::unordered_map<std::string, Language>; // code, Language

	class LOCFile {
	public:
		LOCFile(std::istream& input);
		
		#ifdef USE_JSON
		std::unique_ptr<nlohmann::json> ToJson() const;
		#endif
		
		void Write(std::ostream& output) const;
		uint32_t GetKeyCount() const;
		
	private:
		uint32_t version;		
		bool useUniqueIds = false;
		
		// Shared with every language.
		std::vector<std::string> keys;
		Languages languages;
	};

}
#endif //LOCFILE_H

