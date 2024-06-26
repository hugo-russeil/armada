#ifndef TASKFORCE_H
#define TASKFORCE_H

#include "ship.h"
#include <vector>

class TaskForce {
    public:
        TaskForce();
        ~TaskForce();

        void addShip(Ship* ship);
        void removeShip(Ship* ship);
        void orderMove(Vector2 target);
        void orderHold();
        std::vector<Ship*>& GetShips();
    private:
        std::vector<Ship*> ships;
};

extern std::vector<TaskForce*> taskForces; // Vector of all task forces
extern TaskForce* selectedTaskForce;

#endif // TASKFORCE_H