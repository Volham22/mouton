cmake_minimum_required(VERSION 3.9)

project(Mouton)

# Set a default build type if none was specified
set(default_build_type "Release")
if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
    set(default_build_type "Debug")
endif()

add_subdirectory(Mouton)
add_subdirectory(Sandbox)
