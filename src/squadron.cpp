#include "squadron.hpp"

Squadron::Squadron(Carrier* carrier) {
    this->carrier = carrier;
    this->target = nullptr;
}

Squadron::~Squadron() {

}

void Squadron::Deploy(Ship* target) {
    this->target = target;
    deploying = true;
}

void Squadron::Update() {
    static int delay = 0;
    if (deploying) {
        if (delay > 0) {
            delay--;
            return;
        }
        if (activePlanes < planeCount) {
            Plane* plane = new Plane(carrier->GetPosition(), carrier->GetTeam(), carrier);
            plane->SetTarget(target);
            squadronPlanes.push_back(plane);
            planes.push_back(plane);
            activePlanes++;
            delay = 100;
        } else {
            deploying = false;
        }
    }
}

void Squadron::setTarget(Ship* target) {
    this->target = target;
}