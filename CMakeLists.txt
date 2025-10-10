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

# GLAD
add_subdirectory(external/glad)

add_executable(OpenGLGame main.cpp
        CPLib/Shader.cpp
        CPLib/Shader.h
        CPLib/Triangle.cpp
        CPLib/Triangle.h
        CPLib/CPLib.h)

target_link_libraries(OpenGLGame PRIVATE glfw glad)

if (WIN32)
    target_link_libraries(OpenGLGame PRIVATE opengl32)
endif ()