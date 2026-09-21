#include <iostream>

#include "window.h"

int main()
{
    namespace UI = PerlinUI;

    UI::Window window(800, 800, "Test. Future Perlin noise!", 240);
    window.update();

    return 0;
}
