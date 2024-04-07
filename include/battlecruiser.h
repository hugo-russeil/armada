#ifndef BATTLESHIP_HPP
#define BATTLESHIP_HPP

#include "ship.h"

class Battlecruiser : public Ship {
public:
    Battlecruiser(Vector2 position, int team);
    ~Battlecruiser();
    void Draw() override;
    std::string GetClass() override;
};

#endif // BATTLESHIP_HPP