#ifndef CRUISER_HPP
#define CRUISER_HPP

#include "ship.h"

class Cruiser : public Ship {
    public:
        Cruiser(Vector2 position, int team);
        virtual ~Cruiser();
        void Draw() override;
        std::string GetClass() override;
};

#endif // CRUISER_HPP