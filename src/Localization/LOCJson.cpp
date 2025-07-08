/* 
Defines optional methods for dumping the LOC file as a JSON with nlohmann::json
Copyright 2025 Boreal | Licensed under BSD-3
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
		
		nlohmann::json languagesJson = nlohmann::json::array();
 
		for(const auto& language : languages) {
			languagesJson.push_back({
				{"shouldReadByte", language.shouldReadByte},
				{"byte", language.byte},
				{"code", language.code},
				{"bytesLength", language.bytesLength}
			});
		}
		
		j["languages"] = languagesJson;
		
		j["strings"] = strings;
		
		return std::make_unique<nlohmann::json>(j);
	}
	
	LOCFile::LOCFile(const nlohmann::json& fromJson) {
		version = fromJson["version"];
		
		if(fromJson["useUniqueIds"]) {
			useUniqueIds = fromJson["useUniqueIds"];
		}
		
		keys = fromJson["keys"];
		strings = fromJson["strings"];
		
		for (const auto& language : fromJson["languages"].items()) {
			Language lang;
			
			lang.shouldReadByte = language.value()["shouldReadByte"];
			lang.byte = language.value()["byte"];
			lang.bytesLength = language.value()["bytesLength"];
			lang.code = language.value()["code"];
			
			languages.push_back(lang);
		}

	}
}

#endif //LOCJSON_H
#endif //USE_JSON
