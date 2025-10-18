#include "CPLibrary/CPLibrary.h"
using namespace CPL;

// ----- Prioritize GPUs from NVIDIA or AMD over Intel ----- //
PRIORITIZE_GPU_BY_VENDOR
// --------------------------------------------------------- //

class Bird {
public:
    glm::vec2 position;
    float velocity = 100.0f;
    float gravity = 200.0f;
    float jumpForce = 150.0f;

    float rotation = 0.0f;
    bool isFalling = false;

    void Update() {
        rotation = 45.0f * velocity / jumpForce;
        if (velocity < jumpForce) velocity += gravity * GetDeltaTime();
        position.y += velocity * GetDeltaTime();
    }
};

class Pipe {
public:
    glm::vec2 position;
    glm::vec2 size = {100.0f, 500.0f};
    bool active = true;

    void Update() {
        position.x -= 100.0f * GetDeltaTime();
        if (active & position.x + size.x < 0) active = false;
    }
};
std::vector<Pipe> pipes;

class Background {
public:
    std::vector<glm::vec2> skyPositions;

    void Init() {
        skyPositions.emplace_back(0, 0);
        skyPositions.emplace_back(SCREEN_WIDTH, 0);
    }
    void Update() {
        for (auto& position : skyPositions) {
            if (position.x + 736 * 1.5 <= 0) {
                skyPositions.erase(skyPositions.begin());
                skyPositions.emplace_back(skyPositions.end()->x + 736 * 1.5, 0);
            }
            position.x -= 25.0f * GetDeltaTime();
        }
    }
};

class UI {
public:
    static void Menu() {
        const std::string title = "Flappy Bird";
        const float textWidth = Text::GetTextSize("defaultFont", title, 2).x;
        DrawTextShadow({static_cast<float>(SCREEN_WIDTH) / 2 - textWidth / 2, SCREEN_HEIGHT - 48 * 3},{5, 5}, 2, title, WHITE, DARK_GRAY);

        const std::string info = "Press [SPACE] to start";
        const float textWidthInfo = Text::GetTextSize("defaultFont", info, 0.5).x;
        DrawTextShadow({static_cast<float>(SCREEN_WIDTH) / 2 - textWidthInfo / 2, SCREEN_HEIGHT / 4},{5, 5}, 0.5, info, WHITE, DARK_GRAY);
    }
    static void GameOver() {
        const std::string title = "Game Over";
        const float textWidth = Text::GetTextSize("defaultFont", title, 2).x;
        DrawTextShadow({static_cast<float>(SCREEN_WIDTH) / 2 - textWidth / 2, SCREEN_HEIGHT - 48 * 3},{5, 5}, 2, title, WHITE, DARK_GRAY);

        const std::string info = "Press [SPACE] to restart";
        const float textWidthInfo = Text::GetTextSize("defaultFont", info, 0.5).x;
        DrawTextShadow({static_cast<float>(SCREEN_WIDTH) / 2 - textWidthInfo / 2, SCREEN_HEIGHT / 4},{5, 5}, 0.5, info, WHITE, DARK_GRAY);
    }
};

void HandleInput(Bird& player);

bool gameOver = false;
float score;

void SpawnPipe() {
    Pipe pipe{};
    pipe.position = {SCREEN_WIDTH, static_cast<float>(SCREEN_HEIGHT) - RandFloat(0, 350)};
    pipes.push_back(pipe);
}
bool spawnPipe = false;

void RemovePipe() {
    std::erase_if(pipes, [](const Pipe &p) { return !p.active; });
}

int main() {
    InitWindow(800, 600, "Flappy Bird OpenGL");
    AudioManager::Init();

    auto skyTexture = Texture2D("../assets/images/background.jpg", {736 * 1.5, 414 * 1.5});
    auto birdTexture = Texture2D("../assets/images/bird.png", {100, 100});
    auto pipeTexture = Texture2D("../assets/images/pipe2.png", {100, 500});
    Bird player{};
    player.position = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    camera.position = glm::vec2{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    Background background{};
    background.Init();

    Text::Init("../assets/fonts/arial.ttf", "arial");
    while (!WindowShouldClose()) {
        UpdateInput();
        CalculateDeltaTime();
        CalculateFPS();
        TimerManager::Update(GetDeltaTime());

        HandleInput(player);

        if (!gameOver) background.Update();
        if (player.isFalling && !gameOver) player.Update();

        if (player.isFalling && !spawnPipe && !gameOver) {
            SpawnPipe();
            spawnPipe = true;
            TimerManager::AddTimer(3.0f, false, [] {
                spawnPipe = false;
            });
        }
        RemovePipe();

        Circle playerCircle(player.position, birdTexture.textureSize.x / 4 - 4, WHITE);
        for (auto& pipe : pipes) {
            if (!gameOver) pipe.Update();
            Rectangle upperPipeRect(pipe.position, pipe.size, WHITE);
            Rectangle lowerPipeRect(pipe.position - glm::vec2(0, pipe.size.y + 150), pipe.size, WHITE);
            if (CheckCollisionCircleRect(playerCircle, upperPipeRect) || CheckCollisionCircleRect(playerCircle, lowerPipeRect)) {
                gameOver = true;
            }
        }

        if (player.position.y <= 0) {
            player.velocity = 0;
            player.position.y = 0;
        }
        else if (player.position.y - birdTexture.textureSize.y / 4 >= static_cast<float>(SCREEN_HEIGHT)) gameOver = true;

        ClearBackground(BLACK);
        BeginDrawing(TEXTURE_2D, false);
        for (auto& position : background.skyPositions) {
            DrawTexture2D(&skyTexture, position, WHITE);
        }
        const glm::vec2 offset = {birdTexture.textureSize.x / 2, birdTexture.textureSize.y / 2};
        DrawTexture2DRotated(&birdTexture, player.position - offset, player.rotation, WHITE);
        for (const auto& pipe : pipes) {
            DrawTexture2DRotated(&pipeTexture, pipe.position - glm::vec2(0, pipe.size.y + 145), 180, WHITE);
            DrawTexture2DRotated(&pipeTexture, pipe.position - glm::vec2(0, 0), 0, WHITE);
        }

        BeginDrawing(SHAPE_2D, false);
        if (gameOver) DrawRectangle({0, 0}, {SCREEN_WIDTH, SCREEN_HEIGHT}, Color{0, 0, 0, 150});

        BeginDrawing(TEXT, false);
        if (!gameOver && player.isFalling) score += 1 * GetDeltaTime();
        float textWidth = Text::GetTextSize("defaultFont", std::to_string(static_cast<int>(std::floor(score))), 1).x;
        if (player.isFalling) DrawTextShadow({static_cast<float>(SCREEN_WIDTH) / 2 - textWidth / 2, SCREEN_HEIGHT - 48},{5, 5}, 1, std::to_string(static_cast<int>(std::floor(score))), WHITE, DARK_GRAY);
        if (!player.isFalling) UI::Menu();
        if (gameOver) UI::GameOver();
        ShowDetails();

        EndDrawing();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    CloseWindow();
    AudioManager::Close();
}

void HandleInput(Bird& player) {
    if (IsKeyPressedOnce(KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, true);
    }
    if (IsKeyPressedOnce(KEY_SPACE)) {
        if (!player.isFalling) player.isFalling = true;
        player.velocity = -player.jumpForce;
        AudioManager::PlaySFX("../assets/sounds/jump.mp3");
    }
    if (IsKeyPressedOnce(KEY_SPACE) && gameOver) {
        gameOver = false;
        player.position = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
        player.velocity = 0;
        score = 0;
        pipes.clear();
    }
}