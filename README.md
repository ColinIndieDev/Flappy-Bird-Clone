# CPLibrary (CPL)
### About
CPL (named by me) is my custom framework made from scratch. This framework is entirely written
in C++ and uses OpenGL & other low-level libraries like GLFW, GLAD, STBImage etc.
Currently I worked on this just for 1-2 months
### Example code

#include "../CPLibrary/CPLibrary.h"

using namespace CPL;
PRIORITIZE_GPU_BY_VENDOR

int main() {
    InitWindow(800, 600, "Welcome to CPL");

    while (!WindowShouldClose()) {
        UpdateCPL();

        ClearBackground(BLACK);
        
        BeginDrawing(SHAPE_2D, true);
        DrawRectangle({0, 0}, {100, 100}, RED);

        BeginDrawing(TEXT, false);
        DrawText({GetScreenWidth() / 2, GetScreenHeight() / 2}, 
            1.0f, "Hello OpenGL", WHITE);

        EndDrawing();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    CloseWindow();

    return 0;
}

As you can see, the functions and naming conventions are pretty similar
and inspired by the ones from Raylib

### Functionality
CPL currently only supports 2D, but 3D is planned for the future.
Since CPL is written in C++ and open source, you may look up the code
and modify it potentially for personal purpose

2D:
- drawing primitives like rectangles, circles, triangles and more!
- drawing 2D textures from every image format (.png, .jpg, ...) with stb
- drawing texts with custom fonts with freetype
- 2D camera
- creating and drawing tilemaps

Others:
- random number generator or probabilities by percent
- key and mouse inputs
- audio for playing sounds & music
- timer & cooldowns
