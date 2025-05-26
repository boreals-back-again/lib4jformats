# Building

lib4jformats is built like any other CMake library, and can be added as a submodule with `add_subrectory(lib4jformats)` and `target_link_libraries({app} PRIVATE lib4jformats)` in CMakeLists.txt.

## JSON

Optionally, you can enable functions that use [json](https://github.com/nlohmann/json), such as converting the file to and from a JSON object, by enabling the `USE_JSON` directive with `option(USE_JSON ON)`.