#ifndef DEBUG_H
#define DEBUG_H

class Ship;
class Plane;

extern bool debug;

void toogleDebug();
void displayShipOutlines(Ship* ship);
void displayPlaneOutlines(Plane* plane);

#endif // DEBUG_H