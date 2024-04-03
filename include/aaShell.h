#ifndef AA_SHELL_HPP
#define AA_SHELL_HPP

#include "projectile.h"

class AAShell : public Projectile{
    public:
        AAShell(Vector2 position, Vector2 targetPosition, int damage, Ship* owner);
        ~AAShell();
        bool Update() override;
        void Draw() override;
        bool hasHitShip() override; // will always return false as AA Shell is not meant to hit ships
        bool hasHitAircraft();
};

#endif // AA_SHELL_HPP