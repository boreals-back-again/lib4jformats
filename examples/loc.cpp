#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <chrono>

#include "Localization/LOCFile.h"

void loc1() {
	std::filesystem::path locPath = "languages.loc";
	
    std::ifstream stream(locPath, std::ios::in | std::ios::binary);
    if (!stream) {
        std::cerr << "Failed to open input file.\n";
        return;
    }

    l4jf::loc::LOCFile loc(stream);
     
    std::filesystem::path locCopyPath = "languages_copy.loc";
    std::ofstream out(locCopyPath, std::ios::out | std::ofstream::trunc | std::ios::binary);
    if (!out) {
        std::cerr << "Failed to open output file.\n";
        return;
    }

    loc.Write(out);
}

void loc2() {
	std::filesystem::path locPath = "languagesOld.loc";
	
    std::ifstream stream(locPath, std::ios::in | std::ios::binary);
    if (!stream) {
        std::cerr << "Failed to open input file.\n";
        return;
    }

    l4jf::loc::LOCFile loc(stream);
    
    std::cout << loc.ToJson()->dump(4) << std::endl;
     
    std::filesystem::path locCopyPath = "languages_copy.loc";
    std::ofstream out(locCopyPath, std::ios::out | std::ofstream::trunc | std::ios::binary);
    if (!out) {
        std::cerr << "Failed to open output file.\n";
        return;
    }

    loc.Write(out);
}


int main() {    
    loc2();

    return 0;
}
