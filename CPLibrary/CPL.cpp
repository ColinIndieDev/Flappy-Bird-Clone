#include "CPL.h"
#include "shapes2D/Triangle.h"
#include "shapes2D/Rectangle.h"
#include "shapes2D/Circle.h"
#include "shapes2D/Line.h"
#include "Shader.h"
#include "Text.h"
#include "shapes2D/Texture2D.h"

namespace CPL {
    Shader shapeShader;
    Shader textShader;
    Shader textureShader;

    void ShowDetails() {
        const GLubyte* renderer = glGetString(GL_RENDERER);
        const GLubyte* vendor = glGetString(GL_VENDOR);
        const GLubyte* version = glGetString(GL_VERSION);
        const std::string rendererString(reinterpret_cast<const char*>(renderer));
        const std::string vendorString(reinterpret_cast<const char*>(vendor));
        const std::string versionString(reinterpret_cast<const char*>(version));

        BeginDrawing(TEXT, false);
        const std::string fpsText = "FPS: " + std::to_string(GetFPS());
        DrawText({0, 25}, 0.3, fpsText, WHITE);
        const std::string vendorText = "Vendor: " + vendorString;
        DrawText({0, 60}, 0.3, vendorText, WHITE);
        const std::string rendererText = "GPU: " + rendererString;
        DrawText({0, 95}, 0.3, rendererText, WHITE);
        const std::string versionText = "Version: " + versionString;
        DrawText({0, 130}, 0.3, versionText, WHITE);
        EndDrawing();
    }


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
        textureShader = Shader("../CPLibrary/shaders/texture.vert", "../CPLibrary/shaders/texture.frag");
    }

    void BeginDrawing(const DrawModes& mode, const bool mode2D) {
        Shader shader{};
        if (mode == SHAPE_2D) shader = shapeShader;
        else if (mode == TEXT) {
            shader = textShader;
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
        else if (mode == TEXTURE_2D) shader = textureShader;

        shader.Use();
        const glm::mat4 view = camera.GetViewMatrix();
        const glm::mat4 viewProjection = projection * view;
        shader.SetMatrix4fv("projection", mode2D ? viewProjection : projection);
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

    void DrawTexture2D(Texture2D* texture, const glm::vec2 position, const Color& color) {
        texture->position = position;
        texture->color = color;
        texture->Draw(textureShader);
    }
    void DrawTexture2DRotated(Texture2D* texture, const glm::vec2 position, const float angle, const Color& color) {
        texture->position = position;
        texture->color = color;
        texture->rotationAngle = angle;
        texture->Draw(textureShader);
    }
    void DrawTex2DCpy(Texture2D texture, const glm::vec2 position, const Color& color) {
        texture.position = position;
        texture.color = color;
        texture.Draw(textureShader);
    }

    void DrawText(const glm::vec2 position, const float scale, const std::string& text, const Color& color) {
        Text::DrawText(textShader, text, position, scale, color);
    }

}
