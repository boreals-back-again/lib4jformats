/* 
Defines optional methods for dumping the LOC file as a JSON with nlohmann::json
Copyright 2025 Boreal | Licensed under LICENSE_TBD
*/

#ifdef USE_JSON
#ifndef LOCJSON_H

#include "LOCFile.h"
#include "../IO/Conversion.h"
#include <nlohmann/json.hpp>

namespace l4jf::loc {
	
	std::unique_ptr<nlohmann::json> LOCFile::ToJson() const {
		nlohmann::json j;
		
		j["version"] = version;
			
		if(useUniqueIds) {
			j["useUniqueIds"] = useUniqueIds;
		}
		
		j["keys"] = keys;
		
		for(const auto& language : languages) {
			j["languages"][language.first]["shouldReadByte"] = language.second.shouldReadByte;
			if(language.second.shouldReadByte)
			j["languages"][language.first]["byte"] = language.second.byte;
			j["languages"][language.first]["bytesLength"] = language.second.bytesLength;
			j["languages"][language.first]["strings"] = language.second.strings;
		}
		
		return std::make_unique<nlohmann::json>(j);
	}
	
	LOCFile::LOCFile(const nlohmann::json& fromJson) {
		version = fromJson["version"];
		
		if(fromJson["useUniqueIds"]) {
			useUniqueIds = fromJson["useUniqueIds"];
		}
		
		keys = fromJson["keys"];
		
		for (const auto& language : fromJson["languages"].items()) {
			Language lang;
			
			lang.shouldReadByte = language.value()["shouldReadByte"];
			lang.byte = language.value()["byte"];
			lang.bytesLength = language.value()["bytesLength"];
			lang.strings = language.value()["strings"];
			
			languages[language.key()] = lang;
		}

	}
}

#endif //LOCJSON_H
#endif //USE_JSON
