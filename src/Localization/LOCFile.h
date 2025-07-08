/* 
Declares the LOCFile class, which implements the LOC file type.
Documentation for this file type is available at:
https://team-lodestone.github.io/Documentation/LCE/File%20Types/LOC.html
Copyright 2025 Boreal | Licensed under BSD-3
*/

#ifndef LOCFILE_H
#define LOCFILE_H

#include "../IO/BinaryIO.h"

#include <optional>
#include <unordered_map>
#include <map>
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
		std::string code;
		uint32_t bytesLength;
		
		uint32_t shouldReadByte;
		uint8_t byte{};
		 // key, value
	};

	class LOCFile {
	public:
		LOCFile(std::istream& input);
		
		#ifdef USE_JSON
		std::unique_ptr<nlohmann::json> ToJson() const;
		LOCFile(const nlohmann::json& fromJson);
		#endif
		
		void Write(std::ostream& output) const;
		
		bool HasLanguage(const std::string& code);
		void RemoveLanguage(const std::string& code);
		void AddLanguage(const Language& lang);
		
		std::optional<std::map<std::string, std::string>> GetString(const std::string& key);
		void SetString(const std::string& key, const std::string& value);
		void SetString(const std::string& key, const std::string& value, const std::string& language);
		
		std::unordered_map<std::string, std::map<std::string, std::string>> GetStrings();
	private:
		uint32_t version;		
		bool useUniqueIds = false;
		
		// Shared with every language.
		std::vector<std::string> keys;
		std::vector<Language> languages;
		std::unordered_map<std::string, std::map<std::string, std::string>> strings;
	};

}
#endif //LOCFILE_H

