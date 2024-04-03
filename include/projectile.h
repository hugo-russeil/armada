#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "ship.hpp"
#include "raylib.h"
#include <vector>

class Projectile{
    protected:
        Vector2 position;
        Vector2 targetPosition;
        Vector2 velocity;
        int damage;
        Ship* owner;

    public:
        Projectile(Vector2 position, Vector2 targetPosition, int damage, Ship* owner);
        ~Projectile();
        virtual bool Update() = 0; // returns true if the projectile is still active
        virtual void Draw() = 0;
        virtual bool hasHitShip() = 0;
        bool active = true;
};

extern std::vector<Projectile*> projectiles;
extern int projectileCount;

#endif // PROJECTILE_HPP