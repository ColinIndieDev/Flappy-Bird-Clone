#pragma once

#include "vec2.hpp"
#include "../CPL.h"

namespace CPL {
    struct Color;
    class Shader;

    class Rectangle {
    public:
        glm::vec2 position;
        glm::vec2 size;
        Color color;
        mutable float rotationAngle = 0.0f;

        explicit Rectangle(glm::vec2 pos, glm::vec2 size, Color color);
        void Draw(const Shader& shader, bool filled) const;
    private:
        unsigned int outlineVBO{}, outlineVAO{}, outlineEBO{};
        unsigned int VBO{}, VAO{}, EBO{};
    };
}