extern "C" {
    #include "raylib.h"
    #include "raymath.h"
    #include "camera.h"
}

#include "input.hpp"
#include "debug.hpp"
#include "mainMenu.hpp"
#include "projectile.hpp"

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

Projectile* projectiles[25] = {nullptr};
int projectileCount = 0;

bool debug = false;

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
    redCruiser->SetRotation(180.0f);
    redCruiser->IndexShip();

    Destroyer* redDestroyer = new Destroyer(Vector2{300, 800}, 2);
    redDestroyer->SetRotation(180.0f);
    redDestroyer->IndexShip();

    Battleship* redBattleship = new Battleship(Vector2{400, 800}, 2);
    redBattleship->SetRotation(180.0f);
    redBattleship->IndexShip();

    // Carrier* redCarrier = new Carrier(Vector2{500, 800}, 2);
    // redCarrier->SetRotation(180.0f);
    // redCarrier->IndexShip();

    Submarine* redSubmarine = new Submarine(Vector2{600, 800}, 2);
    redSubmarine->SetRotation(180.0f);
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
                        for(int i = 0; i < projectileCount; i++){
                            Projectile* projectile = projectiles[i];
                            if(projectile != nullptr && !projectile->toBeDestroyed){
                                projectile->Update();
                                if(projectile != nullptr && !projectile->toBeDestroyed){
                                    projectile->Draw();
                                    if(projectile != nullptr && projectile->hasHitShip()){
                                        projectile->toBeDestroyed = true;
                                    }
                                }
                            }
                        }
                        for(int i = 0; i < projectileCount; i++){
                            if(projectiles[i] != nullptr && projectiles[i]->toBeDestroyed){
                                projectiles[i]->DestroyProjectiles();
                            }
                        }
                        
                        if(debug) displayShipsOutlines();

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
