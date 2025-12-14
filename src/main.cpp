#include "../CPLibrary/CPLibrary.h"
#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif
#include "StartAnimation.h"
#include <filesystem>
#include <fstream>

using namespace CPL;

PRIORITIZE_GPU_BY_VENDOR

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
        if (rotation > 45.0f)
            rotation = 45.0f;
        velocity += gravity * GetDeltaTime();
        position.y += velocity * GetDeltaTime();
    }

    void GameOverAnimation() {
        if (!(position.y - 100.0f / 4 >= GetScreenHeight())) {
            velocity += gravity * GetDeltaTime() * 5.0f;
            position.y += velocity * GetDeltaTime();
        }
    }
};

class Pipe {
  public:
    glm::vec2 position;
    glm::vec2 size = {100.0f, 500.0f};
    bool active = true;

    void Update() {
        position.x -= 100.0f * GetDeltaTime();
        if (active && position.x + size.x < 0)
            active = false;
    }
};
std::vector<Pipe> pipes;

class Background {
  public:
    std::vector<glm::vec2> skyPositions;
    std::vector<glm::vec2> buildingsPositions;
    std::vector<glm::vec2> woodsPositions;

    void Init() {
        skyPositions.emplace_back(0, 0);
        skyPositions.emplace_back(GetScreenWidth(), 0);
        buildingsPositions.emplace_back(0, 0);
        buildingsPositions.emplace_back(GetScreenWidth(), 0);
        woodsPositions.emplace_back(0, 0);
        woodsPositions.emplace_back(GetScreenWidth(), 0);
    }
    void Update() {
        for (auto &position : skyPositions) {
            position.x -= 15.0f * GetDeltaTime();
        }
        for (auto &position : buildingsPositions) {
            position.x -= 25.0f * GetDeltaTime();
        }
        for (auto &position : woodsPositions) {
            position.x -= 35.0f * GetDeltaTime();
        }

        if (!skyPositions.empty() &&
            skyPositions.front().x + GetScreenWidth() <= 0) {

            float rightmostX = skyPositions.back().x;
            skyPositions.erase(skyPositions.begin());
            skyPositions.emplace_back(rightmostX + GetScreenWidth(), 0);
        }
        if (!buildingsPositions.empty() &&
            buildingsPositions.front().x + GetScreenWidth() <= 0) {

            float rightmostX = buildingsPositions.back().x;
            buildingsPositions.erase(buildingsPositions.begin());
            buildingsPositions.emplace_back(rightmostX + GetScreenWidth(), 0);
        }
        if (!woodsPositions.empty() &&
            woodsPositions.front().x + GetScreenWidth() <= 0) {

            float rightmostX = woodsPositions.back().x;
            woodsPositions.erase(woodsPositions.begin());
            woodsPositions.emplace_back(rightmostX + GetScreenWidth(), 0);
        }
    }
};

float alpha = 0.0f;
void RestartAnimation() {
    if (alpha < 255.0f)
        alpha += 255.0f * GetDeltaTime() / 2;
}

bool gameOver = false;
bool isRestarting = false;
float score;
float highscore;

class UI {
  public:
    static void Menu() {
        const std::string title = "Flappy Bird";
        const float textWidth = Text::GetTextSize("defaultFont", title, 2).x;
        DrawTextShadow({GetScreenWidth() / 2 - textWidth / 2, 48 * 2}, {5, 5},
                       2, title, WHITE, DARK_GRAY);

        const std::string info = "[ Click to start ]";
        const float textWidthInfo =
            Text::GetTextSize("defaultFont", info, 0.5).x;
        DrawTextShadow({GetScreenWidth() / 2 - textWidthInfo / 2,
                        GetScreenHeight() / 1.5f},
                       {5, 5}, 0.5, info, WHITE, DARK_GRAY);

        const float textWidthHighscore =
            Text::GetTextSize("defaultFont",
                              "Highscore: " + std::to_string(static_cast<int>(
                                                  std::floor(highscore))),
                              0.75)
                .x;
        DrawTextShadow({GetScreenWidth() / 2 - textWidthHighscore / 2, 48 * 5},
                       {5, 5}, 0.75,
                       "Highscore: " + std::to_string(static_cast<int>(
                                           std::floor(highscore))),
                       WHITE, DARK_GRAY);
    }
    static void GameOver() {
        const std::string title = "Game Over";
        const float textWidth = Text::GetTextSize("defaultFont", title, 2).x;
        DrawTextShadow({GetScreenWidth() / 2 - textWidth / 2, 48 * 2}, {5, 5},
                       2, title, WHITE, DARK_GRAY);

        const std::string info = "[ Click to restart ]";
        const float textWidthInfo =
            Text::GetTextSize("defaultFont", info, 0.5).x;
        DrawTextShadow({GetScreenWidth() / 2 - textWidthInfo / 2,
                        GetScreenHeight() / 1.5f},
                       {5, 5}, 0.5, info, WHITE, DARK_GRAY);

        const float textWidthHighscore =
            Text::GetTextSize("defaultFont",
                              "Highscore: " + std::to_string(static_cast<int>(
                                                  std::floor(highscore))),
                              0.75)
                .x;
        DrawTextShadow({GetScreenWidth() / 2 - textWidthHighscore / 2, 48 * 5},
                       {5, 5}, 0.75,
                       "Highscore: " + std::to_string(static_cast<int>(
                                           std::floor(highscore))),
                       WHITE, DARK_GRAY);
    }
};

