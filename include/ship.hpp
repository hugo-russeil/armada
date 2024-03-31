#ifndef SHIP_HPP
#define SHIP_HPP

#include <string>
#include "raylib.h"

class Plane; // forward declaration

class Ship {
    public:
        Ship(Vector2 position, int team);
        virtual ~Ship();
        virtual void IndexShip();
        virtual void Update();
        virtual void Draw();
        virtual void Move(float deltaTime);
        virtual void Rotate(float deltaTime);
        virtual Ship* isEnemyNear(); // returns the nearest enemy ship
        virtual Plane* isEnemyPlaneNear(); // returns the nearest enemy plane
        virtual void Shoot(Ship* target, Plane* airTarget);

        bool isPointInside(Vector2 point, Camera2D camera);

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
        virtual std::string GetClass();
        bool active = true;
        
    protected:
        Texture2D sprite;
        int team; 
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

        bool hasAAGun;
        int AAGunDamage;

        bool hasTorpedo;
        int torpedoDamage;

        bool hasDepthCharge;
        int depthChargeDamage;
};

extern Ship* ships[10];
extern int shipCount;
extern Ship* selectedShip;

#endif // SHIP_HPP