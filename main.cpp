#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "CPLibrary/Triangle.h"
#include "CPLibrary/Circle.h"
#include "CPLibrary/Rectangle.h"
#include "CPLibrary/Globals.h"
#include "CPLibrary/Shader.h"

constexpr CPL::Color black = {0.0f, 0.0f, 0.0f, 1.0f};
constexpr CPL::Color red = {1.0f, 0.0f, 0.0f, 1.0f};
int main() {
    CPL::InitWindow(800, 600, "OpenGL Demo");

    while (!glfwWindowShouldClose(CPL::window)) {
        CPL::HandleInput(CPL::window);
        CPL::ShowFPS();

        CPL::ClearBackground(black);

        // Draw stuff here
        auto shader = CPL::Shader("../CPLibrary/shaders/shader.vert", "../CPLibrary/shaders/shader.frag");
        shader.Use();
        CPL::DrawTriangle(shader, 400, 300, red);
        //DrawCircle(shader, red);

        // In order to detect inputs
        glfwSwapBuffers(CPL::window);
        glfwPollEvents();
    }
    CPL::CloseWindow();
}