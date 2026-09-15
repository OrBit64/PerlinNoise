/**
 * Прослойка между UI и математикой. Тут хранятся и меняются отображаемые данные.
 * Для ввода используется ImGui. Использует Raylib.
 */
#pragma once

#include <vector>

// #include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"

// #include "window.h"

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

    // Class Grid have to share size and scale of grid
    class Grid  
    {
    private:
        int size; 
        int scale;

    public:
        int getSize()   { return size; }
        int* getSize_ptr()  { return &size; }
        int getScale()  { return scale; }
        int* getScale_ptr()  { return &scale; }
        bool setSize(int new_size);
        bool setScale(int new_scale);

        bool checkSize();
        bool checkScale();

        const int MIN_SIZE = 1;
        const int MAX_SIZE = 100;
        const int MIN_SCALE = 1;
        const int MAX_SCALE = 20;
    };

    class Dispatcher
    {
    private:
        Grid grid;
        int g_size;     // Using only for ImGui    
        int g_scale;    // Using only for ImGui
        
        int w_width;
        int w_height;

        int cell_size;
        int pixel_size;
    public:
        Dispatcher(bool dark_theme = true);
        ~Dispatcher();
        std::vector<Pixel> pixels;  // Saving every pixel (point) to draw
        std::vector<Node2> nodes;   // Saving every node to simplify calcucations

        int getGSize()  { return grid.getSize(); }
        int getGScale() { return grid.getScale(); }

        int getCellSize()   { return cell_size; }
        int getPixelSize()  { return pixel_size; }

        void draw();

        void rebuild();
        // void setWSize(int new_width, int new_height);
    };

}