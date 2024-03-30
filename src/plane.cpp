#include "plane.hpp"


#include "camera.h"
#include "raylib.h"
#include "raymath.h"

std::vector<Plane*> planes; // Vector to hold all the planes

Plane::Plane(Vector2 position, int team, Carrier* owner){
    this->position = position;
    this->targetPosition = position;
    this->owner = owner;
    this->damage = 5;
    planes.push_back(this);
}

Plane::~Plane(){

}

bool Plane::Update(){
    if(active){
        
        Rotate(GetFrameTime());

        if(bombCount > 0){
            // If the plane has bombs, set target to the enemy ship
            SetTargetPosition(target->GetPosition());
            // If the plane is close to the target, drop a bomb
            if(Vector2Distance(position, target->GetPosition()) < 10){
                DropBomb(target);
                SetTargetPosition(owner->GetPosition());
            }
        } else {
            // If the plane has no bombs left, return to the carrier
            SetTargetPosition(owner->GetPosition());
            if(Vector2Distance(position, owner->GetPosition()) < 10){ // The plane has returned to the carrier, stand down
                active = false;
            }
        }

        Move(GetFrameTime());

        if(hp <= 0){
            active = false;
        }
    }else{ // Simply ensure the plane stays in its carrier
        SetPosition(owner->GetPosition());
        SetRotation(owner->GetRotation());
    }
    return active;
}

void Plane::Move(float deltaTime){
    Vector2 direction = Vector2Subtract(targetPosition, position);
    float distance = Vector2Length(direction);

    if(distance > 10.0f){ // 10.0f is the threshold value for the plane to stop moving
        float speed = 20.0f; // Twice the speed of the ships, so they cannot flee from the planes forever
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

void Plane::Rotate(float deltaTime){
    if(position.x != targetPosition.x || position.y != targetPosition.y){
        Vector2 direction = Vector2Subtract(targetPosition, position);
        float targetRotation = atan2(direction.y, direction.x) * RAD2DEG - 90.0f;

        // Normalize targetRotation and rotation to the range of 0 to 360
        targetRotation = fmod(targetRotation + 360.0f, 360.0f);
        rotation = fmod(rotation + 360.0f, 360.0f);

        float rotationSpeed = 50.0f; // in degrees per second
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

void Plane::DropBomb(Ship* target){
    if(bombCount > 0){
        bombCount--;
        target->SetHp(target->GetHp() - damage);
    }
}

void Plane::Draw(){
    if(!active) return;
    Vector2 drawPosition = this->position;
    Vector2 origin = { static_cast<float>(this->sprite.width) / 2.0f, static_cast<float>(this->sprite.height) / 2.0f };
    Rectangle sourceRec = { 0.0f, 0.0f, (float)this->sprite.width, (float)this->sprite.height };
    Rectangle destRec = { drawPosition.x, drawPosition.y, (float)this->sprite.width, (float)this->sprite.height };
    float rotationInDegrees = this->rotation +180;
    DrawTexturePro(this->sprite, sourceRec, destRec, origin, rotationInDegrees, WHITE);
}

Vector2 Plane::GetPosition(){
    return position;
}


Vector2 Plane::GetDimensions(){
    return { static_cast<float>(sprite.width), static_cast<float>(sprite.height) };
}
float Plane::GetRotation(){
    return rotation;
}

void Plane::SetPosition(Vector2 position){
    this->position = position;
}

void Plane::SetRotation(float rotation){
    this->rotation = rotation;
}

void Plane::SetTargetPosition(Vector2 targetPosition){
    this->targetPosition = targetPosition;
}

void Plane::SetTarget(Ship* target){
    this->target = target;
}