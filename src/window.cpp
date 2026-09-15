#include <iostream>
#include <vector>

#include "raylib.h"
// #include "imgui.h"
// #include "rlImGui.h"

#include "window.h"
#include "dispatcher.h"

namespace PerlinUI
{

    Window::Window(int width, int height, const char* title, int target_fps)
        : w_width(width)
        , w_height(height)
        , w_title(title)
        , targetFPS(target_fps)
    {
        InitWindow(w_width, w_height, w_title);
        SetTargetFPS(targetFPS);

        flag_show_grid = true;

        dispatcher.rebuild();
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
            // Draw every pixel (Rectangle).
            for (auto pixel_p = dispatcher.pixels.begin(); pixel_p != dispatcher.pixels.end(); pixel_p++)
                DrawRectangle(pixel_p->x, pixel_p->y, pixel_p->size, pixel_p->size, pixel_p->c);
            
            // Draw a grid with size = g_size, scale = g_scale.
            if (flag_show_grid)
                drawGrid();

            // ImGui
            dispatcher.draw();

        EndDrawing();
    }

    // The main cicle of the window. Running till window isn't close.
    void Window::update()
    {
        while (!WindowShouldClose())
        {
            if (IsWindowResized())  // Make window unresizable (temporary)
            {
                w_width  = GetRenderWidth();
                w_height = GetRenderHeight();
                dispatcher.rebuild();
            }
            get_input();
            calculate();
            draw();
        }
    }

    // Getting input
    void Window::get_input()
    {
        if (IsKeyPressed(KEY_G))        // Press G to show/hide grid
            flag_show_grid = flag_show_grid ? false : true;
    }

    // Methods for grid
    // Drawing grid
    void Window::drawGrid()
    {
        // TODO: Add members cell_size and pixel_size in Dispatcher?
        for (int x = 0; x < w_width; x += dispatcher.getPixelSize() * dispatcher.getGScale())
            DrawLine(x, 0, x, w_height, BLACK);
        for (int y = 0; y < w_height; y += dispatcher.getPixelSize() * dispatcher.getGScale())
            DrawLine(0, y, w_width, y, BLACK);

        for (auto node_p = dispatcher.nodes.begin(); node_p != dispatcher.nodes.end(); node_p++)
            DrawCircle(node_p->x, node_p->y, 3.f, RED);
    }

}
