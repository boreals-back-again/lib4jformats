#include <iostream>
#include <fstream>
#include <filesystem>

#include "Localization/LOCFile.h"

void locNew() {
	std::filesystem::path locPath = "languages.loc";
	
    std::ifstream stream(locPath, std::ios::in | std::ios::binary);
    if (!stream) {
        std::cerr << "Failed to open input file.\n";
        return;
    }

    l4jf::loc::LOCFile loc(stream);
    std::cout << loc.ToJson()->dump(4) << std::endl;
    l4jf::loc::LOCFile locFromJson(*loc.ToJson());

    std::filesystem::path locCopyPath = "languages_copy.loc";
    std::ofstream out(locCopyPath, std::ios::out | std::ofstream::trunc | std::ios::binary);
    if (!out) {
        std::cerr << "Failed to open output file.\n";
        return;
    }

    locFromJson.Write(out);
}

int main() {
    locNew();
	
    return 0;
}
