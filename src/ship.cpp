#include "ship.hpp"
#include "camera.h"
#include "raylib.h"
#include "raymath.h"

#include "projectile.hpp"
#include "shell.hpp"

#include "submarine.hpp"

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
    if(!active) return;
    Rotate(GetFrameTime());
    Move(GetFrameTime());
    Ship target = isEnemyNear();
    if(hp <= 0){
        active = false;
    }
}

void Ship::Draw(){
    
}

void Ship::Move(float deltaTime){
    Vector2 direction = Vector2Subtract(targetPosition, position);
    float distance = Vector2Length(direction);

    if(distance > 10.0f){ // 10.0f is the threshold value for the ship to stop moving
        float speed = 10.0f;
        float rotationInRadians = (rotation + 90) * DEG2RAD; // adjust rotation and convert to radians
        velocity.x = cos(rotationInRadians) * speed;
        velocity.y = sin(rotationInRadians) * speed;

        // Update position based on velocity and deltaTime
        position.x += velocity.x * deltaTime;
        position.y += velocity.y * deltaTime;
    }
    else{
        targetPosition = position;
        velocity = {0, 0};
    }
}

void Ship::Rotate(float deltaTime){
    if(position.x != targetPosition.x || position.y != targetPosition.y){
        Vector2 direction = Vector2Subtract(targetPosition, position);
        float targetRotation = atan2(direction.y, direction.x) * RAD2DEG - 90.0f;

        // Normalize targetRotation and rotation to the range of 0 to 360
        targetRotation = fmod(targetRotation + 360.0f, 360.0f);
        rotation = fmod(rotation + 360.0f, 360.0f);

        float rotationSpeed = 20.0f; // in degrees per second
        float difference = targetRotation - rotation;

        // Normalize difference to the range of -180 to 180
        difference = fmod(difference + 540.0f, 360.0f) - 180.0f;

        float step = rotationSpeed * deltaTime;

        if (abs(difference) < step) {
            rotation = targetRotation;
        } else {
            rotation += copysign(step, difference);
        }
    }
}

void Ship::Shoot(Ship* target){
    static int shootCooldown = 0;
    // Shoot deck battery
    if(hasDeckBattery && dynamic_cast<Submarine*>(target) == nullptr){ // A deck battery would be ineffective against a submarine (source : i said so)
        if(shootCooldown > 0){
            shootCooldown--;
            return;
        }
        Shell* shell = new Shell(position, target->position, deckBatteryDamage, this);
        shootCooldown = 100;
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
            if(distance < nearestDistance && ships[i]->active){
                nearestDistance = distance;
                nearestEnemy = ships[i];
            }
        }
    }
    if(nearestDistance < 100){
        Shoot(nearestEnemy);
        return *nearestEnemy;
    }
    else{
        //printf("No enemy is near\n");
        return *this; // return itself if no enemy is near
    }
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

// ========== Setters ==========

void Ship::SetTargetPosition(Vector2 targetPosition){
    this->targetPosition = targetPosition;
}

void Ship::SetRotation(float rotation){
    this->rotation = rotation;
}

void Ship::SetHp(int hp){
    this->hp = hp;
}

// ========== Getters ==========

Vector2 Ship::GetPosition(){
    return position;
}
Vector2 Ship::GetTargetPosition(){
    return targetPosition;
}
Vector2 Ship::GetDimensions(){
    return dimensions;
}

int Ship::GetHp(){
    return hp;
}

int Ship::GetMaxHp(){
    return maxHp;
}

int Ship::GetFuel(){
    return fuel;
}

float Ship::GetRotation(){
    return rotation;
}