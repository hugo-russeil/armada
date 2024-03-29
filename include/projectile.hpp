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
        bool Update();
        void Draw();
        bool hasHitShip();
        bool active = true;
};

extern std::vector<Projectile*> projectiles;
extern int projectileCount;

#endif // PROJECTILE_HPP