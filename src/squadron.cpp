#include "squadron.hpp"

Squadron::Squadron(Carrier* carrier) {
    this->carrier = carrier;
    this->target = nullptr;
    // Create 5 planes
    for (int i = 0; i < planeCount; i++) {
        Plane* plane = new Plane(carrier->GetPosition(), carrier->GetTeam(), carrier);
        plane->active = false; // Planes are inactive until deployed
        plane->SetSquadron(this);
        squadronPlanes.push_back(plane);
    }
    carrier->SetSquadron(this);
}

Squadron::~Squadron() {

}

void Squadron::Deploy(Ship* target) {
    if(activePlanes != 0 || deploying) return; // Can't give the order to deploy if already deployed
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
            Plane* plane = squadronPlanes[activePlanes];
            plane->SetTarget(target);
            plane->active = true;
            activePlanes++;
            delay = 40;
        } else {
            deploying = false;
        }
    }
}

void Squadron::setTarget(Ship* target) {
    this->target = target;
}

int Squadron::GetActivePlanes() {
    return activePlanes;
}

void Squadron::SetActivePlanes(int activePlanes) {
    this->activePlanes = activePlanes;
}