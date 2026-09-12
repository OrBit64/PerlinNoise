#pragma once

#include <raylib.h>

namespace PerlinUI
{

    class Window
    {
    private:
        int w_width;            // window's width
        int w_height;           // window's height
        const char* w_title;    // window's title
        int targetFPS;          // target FPS
        int g_scale;
        int g_size;
    public:
        Window(int width, int height, const char* title, int target_fps = 60);
        ~Window() { CloseWindow(); }
        void update();      // main cicle of the window. Running till window isn't close.
        bool setGridSize(int new_size);     // Set new size for grid
        bool setGridScale(int new_scale);   // Set new scale for grid
    private:
        void draw();        // draw Perlin noise every frame
        void calculate();   // calculate Perlin noise every frame

        void drawGrid();    // Draws grid on the screen
        
    };

}