void HandleInput(Bird &player, const Audio &flySound,
                 const Audio &restartSound);

void InitHighScoreFile() {
    if (const std::string path = "highscore.txt";
        !std::filesystem::exists(path)) {
        std::ofstream file(path);
        file.close();
    }
}
void UpdateHighScore() {
    if (score > highscore) {
        highscore = score;
    }
}
void ReadHighScore() {
    const std::string path = "highscore.txt";
    std::string highScoreStr;
    std::ifstream file(path);
    while (getline(file, highScoreStr)) {
        highscore = std::stof(highScoreStr);
    }
    file.close();
}
void SaveHighScore() {
    const std::string path = "highscore.txt";
    std::string highScoreStr;
    std::ofstream file(path, std::ios::trunc);
    file << highscore;
    file.close();
}

void SpawnPipe() {
    Pipe pipe{};
    pipe.position = {GetScreenWidth(), GetScreenHeight() - RandFloat(0, 350)};
    pipes.push_back(pipe);
}
bool spawnPipe = false;
void RemovePipe() {
    std::erase_if(pipes, [](const Pipe &p) { return !p.active; });
}

std::unique_ptr<Texture2D> skyTexture;
std::unique_ptr<Texture2D> buildingsTexture;
std::unique_ptr<Texture2D> woodsTexture;
std::unique_ptr<Texture2D> birdTexture;
std::unique_ptr<Texture2D> pipeTexture;
Bird player{};
Background background{};
Audio damageSound;
Audio flySound;
Audio restartSound;
Audio music;

