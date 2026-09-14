#pragma once

// #include <raylib.h>
#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"

#include <vector>

namespace PerlinUI
{

    struct Pixel
    {
        int x;
        int y;
        int size;
        Color c;
    };

    struct Node2
    {
        int x;
        int y;
        // Vector2 gradient; // Random vector of gradient with length 1.
    };

    class Window
    {
    private:
        int w_width;            // window's width
        int w_height;           // window's height
        const char* w_title;    // window's title
        int targetFPS;          // target FPS
        int g_scale;
        int g_size;
        bool flag_show_grid;

        std::vector<Pixel> pixels;  // Saving every pixel (point) to draw
        std::vector<Node2> nodes;   // Saving every node to simplify calcucations

    public:
        Window(int width, int height, const char* title, int target_fps = 60);
        ~Window() { rlImGuiShutdown(); CloseWindow(); }
        void update();      // main cicle of the window. Running till window isn't close.
        bool setGridSize(int new_size);     // Set new size for grid
        bool setGridScale(int new_scale);   // Set new scale for grid

    private:
        void draw();        // draw Perlin noise every frame
        void calculate();   // calculate Perlin noise every frame
        void get_input();

        void drawGrid();    // Draws grid on the screen
        void rebuildGrid();
    };

}
