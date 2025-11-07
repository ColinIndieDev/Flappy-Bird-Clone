cmake_minimum_required(VERSION 3.31)
project(OpenGLGame)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -----------------------------
# Detect Web platform (Emscripten)
# -----------------------------
# if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" AND "${CMAKE_SYSTEM_NAME}" STREQUAL "Emscripten")
#    set(PLATFORM "Web")
#endif()
# -----------------------------
# GLFW Web-only Options
# -----------------------------
# WICHTIG: global, vor FetchContent!
#set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
#set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
#set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
#set(GLFW_USE_POSIX_TIME OFF CACHE BOOL "" FORCE)
#set(GLFW_BUILD_WSI_EMSCRIPTEN ON CACHE BOOL "" FORCE)
#set(GLFW_USE_EMSCRIPTEN ON CACHE BOOL "" FORCE)

# Alle Desktop-Backends deaktivieren
#set(GLFW_BUILD_X11 OFF CACHE BOOL "" FORCE)
#set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "" FORCE)
#set(GLFW_BUILD_COCOA OFF CACHE BOOL "" FORCE)
#set(GLFW_BUILD_WIN32 OFF CACHE BOOL "" FORCE)
#set(GLFW_USE_OSMESA OFF CACHE BOOL "" FORCE)
#set(GLFW_USE_HYBRID_HPG OFF CACHE BOOL "" FORCE)

# GLFW
include(FetchContent)
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG master
)
FetchContent_MakeAvailable(glfw)

# GLM
FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG master
)
FetchContent_MakeAvailable(glm)

# Freetype
FetchContent_Declare(
        freetype
        GIT_REPOSITORY https://github.com/freetype/freetype.git
        GIT_TAG VER-2-14-1
)
FetchContent_MakeAvailable(freetype)

# STB
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

add_executable(OpenGLGame src/main.cpp
        src/resources.rc
        src/StartAnimation.h
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
        CPLibrary/Path.h
)

# Include directories
target_include_directories(OpenGLGame PRIVATE ${stb_SOURCE_DIR})

# Link libraries
target_link_libraries(OpenGLGame PRIVATE glfw glad freetype miniaudio glm)

# -----------------------------
# Desktop-specific
# -----------------------------
#if (WIN32 AND NOT PLATFORM STREQUAL "Web")
#    set_target_properties(OpenGLGame PROPERTIES WIN32_EXECUTABLE TRUE)
#    target_link_libraries(OpenGLGame PRIVATE opengl32)
#endif()
# -----------------------------
# Web-specific
# -----------------------------
#if(PLATFORM STREQUAL "Web")
#    set_target_properties(OpenGLGame PROPERTIES SUFFIX ".html")

#    set(ASSETS_SRC_DIR "${CMAKE_SOURCE_DIR}/assets")
#    set(ASSETS_DST_DIR "${CMAKE_CURRENT_BINARY_DIR}/assets")
#    add_custom_command(TARGET OpenGLGame POST_BUILD
#            COMMAND ${CMAKE_COMMAND} -E copy_directory
#            ${ASSETS_SRC_DIR} ${ASSETS_DST_DIR}
#    )

#    target_link_options(OpenGLGame PRIVATE
#            "-sUSE_GLFW=3"
#            "-sASYNCIFY"
#            "-sFULL_ES2=1"
#            "-sFORCE_FILESYSTEM=1"
#            "--preload-file"
#            "${CMAKE_SOURCE_DIR}/assets@/assets"
#    )
#endif()
