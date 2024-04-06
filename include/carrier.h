#ifndef CARRIER_HPP
#define CARRIER_HPP

#include "ship.h"
#include <vector>

class Squadron;

class Carrier : public Ship{
    public:
        Carrier(Vector2 position, int team);
        ~Carrier();
        void Draw() override;
        std::string GetClass() override;
        std::vector<Squadron*> GetSquadrons();
        void AddSquadron(Squadron* squadron);
    private:
        std::vector<Squadron*> squadrons;
};

#endif // CARRIER_HPP