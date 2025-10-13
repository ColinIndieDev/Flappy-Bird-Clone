#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "CPLibrary/2D_Shapes/Triangle.h"
#include "CPLibrary/2D_Shapes/Circle.h"
#include "CPLibrary/2D_Shapes/Rectangle.h"
#include "CPLibrary/CPL.h"
#include "CPLibrary/Shader.h"
#include "CPLibrary/Text.h"

#include <filesystem>

#include <ft2build.h>
#include FT_FREETYPE_H

using namespace CPL;

// Here ends my framework

auto playerPos = glm::vec2(0, 300);
void HandleInput();

int main() {
    InitWindow(800, 600, "OpenGL Demo");
    InitShaders();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // ----- If you want to debug and look how the shapes are made from polygons ----- //
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // ------------------------------------------------------------------------------- //
    Text::Init("../assets/fonts/arial.ttf");
    while (!WindowShouldClose()) {
        HandleInput();
        CalculateDeltaTime();
        CalculateFPS();

        // ----- Collision ----- //
        //if (CheckCollisionRects(playerRect, wallRect)) {
        //    std::cout << "Collision" << std::endl;
        //}
        // --------------------- //

        ClearBackground(BLACK);

        BeginDrawing(SHAPE_2D);

        DrawTriangleRotated({200, 200}, {100, 100}, 90, LIME_GREEN);
        const float rotation = GetTime() * 360;
        DrawRectangleRotated({400, 300}, {200, 100}, rotation, RED);
        DrawRectangle(playerPos, {100, 100}, BLUE);
        //DrawCircle({400, 100}, 100, WHITE); //Somehow crashes with Text::Init()

        BeginDrawing(TEXT);

        std::string fpsText = "FPS: " + std::to_string(GetFPS());
        DrawText({0, 25}, 1, "Hallo, mein name... : cool!?", WHITE);

        EndDrawing();

        // In order to detect inputs
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    CloseWindow();
}

void HandleInput() {
    if (IsKeyDown(GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, true);
    }
    if (IsKeyDown(KEY_SPACE)) {
        playerPos.x += 100 * GetDeltaTime();
    }
}