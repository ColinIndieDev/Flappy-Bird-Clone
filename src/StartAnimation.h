#pragma once
#include "../CPLibrary/CPLibrary.h"

using namespace CPL;

namespace StartAnimation {
    inline float alphaLogo = 255.f;
    inline float alphaBackground = 255.f;

    inline bool isFading = true;
    inline std::unique_ptr<Texture2D> texture;

    inline void Init() {
        texture = std::make_unique<Texture2D>(Texture2D("assets/images/logo.png", {250, 250}, LINEAR));
    }

    inline void Update() {
        BeginDrawing(SHAPE_2D, false);
        DrawRectangle({0, 0}, {GetScreenWidth(), GetScreenHeight()}, Color{0, 0, 0, alphaBackground});
        BeginDrawing(TEXTURE_2D, false);
        const glm::vec2 logoPos = {GetScreenWidth() / 2.0f - texture->textureSize.x / 2.0f, GetScreenHeight() / 2.0f - texture->textureSize.y / 2.0f};
        DrawTexture2D(texture.get(), logoPos, Color{255, 255, 255, alphaLogo});

        if (alphaLogo > 0) alphaLogo -= 75.f * GetDeltaTime();
        if (alphaLogo <= 0 && alphaBackground > 0) alphaBackground -= 125.f * GetDeltaTime();

        if (alphaBackground <= 0 && alphaLogo <= 0 && isFading) isFading = false;
    }
}
