#pragma once

#include "vec2.hpp"
#include "../CPL.h"

namespace CPL {
    struct Color;
    class Shader;

    class Triangle {
    public:
        glm::vec2 position;
        glm::vec2 size;
        Color color;
        mutable float rotationAngle = 0.0f;

        explicit Triangle(glm::vec2 pos, glm::vec2 size, Color color);
        void Draw(const Shader& shader) const;
    private:
        unsigned int VBO{}, VAO{};
    };
}
