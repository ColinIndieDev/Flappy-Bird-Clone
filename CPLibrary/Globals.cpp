#include "Globals.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Circle.h"

namespace CPL {
    void DrawTriangle(const Shader& shader, const float x, const float y, const Color& color) {
        const Triangle triangle;
        triangle.Draw(shader, x, y, color);
    }

    void DrawRectangle(const Shader& shader, const Color& color) {
        const Rectangle rectangle;
        rectangle.Draw(shader, color);
    }

    void DrawCircle(const Shader& shader, const Color& color) {
        const Circle circle;
        circle.Draw(shader, color);
    }
}