void MainLoop() {
    UpdateCPL();
    if (!StartAnimation::isFading)
        HandleInput(player, flySound, restartSound);
    UpdateHighScore();
    if (!gameOver)
        background.Update();
    if (player.isFalling && !gameOver)
        player.Update();
    if (gameOver)
        player.GameOverAnimation();

    if (gameOver)
        AudioManager::StopMusic();
    else
        AudioManager::ResumeMusic();

    if (player.isFalling && !spawnPipe && !gameOver) {
        SpawnPipe();
        spawnPipe = true;
        TimerManager::AddTimer(3.0f, false, [] { spawnPipe = false; });
    }
    RemovePipe();

    Circle playerCircle(player.position, birdTexture->textureSize.x / 4 - 4,
                        WHITE);
    for (auto &pipe : pipes) {
        if (!gameOver)
            pipe.Update();
        Rectangle upperPipeRect(pipe.position, pipe.size, WHITE);
        if (Rectangle lowerPipeRect(pipe.position -
                                        glm::vec2(0, pipe.size.y + 150),
                                    pipe.size, WHITE);
            CheckCollisionCircleRect(playerCircle, upperPipeRect) ||
            CheckCollisionCircleRect(playerCircle, lowerPipeRect)) {
            if (!gameOver)
                AudioManager::PlaySFX(damageSound);
            gameOver = true;
        }
    }

    if (player.position.y <= 0) {
        player.velocity = 0;
        player.position.y = 0;
    } else if (!gameOver &&
               player.position.y - birdTexture->textureSize.y / 4 >=
                   GetScreenHeight()) {
        AudioManager::PlaySFX(damageSound);
        gameOver = true;
    }

    ClearBackground(BLACK);
    BeginDrawing(TEXTURE_2D, false);
    for (auto &position : background.skyPositions) {
        DrawTexture2D(skyTexture.get(), position, WHITE);
    }
    for (auto &position : background.buildingsPositions) {
        DrawTexture2D(buildingsTexture.get(), position, WHITE);
    }
    for (auto &position : background.woodsPositions) {
        DrawTexture2D(woodsTexture.get(), position, WHITE);
    }
    for (const auto &pipe : pipes) {
        DrawTexture2DRotated(pipeTexture.get(),
                             pipe.position - glm::vec2(0, pipe.size.y + 145),
                             180, WHITE);
        DrawTexture2DRotated(pipeTexture.get(), pipe.position - glm::vec2(0, 0),
                             0, WHITE);
    }
    const glm::vec2 offset = {birdTexture->textureSize.x / 2,
                              birdTexture->textureSize.y / 2};
    DrawTexture2DRotated(birdTexture.get(), player.position - offset,
                         player.rotation, WHITE);

    BeginDrawing(SHAPE_2D, false);
    if (gameOver && !isRestarting)
        DrawRectangle({0, 0}, {GetScreenWidth(), GetScreenHeight()},
                      Color{0, 0, 0, 150});
    if (isRestarting) {
        RestartAnimation();
        DrawRectangle({0, 0}, {GetScreenWidth(), GetScreenHeight()},
                      Color{255, 255, 255, alpha});
    }

    BeginDrawing(TEXT, false);
    if (!gameOver && player.isFalling)
        score += 1 * GetDeltaTime();
    float textWidth =
        Text::GetTextSize("defaultFont",
                          std::to_string(static_cast<int>(std::floor(score))),
                          1)
            .x;
    if (player.isFalling)
        DrawTextShadow({GetScreenWidth() / 2 - textWidth / 2, 10}, {5, 5}, 1.5f,
                       std::to_string(static_cast<int>(std::floor(score))),
                       WHITE, DARK_GRAY);
    if (!player.isFalling)
        UI::Menu();
    if (gameOver && !isRestarting)
        UI::GameOver();

#ifndef __EMSCRIPTEN__
    ShowDetails();
#endif

    StartAnimation::Update();
    EndDrawing();

    glfwSwapBuffers(window);
    glfwPollEvents();
}
int main() {
    InitWindow(800, 600, "Flappy Bird Clone");

#ifndef __EMSCRIPTEN__
    SetWindowIcon("assets/images/icon.png");
    InitHighScoreFile();
    ReadHighScore();
#endif

    player.position = {GetScreenWidth() / 2, GetScreenHeight() / 2};
    camera.position = glm::vec2{GetScreenWidth() / 2, GetScreenHeight() / 2};
    background.Init();
    skyTexture = std::make_unique<Texture2D>(
        Texture2D("assets/images/sky.png",
                  {GetScreenWidth(), GetScreenHeight()}, LINEAR));
    buildingsTexture = std::make_unique<Texture2D>(
        Texture2D("assets/images/buildings.png",
                  {GetScreenWidth(), GetScreenHeight()}, LINEAR));
    woodsTexture = std::make_unique<Texture2D>(
        Texture2D("assets/images/woods.png",
                  {GetScreenWidth(), GetScreenHeight()}, LINEAR));
    birdTexture = std::make_unique<Texture2D>(
        Texture2D("assets/images/bird.png", {100, 100}, LINEAR));
    pipeTexture = std::make_unique<Texture2D>(
        Texture2D("assets/images/pipe.png", {100, 500}, LINEAR));
    damageSound = AudioManager::LoadAudio("assets/sounds/damage.wav");
    damageSound = AudioManager::LoadAudio("assets/sounds/damage.wav");
    flySound = AudioManager::LoadAudio("assets/sounds/jump.mp3");
    restartSound = AudioManager::LoadAudio("assets/sounds/restart.mp3");
    music = AudioManager::LoadAudio("assets/sounds/music.mp3");
    StartAnimation::Init();
    AudioManager::PlayMusic(music);

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(MainLoop, 0, true);
#else
    while (!WindowShouldClose()) {
        MainLoop();
    }
#endif

#ifndef __EMSCRIPTEN__
    SaveHighScore();
#endif

    CloseWindow();
}

void HandleInput(Bird &player, const Audio &flySound,
                 const Audio &restartSound) {
    if (IsKeyPressedOnce(KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, true);
    }
    if (IsMousePressedOnce(MOUSE_BUTTON_LEFT) && !gameOver) {
        if (!player.isFalling)
            player.isFalling = true;
        player.velocity = -player.jumpForce;
        AudioManager::PlaySFX(flySound);
    }
    if (IsMousePressedOnce(MOUSE_BUTTON_LEFT) && gameOver && !isRestarting) {
        AudioManager::PlaySFX(restartSound);
        if (!isRestarting) {
            isRestarting = true;
            alpha = 0.0f; // Alpha for restart animation
            TimerManager::AddTimer(2.0f, false, [&] {
                player.position = {GetScreenWidth() / 2, GetScreenHeight() / 2};
                player.velocity = 0;
                score = 0;
                pipes.clear();
                gameOver = false;
                isRestarting = false;
            });
        }
    }
}
