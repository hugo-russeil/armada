#ifndef PLANES_HPP
#define PLANES_HPP

#include <vector>
#include "raylib.h"
#include "ship.hpp"
#include "carrier.hpp"

class Squadron; // forward declaration

class Plane {
public:
    Plane(Vector2 position, int team, Carrier* owner);
    ~Plane();
    bool Update();
    void Move(float deltaTime);
    void Rotate(float deltaTime);
    void DropBomb(Ship* target);
    void Draw();
    bool active = true;

    Vector2 GetPosition();
    Vector2 GetDimensions();
    float GetRotation();
    void SetRotation(float rotation);
    void SetPosition(Vector2 position);
    void SetTargetPosition(Vector2 targetPosition);
    void SetSquadron(Squadron* squadron);
    void SetTarget(Ship* target);
private:
    Squadron* squadron;
    Texture2D sprite = LoadTexture("assets/gfx/plane.png");
    Vector2 position;
    Vector2 targetPosition;
    Vector2 velocity;
    float rotation;
    int hp = 50;
    int bombCount = 4;
    int damage;
    Carrier* owner;
    Ship* target;
};

extern std::vector<Plane*> planes; // vector to hold all the planes

#endif // PLANES_HPP