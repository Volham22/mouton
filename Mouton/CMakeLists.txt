add_subdirectory(src)
add_subdirectory(vendor/spdlog)

add_library(Mouton ${MTN_SRC})
target_precompile_headers(Mouton PRIVATE src/MoutonPch.h)
target_include_directories(Mouton PRIVATE src/ includes/ vendor/spdlog/include/)
