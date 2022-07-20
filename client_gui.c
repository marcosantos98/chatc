#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "client.h"

int main(void)
{
    SetTraceLogLevel(LOG_NONE);
    InitWindow(400, 400, "Chatc");

    while (!WindowShouldClose())
    {
        BeginDrawing();
       
        EndDrawing();
    }

    CloseWindow();
}