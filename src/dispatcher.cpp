#include <iostream>
#include <vector>

#include "imgui.h"
#include "rlImGui.h"

#include "dispatcher.h"

namespace PerlinUI
{

    // Grid class methods -----------------------------------------------------
    bool Grid::setSize(int new_size)
    {
        if (new_size > 0 && new_size <= MAX_SIZE)
        {
            size = new_size;
            return true;
        }
        std::cerr << "[ERROR] Bad arguments for grid's size. Size > 0 && size <= w_width.\n";
        return false;
    }
    bool Grid::setScale(int new_scale)
    {
        if (new_scale > 0 && new_scale <= MAX_SCALE)
        {
            scale = new_scale;
            return true;
        }
        std::cerr << "[ERROR] Bad arguments for grid's scale. Scale > 0 && scale <= grid's size.\n";
        return false;
    }

    bool Grid::checkSize()
    {
        if (size < MIN_SIZE)
        {
            std::cerr << "[ERROR] Size checked: it's < MIN_SIZE.\n";
            setSize(MIN_SIZE);
            return false;
        }
        if (size > MAX_SIZE)
        {
            std::cerr << "[ERROR] Size checked: it's > MAX_SIZE.\n";
            setSize(MAX_SIZE);
            return false;
        }
        return true;
    }
    bool Grid::checkScale()
    {
        if (scale < MIN_SCALE)
        {
            std::cerr << "[ERROR] Scale checked: it's < MIN_SIZE.\n";
            setScale(MIN_SCALE);
            return false;
        }
        if (scale > MAX_SCALE)
        {
            std::cerr << "[ERROR] Scale checked: it's > MAX_SCALE.\n";
            setScale(MAX_SCALE);
            return false;
        }
        return true;
    }


    // Dispatcher class methods ===============================================
    Dispatcher::Dispatcher(bool dark_theme)
    {
        rlImGuiSetup(dark_theme);

        grid.setSize(5);
        grid.setScale(5);
        g_size = grid.getSize();
        g_scale = grid.getScale();
    }
    Dispatcher::~Dispatcher()
    {
        rlImGuiShutdown();
    }
    
    void Dispatcher::draw()
    {
        rlImGuiBegin();

        // Create a window called "My First Tool", with a menu bar.
        ImGui::Begin("My First Tool", nullptr);
            if (ImGui::BeginMenuBar())
            {
                if (ImGui::BeginMenu("File"))
                {
                    if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
                    if (ImGui::MenuItem("Save", "Ctrl+S"))   { /* Do stuff */ }
                    if (ImGui::MenuItem("Close", "Ctrl+W"))  {  }
                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar();
            }

            // ImGui::Columns(1);
            if (ImGui::ArrowButton("Decrease size", ImGuiDir::ImGuiDir_Left))
            {
                if (grid.setSize(grid.getSize() - 1))
                {
                    g_size = grid.getSize();
                }
                rebuild();
            }
            if (ImGui::ArrowButton("Increase size", ImGuiDir::ImGuiDir_Right))
            {
                if (grid.setSize(grid.getSize() + 1))
                {
                    g_size = grid.getSize();
                }
                rebuild();
            }

            if (ImGui::SliderInt("Size", &g_size, grid.MIN_SIZE, grid.MAX_SIZE))
            {
                grid.setSize(g_size);
                rebuild();
            }
                
            
            if (ImGui::SliderInt("Scale", &g_scale, grid.MIN_SCALE, grid.MAX_SCALE))
            {
                grid.setScale(g_scale);
                rebuild();
            }


        ImGui::End();

        // ImGui::ShowDemoWindow();

        rlImGuiEnd();
    }

    void Dispatcher::rebuild()
    {
        pixels.clear();
        nodes.clear();

        int cell_size = GetRenderWidth() / grid.getSize();
        int pixel_size = cell_size / grid.getScale();
        cell_size = cell_size > 0 ? cell_size : 1;
        pixel_size = pixel_size > 0 ? pixel_size : 1;
        
        for (int x = 0; x <= GetRenderWidth(); x += pixel_size)
        {
            for (int y = 0; y <= GetRenderHeight(); y += pixel_size)
            {
                // Save every point and calculate it's gradient color;
                pixels.push_back({
                    x, y, pixel_size,
                    {
                        (unsigned char) (float(x) / float(GetRenderWidth()) * 255.f),
                        (unsigned char) (float(y) / float(GetRenderHeight()) * 255.f),
                        (unsigned char) (float(x*y) / float(GetRenderWidth()*GetRenderHeight()) * 255.f),
                        255
                    }
                    // {
                    //     (unsigned char) GetRandomValue(0, 255), 
                    //     (unsigned char) GetRandomValue(0, 255),
                    //     (unsigned char) GetRandomValue(0, 255),
                    //      255
                    // }
                });
                // // Save every node in vector<Node2> dispatcher.nodes and calculate it's gradient vector
                if (x % (pixel_size * grid.getScale()) == 0 && y % (pixel_size * grid.getScale()) == 0)
                {
                    Node2 new_node = { x, y };
                    nodes.push_back(new_node);
                }
            }
        }
    }

}