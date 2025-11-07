cmake_minimum_required(VERSION 3.28)
project(TodoListBubble)

# glad library
add_library(glad STATIC
    ${CMAKE_SOURCE_DIR}/libs/include/glad/glad.c
)

add_subdirectory(bgui)
add_subdirectory(tlb)