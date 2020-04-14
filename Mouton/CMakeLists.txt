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

add_library(Mouton ${MTN_SRC})
target_precompile_headers(Mouton PUBLIC src/MoutonPch.h)

target_link_libraries(Mouton glfw Glad)
target_include_directories(Mouton PRIVATE src/ includes/ vendor/spdlog/include/ vendor/glfw/include vendor/Glad/include vendor/imgui)
