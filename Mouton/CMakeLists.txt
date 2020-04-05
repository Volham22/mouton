add_subdirectory(src)

add_library(Mouton ${MTN_SRC})
target_include_directories(Mouton PRIVATE src/ includes/)
