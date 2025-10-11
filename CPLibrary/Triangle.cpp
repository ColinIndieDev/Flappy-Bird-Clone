#include "Triangle.h"
#include "Shader.h"
#include "Globals.h"

namespace CPL {
    Triangle::Triangle() {
        //constexpr float vertices[] = {
        //    -0.5f, -0.5f, 0.0f, // left
        //    0.5f, -0.5f, 0.0f, // right
        //    0.0f, 0.5f, 0.0f, // top
        //};
        constexpr float vertices[] = {
            0.0f,   0.0f,   0.0f, // left
            100.0f, 0.0f,   0.0f, // right
            50.0f,  100.0f, 0.0f // top
        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void Triangle::Draw(const Shader& shader, const float x, const float y, const Color& color) const {
        shader.SetMatrix4fv("projection", projection);
        shader.SetVector3f("offset", glm::vec3(x, y, 0)); // Z not required for 2D shape
        shader.SetColor("inputColor", color);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
    }
}