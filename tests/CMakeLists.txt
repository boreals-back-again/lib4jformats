add_executable(tests src/loc.cpp)
target_link_libraries(tests PRIVATE lib4jformats)
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Download the test files: seperate repo to not bloat this one
include(ExternalProject)
ExternalProject_Add(
    l4jf-tests-files
    GIT_REPOSITORY https://github.com/boreals-back-again/l4jf-tests-files.git
    GIT_TAG main
    PREFIX ${CMAKE_BINARY_DIR}/_deps/l4jf-tests-files
    SOURCE_DIR ${CMAKE_BINARY_DIR}/tests/files
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)

# Catch2
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.8.1
)
FetchContent_MakeAvailable(Catch2)

target_compile_definitions(tests PRIVATE USE_JSON=1)
target_link_libraries(tests PRIVATE nlohmann_json::nlohmann_json)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

include(Catch)
catch_discover_tests(tests)

