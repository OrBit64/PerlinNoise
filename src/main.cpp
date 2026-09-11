#include <iostream>
#include <raylib.h>

int main()
{
    const int screenWidth = 1200;
    const int screenHeight = 900;
    const char* screenTitle = "Test. Future Perlin noise!";
    InitWindow(screenWidth, screenHeight, screenTitle);
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {

        BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawText("Hello! It's Raylib. I'm waiting for Perlin noise! Nigga sisi.",
                10, screenHeight/2, 40, BLUE);
            
            DrawCircle(100, 700, 30, RED);
            DrawCircle(100, 760, 30, RED);
            DrawRectangle(100, 700, 400, 60, RED);
            DrawCircle(500, 730, 30, RED);
            DrawRectangle(480, 727, 50, 5, BLACK);
            DrawText("Hello Dima. It was pretty hard to draw\nthis cock. I hope you'll love it.",
                120, 710, 20, BLACK);

        EndDrawing();
    }
    CloseWindow();

    return 0;
}