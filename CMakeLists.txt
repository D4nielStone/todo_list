cmake_minimum_required(VERSION 3.28)
# set the name of the project
project(TodoListBubble)
# set the out directory
set(OUT_DIR ${CMAKE_SOURCE_DIR}/out)

# platform-specific include directories
if(WIN32)
    message(STATUS "Configuring for Windows (WIN32)")
    include_directories(
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/libs/include/GLFW
        ${CMAKE_SOURCE_DIR}/libs/include/glad
        ${CMAKE_SOURCE_DIR}/libs/include/
    )
else()
    # default includes for Unix-like systems
    include_directories(
        libs/include
        include
        )
endif()


# set the source of the project
add_executable(TodoListBubble
    libs/include/glad/glad.c
    source/tlb.cpp
    source/main.cpp
    )
    
target_include_directories(TodoListBubble PUBLIC
    ${GLFW_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIR}
)

target_link_libraries(TodoListBubble PRIVATE
    glfw3
    opengl32
)