#include "battleship.hpp"

Battleship::Battleship(Vector2 position, int team) : Ship(position, team) {
    this->sprite = LoadTexture("assets/gfx/battleship.png");
    this->dimensions = Vector2{this->sprite.width, this->sprite.height};
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
    Vector2 drawPosition = { this->position.x - this->sprite.width / 2, this->position.y - this->sprite.height / 2 };
    DrawTextureEx(this->sprite, drawPosition, this->rotation, 1, WHITE);
}