set(MTN_SB_SRC)

add_subdirectory(src)

add_executable(MoutonEditor ${MTN_SB_SRC})
target_link_libraries(MoutonEditor Mouton)
target_precompile_headers(MoutonEditor REUSE_FROM Mouton)
target_include_directories(MoutonEditor PRIVATE ../Mouton/src/ ../Mouton/vendor/spdlog/include ../Mouton/vendor/imgui)
