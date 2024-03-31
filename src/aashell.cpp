#include "aaShell.hpp"
#include "camera.h"
#include "plane.hpp"
#include "raymath.h"

#include <iostream>

AAShell::AAShell(Vector2 position, Vector2 targetPosition, int damage, Ship* owner) : Projectile(position, targetPosition, damage, owner){
    this->position = position;
    this->targetPosition = targetPosition;
    this->damage = damage;
    this->owner = owner;
    projectiles.push_back(this);
}

AAShell::~AAShell(){

}

bool AAShell::Update(){
    std::cout << "AAShell::Update()" << std::endl;
    if(active){
        Vector2 direction = Vector2Subtract(targetPosition, position);
        float distance = Vector2Length(direction);

        if(distance > 2.0f){ // 2.0f is the threshold value for the shell to stop moving
            float speed = 100.0f;
            direction = Vector2Normalize(direction);
            velocity.x = direction.x * speed;
            velocity.y = direction.y * speed;

            // Update position based on velocity and deltaTime
            position.x += velocity.x * GetFrameTime();
            position.y += velocity.y * GetFrameTime();
            active = true;
        }
        else{
            targetPosition = position;
            velocity = {0, 0};
            // Projectile has reached its target, it should be deleted
            active = false;
        }
        if(hasHitAircraft()){
            active = false;
        }
    }
    return active;
}

void AAShell::Draw(){
    if(active) DrawCircleV(position, 2, ORANGE);
}

bool AAShell::hasHitShip(){
    return false; // Unless ships can fly, a round fired at the sky is highly unlikely to hit a ship
}

bool AAShell::hasHitAircraft(){
    Vector2 direction = Vector2Subtract(targetPosition, position);
    float distanceToTarget = Vector2Length(direction);

    if(distanceToTarget < 10.0f){ // Check for collisions only when the AAShell is close to its target
        for(int i = 0; i < 10; i++){
            if(planes[i] != nullptr){
                Vector2 directionToPlane = Vector2Subtract(planes[i]->GetPosition(), position);
                float distanceToPlane = Vector2Length(directionToPlane);

                if(distanceToPlane < 10.0f){ // If the AAShell is close enough to the Plane
                    planes[i]->SetHp(planes[i]->GetHp() - damage);
                    return true;
                }
            }
        }
    }
    return false;
}

