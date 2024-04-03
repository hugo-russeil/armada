extern "C" {
    #include "camera.h"
}

#include "raylib.h"
#include "input.h"
#include "debug.h"
#include "ship.h"
#include "taskForce.h"
#include "squadron.h"
#include <iostream>

Ship* selectedShip = nullptr;
Squadron* selectedSquadron = nullptr;
TaskForce* selectedTaskForce = nullptr;
std::vector<Ship*> multipleSelection = std::vector<Ship*>();

void clearSelection() {
    selectedShip = nullptr;
    selectedSquadron = nullptr;
    selectedTaskForce = nullptr;
    multipleSelection.clear();
}

// Input for the staging phase
void stagingInput() {
    Vector2 mousePosition = GetMousePosition();
    Vector2 worldPoint;
    worldPoint.x = (mousePosition.x - camera.offset.x) / camera.zoom + camera.target.x;
    worldPoint.y = (mousePosition.y - camera.offset.y) / camera.zoom + camera.target.y;

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        selectedShip = nullptr;
        for (int i = 0; i < ships.size(); i++) {
            if (ships[i]->isPointInside(worldPoint, camera)) {
                selectedShip = ships[i];
                std::cout << "Selected ship: " << selectedShip << std::endl;
                break;
            }
        }
    }

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && selectedShip != nullptr) {
        selectedShip->SetPosition(worldPoint);
        selectedShip->SetTargetPosition(worldPoint); // Also setting target position to prevent ships from moving back to their original position
    }

    Vector2 mouseDelta = GetMouseDelta();
    if (IsMouseButtonDown(MOUSE_MIDDLE_BUTTON) || (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))) { // Right click doesn't move the camera if dragging a ship
        camera.target.x -= mouseDelta.x / camera.zoom;
        camera.target.y -= mouseDelta.y / camera.zoom;
    }

    float mouseWheelMove = GetMouseWheelMove();
    float newZoom = camera.zoom + mouseWheelMove * 0.1f;

    // Limit the zoom level to a range between 0.1 and 3.0
    if (newZoom < 0.1f) {
        newZoom = 0.1f;
    } else if (newZoom > 3.0f) {
        newZoom = 3.0f;
    }

    camera.zoom = newZoom;
}

