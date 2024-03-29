#include "shell.hpp"
#include "camera.h"
#include "submarine.hpp"

Shell::Shell(Vector2 position, Vector2 targetPosition, int damage, Ship* owner) : Projectile(position, targetPosition, damage, owner){
    this->position = position;
    this->targetPosition = targetPosition;
    this->damage = damage;
    this->owner = owner;
    projectiles.push_back(this);
}

Shell::~Shell(){

}

bool Shell::hasHitShip(){
    for(int i = 0; i < 10; i++){
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
