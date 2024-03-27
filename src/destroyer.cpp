#include "destroyer.hpp"

Destroyer::Destroyer(Vector2 position, int team) : Ship(position, team) {
    this->sprite = LoadTexture("assets/gfx/destroyer.png");
    this->dimensions = Vector2{this->sprite.width, this->sprite.height};
    this->position = position;
    this->targetPosition = position;
    this->velocity = Vector2{0, 0};
    this->rotation = 0;
    this->hp = 100;
    this->maxHp = 100;
    this->fuel = 100;

    this->hasDeckBattery = true;
    this->deckBatteryDamage = 10;

    this->hasAAGun = true;
    this->AAGunDamage = 10;

    this->hasTorpedo = true;
    this->torpedoDamage = 15;

    this->hasDepthCharge = true;
    this->depthChargeDamage = 15;
}

Destroyer::~Destroyer() {
    
}

void Destroyer::Draw() {
    Vector2 drawPosition = this->position;
    Vector2 origin = { this->sprite.width / 2, this->sprite.height / 2 };
    Rectangle sourceRec = { 0.0f, 0.0f, (float)this->sprite.width, (float)this->sprite.height };
    Rectangle destRec = { drawPosition.x, drawPosition.y, (float)this->sprite.width, (float)this->sprite.height };
    float rotationInDegrees = this->rotation +180;
    DrawTexturePro(this->sprite, sourceRec, destRec, origin, rotationInDegrees, WHITE);
}