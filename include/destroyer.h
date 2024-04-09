#ifndef DESTROYER_H
#define DESTROYER_H

#include "ship.h"

class Destroyer : public Ship {
public:
    Destroyer(Vector2 position, int team);
    ~Destroyer();
    void Draw() override;
    std::string GetClass() override;
};

#endif // DESTROYER_H