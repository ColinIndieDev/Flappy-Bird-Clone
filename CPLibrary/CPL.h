#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <iostream>
#include "Colors.h"
#include "KeyInputs.h"

namespace CPL {
    struct Color {
        float r, g, b, a;
    };

    class Shader;
    class Triangle;
    class Rectangle;
    class Circle;

    inline unsigned int SCREEN_WIDTH;
    inline unsigned int SCREEN_HEIGHT;
    inline glm::mat4 projection;

    extern Shader shapeShader;

    inline GLFWwindow* window;

    bool CheckCollisionRects(const Rectangle &one, const Rectangle &two);

    void InitShaders();

    void DrawTriangle(glm::vec2 position, glm::vec2 size, const Color& color);
    void DrawTriangleRotated(glm::vec2 position, glm::vec2 size, float angle, const Color& color);
    void DrawRectangle(glm::vec2 position, glm::vec2 size, const Color& color);
    void DrawRectangleRotated(glm::vec2 position, glm::vec2 size, float angle, const Color& color);
    void DrawCircle(glm::vec2 position, float radius, const Color& color);
    void DrawCircleRotated(glm::vec2 position, float radius, float angle, const Color& color);

    inline void ClearBackground(const Color& color) {
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void BeginDrawShape();

    inline void EndDrawing() {
        glUseProgram(0);
    }

    inline void framebuffer_size_callback(GLFWwindow* window, const int width, const int height) {
        glViewport(0, 0, width, height);
    }

    inline double lastTime = 0.0;
    inline int nbFrames = 0;
    inline void ShowFPS() {
        const double currentTime = glfwGetTime();
        nbFrames++;

        if (currentTime - lastTime >= 1.0) {
            std::cout << "FPS: " << nbFrames << std::endl;
            nbFrames = 0;
            lastTime += 1.0;
        }
    }
    inline float deltaTime = 0;
    inline float lastFrame = 0;

    inline void CalculateDeltaTime() {
        const auto currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
    }

    inline float GetDeltaTime() { return deltaTime; }
    inline float GetTime() { return static_cast<float>(glfwGetTime()); }

    inline void InitWindow(const int width, const int height, const char* title) {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        SCREEN_WIDTH = width;
        SCREEN_HEIGHT = height;
        projection = glm::ortho(
            0.0f, static_cast<float>(width),
            static_cast<float>(height), 0.0f,
            -1.0f, 1.0f
        );

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

    inline int WindowShouldClose() {
        return glfwWindowShouldClose(window);
    }

    inline int IsKeyDown(const int keycode) {
        return glfwGetKey(window, keycode) == GLFW_PRESS;
    }
    inline int IsKeyUp(const int keycode) {
        return glfwGetKey(window, keycode) == GLFW_RELEASE;
    }

    inline void CloseWindow() { glfwTerminate(); }
}