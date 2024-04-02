#include "projectile.hpp"
#include "raymath.h"
#include "camera.h"
#include "ship.hpp"

std::vector<Projectile*> projectiles; // Vector to hold all the projectiles

Projectile::Projectile(Vector2 position, Vector2 targetPosition, int damage, Ship* owner){
    this->position = position;
    this->targetPosition = targetPosition;
    this->damage = damage;
    this->owner = owner;
}

Projectile::~Projectile() = default;

