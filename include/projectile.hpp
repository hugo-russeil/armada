#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "ship.hpp"
#include "raylib.h"

class Projectile{
    protected:
        Vector2 position;
        Vector2 targetPosition;
        Vector2 velocity;
        int damage;
        Ship* owner;

    public:
        bool toBeDestroyed = false;
        Projectile(Vector2 position, Vector2 targetPosition, int damage, Ship* owner);
        ~Projectile();
        void Update();
        void Draw();
        bool hasHitShip();
        void DestroyProjectiles();
};

extern Projectile* projectiles[25];
extern int projectileCount;

#endif // PROJECTILE_HPP