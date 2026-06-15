cmake_minimum_required(VERSION 4.0)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES src/*.c*)
add_library(Nova STATIC ${SOURCES} thirdparty/stb/stb_image.c "src/Transform.cpp")
target_include_directories(Nova PUBLIC include/ thirdparty/stb/)
target_link_libraries(Nova PUBLIC d3d11 d3dcompiler)

if (CMAKE_BUILD_TYPE STREQUAL "Debug") 
    add_compile_definitions(DEBUG) 
else() 
    add_compile_definitions(NDEBUG) 
endif()