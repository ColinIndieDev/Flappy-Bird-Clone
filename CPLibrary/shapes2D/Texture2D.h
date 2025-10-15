#pragma once

#include "../CPL.h"

namespace CPL {
    struct Color;
    class Shader;

    class Texture2D {
    public:
        glm::vec2 position;
        glm::vec2 size;
        int channels{};
        float rotationAngle = 0;
        Color color;

        explicit Texture2D(const std::string& filePath, glm::vec2 size);
        Texture2D(const std::string& filePath, glm::vec2 position, glm::vec2 size, const Color& color);
        void Draw(const Shader& shader) const;
    private:
        unsigned int VBO{}, VAO{}, EBO{};
        unsigned int texture{};
    };
}