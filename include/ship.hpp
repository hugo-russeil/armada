#ifndef SHIP_HPP
#define SHIP_HPP

#include <string>
#include <vector>
#include "raylib.h"

class Plane; // forward declaration

class Ship {
    public:
        Ship(Vector2 position, int team);
        virtual ~Ship();
        virtual void Update();
        virtual void Draw();
        virtual void Move(float deltaTime);
        virtual void Rotate(float deltaTime);
        virtual Ship* isEnemyNear(); // returns the nearest enemy ship
        virtual Plane* isEnemyPlaneNear(); // returns the nearest enemy plane
        virtual void Shoot(Ship* target, Plane* airTarget);

        bool isPointInside(Vector2 point, Camera2D camera);

        void SetPosition(Vector2 position);
        void SetTargetPosition(Vector2 targetPosition);
        void SetRotation(float rotation);
        void SetHp(int hp);

        Vector2 GetPosition();
        Vector2 GetTargetPosition();
        Vector2 GetDimensions();
        int GetHp();
        int GetMaxHp();
        int GetFuel();
        float GetRotation();
        int GetTeam();
        Color GetTeamColour();
        virtual std::string GetClass();
        bool active = true;
        
    protected:
        Texture2D sprite;
        int team;
        Color teamColour;
        Vector2 dimensions;
        Vector2 position;
        Vector2 targetPosition;
        Vector2 velocity;
        float rotation;
        int hp;
        int maxHp;
        int fuel;
        int maxFuel;

        bool hasDeckBattery;
        int deckBatteryDamage;
        int batteryCooldown = 0;

        bool hasAAGun;
        int AAGunDamage;
        int AAGunCooldown = 0;

        bool hasTorpedo;
        int torpedoDamage;
        int torpedoCooldown = 0;

        bool hasDepthCharge;
        int depthChargeDamage;
};

extern std::vector<Ship*> ships; // vector to hold all the ships
extern Ship* selectedShip;

#endif // SHIP_HPP