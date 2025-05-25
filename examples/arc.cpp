#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <chrono>

#include "Archive/ARCFile.h"

int main() {
    using namespace std::chrono;

    std::filesystem::path arcPath = "MediaWiiU.arc";
	
    std::ifstream stream(arcPath, std::ios::in | std::ios::binary);
    if (!stream) {
        std::cerr << "Failed to open input file.\n";
        return 1;
    }

    l4jf::arc::ARCFile archive(stream);

    // Measure copy time
    std::filesystem::path arcCopyPath = "MediaWiiU_copy.arc";
    std::ofstream out(arcCopyPath, std::ios::out | std::ofstream::trunc | std::ios::binary);
    if (!out) {
        std::cerr << "Failed to open output file.\n";
        return 1;
    }

    archive.Write(out);
    
    return 0;
}
