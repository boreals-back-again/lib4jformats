/* 
Defines optional methods for dumping the LOC file as a JSON with nlohmann::json
Copyright 2025 Boreal | Licensed under LICENSE_TBD
*/

#ifdef USE_JSON
#ifndef LOCJSON_H

#include "LOCFile.h"
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
			j["languages"][language.first] = language.second.strings;
		}
		
		return std::make_unique<nlohmann::json>(j);
	}
}

#endif //LOCJSON_H
#endif //USE_JSON
