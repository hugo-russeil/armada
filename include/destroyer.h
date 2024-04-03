#ifndef DESTROYER_HPP
#define DESTROYER_HPP

#include "ship.hpp"

class Destroyer : public Ship {
public:
    Destroyer(Vector2 position, int team);
    ~Destroyer();
    void Draw() override;
    std::string GetClass() override;
};

#endif // DESTROYER_HPP