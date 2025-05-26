/* 
Declares the LOCFile class, which implements the LOC file type.
Documentation for this file type is available at:
https://team-lodestone.github.io/Documentation/LCE/File%20Types/LOC.html
Copyright 2025 Boreal | Licensed under LICENSE_TBD
*/

#ifndef LOCFILE_H
#define LOCFILE_H

#include "../IO/BinaryIO.h"
#include "Language.h"

#include <map>
#include <unordered_map>
#include <vector>
#include <memory>

#ifdef USE_JSON
#include <nlohmann/json.hpp>
#endif // USE_JSON

namespace l4jf::loc {

	// Either a vector of strings or uint32, for either useUniqueIds;
	using LangIds = std::map<std::string, uint32_t>; // id, code
	using Languages = std::map<std::string, Language>; // code, Language

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
		std::shared_ptr<Keys> keys;
		LangIds langIds;
		Languages languages;
	};

}
#endif //LOCFILE_H

