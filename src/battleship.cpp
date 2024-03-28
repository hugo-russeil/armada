#include "battleship.hpp"

Battleship::Battleship(Vector2 position, int team) : Ship(position, team) {
    this->sprite = LoadTexture("assets/gfx/battleship.png");
    this->dimensions = Vector2{static_cast<float>(this->sprite.width), static_cast<float>(this->sprite.height)};
    this->position = position;
    this->targetPosition = position;
    this->team = team;
    this->velocity = Vector2{0, 0};
    this->rotation = 0;
    this->hp = 200;
    this->maxHp = 200;
    this->fuel = 150;

    this->hasDeckBattery = true;
    this->deckBatteryDamage = 20;

    this->hasAAGun = true;
    this->AAGunDamage = 15;

    this->hasTorpedo = false;
    this->torpedoDamage = 0;

    this->hasDepthCharge = false;
    this->depthChargeDamage = 0;
}

Battleship::~Battleship() {
    
}

void Battleship::Draw() {
    Vector2 drawPosition = this->position;
    Vector2 origin = { static_cast<float>(this->sprite.width) / 2.0f, static_cast<float>(this->sprite.height) / 2.0f };
    Rectangle sourceRec = { 0.0f, 0.0f, (float)this->sprite.width, (float)this->sprite.height };
    Rectangle destRec = { drawPosition.x, drawPosition.y, (float)this->sprite.width, (float)this->sprite.height };
    float rotationInDegrees = this->rotation +180;
    DrawTexturePro(this->sprite, sourceRec, destRec, origin, rotationInDegrees, WHITE);

    if (this == selectedShip) {
        DrawLineV(this->position, this->targetPosition, YELLOW);
    }
}