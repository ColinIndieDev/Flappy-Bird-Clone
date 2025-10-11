#pragma once

namespace CPL {
    struct Color;
    class Shader;

    class Rectangle {
    public:
        unsigned int VBO{}, VAO{}, EBO{};

        explicit Rectangle();
        void Draw(const Shader& shader, const Color& color) const;
    };
}