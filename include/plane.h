#ifndef PLANE_HPP
#define PLANE_HPP

#include <vector>
#include "raylib.h"
#include "ship.h"
#include "carrier.h"

class Squadron; // forward declaration

enum class PlaneType{
    FIGHTER,
    BOMBER,
    DEFAULT
};

class Plane {
public:
    Plane(Vector2 position, int team, Carrier* owner);
    ~Plane();
    virtual bool Update();
    void Move(float deltaTime);
    void Rotate(float deltaTime);
    void DivineWind(); // if you know, you know...
    void Draw();
    bool active = true;
    bool downed = false;

    Ship* GetNearestEnemy();
    Vector2 GetPosition();
    Vector2 GetDimensions();
    float GetRotation();
    Carrier* GetOwner();
    void SetRotation(float rotation);
    void SetPosition(Vector2 position);
    void SetTargetPosition(Vector2 targetPosition);
    void SetSquadron(Squadron* squadron);
    void SetTarget(Ship* target);
    void SetHp(int hp);
    void SetRetreat();
    void SetOneWayTrip();
    int GetHp();
protected:
    Squadron* squadron;
    Texture2D sprite = LoadTexture("assets/gfx/plane.png");
    Vector2 position;
    Vector2 targetPosition;
    Vector2 velocity;
    float rotation;
    int hp = 50;
    int bombCount = 4;
    int damage;
    bool retreat = false; // if true, the plane will return to the carrier
    bool oneWayTrip = false; // if true, the plane will... not be coming back
    Carrier* owner;
    Ship* target;
};

extern std::vector<Plane*> planes; // vector to hold all the planes

#endif // PLANE_HPP