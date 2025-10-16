#pragma once

#include "vec2.hpp"
#include "../CPL.h"

namespace CPL {
    struct Color;
    class Shader;

    class Circle {
    public:
        glm::vec2 position;
        float radius;
        Color color;
        mutable float rotationAngle = 0.0f;

        explicit Circle(glm::vec2 pos, float radius, Color color);
        void Draw(const Shader& shader) const;
        void DrawOutline(const Shader& shader) const;
    private:
        unsigned int VBO{}, VAO{};
        unsigned int outlineVBO{}, outlineVAO{};
        int vertexCount = 0;
    };
}