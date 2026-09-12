#include <iostream>

#include <raylib.h>
#include <window.h>

namespace PerlinUI
{

    Window::Window(int width, int height, const char* title, int target_fps)
        : w_width(width)
        , w_height(height)
        , w_title(title)
        , targetFPS(target_fps)
    {
        InitWindow(w_width, w_height, w_title);
        ClearWindowState(FLAG_FULLSCREEN_MODE);
        SetTargetFPS(targetFPS);
        setGridScale(5);
        setGridSize(10);
    }

    // Calculate Perlin noise every frame
    void Window::calculate()
    {
        float dt = GetFrameTime();
        // TODO: Calculating Perlin noise
        // This is where most of our math will be placed
    }

    // Draw frame's contents every frame
    void Window::draw()
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);

            // TODO: Draw Perlin noise
            // Draw a grid with size = g_size, scale = g_scale. Now it's more for debugging.
            drawGrid();

        EndDrawing();
    }

    // The main cicle of the window. Running till window isn't close.
    void Window::update()
    {
        while (!WindowShouldClose())
        {
            if (IsWindowResized()) 
            {
                SetWindowSize(w_width, w_height);
                // w_width = GetRenderWidth();
                // w_height = GetRenderHeight();
            }
            calculate();
            draw();
        }
    }

    // Methods for grid
    // Set new size for grid
    bool Window::setGridSize(int new_size)
    {
        if (new_size > 0 && new_size <= w_width)
        {
            g_size = new_size;
            return true;
        }
        std::cerr << "[ERROR] Bad arguments for grid's size. Size > 0 && size <= w_width.\n";
        return false;
    }
    // Set new scale for grid
    bool Window::setGridScale(int new_scale)
    {
        if (new_scale > 0 && new_scale < 1000)
        {
            g_scale = new_scale;
            return true;
        }
        std::cerr << "[ERROR] Bad arguments for grid's scale. Scale > 0 && scale <= grid's size.\n";
        return false;
    }

    // Drawing grid
    void Window::drawGrid()
    {
        int cell_size = w_width / g_size;
        int pixel_size = cell_size / g_scale;
        for (int x = 0; x < w_width; x += pixel_size * g_size)
            DrawLine(x, 0, x, w_height, BLACK);
        for (int y = 0; y < w_height; y += pixel_size * g_size)
            DrawLine(0, y, w_width, y, BLACK);
    }

}
