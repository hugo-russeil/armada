extern "C" {
    #include "camera.h"
}

#include "raylib.h"
#include "input.hpp"
#include "debug.hpp"
#include "ship.hpp"
#include "taskForce.hpp"
#include "squadron.hpp"
#include <iostream>

Ship* selectedShip = nullptr;
Squadron* selectedSquadron = nullptr;
TaskForce* selectedTaskForce = nullptr;
std::vector<Ship*> multipleSelection = std::vector<Ship*>();

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

    if (IsMouseButtonReleased(MOUSE_RIGHT_BUTTON) && selectedShip != nullptr) {
        selectedShip->SetPosition(worldPoint);
        selectedShip->SetTargetPosition(worldPoint); // Also setting target position to prevent ships from moving back to their original position
        std::cout << "Moved ship to: " << worldPoint.x << ", " << worldPoint.y << std::endl;
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
}

void handleInput() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if(!IsKeyDown(KEY_LEFT_SHIFT) && !IsKeyDown(KEY_RIGHT_SHIFT)){
            selectedShip = nullptr;
            multipleSelection.clear();
            selectedSquadron = nullptr;
            selectedTaskForce = nullptr;
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

    if (IsKeyPressed(KEY_GRAVE)) { // ` key (or ² key if you're using an AZERTY keyboard, the key above TAB, left to 1 anyway)
        debug = !debug;
    }

    if(selectedShip != nullptr){
        if (IsKeyPressed(KEY_H)) { // H for "hold"
            selectedShip->SetTargetPosition(selectedShip->GetPosition());
        }
        Carrier* carrier = dynamic_cast<Carrier*>(selectedShip);
        if(carrier != nullptr){
            if (IsKeyPressed(KEY_B)) { // idk why B, it seemed like a good key
                selectedSquadron = carrier->GetSquadron();
                selectedShip = nullptr; // can't have two selected objects at once
            }
        }         
    }

    if(selectedSquadron != nullptr){
        if (IsKeyPressed(KEY_K)) {
            for (int i = 0; i < selectedSquadron->GetSquadronPlanes().size(); i++) {
                selectedSquadron->GetSquadronPlanes()[i]->SetOneWayTrip();
            }
        }
        if (IsKeyPressed(KEY_H)) { // H for "hold"
            selectedSquadron->SetDeploying(false);
            for (int i = 0; i < selectedSquadron->GetSquadronPlanes().size(); i++) {
                if(selectedSquadron->GetSquadronPlanes()[i]->active)
                    selectedSquadron->GetSquadronPlanes()[i]->SetRetreat();
            }
        }
    }

    if (IsKeyPressed(KEY_G)) {
        if (!multipleSelection.empty()) {
            // Create a new task force with the selected ships
            TaskForce* taskForce = new TaskForce();
            for (int i = 0; i < multipleSelection.size(); i++) {
                taskForce->addShip(multipleSelection[i]);
            }
            printf("Created new task force with %d ships\n", taskForce->ships.size());
            // Clear the multiple selection
            multipleSelection.clear();
            std::cout << "Created new task force: " << taskForce << std::endl;
        }
    }

    // if a number key is pressed, select the corresponding task force
    if (IsKeyPressed(KEY_ONE)) {
        selectedTaskForce = nullptr;
        selectedSquadron = nullptr;
        selectedShip = nullptr;
        multipleSelection.clear();
        if (taskForces.size() > 0) {
            selectedTaskForce = taskForces[0];
            std::cout << "Selected task force: " << selectedTaskForce << std::endl;
        }
    }
    if (IsKeyPressed(KEY_TWO)) {
        selectedTaskForce = nullptr;
        selectedSquadron = nullptr;
        selectedShip = nullptr;
        multipleSelection.clear();
        if (taskForces.size() > 1) {
            selectedTaskForce = taskForces[1];
            std::cout << "Selected task force: " << selectedTaskForce << std::endl;
        }
    }
    if (IsKeyPressed(KEY_THREE)) {
        selectedTaskForce = nullptr;
        selectedSquadron = nullptr;
        selectedShip = nullptr;
        multipleSelection.clear();
        if (taskForces.size() > 2) {
            selectedTaskForce = taskForces[2];
            std::cout << "Selected task force: " << selectedTaskForce << std::endl;
        }
    }
}
