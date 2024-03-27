extern "C" {
    #include "raylib.h"
    #include "raymath.h"
    #include "camera.h"
}

#include "input.hpp"
#include "mainMenu.hpp"

// Include the ship classes
#include "battleship.hpp"
#include "cruiser.hpp"
#include "destroyer.hpp"
#include "submarine.hpp"

#define SEABLUE Color{0, 105, 148, 255}

typedef enum gameStage {
    MAIN_MENU,
    GAMEPLAY,
    GAME_OVER
} GameStage;


GameStage stage = MAIN_MENU;
Camera2D camera;

Ship* ships[10] = {nullptr};
int shipCount = 0;

void DrawRotatedRectangleLines(Vector2 position, Vector2 dimensions, float rotation, Color color) {
    // Calculate the four corners of the rectangle
    Vector2 corners[4] = {
        { position.x - dimensions.x / 2, position.y - dimensions.y / 2 },
        { position.x + dimensions.x / 2, position.y - dimensions.y / 2 },
        { position.x + dimensions.x / 2, position.y + dimensions.y / 2 },
        { position.x - dimensions.x / 2, position.y + dimensions.y / 2 }
    };

    // Rotate each corner around the center of the rectangle
    for (int i = 0; i < 4; i++) {
        float dx = corners[i].x - position.x;
        float dy = corners[i].y - position.y;
        corners[i].x = dx * cos(rotation) - dy * sin(rotation) + position.x;
        corners[i].y = dx * sin(rotation) + dy * cos(rotation) + position.y;
    }

    // Draw the four sides of the rectangle
    for (int i = 0; i < 4; i++) {
        DrawLineV(corners[i], corners[(i + 1) % 4], color);
    }
}

void displayShipsOutlines(){
    for(int i = 0; i < shipCount; i++){
        DrawRotatedRectangleLines(ships[i]->GetPosition(), ships[i]->GetDimensions(), ships[i]->GetRotation() * DEG2RAD, BLACK);
    }
}

int main() {
    const int screenWidth = GetMonitorWidth(0);
    const int screenHeight = GetMonitorHeight(0);

    InitWindow(screenWidth, screenHeight, "Flattops");

    SetTargetFPS(60);

    setupCamera(&camera);

    // Team 1 (Blue)
    Cruiser* blueCruiser = new Cruiser(Vector2{200, 200}, 1);
    blueCruiser->IndexShip();

    Destroyer* blueDestroyer = new Destroyer(Vector2{300, 200}, 1);
    blueDestroyer->IndexShip();

    Battleship* blueBattleship = new Battleship(Vector2{400, 200}, 1);
    blueBattleship->IndexShip();

    // Carrier* blueCarrier = new Carrier(Vector2{500, 200}, 1);
    // blueCarrier->IndexShip();

    Submarine* blueSubmarine = new Submarine(Vector2{600, 200}, 1);
    blueSubmarine->IndexShip();

    // Team 2 (Red)
    Cruiser* redCruiser = new Cruiser(Vector2{200, 800}, 2);
    redCruiser->IndexShip();

    Destroyer* redDestroyer = new Destroyer(Vector2{300, 800}, 2);
    redDestroyer->IndexShip();

    Battleship* redBattleship = new Battleship(Vector2{400, 800}, 2);
    redBattleship->IndexShip();

    // Carrier* redCarrier = new Carrier(Vector2{500, 800}, 2);
    // redCarrier->IndexShip();

    Submarine* redSubmarine = new Submarine(Vector2{600, 800}, 2);
    redSubmarine->IndexShip();

    while (!WindowShouldClose()){
        
        switch (stage) {
            case MAIN_MENU:
                mainMenu();
                if (IsKeyPressed(KEY_ENTER)) stage = GAMEPLAY;
                break;
            case GAMEPLAY:
                BeginDrawing();

                    ClearBackground(SEABLUE);
                    
                    BeginMode2D(camera);

                        for(int i = 0; i < shipCount; i++){
                            ships[i]->Update();
                            ships[i]->Draw();
                        }
                        displayShipsOutlines();

                    EndMode2D();

                EndDrawing();

                handleInput();

                break;
            case GAME_OVER:
                break;
        }
    }

    return 0;
}
