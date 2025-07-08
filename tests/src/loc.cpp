/* 
Tests for the LOCFile class.
Copyright 2025 Boreal | Licensed under BSD-3
*/

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "Localization/LOCFile.h"
#include <fstream>
#include <sstream>

TEST_CASE("Parse and write LOC") {
	std::ifstream input("files/languages.loc", std::ios::in | std::ios::binary);
	
	std::stringstream original;
	original << input.rdbuf();
	input.clear();
	input.seekg(0, std::ios::beg);
	
	l4jf::loc::LOCFile loc(input);
	std::ostringstream locStream;
	loc.Write(locStream);
	
	CHECK(locStream.str() == original.str());
}

#ifdef USE_JSON
TEST_CASE("Convert between LOC and JSON") {
	std::ifstream input("files/languages.loc", std::ios::in | std::ios::binary);
	
	l4jf::loc::LOCFile loc(input);
	
	l4jf::loc::LOCFile locFromJson(*loc.ToJson());
	
	std::ostringstream locStream;
	loc.Write(locStream);
	
	std::ostringstream locFromJsonStream;
	locFromJson.Write(locFromJsonStream);
	
	CHECK(locStream.str() == locFromJsonStream.str());
}
#endif //USE_JSON

TEST_CASE("Getting and setting LOC entries") {
	std::ifstream input("files/languages.loc", std::ios::in | std::ios::binary);
	
	l4jf::loc::LOCFile loc(input);
	
	auto cookedChickenKey = loc.GetString("351cc791");
	REQUIRE(cookedChickenKey != std::nullopt);
	
	CHECK(cookedChickenKey.value()["en-EN"] == "Cooked Chicken");
	
	loc.SetString("351cc791", "LOC Test...");
	
	auto testKey = loc.GetString("351cc791");
	REQUIRE(testKey != std::nullopt);
	
	CHECK(testKey.value()["ja-JP"] == "LOC Test...");
	
	loc.SetString("95744b8a", "GB only", "EN-gb");
	CHECK(loc.GetString("95744b8a").value()["es-MX"] != "GB only");
}

TEST_CASE("Getting and setting LOC languages") {
	std::ifstream input("files/languages.loc", std::ios::in | std::ios::binary);
	
	l4jf::loc::LOCFile loc(input);
	
	CHECK(loc.HasLanguage("cs-CZ") == true);
	loc.RemoveLanguage("cs-CZ");
	CHECK(loc.HasLanguage("cs-CZ") == false);
	
	loc.AddLanguage({"te-ST", 0x100, 0x0, 0x0});
	
	CHECK(loc.HasLanguage("te-ST"));
}

TEST_CASE("Getting all LOC strings") {
	std::ifstream input("files/languages.loc", std::ios::in | std::ios::binary);
	
	l4jf::loc::LOCFile loc(input);
	
	CHECK(loc.GetStrings()["351cc791"].size() == 25);
}
