#ifndef BATTLECRUISER_H
#define BATTLECRUISER_H

#include "ship.h"

class Battlecruiser : public Ship {
public:
    Battlecruiser(Vector2 position, int team);
    ~Battlecruiser();
    void Draw() override;
    std::string GetClass() override;
};

#endif // BATTLECRUISER_H