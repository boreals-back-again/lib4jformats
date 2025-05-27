/* 
Tests for the LOCFile class.
Copyright 2025 Boreal | Licensed under LICENSE_TBD
*/

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "Localization/LOCFile.h"
#include <fstream>
#include <sstream>

TEST_CASE("Parse and write LOC") {
	std::ifstream input("files/languages.loc", std::ios::in | std::ios::binary);
	REQUIRE(input.is_open());
	
	std::stringstream original;
	original << input.rdbuf();
	input.clear();
	input.seekg(0, std::ios::beg);
	
	l4jf::loc::LOCFile loc(input);
	std::ostringstream locStream;
	loc.Write(locStream);
	
	CHECK(locStream.str() == original.str());
}

TEST_CASE("Convert between LOC and JSON") {
	std::ifstream input("files/languages.loc", std::ios::in | std::ios::binary);
	REQUIRE(input.is_open());
	
	l4jf::loc::LOCFile loc(input);
	
	l4jf::loc::LOCFile locFromJson(*loc.ToJson());
	
	std::ostringstream locStream;
	loc.Write(locStream);
	
	std::ostringstream locFromJsonStream;
	locFromJson.Write(locFromJsonStream);
	
	CHECK(locStream.str() == locFromJsonStream.str());
}
