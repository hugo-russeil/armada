#include "taskForce.hpp"
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

    // Set the target position for the first ship
    Ship* firstShip = ships[0];
    Vector2 originalPosition = firstShip->GetPosition();
    firstShip->SetTargetPosition(target);

    // Set the target position for the other ships
    for (int i = 1; i < ships.size(); i++) {
        Vector2 currentPos = ships[i]->GetPosition();
        Vector2 offset = {currentPos.x - originalPosition.x, currentPos.y - originalPosition.y};
        Vector2 newTarget = {target.x + offset.x, target.y + offset.y};
        ships[i]->SetTargetPosition(newTarget);
    }
}
