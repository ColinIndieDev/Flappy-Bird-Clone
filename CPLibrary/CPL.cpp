#include "CPL.h"
#include "2D_Shapes/Triangle.h"
#include "2D_Shapes/Rectangle.h"
#include "2D_Shapes/Circle.h"
#include "2D_Shapes/Line.h"
#include "Shader.h"
#include "Text.h"

namespace CPL {
    Shader shapeShader;
    Shader textShader;

    bool CheckCollisionRects(const Rectangle& one, const Rectangle& two) {
        // X Axis
        const bool collisionX = one.position.x + one.size.x >= two.position.x &&
            two.position.x + two.size.x >= one.position.x;
        // Y Axis
        const bool collisionY = one.position.y + one.size.y >= two.position.y &&
            two.position.y + two.size.y >= one.position.y;

        return collisionX && collisionY;
    }

    void InitShaders() {
        shapeShader = Shader("../CPLibrary/shaders/shader.vert", "../CPLibrary/shaders/shader.frag");
        textShader = Shader("../CPLibrary/shaders/text.vert", "../CPLibrary/shaders/text.frag");
    }

    void BeginDrawing(const DrawModes& mode) {
        if (mode == SHAPE_2D) shapeShader.Use();
        else if (mode == TEXT) textShader.Use();
    }

    void DrawTriangle(const glm::vec2 position, const glm::vec2 size, const Color& color) {
        const auto triangle = Triangle(position, size, color);
        triangle.Draw(shapeShader);
    }
    void DrawTriangleRotated(const glm::vec2 position, const glm::vec2 size, const float angle, const Color& color) {
        const auto triangle = Triangle(position, size, color);
        triangle.rotationAngle = angle;
        triangle.Draw(shapeShader);
    }

    void DrawRectangle(const glm::vec2 position, const glm::vec2 size, const Color& color) {
        const auto rectangle = Rectangle(position, size, color);
        rectangle.Draw(shapeShader);
    }
    void DrawRectangleRotated(const glm::vec2 position, const glm::vec2 size, const float angle, const Color& color) {
        const auto rectangle = Rectangle(position, size, color);
        rectangle.rotationAngle = angle;
        rectangle.Draw(shapeShader);
    }

    void DrawCircle(const glm::vec2 position, const float radius, const Color& color) {
        const auto circle = Circle(position, radius, color);
        circle.Draw(shapeShader);
    }
    void DrawCircleRotated(const glm::vec2 position, const float radius, const float angle, const Color& color) {
        const auto circle = Circle(position, radius, color);
        circle.rotationAngle = angle;
        circle.Draw(shapeShader);
    }

    void DrawLine(const glm::vec2 startPos, const glm::vec2 endPos, const Color& color) {
        const auto line = Line(startPos, endPos, color);
        line.Draw(shapeShader);
    }

    void DrawText(const glm::vec2 position, const float scale, const std::string& text, const Color& color) {
        Text::DrawText(textShader, text, position, scale, color);
    }

}
