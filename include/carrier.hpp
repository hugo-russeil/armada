#ifndef CARRIER_HPP
#define CARRIER_HPP

#include "ship.hpp"

class Carrier : public Ship{
    public:
        Carrier(Vector2 position, int team);
        ~Carrier();
        void Draw() override;
        std::string GetClass() override;
};

#endif // CARRIER_HPP