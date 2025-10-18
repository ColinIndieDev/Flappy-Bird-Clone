cmake_minimum_required(VERSION 3.31)
project(OpenGLGame)

set(CMAKE_CXX_STANDARD 20)

# Detect if we're using Emscripten
if("${CMAKE_CXX_COMPILER}" MATCHES "em\\+\\+")
    set(PLATFORM "Web")
endif()

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

# STB Image
include(FetchContent)
FetchContent_Declare(
        stb
        GIT_REPOSITORY https://github.com/nothings/stb.git
        GIT_TAG master
)
FetchContent_MakeAvailable(stb)

# Miniaudio
set(MINIAUDIO_PATH "${CMAKE_BINARY_DIR}/_deps/miniaudio/miniaudio.h")
file(DOWNLOAD
        https://raw.githubusercontent.com/mackron/miniaudio/master/miniaudio.h
        ${MINIAUDIO_PATH}
        SHOW_PROGRESS
)
add_library(miniaudio INTERFACE)
target_include_directories(miniaudio INTERFACE "${CMAKE_BINARY_DIR}/_deps/miniaudio")

# GLAD
add_subdirectory(external/glad)

add_executable(OpenGLGame main.cpp
        CPLibrary/Shader.cpp
        CPLibrary/Shader.h
        CPLibrary/shapes2D/Triangle.cpp
        CPLibrary/shapes2D/Triangle.h
        CPLibrary/CPL.h
        CPLibrary/CPL.cpp
        CPLibrary/shapes2D/Rectangle.cpp
        CPLibrary/shapes2D/Rectangle.h
        CPLibrary/shapes2D/Circle.cpp
        CPLibrary/shapes2D/Circle.h
        CPLibrary/Colors.h
        CPLibrary/KeyInputs.h
        CPLibrary/Text.cpp
        CPLibrary/Text.h
        CPLibrary/shapes2D/Line.cpp
        CPLibrary/shapes2D/Line.h
        CPLibrary/shapes2D/Texture2D.cpp
        CPLibrary/shapes2D/Texture2D.h
        CPLibrary/timers/Timer.h
        CPLibrary/timers/TimerManager.cpp
        CPLibrary/timers/TimerManager.h
        CPLibrary/CPLibrary.h
        CPLibrary/Logging.h
        CPLibrary/Audio.cpp
        CPLibrary/Audio.h
)

# GLM
target_include_directories(OpenGLGame PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/external/glm/glm)

# STB Image
target_include_directories(OpenGLGame PRIVATE ${stb_SOURCE_DIR})

target_link_libraries(OpenGLGame PRIVATE glfw glad freetype miniaudio)

if (WIN32)
    target_link_libraries(OpenGLGame PRIVATE opengl32)
endif ()

# Web-specific options
if(PLATFORM STREQUAL "Web")
    set_target_properties(OpenGLGame PROPERTIES SUFFIX ".html")

    target_link_options(OpenGLGame PRIVATE
            "-sUSE_GLFW=3"
            "-sASYNCIFY"
            "-sFULL_ES2=1"
            "-sFORCE_FILESYSTEM=1"
    )
endif()