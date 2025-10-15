#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <iostream>
#include "Colors.h"
#include "KeyInputs.h"

#define PRIORITIZE_GPU_BY_VENDOR extern "C" { __declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001; __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1; }

namespace CPL {
    enum DrawModes {
        SHAPE_2D,
        TEXTURE_2D,
        TEXT,
    };

    struct Color {
        float r, g, b, a;
    };

    struct Timer;
    class TimerManager;

    class Shader;
    class Triangle;
    class Rectangle;
    class Circle;
    class Line;
    class Texture2D;

    struct Character;
    class Text;

    inline unsigned int SCREEN_WIDTH;
    inline unsigned int SCREEN_HEIGHT;
    inline glm::mat4 projection;

    extern Shader shapeShader;
    extern Shader textShader;
    extern Shader textureShader;

    inline GLFWwindow* window;

    struct Camera2D {
        float zoom = 1.0f;
        float rotation = 0.0f;

        void Init() {
            position = {-static_cast<float>(SCREEN_WIDTH) / 2.0f, -static_cast<float>(SCREEN_HEIGHT) / 2.0f};
        }

        void SetPosition(const glm::vec2 position) {
            this->position = position - glm::vec2(static_cast<float>(SCREEN_WIDTH) / 2.0f, static_cast<float>(SCREEN_HEIGHT) / 2.0f);
        }

        [[nodiscard]] glm::mat4 GetViewMatrix() const {
            auto view = glm::mat4(1.0f);
            view = glm::translate(view, glm::vec3(-position, 0.0f));
            view  = glm::scale(view, glm::vec3(zoom, zoom, 1.0f));
            view = glm::rotate(view, glm::radians(rotation), glm::vec3(0, 0, 1));
            return view;
        }
    private:
        glm::vec2 position{0.0f};
    };

    inline Camera2D camera;

    bool CheckCollisionRects(const Rectangle &one, const Rectangle &two);

    void InitShaders();

    void DrawTriangle(glm::vec2 position, glm::vec2 size, const Color& color);
    void DrawTriangleRotated(glm::vec2 position, glm::vec2 size, float angle, const Color& color);
    void DrawRectangle(glm::vec2 position, glm::vec2 size, const Color& color);
    void DrawRectangleRotated(glm::vec2 position, glm::vec2 size, float angle, const Color& color);
    void DrawCircle(glm::vec2 position, float radius, const Color& color);
    void DrawCircleRotated(glm::vec2 position, float radius, float angle, const Color& color);
    void DrawLine(glm::vec2 startPos, glm::vec2 endPos, const Color& color);
    void DrawTexture2D(Texture2D* texture, glm::vec2 position, const Color& color);
    void DrawTexture2DRotated(Texture2D* texture, glm::vec2 position, float angle, const Color& color);
    void DrawTex2DCpy(Texture2D texture, glm::vec2 position, const Color& color);

    void DrawText(glm::vec2 position, float scale, const std::string& text, const Color& color);

    inline void ClearBackground(const Color& color) {
        glClearColor(color.r / 255, color.g / 255, color.b / 255, color.a / 255);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void BeginDrawing(const DrawModes& mode, bool mode2D);

    inline void EndDrawing() {
        glUseProgram(0);
    }

    inline void framebuffer_size_callback(GLFWwindow* window, const int width, const int height) {
        glViewport(0, 0, width, height);
    }

    inline double lastTime = 0.0;
    inline int nbFrames = 0;
    inline int FPS;
    inline void CalculateFPS() {
        const double currentTime = glfwGetTime();
        nbFrames++;
        if (currentTime - lastTime >= 1.0) {
            FPS = nbFrames;
            nbFrames = 0;
            lastTime += 1.0;
        }
    }
    inline int GetFPS() {
        return FPS;
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

    void ShowDetails();

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