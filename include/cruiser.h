#ifndef CRUISER_H
#define CRUISER_H

#include "ship.h"

class Cruiser : public Ship {
    public:
        Cruiser(Vector2 position, int team);
        virtual ~Cruiser();
        void Draw() override;
        std::string GetClass() override;
};

#endif // CRUISER_H