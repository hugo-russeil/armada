#ifndef SQUADRON_HPP
#define SQUADRON_HPP

#include "plane.h"
#include "ship.h"
#include "carrier.h"
#include "raylib.h"
#include <vector>

class Squadron {
    public:
        Squadron(Carrier* carrier, PlaneType type);
        ~Squadron();
        void Deploy(Ship* target);
        void Update();
        void setTarget(Ship* target);
        int GetActivePlanes();
        int GetPlaneCount();
        Carrier* GetCarrier();
        void SetActivePlanes(int activePlanes);
        void SetPlaneCount(int planeCount);
        void SetDeploying(bool deploying);
        std::vector<Plane*> GetSquadronPlanes();
    private:
        std::vector<Plane*> squadronPlanes;
        Carrier* carrier;
        Ship* target;
        int planeCount = 5;
        int activePlanes = 0;
        bool deploying = false;
};

extern std::vector<Squadron*> squadrons; // Vector of all squadrons
extern Squadron* selectedSquadron;

#endif // SQUADRON_HPP