#include "Circle.h"
#include "Globals.h"
#include <cmath>
#include <vector>

#include "Shader.h"

namespace CPL {
    Circle::Circle() {
        std::vector vertices = {
            0.0f, 0.0f, 0.0f // Center
        };

        constexpr int segments = 100;
        for (int i = 0; i <= segments; i++) {
            const float theta = 2 * static_cast<float>(M_PI)  / static_cast<float>(segments) * static_cast<float>(i);
            float x = 0.0f + 1.0f * std::cos(theta);
            float y = 0.0f + 1.0f * std::sin(theta);
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(0);
        }

        vertexCount = static_cast<int>(vertices.size()) / 3;

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertices.size() * sizeof(vertices.data())), vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void Circle::Draw(const Shader& shader, const Color& color) const {
        shader.SetColor("inputColor", color);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);
    }
}
