#ifndef SUBMARINE_H
#define SUBMARINE_H

#include "ship.h"

class Submarine : public Ship {
public:
    Submarine(Vector2 position, int team);
    ~Submarine();
    void Draw() override;
    std::string GetClass() override;
};

#endif // SUBMARINE_H