#include "ship.hpp"
#include "camera.h"
#include "raylib.h"
#include "raymath.h"

#include <iostream>

Ship::Ship(Vector2 position, int team) {
    this->position = position;
    this->targetPosition = position;
    this->team = team;
}

Ship::~Ship() {

}

void Ship::IndexShip(){ // add this ship to the ships array
    for(int i = 0; i < 10; i++){
        if(ships[i] == nullptr){
            ships[i] = this;
            break;
        }
    }
    shipCount++;
}

void Ship::Update(){
    Move();
    Rotate();
}

void Ship::Draw(){
    if(team == 1){
        DrawRectangle(position.x, position.y, 50, 50, BLUE);
    }
    else{
        DrawRectangle(position.x, position.y, 50, 50, RED);
    }
    //DrawTexture(texture, position.x, position.y, WHITE);
}

void Ship::SetTargetPosition(Vector2 targetPosition){
            this->targetPosition = targetPosition;
}


void Ship::Move(){
    Vector2 direction = Vector2Subtract(targetPosition, position);
    float distance = Vector2Length(direction);

    if(distance > 10.0f){ // 10.0f is the threshold value for the ship to stop moving
        direction = Vector2Normalize(direction);
        velocity = Vector2Scale(direction, 5);
        position = Vector2Add(position, velocity);
    }
    else{
        position = targetPosition;
        velocity = {0, 0};
    }
}

void Ship::Rotate(){
    if(position.x != targetPosition.x || position.y != targetPosition.y){
        Vector2 direction = Vector2Subtract(targetPosition, position);
        rotation = (atan2(direction.y, direction.x) * RAD2DEG) - 90.0f;
    }
}

void Ship::Shoot(Ship target){
    // Shoot deck battery
    if(hasDeckBattery){
        // Shoot deck battery
    }

    // Shoot AA gun
    if(hasAAGun){
        // Shoot AA gun
    }

    // Shoot torpedo
    if(hasTorpedo){
        // Shoot torpedo
    }

    // Shoot depth charge
    if(hasDepthCharge){
        // Shoot depth charge
    }
}

Ship Ship::isEnemyNear(){
    Ship* nearestEnemy = nullptr;
    float nearestDistance = 1000000.0f;

    for(int i = 0; i < 10; i++){
        if(ships[i] != nullptr && ships[i]->team != team){
            float distance = Vector2Distance(position, ships[i]->position);
            if(distance < nearestDistance){
                nearestDistance = distance;
                nearestEnemy = ships[i];
            }
        }
    }

    return *nearestEnemy;
}

bool Ship::isPointInside(Vector2 point, Camera2D camera) {
    // Translate point back to origin
    point.x -= position.x;
    point.y -= position.y;

    // Rotate point
    float tempX = point.x * cos(rotation) + point.y * sin(rotation);
    float tempY = -point.x * sin(rotation) + point.y * cos(rotation);

    // Translate point back
    point.x = tempX + position.x;
    point.y = tempY + position.y;

    // Adjust rectangle position and dimensions
    Vector2 recPosition = {position.x - dimensions.x / 2, position.y - dimensions.y / 2};

    // Check collision
    return CheckCollisionPointRec(point, Rectangle{recPosition.x, recPosition.y, dimensions.x, dimensions.y});
}

Vector2 Ship::GetPosition(){
    return position;
}
Vector2 Ship::GetDimensions(){
    return dimensions;
}

float Ship::GetRotation(){
    return rotation;
}