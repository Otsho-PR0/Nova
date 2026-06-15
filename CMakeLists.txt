cmake_minimum_required(VERSION 4.0)

set(CMAKE_CXX_STANDARD 20)

project(Nova)

add_subdirectory(Nova/)

file(GLOB_RECURSE SOURCES Editor/src/*.c*)
file(GLOB_RECURSE IMGUI_SOURCES thirdparty/imgui/*.c*)
file(GLOB_RECURSE RESOURCES Editor/res/resource.rc)
add_executable(Editor WIN32 ${SOURCES} ${IMGUI_SOURCES} ${RESOURCES})
target_include_directories(Editor PRIVATE Editor/include/ Editor/res/ thirdparty/imgui/)
target_link_libraries(Editor PRIVATE Nova)

add_dependencies(Editor Nova)

if (CMAKE_BUILD_TYPE STREQUAL "Debug") 
    add_compile_definitions(DEBUG) 
else() 
    add_compile_definitions(NDEBUG) 
endif()

#add_custom_command(TARGET Editor POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        $<TARGET_RUNTIME_DLLS:Editor>
#        $<TARGET_FILE_DIR:Editor>
#    COMMAND_EXPAND_LISTS
#)