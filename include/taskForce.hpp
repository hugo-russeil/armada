#ifndef TASKFORCE_HPP
#define TASKFORCE_HPP

#include "ship.hpp"
#include <vector>

class TaskForce {
    public:
        TaskForce();
        ~TaskForce();

        void addShip(Ship* ship);
        void removeShip(Ship* ship);
        void orderMove(Vector2 target);
        std::vector<Ship*> getShips();
    //private:
        std::vector<Ship*> ships;
};

extern std::vector<TaskForce*> taskForces; // Vector of all task forces
extern TaskForce* selectedTaskForce;

#endif // TASKFORCE_HPP