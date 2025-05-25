add_executable(arc arc.cpp)
target_link_libraries(arc PRIVATE lib4jformats)
target_include_directories(arc PRIVATE ${CMAKE_SOURCE_DIR}/src)

add_executable(loc loc.cpp)
target_link_libraries(loc PRIVATE lib4jformats)
target_compile_definitions(loc PRIVATE USE_JSON=1)
target_include_directories(loc PRIVATE ${CMAKE_SOURCE_DIR}/src)
