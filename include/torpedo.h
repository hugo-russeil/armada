#ifndef TORPEDO_H
#define TORPEDO_H

#include "projectile.h"

class Torpedo : public Projectile {
public:
    Torpedo(Vector2 position, Vector2 targetPosition, int damage, Ship* owner);
    ~Torpedo();
    bool Update() override;
    void Draw() override;
    bool hasHitShip();
};

#endif // TORPEDO_H