// Input for the main game phase
void handleInput() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if(!IsKeyDown(KEY_LEFT_SHIFT) && !IsKeyDown(KEY_RIGHT_SHIFT)){
            clearSelection();
        }
        Vector2 mousePosition = GetMousePosition();
        Vector2 worldPoint;
        worldPoint.x = (mousePosition.x - camera.offset.x) / camera.zoom + camera.target.x;
        worldPoint.y = (mousePosition.y - camera.offset.y) / camera.zoom + camera.target.y;
        for (int i = 0; i < ships.size(); i++) {
            if (ships[i]->isPointInside(worldPoint, camera)) {
                if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
                    // If Shift is held down, add the ship to the multiple selection
                    if(selectedShip != nullptr){
                        multipleSelection.push_back(selectedShip); // Add the previously selected ship to the multiple selection
                        selectedShip = nullptr;
                    }
                    multipleSelection.push_back(ships[i]);
                    std::cout << "Added ship to multiple selection: " << ships[i] << std::endl;
                } else {
                    // If Shift is not held down, select the ship normally
                    selectedShip = ships[i];
                    std::cout << "Selected ship: " << selectedShip << std::endl;
                }
                break;
            }
        }
    }

    if (IsMouseButtonReleased(MOUSE_RIGHT_BUTTON)) {
        if(selectedShip != nullptr){
            Vector2 mousePosition = GetMousePosition();
            Vector2 worldPoint;
            worldPoint.x = (mousePosition.x - camera.offset.x) / camera.zoom + camera.target.x;
            worldPoint.y = (mousePosition.y - camera.offset.y) / camera.zoom + camera.target.y;
            selectedShip->SetTargetPosition(worldPoint);
        }
        if(selectedSquadron != nullptr){
            Vector2 mousePosition = GetMousePosition();
            Vector2 worldPoint;
            worldPoint.x = (mousePosition.x - camera.offset.x) / camera.zoom + camera.target.x;
            worldPoint.y = (mousePosition.y - camera.offset.y) / camera.zoom + camera.target.y;
            for (int i = 0; i < ships.size(); i++) {
                if (ships[i]->isPointInside(worldPoint, camera) &&
                    ships[i]->GetTeam() != selectedSquadron->GetCarrier()->GetTeam() && // Ignore order to bomb an ally
                    ships[i]->GetHp() > 0 // Ignore order to bomb a sunken ship
                ){
                    Ship* target = ships[i];
                    selectedSquadron->Deploy(target);
                    break;
                }
            }
        }
        if(selectedTaskForce != nullptr){
            Vector2 mousePosition = GetMousePosition();
            Vector2 worldPoint;
            worldPoint.x = (mousePosition.x - camera.offset.x) / camera.zoom + camera.target.x;
            worldPoint.y = (mousePosition.y - camera.offset.y) / camera.zoom + camera.target.y;
            selectedTaskForce->orderMove(worldPoint);
        }
    }

    Vector2 mouseDelta = GetMouseDelta();
    if (IsMouseButtonDown(MOUSE_MIDDLE_BUTTON) || IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
        camera.target.x -= mouseDelta.x / camera.zoom;
        camera.target.y -= mouseDelta.y / camera.zoom;
    }

    float mouseWheelMove = GetMouseWheelMove();
    float newZoom = camera.zoom + mouseWheelMove * 0.1f;

    // Limit the zoom level to a range between 0.1 and 3.0
    if (newZoom < 0.1f) {
        newZoom = 0.1f;
    } else if (newZoom > 3.0f) {
        newZoom = 3.0f;
    }

    camera.zoom = newZoom;

    //========================================| Keyboard shortcuts |========================================//

    if (IsKeyPressed(KEY_GRAVE)) { // ` key (or ² key if you're using an AZERTY keyboard, the key above TAB, left to 1 anyway)
        debug = !debug;
    }

    if (IsKeyPressed(KEY_H)) { // H for "hold"
        if(selectedShip != nullptr){
            selectedShip->SetTargetPosition(selectedShip->GetPosition());
        }
        // If a task force is selected, order all ships to hold position
        else if(selectedTaskForce != nullptr){
            selectedTaskForce->orderHold();
        }
        // If a squadron is selected, order all planes to retreat to their carrier
        else if(selectedSquadron != nullptr){
            selectedSquadron->SetDeploying(false);
            for (int i = 0; i < selectedSquadron->GetSquadronPlanes().size(); i++) {
                if(selectedSquadron->GetSquadronPlanes()[i]->active)
                    selectedSquadron->GetSquadronPlanes()[i]->SetRetreat();
            }
        }
    }

    if (IsKeyPressed(KEY_B)) { // idk why B, it seemed natural to me
        // If a ship is selected, check if it's a carrier and select its squadron
        if(selectedShip != nullptr){
            Carrier* carrier = dynamic_cast<Carrier*>(selectedShip);
            if(carrier != nullptr){
                clearSelection();
                selectedSquadron = carrier->GetSquadron();
                selectedShip = nullptr; // can't have two selected objects at once
            }
        }
        // If a task force is selected, look for a carrier in it and select its squadron
        else if(selectedTaskForce != nullptr){
            for (int i = 0; i < selectedTaskForce->GetShips().size(); i++) {
                Carrier* carrier = dynamic_cast<Carrier*>(selectedTaskForce->GetShips()[i]);
                if(carrier != nullptr){
                    clearSelection();
                    selectedSquadron = carrier->GetSquadron();
                    selectedTaskForce = nullptr;
                    break;
                }
            }
        }
    }

    if (IsKeyPressed(KEY_K)) { // K for "kamikaze"
        // If a squadron is selected, order all planes to go on a one-way trip
        if(selectedSquadron != nullptr){
            for (int i = 0; i < selectedSquadron->GetSquadronPlanes().size(); i++) {
                selectedSquadron->GetSquadronPlanes()[i]->SetOneWayTrip();
            }
        }
    }

    if (IsKeyPressed(KEY_G)) { // G for "group"
        // If multiple ships are selected, create a new task force with them
        if (!multipleSelection.empty()) {
            // Create a new task force with the selected ships
            TaskForce* taskForce = new TaskForce();
            for (int i = 0; i < multipleSelection.size(); i++) {
                taskForce->addShip(multipleSelection[i]);
            }
            // Clear the multiple selection
            multipleSelection.clear();
            selectedTaskForce = taskForce;
        }
    }

    // if a number key is pressed, select the corresponding task force
    int key = GetKeyPressed();
    if (key >= KEY_ONE && key <= KEY_NINE) {
        clearSelection();
        multipleSelection.clear();
        int index = key - KEY_ONE; // Starting from key one as index 0
        if (taskForces.size() > index) {
            selectedTaskForce = taskForces[index];
            std::cout << "Selected task force: " << selectedTaskForce << std::endl;
        }
    }
}
