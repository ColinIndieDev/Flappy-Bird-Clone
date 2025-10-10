#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

struct Color {
    float r, g, b, a;
};

namespace CPL {
    inline unsigned int SCREEN_WIDTH;
    inline unsigned int SCREEN_HEIGHT;

    inline GLFWwindow* window;

    inline void ClearBackground(const Color& color) {
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    inline void framebuffer_size_callback(GLFWwindow* window, const int width, const int height) {
        glViewport(0, 0, width, height);
    }

    inline void InitWindow(const int width, const int height, const char* title) {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        SCREEN_WIDTH = width;
        SCREEN_HEIGHT = height;

        window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (window == nullptr) {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            exit(-1);
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
            std::cout << "Failed to initialize GLAD" << std::endl;
            exit(-1);
        }
    }

    inline void HandleInput(GLFWwindow* window) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
    }

    inline void CloseWindow() { glfwTerminate(); }
}