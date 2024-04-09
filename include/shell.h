#ifndef SHELL_H
#define SHELL_H

#include "projectile.h"

class Shell : public Projectile{
    public:
        Shell(Vector2 position, Vector2 targetPosition, int damage, Ship* owner);
        ~Shell();
        bool Update() override;
        void Draw() override;
        bool hasHitShip() override;
};

#endif // SHELL_H