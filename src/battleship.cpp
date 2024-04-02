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
    this->maxFuel = 150;

    this->hasDeckBattery = true;
    this->deckBatteryDamage = 20;

    this->hasAAGun = true;
    this->AAGunDamage = 10;

    this->hasTorpedo = false;
    this->torpedoDamage = 0;

    this->hasDepthCharge = false;
    this->depthChargeDamage = 0;
}

Battleship::~Battleship() = default;

void Battleship::Draw() {
    if(!active) return;
    Vector2 drawPosition = this->position;
    Vector2 origin = { static_cast<float>(this->sprite.width) / 2.0f, static_cast<float>(this->sprite.height) / 2.0f };
    Rectangle sourceRec = { 0.0f, 0.0f, (float)this->sprite.width, (float)this->sprite.height };
    Rectangle destRec = { drawPosition.x, drawPosition.y, (float)this->sprite.width, (float)this->sprite.height };
    float rotationInDegrees = this->rotation +180;
    DrawTexturePro(this->sprite, sourceRec, destRec, origin, rotationInDegrees, teamColour);

    if (this == selectedShip) {

        DrawLineV(this->position, this->targetPosition, YELLOW);

        float barWidth = 20.0f; // Set a fixed width for the bars

        // Draw health bar
        float currentHealthWidth = barWidth * (this->hp / this->maxHp);
        Color healthBarColor = RED;
        Color currentHealthColor = GREEN;
        DrawRectangle(drawPosition.x - barWidth/2, drawPosition.y + this->sprite.height - 20, barWidth, 2, healthBarColor);
        DrawRectangle(drawPosition.x - barWidth/2, drawPosition.y + this->sprite.height - 20, currentHealthWidth, 2, currentHealthColor);

        // Draw fuel bar
        float currentFuelWidth = barWidth * (this->fuel / this->maxFuel);
        float lostFuelWidth = barWidth - currentFuelWidth;
        Color fuelBarColor = RED;
        Color currentFuelColor = YELLOW;
        DrawRectangle(drawPosition.x - barWidth/2, drawPosition.y + this->sprite.height - 15, currentFuelWidth, 2, currentFuelColor);
        DrawRectangle(drawPosition.x - barWidth/2 + currentFuelWidth, drawPosition.y + this->sprite.height - 15, lostFuelWidth, 2, fuelBarColor);
    }

    // if is selected or in the multipleSelection vector
    if(this == selectedShip || std::find(multipleSelection.begin(), multipleSelection.end(), this) != multipleSelection.end()){
        displayShipOutlines(this);
    }
}

std::string Battleship::GetClass() {
    return "Battleship";
}
