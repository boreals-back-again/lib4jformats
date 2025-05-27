/* 
Tests for the ARCFile class.
Copyright 2025 Boreal | Licensed under LICENSE_TBD
*/

#include <doctest/doctest.h>
#include "Archive/ARCFile.h"
#include <fstream>
#include <sstream>

TEST_CASE("Parse and write ARC") {
    std::ifstream input("files/MediaWiiU.arc", std::ios::in | std::ios::binary);
    REQUIRE(input.is_open());

    std::stringstream original;
    original << input.rdbuf();
    input.clear();
    input.seekg(0, std::ios::beg);

    l4jf::arc::ARCFile arc(input);
    std::ostringstream arcStream;
    arc.Write(arcStream);

    CHECK(arcStream.str() == original.str());
}
