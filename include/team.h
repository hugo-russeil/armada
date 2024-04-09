#ifndef TEAM_H
#define TEAM_H

#include <vector>
#include "ship.h"

class Team {
public:
    Team(int teamNumber, bool isPlayer);
    ~Team();
    bool isPlayer;
    int teamNumber;
    std::vector<Ship*> TeamShips;
};

#endif // TEAM_H