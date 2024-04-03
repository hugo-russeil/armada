#ifndef DEBUG_HPP
#define DEBUG_HPP

class Ship;
class Plane;

extern bool debug;

void toogleDebug();
void displayShipOutlines(Ship* ship);
void displayPlaneOutlines(Plane* plane);

#endif // DEBUG_HPP