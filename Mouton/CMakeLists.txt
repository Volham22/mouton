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
option(ENABLE_BOOST_WORKAROUND ON)
option(ZLIB_LIBRARIES zlibstatic)
option(BUILD_STATIC_LIB ON)
option(BUILD_ASSIMP_TOOLS  ON)
option(ASSIMP_BUILD_STATIC_LIB ON)
option(ASSIMP_NO_EXPORT ON)
option(ASSIMP_BUILD_TESTS OFF)
option(ASSIMP_WERROR OFF)

add_subdirectory(vendor/assimp)

add_library(Mouton ${MTN_SRC})
target_precompile_headers(Mouton PUBLIC src/MoutonPch.h)

target_link_libraries(Mouton glfw Glad imgui assimp)
target_include_directories(Mouton PRIVATE
    src/
    includes/
    vendor/stb_image/
    vendor/spdlog/include/
    vendor/glfw/include
    vendor/Glad/include
    vendor/imgui
    vendor/glm/
    vendor/assimp/include)
