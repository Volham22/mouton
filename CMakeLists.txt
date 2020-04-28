cmake_minimum_required(VERSION 3.16)

project(Mouton)

# Set some CXX flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set a default build type if none was specified
set(default_build_type "Release")
if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
    set(default_build_type "Debug")
endif()

add_subdirectory(Mouton)
add_subdirectory(Sandbox)
