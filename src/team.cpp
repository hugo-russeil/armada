#include "team.hpp"

Team::Team(int teamNumber, bool isPlayer) {
    this->teamNumber = teamNumber;
    this->isPlayer = isPlayer;
}

Team::~Team() {
    for (int i = 0; i < TeamShips.size(); i++) {
        delete TeamShips[i];
    }
}