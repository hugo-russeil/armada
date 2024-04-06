#ifndef BOBMER_HPP
#define BOMBER_HPP

#include "plane.h"

class Bomber : public Plane {
public:
    Bomber(Vector2 position, int team, Carrier* owner);
    ~Bomber();
    bool Update() override;
    void DropBomb(Ship* target);
};

#endif //BOMBER_HPP