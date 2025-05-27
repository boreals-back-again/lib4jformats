#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "Localization/LOCFile.h"
#include <fstream>
#include <sstream>

TEST_CASE("LOC <--> JSON") {
	std::ifstream input("files/languages.loc", std::ios::in | std::ios::binary);
	CHECK(input.is_open());

	l4jf::loc::LOCFile loc(input);

	l4jf::loc::LOCFile locFromJson(*loc.ToJson());

	std::ostringstream locStream;
	loc.Write(locStream);

	std::ostringstream locFromJsonStream;
	locFromJson.Write(locFromJsonStream);

	CHECK(locStream.str() == locFromJsonStream.str());
}
