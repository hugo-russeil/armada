#include "projectile.hpp"
#include "raymath.h"
#include "camera.h"
#include "ship.hpp"

Projectile::Projectile(Vector2 position, Vector2 targetPosition, int damage, Ship* owner){
    this->position = position;
    this->targetPosition = targetPosition;
    this->damage = damage;
    this->owner = owner;
    for(int i = 0; i < projectileCount; i++){
        if(projectiles[i] == nullptr){
            projectiles[i] = this;
            break;
        }
    }
    projectileCount++;
}

Projectile::~Projectile(){

}

void Projectile::Update(){
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
    }
    else{
        targetPosition = position;
        velocity = {0, 0};
        // Projectile has reached its target, it should be deleted
        toBeDestroyed = true;
    }
}

void Projectile::Draw(){
    DrawCircleV(position, 2, RED);
}

bool Projectile::hasHitShip(){
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

void Projectile::DestroyProjectiles() {
    int j = 0;
    for(int i = 0; i < projectileCount; i++){
        if(projectiles[i] != nullptr){
            if(projectiles[i]->toBeDestroyed){
                
                delete projectiles[i];
                projectiles[i] = nullptr;
            }
            
            else {
            if(i != j) {
                projectiles[j] = projectiles[i];
            }
            j++;
        }
        }
    }
    projectileCount = j;
}
