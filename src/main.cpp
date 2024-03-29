extern "C" {
    #include "raylib.h"
    #include "raymath.h"
    #include "camera.h"
}

#include <sstream>

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
    Cruiser* redCruiser = new Cruiser(Vector2{200, 400}, 2);
    redCruiser->SetRotation(180.0f);
    redCruiser->IndexShip();

    Destroyer* redDestroyer = new Destroyer(Vector2{300, 400}, 2);
    redDestroyer->SetRotation(180.0f);
    redDestroyer->IndexShip();

    Battleship* redBattleship = new Battleship(Vector2{400, 400}, 2);
    redBattleship->SetRotation(180.0f);
    redBattleship->IndexShip();

    // Carrier* redCarrier = new Carrier(Vector2{500, 400}, 2);
    // redCarrier->SetRotation(180.0f);
    // redCarrier->IndexShip();

    Submarine* redSubmarine = new Submarine(Vector2{600, 400}, 2);
    redSubmarine->SetRotation(180.0f);
    redSubmarine->IndexShip();
    std::vector<Projectile*>::iterator it;
    while (!WindowShouldClose()){
        
        switch (stage) {
            case MAIN_MENU:
                mainMenu();
                if (IsKeyPressed(KEY_ENTER)) stage = GAMEPLAY;
                break;
            case GAMEPLAY:

                handleInput();

                for(int i = 0; i < shipCount; i++){
                    ships[i]->Update();
                }

                for(it = projectiles.begin(); it != projectiles.end();){
                    (*it)->active = (*it)->Update();
                    it++;
                }

                BeginDrawing();
                    ClearBackground(SEABLUE);
                    BeginMode2D(camera);

                        for(int i = 0; i < shipCount; i++){
                            ships[i]->Draw();
                        }
                        for(it = projectiles.begin(); it != projectiles.end(); ++it){
                            if((*it)->active) (*it)->Draw();
                        }
                        
                        if(debug){
                            displayShipsOutlines();
                            DrawText(("FPS: " + std::to_string(GetFPS())).c_str(), 10, 10, 20, BLACK);
                            DrawText(("Projectiles: " + std::to_string(projectiles.size())).c_str(), 10, 30, 20, BLACK);
                        } 

                    EndMode2D();
                EndDrawing();

                break;
            case GAME_OVER:
                break;
        }
        for(it = projectiles.begin(); it != projectiles.end();){
            if(!(*it)->active){
                delete *it;
                it = projectiles.erase(it);
            }
            else{
                it++;
            }
        }
    }

    return 0;
}
