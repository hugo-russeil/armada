#ifndef SQUADRON_HPP
#define SQUADRON_HPP

#include "plane.hpp"
#include "ship.hpp"
#include "carrier.hpp"
#include "raylib.h"
#include <vector>

class Squadron {
    public:
        Squadron(Carrier* carrier);
        ~Squadron();
        void Deploy(Ship* target);
        void Update();
        void setTarget(Ship* target);
    private:
        std::vector<Plane*> squadronPlanes;
        Carrier* carrier;
        Ship* target;
        int planeCount = 5;
        int activePlanes = 0;
        bool deploying = false;
};

#endif // SQUADRON_HPP