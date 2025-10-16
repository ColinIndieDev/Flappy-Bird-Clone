#include "CPLibrary/CPLibrary.h"

using namespace CPL;

// ----- Prioritize GPUs from NVIDIA or AMD over Intel ----- //
PRIORITIZE_GPU_BY_VENDOR
// --------------------------------------------------------- //

auto playerPos = glm::vec2(0, 300);
void HandleInput();

int main() {
    InitWindow(800, 600, "OpenGL Demo");

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    auto skyTexture = Texture2D("../assets/images/sky.jpg", {736 * 1.5, 414 * 1.5});
    auto texture = Texture2D("../assets/images/block.jpeg", {100, 100});

    while (!WindowShouldClose()) {
        HandleInput();
        CalculateDeltaTime();
        CalculateFPS();
        TimerManager::Update(GetDeltaTime());
        camera.SetPosition(playerPos);

        ClearBackground(BLACK);
        BeginDrawing(TEXTURE_2D, false);
        DrawTexture2D(&skyTexture, {0, 0}, WHITE);

        BeginDrawing(TEXTURE_2D, true);
        for (int y = 0; y < 8; y++) {
            for (int x = 0; x < 8; x++) {
                DrawTexture2D(&texture, {x * 100, y * 100}, WHITE);
            }
        }

        BeginDrawing(SHAPE_2D, true);
        DrawCircle({0, 0}, 100, DARK_GRAY);

        BeginDrawing(TEXT, false);
        ShowDetails();

        EndDrawing();

        // In order to detect inputs
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    CloseWindow();
}

void HandleInput() {
    if (IsKeyDown(KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, true);
    }
    if (IsKeyDown(KEY_W)) {
        playerPos.y -= 100 * GetDeltaTime();
    }
    if (IsKeyDown(KEY_S)) {
        playerPos.y += 100 * GetDeltaTime();
    }
    if (IsKeyDown(KEY_A)) {
        playerPos.x -= 100 * GetDeltaTime();
    }
    if (IsKeyDown(KEY_D)) {
        playerPos.x += 100 * GetDeltaTime();
    }
}