set(GLAD_SRC
    src/glad.c)

add_library(Glad ${GLAD_SRC})
target_include_directories(Glad PUBLIC include/)