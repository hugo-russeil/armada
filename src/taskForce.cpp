#include "taskForce.h"
#include <algorithm>

std::vector<TaskForce*> taskForces;

TaskForce::TaskForce() {
    printf ("TaskForce created\n");
    ships = std::vector<Ship*>();
    taskForces.push_back(this);
}

TaskForce::~TaskForce() {
    for (Ship* ship : ships) {
        delete ship;
    }
}

void TaskForce::addShip(Ship* ship) {
    ships.push_back(ship);
}

void TaskForce::removeShip(Ship* ship) {
    ships.erase(std::remove(ships.begin(), ships.end(), ship), ships.end());
}

void TaskForce::orderMove(Vector2 target) {
    if (ships.empty()) {
        return;
    }

    // Calculate the centroid of the positions of all the ships
    Vector2 centroid = {0, 0};
    for (Ship* ship : ships) {
        Vector2 position = ship->GetPosition();
        centroid.x += position.x;
        centroid.y += position.y;
    }
    centroid.x /= ships.size();
    centroid.y /= ships.size();

    // Set the target position for each ship
    for (Ship* ship : ships) {
        Vector2 currentPos = ship->GetPosition();
        Vector2 offset = {currentPos.x - centroid.x, currentPos.y - centroid.y};
        Vector2 newTarget = {target.x + offset.x, target.y + offset.y};
        ship->SetTargetPosition(newTarget);
    }
}

void TaskForce::orderHold() {
    for (Ship* ship : ships) {
        ship->SetTargetPosition(ship->GetPosition());
    }
}

std::vector<Ship*>& TaskForce::GetShips() {
    return ships;
}
