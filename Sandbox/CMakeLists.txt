set(MTN_SB_SRC)

add_subdirectory(src)

add_executable(Sandbox ${MTN_SB_SRC})
target_link_libraries(Sandbox Mouton)
target_precompile_headers(Sandbox REUSE_FROM Mouton)
target_include_directories(Sandbox PRIVATE ../Mouton/src/ ../Mouton/vendor/spdlog/include)
