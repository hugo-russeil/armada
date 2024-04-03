#include "mainMenu.h"

extern "C" {
    #include "raylib.h"
}

void mainMenu() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Main Menu", 20, 20, 40, DARKGRAY);
    EndDrawing();
}
    