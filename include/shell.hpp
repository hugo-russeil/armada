#ifndef SHELL_HPP
#define SHELL_HPP

#include "projectile.hpp"

class Shell : public Projectile{
    public:
        Shell(Vector2 position, Vector2 targetPosition, int damage, Ship* owner);
        ~Shell();
        bool hasHitShip();
};

#endif // SHELL_HPP