#ifndef SUBMARINE_HPP
#define SUBMARINE_HPP

#include "ship.hpp"

class Submarine : public Ship {
public:
    Submarine(Vector2 position, int team);
    ~Submarine();
    void Draw() override;
};

#endif // SUBMARINE_HPP