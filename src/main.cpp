#include <sstream>
#include "input.h"
#include "debug.h"
#include "mainMenu.h"
#include "particleSystem.h"
#include "projectile.h"
#include "team.h"
#include "raylib.h"
#include "raymath.h"
#include "camera.h"

// Include the ship classes
#include "carrier.h"
#include "battleship.h"
#include "cruiser.h"
#include "destroyer.h"
#include "submarine.h"

// Include the plane classes
#include "plane.h"
#include "squadron.h"

#define SEABLUE Color{0, 105, 148, 255}

typedef enum gameStage {
    MAIN_MENU,
    STAGING, // Staging phase where players can place their ships
    GAMEPLAY,
    GAME_OVER
} GameStage;


GameStage stage = MAIN_MENU;
Camera2D camera;

ParticleSystem* particleSystem;

bool debug = false;

int main() {
    const int screenWidth = GetMonitorWidth(0);
    const int screenHeight = GetMonitorHeight(0);

    InitWindow(screenWidth, screenHeight, "Navy stuff idk name later");

    SetTargetFPS(60);

    setupCamera(&camera);

    particleSystem = new ParticleSystem();

    // Team 1 (Blue)
    Carrier* blueCarrier = new Carrier(Vector2{200, 200}, 1);

    Battleship* blueBattleship = new Battleship(Vector2{300, 200}, 1);

    Cruiser* blueCruiser1 = new Cruiser(Vector2{400, 200}, 1);

    Cruiser* blueCruiser2 = new Cruiser(Vector2{500, 200}, 1);

    Destroyer* blueDestroyer1 = new Destroyer(Vector2{600, 200}, 1);

    Destroyer* blueDestroyer2 = new Destroyer(Vector2{700, 200}, 1);

    Destroyer* blueDestroyer3 = new Destroyer(Vector2{800, 200}, 1);

    Submarine* blueSubmarine1 = new Submarine(Vector2{900, 200}, 1);

    Submarine* blueSubmarine2 = new Submarine(Vector2{1000, 200}, 1);

    Submarine* blueSubmarine3 = new Submarine(Vector2{1100, 200}, 1);

    // Team 2 (Red)
    Carrier* redCarrier = new Carrier(Vector2{200, 1000}, 2);
    redCarrier->SetRotation(180.0f);

    Battleship* redBattleship = new Battleship(Vector2{300, 1000}, 2);
    redBattleship->SetRotation(180.0f);

    Cruiser* redCruiser1 = new Cruiser(Vector2{400, 1000}, 2);
    redCruiser1->SetRotation(180.0f);

    Cruiser* redCruiser2 = new Cruiser(Vector2{500, 1000}, 2);
    redCruiser2->SetRotation(180.0f);

    Destroyer* redDestroyer1 = new Destroyer(Vector2{600, 1000}, 2);
    redDestroyer1->SetRotation(180.0f);

    Destroyer* redDestroyer2 = new Destroyer(Vector2{700, 1000}, 2);
    redDestroyer2->SetRotation(180.0f);

    Destroyer* redDestroyer3 = new Destroyer(Vector2{800, 1000}, 2);
    redDestroyer3->SetRotation(180.0f);

    Submarine* redSubmarine1 = new Submarine(Vector2{900, 1000}, 2);
    redSubmarine1->SetRotation(180.0f);

    Submarine* redSubmarine2 = new Submarine(Vector2{1000, 1000}, 2);
    redSubmarine2->SetRotation(180.0f);

    Submarine* redSubmarine3 = new Submarine(Vector2{1100, 1000}, 2);
    redSubmarine3->SetRotation(180.0f);

    Squadron* blueSquadron = new Squadron(blueCarrier, PlaneType::BOMBER);
    Squadron* redSquadron = new Squadron(redCarrier, PlaneType::BOMBER);

    std::vector<Ship*>::iterator shipIt;
    std::vector<Projectile*>::iterator it;
    std::vector<Plane*>::iterator planeIt;
    while (!WindowShouldClose()){
        
        switch (stage) {
            case MAIN_MENU:
                mainMenu();
                if (IsKeyPressed(KEY_ENTER)) stage = STAGING;
                break;
            case STAGING:
                stagingInput();

                for(shipIt = ships.begin(); shipIt != ships.end(); shipIt++){
                    (*shipIt)->Update();
                }

                BeginDrawing();
                    ClearBackground(SEABLUE);
                    BeginMode2D(camera);

                        for(shipIt = ships.begin(); shipIt != ships.end(); shipIt++){
                            (*shipIt)->Draw();
                        }
                    EndMode2D();
                EndDrawing();

                if (IsKeyPressed(KEY_ENTER)) stage = GAMEPLAY;
                break;
            case GAMEPLAY:

                handleInput();

                for(shipIt = ships.begin(); shipIt != ships.end(); shipIt++){
                    (*shipIt)->Update();
                }
                for(it = projectiles.begin(); it != projectiles.end();){
                    (*it)->active = (*it)->Update();
                    it++;
                }
                for(planeIt = planes.begin(); planeIt != planes.end(); planeIt++){
                    if(!(*planeIt)->downed) (*planeIt)->Update();
                }

                redSquadron->Update();
                blueSquadron->Update();

                particleSystem->Update();

                BeginDrawing();
                    ClearBackground(SEABLUE);
                    BeginMode2D(camera);

                        for(shipIt = ships.begin(); shipIt != ships.end(); shipIt++){
                            if((*shipIt)->active) (*shipIt)->Draw();
                        }
                        for(it = projectiles.begin(); it != projectiles.end(); ++it){
                            if((*it)->active) (*it)->Draw();
                        }
                        particleSystem->Draw();
                        for(planeIt = planes.begin(); planeIt != planes.end(); ++planeIt){
                            if((*planeIt)->active) (*planeIt)->Draw();
                        }
                        
                        if(debug){
                            for(shipIt = ships.begin(); shipIt != ships.end(); shipIt++){
                                if((*shipIt)->active) displayShipOutlines(*shipIt);
                            }
                            for(planeIt = planes.begin(); planeIt != planes.end(); planeIt++){
                                if((*planeIt)->active) displayPlaneOutlines(*planeIt);
                            }
                            DrawText(("FPS: " + std::to_string(GetFPS())).c_str(), 10, 10, 20, BLACK);
                            DrawText(("Projectiles: " + std::to_string(projectiles.size())).c_str(), 10, 30, 20, BLACK);
                        }

                    EndMode2D();

                    if(selectedShip != nullptr){
                        DrawText(("Selected ship: " + selectedShip->GetClass()).c_str(), 10, 10, 20, BLACK);
                        DrawText(("Fuel: " + std::to_string(selectedShip->GetFuel())).c_str(), 10, 50, 20, BLACK);
                    }
                    if(selectedSquadron != nullptr){
                        DrawText(("Selected" + selectedSquadron->GetType().c_str() + "squadron"), 10, 10, 20, BLACK);
                        DrawText(("Planes: " + std::to_string(selectedSquadron->GetActivePlanes())).c_str(), 10, 30, 20, BLACK);
                    }

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
