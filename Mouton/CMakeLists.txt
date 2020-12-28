add_subdirectory(src)

# SPDLOG
add_subdirectory(vendor/spdlog)

# GLFW
add_subdirectory(vendor/GLFW)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Glad
add_subdirectory(vendor/Glad)

# imgui library
add_subdirectory(vendor/imgui)

# Assimp
add_subdirectory(vendor/assimp)

# Pybind11
add_subdirectory(vendor/pybind11)

add_library(Mouton ${MTN_SRC})
target_precompile_headers(Mouton PUBLIC src/MoutonPch.h)

if(MSVC)
    target_compile_options(Mouton PRIVATE /W4)
else()
    target_compile_options(Mouton PRIVATE -Wall -Wextra)
endif()


target_link_libraries(Mouton glfw Glad imgui assimp pybind11::embed)
target_include_directories(Mouton PRIVATE
    src/
    includes/
    vendor/stb_image/
    vendor/spdlog/include/
    vendor/glfw/include
    vendor/Glad/include
    vendor/imgui
    vendor/glm/
    vendor/assimp/include
    vendor/pybind11/include
    vendor/rapidjson/include)
