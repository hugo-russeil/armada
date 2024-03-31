#include "torpedo.hpp"
#include "camera.h"
#include "raymath.h"

Torpedo::Torpedo(Vector2 position, Vector2 targetPosition, int damage, Ship* owner) : Projectile(position, targetPosition, damage, owner){
    this->position = position;
    this->targetPosition = targetPosition;
    this->damage = damage;
    this->owner = owner;
    projectiles.push_back(this);
}

Torpedo::~Torpedo() {}

bool Torpedo::Update(){
    if(active){
        Vector2 direction = Vector2Subtract(targetPosition, position);
        float distance = Vector2Length(direction);

        if(distance > 2.0f){ // 2.0f is the threshold value for the ship to stop moving
            float speed = 100.0f;
            direction = Vector2Normalize(direction); // normalize the direction vector
            velocity.x = direction.x * speed; // calculate velocity
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
        if(hasHitShip()){
            active = false;
        }
    }
    return active;
}

void Torpedo::Draw(){
    if(active) DrawCircleV(position, 2, BLUE);
}

bool Torpedo::hasHitShip() {
    for(int i = 0; i < 10; i++){
        if(ships[i] != nullptr){
            if(ships[i]->isPointInside(position, camera)){
                if(ships[i] == owner){
                    return false;
                }
                ships[i]->SetHp(ships[i]->GetHp() - damage);
                return true;
            }
        }
    }
    return false;
}
