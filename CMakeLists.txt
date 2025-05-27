cmake_minimum_required(VERSION 3.26)
project(lib4jformats)

set(CMAKE_CXX_STANDARD 17)

set(FILES
	src/IO/BinaryWriter.cpp
	src/IO/BinaryReader.cpp
	src/IO/BinaryIO.t.h
	src/IO/BinaryIO.h
	src/IO/Conversion.h
	src/IO/Types.h
	src/Localization/LOCJson.cpp
	src/Localization/LOCFile.cpp
	src/Localization/LOCFile.h
	src/Archive/ARCFile.cpp
	src/Archive/ARCFile.h
	src/File/InnerFile.cpp
	src/File/InnerFile.h
	src/File/File.cpp
	src/File/File.h
    src/lib4jformats.h
)

set(ENVIRONMENT_TYPE "Native")
set(LIB_TYPE SHARED)
add_library(lib4jformats ${LIB_TYPE} ${FILES})

option(USE_JSON "JSON interop" ON)

if(USE_JSON)
	include(FetchContent)
	FetchContent_Declare(
		nlohmann_json
		GIT_REPOSITORY https://github.com/nlohmann/json.git
		GIT_TAG v3.12.0
	)

	FetchContent_MakeAvailable(nlohmann_json)

	target_link_libraries(lib4jformats PRIVATE nlohmann_json::nlohmann_json)
	target_compile_definitions(lib4jformats PRIVATE USE_JSON=1)
endif()


target_compile_definitions(lib4jformats PRIVATE
    COMPILER_NAME="${CMAKE_CXX_COMPILER_ID}"
    PLATFORM_NAME="${CMAKE_SYSTEM_NAME}"
    PLATFORM_ARCH="${CMAKE_SYSTEM_PROCESSOR}"
    LIBLCE_EXPORTS
)

if (CMAKE_CXX_BYTE_ORDER EQUAL BIG_ENDIAN)
    target_compile_definitions(lib4jformats PRIVATE BR_BIG_ENDIAN)
endif()

add_subdirectory(tests)
