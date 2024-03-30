#ifndef CARRIER_HPP
#define CARRIER_HPP

#include "ship.hpp"

class Squadron;

class Carrier : public Ship{
    public:
        Carrier(Vector2 position, int team);
        ~Carrier();
        void Draw() override;
        std::string GetClass() override;
        Squadron* GetSquadron();
        void SetSquadron(Squadron* squadron);
    private:
        Squadron* squadron;
};

#endif // CARRIER_HPP