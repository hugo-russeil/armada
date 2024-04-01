extern "C" {
    #include "camera.h"
}

#include "raylib.h"
#include "input.hpp"
#include "debug.hpp"
#include "ship.hpp"
#include "squadron.hpp"
#include <iostream>

Ship* selectedShip = nullptr;
Squadron* selectedSquadron = nullptr;

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
        selectedShip = nullptr;
        selectedSquadron = nullptr;
        Vector2 mousePosition = GetMousePosition();
        Vector2 worldPoint;
        worldPoint.x = (mousePosition.x - camera.offset.x) / camera.zoom + camera.target.x;
        worldPoint.y = (mousePosition.y - camera.offset.y) / camera.zoom + camera.target.y;
        for (int i = 0; i < ships.size(); i++) {
            if (ships[i]->isPointInside(worldPoint, camera)) {
                selectedShip = ships[i];
                std::cout << "Selected ship: " << selectedShip << std::endl;
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
}
