#pragma once

namespace CPL {
    struct Color;
    class Shader;

    class Triangle {
    public:
        unsigned int VBO{}, VAO{};

        explicit Triangle();
        void Draw(const Shader& shader, float x, float y, const Color& color) const;
    };
}