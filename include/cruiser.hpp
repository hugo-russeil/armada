#ifndef CRUISER_HPP
#define CRUISER_HPP

#include "ship.hpp"

class Cruiser : public Ship {
    public:
        Cruiser(Vector2 position, int team);
        virtual ~Cruiser();
        void Draw() override;
};

#endif // CRUISER_HPP