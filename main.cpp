#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "CPLib/Triangle.h"
#include "CPLib/CPLib.h"

constexpr Color black = {0.0f, 0.0f, 0.0f, 1.0f};
constexpr Color red = {1.0f, 0.0f, 0.0f, 1.0f};
int main() {
    CPL::InitWindow(800, 600, "OpenGL Demo");

    while (!glfwWindowShouldClose(CPL::window)) {
        CPL::HandleInput(CPL::window);

        CPL::ClearBackground(black);

        // Draw stuff here
        Triangle triangle;
        triangle.Draw(red);

        // In order to detect inputs
        glfwSwapBuffers(CPL::window);
        glfwPollEvents();
    }
    CPL::CloseWindow();
}