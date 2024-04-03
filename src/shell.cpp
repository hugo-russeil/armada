#include "shell.h"
#include "camera.h"
#include "submarine.h"
#include "raymath.h"
#include "particleSystem.h"

#include <iostream>

Shell::Shell(Vector2 position, Vector2 targetPosition, int damage, Ship* owner) : Projectile(position, targetPosition, damage, owner){
    this->position = position;
    this->targetPosition = targetPosition;
    this->damage = damage;
    this->owner = owner;
    projectiles.push_back(this);
}

Shell::~Shell() = default;

bool Shell::Update(){
    std::cout << "Shell::Update()" << std::endl;
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
            particleSystem->Explode(position, 10); // Create an explosion at the target position
            active = false;
        }
        if(hasHitShip()){
            particleSystem->Explode(position, 10); // Create an explosion at the target position
            active = false;
        }
    }
    return active;
}

void Shell::Draw(){
    if(active) DrawCircleV(position, 2, RED);
}

bool Shell::hasHitShip(){
    for(int i = 0; i < ships.size(); i++){
        if(ships[i] != nullptr){
            if(dynamic_cast<Submarine*>(ships[i]) == nullptr){ // A shell can't hit a submarine
                if(ships[i]->isPointInside(position, camera)){
                    if(ships[i] == owner){
                        return false;
                    }
                    ships[i]->SetHp(ships[i]->GetHp() - damage);
                    return true;
                }
            }
        }
    }
    return false;
}
