#ifndef SHIP_HPP
#define SHIP_HPP

extern "C" {
    #include "raylib.h"
}

class Ship {
    public:
        Ship(Vector2 position, int team);
        virtual ~Ship();
        virtual void IndexShip();
        virtual void Update();
        virtual void Draw();
        virtual void Move();
        virtual void Rotate();
        virtual Ship isEnemyNear(); // returns the nearest enemy ship
        virtual void Shoot(Ship target);

        bool isPointInside(Vector2 point, Camera2D camera);

        void SetTargetPosition(Vector2 targetPosition);

        Vector2 GetPosition();
        Vector2 GetDimensions();
        float GetRotation();
        
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

#endif // SHIP_HPP