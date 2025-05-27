add_executable(example example.cpp)
target_link_libraries(example PRIVATE lib4jformats)
target_include_directories(example PRIVATE ${CMAKE_SOURCE_DIR}/src)

option(USE_JSON "JSON interop" ON)

if(USE_JSON)
    target_compile_definitions(example PRIVATE USE_JSON=1)
    target_link_libraries(example PRIVATE nlohmann_json::nlohmann_json)
endif()
