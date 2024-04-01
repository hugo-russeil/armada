#ifndef TEAM_HPP
#define TEAM_HPP

#include <vector>
#include "ship.hpp"

class Team {
public:
    Team(int teamNumber, bool isPlayer);
    ~Team();
    bool isPlayer;
    int teamNumber;
    std::vector<Ship*> TeamShips;
};

#endif // TEAM_HPP