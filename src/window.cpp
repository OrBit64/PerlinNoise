#include <iostream>
#include <vector>

// #include <raylib.h>
#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"

#include "window.h"

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

        rlImGuiSetup(true); // true -- dark theme

        setGridSize(3);
        setGridScale(3);

        flag_show_grid = true;

        rebuildGrid();
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
            for (auto pixel_p = pixels.begin(); pixel_p != pixels.end(); pixel_p++)
                DrawRectangle(pixel_p->x, pixel_p->y, pixel_p->size, pixel_p->size, pixel_p->c);
            
            if (flag_show_grid)
                drawGrid();

            // ImGui
            rlImGuiBegin();

            ImGui::ShowDemoWindow();

            rlImGuiEnd();

        EndDrawing();
    }

    // The main cicle of the window. Running till window isn't close.
    void Window::update()
    {
        while (!WindowShouldClose())
        {
            if (IsWindowResized())  // Make window unresizable (temporary)
            {
                // SetWindowSize(w_width, w_height);
                w_width = GetRenderWidth();
                w_height = GetRenderHeight();
                rebuildGrid();
            }
            get_input();
            calculate();
            draw();
        }
    }

    // Getting input
    void Window::get_input()
    {
        // Change grid's size
        if (IsKeyPressed(KEY_UP))
        {
            setGridSize(g_size + 1);
            rebuildGrid();
        }
        if (IsKeyPressed(KEY_DOWN))
        {
            setGridSize(g_size - 1);
            rebuildGrid();
        }
        // Change grid's scale
        if (IsKeyPressed(KEY_RIGHT))
        {
            setGridScale(g_scale + 1);
            rebuildGrid();
        }
        if (IsKeyPressed(KEY_LEFT))
        {
            setGridScale(g_scale - 1);
            rebuildGrid();
        }
        if (IsKeyPressed(KEY_G))        // Press G to show/hide grid
            flag_show_grid = flag_show_grid ? false : true;
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
        for (int x = 0; x < w_width; x += pixel_size * g_scale)
            DrawLine(x, 0, x, w_height, BLACK);
        for (int y = 0; y < w_height; y += pixel_size * g_scale)
            DrawLine(0, y, w_width, y, BLACK);

        for (auto node_p = nodes.begin(); node_p != nodes.end(); node_p++)
            DrawCircle(node_p->x, node_p->y, 3.f, RED);
    }

    // Rebuild grid with new size and scale
    void Window::rebuildGrid()
    {
        pixels.clear();
        nodes.clear();

        int cell_size = w_width / g_size;
        int pixel_size = cell_size / g_scale;
        for (int x = 0; x <= w_width; x += pixel_size)
        {
            for (int y = 0; y <= w_height; y += pixel_size)
            {
                // Save every point and calculate it's gradient color;
                pixels.push_back({
                    x, y, pixel_size,
                    {
                        (unsigned char) (float(x) / float(w_width) * 255.f),
                        (unsigned char) (float(y) / float(w_height) * 255.f),
                        (unsigned char) (float(x*y) / float(w_width*w_height) * 255.f),
                        255
                    }
                });
                // Save every node in vector<Node2> nodes and calculate it's gradient vector
                if (x % (pixel_size * g_scale) == 0 && y % (pixel_size * g_scale) == 0)
                {
                    Node2 new_node = { x, y };
                    nodes.push_back(new_node);
                }
            }
        }
    }

}
