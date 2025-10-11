#pragma once

namespace CPL {
    struct Color;
    class Shader;

    class Circle {
    public:
        unsigned int VBO{}, VAO{};
        int vertexCount = 0;

        explicit Circle();
        void Draw(const Shader& shader, const Color& color) const;
    };
}