#include "plane.h"
#include "camera.h"
#include "particleSystem.h"
#include "squadron.h"

std::vector<Plane*> planes; // Vector to hold all the planes

Plane::Plane(Vector2 position, int team, Carrier* owner){
    this->position = position;
    this->targetPosition = position;
    this->owner = owner;
    this->damage = 5;
    planes.push_back(this);
}

Plane::~Plane() = default;

bool Plane::Update(){
    return active;
}

void Plane::Move(float deltaTime){
    if(!active || downed) return;
    Vector2 direction = Vector2Subtract(targetPosition, position);
    float distance = Vector2Length(direction);

    if(distance > 2.0f){ // 5.0f is the threshold value for the plane to stop moving
        float speed = 30.0f;
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
    if(!active || downed) return;
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

void Plane::DivineWind(){
    target->SetHp(target->GetHp() - 50);
    hp = 0;
    active = false;
    downed = true;
    particleSystem->Explode(position, 50);
}

void Plane::Draw(){
    if(!active || downed) return;
    Vector2 drawPosition = this->position;
    Vector2 origin = { static_cast<float>(this->sprite.width) / 2.0f, static_cast<float>(this->sprite.height) / 2.0f };
    Rectangle sourceRec = { 0.0f, 0.0f, (float)this->sprite.width, (float)this->sprite.height };
    Rectangle destRec = { drawPosition.x, drawPosition.y, (float)this->sprite.width, (float)this->sprite.height };
    float rotationInDegrees = this->rotation +180;
    DrawTexturePro(this->sprite, sourceRec, destRec, origin, rotationInDegrees, owner->GetTeamColour());
}

Ship* Plane::GetNearestEnemy(){
    Ship* nearestEnemy = nullptr;
    float nearestDistance = 9999999.0f;
    for(Ship* ship : ships){
        if(ship->GetTeam() != owner->GetTeam() && ship->GetHp() > 0){
            float distance = Vector2Distance(position, ship->GetPosition());
            if(distance < nearestDistance){
                nearestDistance = distance;
                nearestEnemy = ship;
            }
        }
    }
    return nearestEnemy;
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

Carrier* Plane::GetOwner(){
    return owner;
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

void Plane::SetSquadron(Squadron* squadron){
    this->squadron = squadron;
}

void Plane::SetTarget(Ship* target){
    this->target = target;
}

void Plane::SetHp(int hp){
    this->hp = hp;
}

void Plane::SetRetreat(){
    this->oneWayTrip = false;
    this->retreat = !retreat;
}

void Plane::SetOneWayTrip(){
    this->retreat = false;
    this->oneWayTrip = !oneWayTrip;
}

int Plane::GetHp(){
    return hp;
}
