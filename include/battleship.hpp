#ifndef BATTLESHIP_HPP
#define BATTLESHIP_HPP

#include "ship.hpp"

class Battleship : public Ship {
public:
    Battleship(Vector2 position, int team);
    ~Battleship();
    void Draw() override;
    std::string GetClass() override;
};

#endif // BATTLESHIP_HPP