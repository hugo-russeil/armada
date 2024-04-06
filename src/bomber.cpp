#include "bomber.h"
#include "particleSystem.h"
#include "squadron.h"

Bomber::Bomber(Vector2 position, int team, Carrier* owner) : Plane(position, team, owner){

}

Bomber::~Bomber() = default;

bool Bomber::Update(){
    if(downed) return false; // If the plane has been shot down, it should not be updated

    // Check if plane has sunk with its carrier
    if(owner->GetHp() < 1){
        hp = 0;
        active = false;
        downed = true;
        return false;
    }

    if(active){
        
        Rotate(GetFrameTime());
        
        if(!oneWayTrip){
            if(bombCount > 0 && target->GetHp() > 0 && !retreat){
                // If the plane has bombs, set target to the enemy ship
                SetTargetPosition(target->GetPosition());
                // If the plane is close to the target, drop a bomb
                if(Vector2Distance(position, target->GetPosition()) < 2.0f && target->GetHp() > 0){
                    DropBomb(target);
                    SetTargetPosition(owner->GetPosition()); // Immediately assigning a new destination to ensure the plane doesn't stop midair
                }
            } else {
                // If the plane has no bombs left, or no valid target, or has been ordered to retreat, return to the carrier
                if(owner->GetHp() > 0){
                    SetTargetPosition(owner->GetPosition());
                    if(Vector2Distance(position, owner->GetPosition()) < 10){ // The plane has returned to the carrier, stand down
                        squadron->SetActivePlanes(squadron->GetActivePlanes() - 1); // Decrement the active planes counter
                        active = false;
                        retreat = false; // Reset the retreat flag
                        bombCount = 4; // Rearm the plane
                    }
                }
            }
        }else{
            // If the plane has no valid target, it must find another
            if(target->GetHp() < 1){
                Ship* newTarget = GetNearestEnemy();
                if(newTarget != nullptr){
                    SetTarget(newTarget);
                    SetTargetPosition(newTarget->GetPosition());
                }
            }
            
            SetTargetPosition(target->GetPosition());

            if(Vector2Distance(position, target->GetPosition()) < 2 && target->GetHp() > 0){
                DivineWind();
            }
        }

        Move(GetFrameTime());

        if(hp <= 0){
            active = false;
            downed = true;
        }
    }else if (!downed){
        SetPosition(owner->GetPosition()); // Simply ensure the plane stays in its carrier
        SetRotation(owner->GetRotation()); // Ensure the plane is facing the same direction as the carrier
        // Repair the plane ?
    }
    return active;
}

void Bomber::DropBomb(Ship* target){
    if(bombCount > 0){
        bombCount--;
        target->SetHp(target->GetHp() - damage);

        // Add a random offset to the position
        Vector2 explosionPosition = position;
        explosionPosition.x += GetRandomValue(-5, 5);
        explosionPosition.y += GetRandomValue(-5, 5);

        particleSystem->Explode(explosionPosition, 20);
    }
}