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
        CPLibrary/Shader.cpp
        CPLibrary/Shader.h
        CPLibrary/Triangle.cpp
        CPLibrary/Triangle.h
        CPLibrary/Globals.h
        CPLibrary/Globals.cpp
        CPLibrary/Rectangle.cpp
        CPLibrary/Rectangle.h
        CPLibrary/Circle.cpp
        CPLibrary/Circle.h)

# GLM
target_include_directories(OpenGLGame PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/external/glm/glm)

target_link_libraries(OpenGLGame PRIVATE glfw glad)

if (WIN32)
    target_link_libraries(OpenGLGame PRIVATE opengl32)
endif ()