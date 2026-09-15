#pragma once

#include <vector>

// #include <raylib.h>
#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"

#include "dispatcher.h"


namespace PerlinUI
{

    class Window
    {
    private:
        int w_width;            // window's width
        int w_height;           // window's height
        const char* w_title;    // window's title
        int targetFPS;          // target FPS
        // int g_scale;    // -> dispatcher.getGScale()
        // int g_size;     // -> dispatcher.getGSize()
        bool flag_show_grid;

        Dispatcher dispatcher;

        // std::vector<Pixel> pixels;  // -> dispatcher.pixels()
        // std::vector<Node2> nodes;   // -> dispatcher.nodes()

    public:
        Window(int width, int height, const char* title, int target_fps = 60);
        ~Window() { rlImGuiShutdown(); CloseWindow(); }
        void update();      // main cicle of the window. Running till window isn't close.

    private:
        void draw();        // draw Perlin noise every frame
        void calculate();   // calculate Perlin noise every frame
        void get_input();

        void drawGrid();    // Draws grid on the screen
        // void rebuildGrid(); // -> dispatcher.rebuild();
    };

}
