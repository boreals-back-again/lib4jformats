add_executable(tests src/loc.cpp src/arc.cpp)
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
  doctest
  GIT_REPOSITORY https://github.com/doctest/doctest.git
  GIT_TAG v2.4.12
)
FetchContent_MakeAvailable(doctest)

target_compile_definitions(tests PRIVATE USE_JSON=1)
target_link_libraries(tests PRIVATE nlohmann_json::nlohmann_json)

target_link_libraries(tests PRIVATE doctest::doctest)

include(CTest)
enable_testing()

target_include_directories(tests PRIVATE ${doctest_SOURCE_DIR})
include("${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake")

doctest_discover_tests(tests)
