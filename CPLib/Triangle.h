#pragma once

#include "Shader.h"

class Triangle {
public:
    Shader triangleShader = Shader("../CPLib/shaders/shader.vert", "../CPLib/shaders/shader.frag");
    unsigned int VBO{}, VAO{};

    explicit Triangle();
    void Draw(const Color& color) const;
};