cmake_minimum_required(VERSION 3.31)
project(OpenGLGame)

set(CMAKE_CXX_STANDARD 20)

# OpenGL
find_package(OpenGL REQUIRED)

# GLFW
include(FetchContent)
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
)
FetchContent_MakeAvailable(glfw)

# FT Library
include(FetchContent)
FetchContent_Declare(
        freetype
        GIT_REPOSITORY https://github.com/freetype/freetype.git
        GIT_TAG VER-2-14-1 # or write highest version
)
FetchContent_MakeAvailable(freetype)

# GLAD
add_subdirectory(external/glad)

add_executable(OpenGLGame main.cpp
        CPLibrary/Shader.cpp
        CPLibrary/Shader.h
        CPLibrary/2D_Shapes/Triangle.cpp
        CPLibrary/2D_Shapes/Triangle.h
        CPLibrary/CPL.h
        CPLibrary/CPL.cpp
        CPLibrary/2D_Shapes/Rectangle.cpp
        CPLibrary/2D_Shapes/Rectangle.h
        CPLibrary/2D_Shapes/Circle.cpp
        CPLibrary/2D_Shapes/Circle.h
        CPLibrary/Colors.h
        CPLibrary/KeyInputs.h
        CPLibrary/Text.cpp
        CPLibrary/Text.h
        CPLibrary/2D_Shapes/Line.cpp
        CPLibrary/2D_Shapes/Line.h)

# GLM
target_include_directories(OpenGLGame PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/external/glm/glm)

target_link_libraries(OpenGLGame PRIVATE glfw glad freetype)

if (WIN32)
    target_link_libraries(OpenGLGame PRIVATE opengl32)
endif ()