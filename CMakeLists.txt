cmake_minimum_required(VERSION 3.16)
project(bgui VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# =============================================
# OPTIONS
# =============================================

option(BGUI_BUILD_SHARED   "Build as shared library"  OFF)
option(BGUI_USE_OPENGL     "Use OpenGL renderer"       ON)
option(BGUI_USE_GLFW       "Use GLFW for window/input" ON)
option(BGUI_USE_FREETYPE   "Use FreeType for fonts"    ON)

# =============================================
# Library type
# =============================================

if(BGUI_BUILD_SHARED)
    set(LIB_TYPE SHARED)
else()
    set(LIB_TYPE STATIC)
endif()

# =============================================
# Final library
# =============================================

add_library(bgui ${LIB_TYPE})

target_include_directories(bgui
    PUBLIC
        ${PROJECT_SOURCE_DIR}/core/include
)

# =============================================
# SOURCE FILES
# =============================================

file(GLOB_RECURSE BGUI_CORE
    core/source/*.cpp
)

target_sources(bgui PRIVATE ${BGUI_CORE})

# =============================================
# BACKEND
# =============================================

if(BGUI_USE_OPENGL)
    message(STATUS "BGUI: OpenGL backend enabled")

    target_compile_definitions(bgui PUBLIC BGUI_USE_OPENGL)

    target_sources(bgui PRIVATE
        backend/source/opengl3/backend.cpp
    )

else()
    message(STATUS "BGUI: NULL backend enabled")

    target_compile_definitions(bgui PUBLIC BGUI_USE_NULL)

    target_sources(bgui PRIVATE
        backend/source/backend_null.cpp
    )
endif()

# =============================================
# GLFW
# =============================================

if(BGUI_USE_GLFW)
    message(STATUS "BGUI: GLFW enabled")

    target_compile_definitions(bgui PUBLIC BGUI_USE_GLFW)

    # Prefer modern glfw config
    find_package(glfw3 CONFIG REQUIRED)
    target_link_libraries(bgui PUBLIC glfw3)
endif()

# =============================================
# GLEW
# =============================================

if(BGUI_USE_OPENGL)
    message(STATUS "BGUI: GLEW required for OpenGL backend")

    find_package(GLEW REQUIRED)

    target_link_libraries(bgui PUBLIC GLEW::GLEW)
endif()

# =============================================
# FREETYPE
# =============================================

if(BGUI_USE_FREETYPE)
    message(STATUS "BGUI: FreeType enabled")

    target_compile_definitions(bgui PUBLIC BGUI_USE_FREETYPE)

    find_package(Freetype REQUIRED)

    target_link_libraries(bgui PUBLIC Freetype::Freetype)
endif()