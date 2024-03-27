#include "debug.hpp"
#include "raylib.h"
#include "raymath.h"
#include "ship.hpp"

void toogleDebug() {
    debug = !debug;
}

void DrawRotatedRectangleLines(Vector2 position, Vector2 dimensions, float rotation, Color color) {
    // Calculate the four corners of the rectangle
    Vector2 corners[4] = {
        { position.x - dimensions.x / 2, position.y - dimensions.y / 2 },
        { position.x + dimensions.x / 2, position.y - dimensions.y / 2 },
        { position.x + dimensions.x / 2, position.y + dimensions.y / 2 },
        { position.x - dimensions.x / 2, position.y + dimensions.y / 2 }
    };

    // Rotate each corner around the center of the rectangle
    for (int i = 0; i < 4; i++) {
        float dx = corners[i].x - position.x;
        float dy = corners[i].y - position.y;
        corners[i].x = dx * cos(rotation) - dy * sin(rotation) + position.x;
        corners[i].y = dx * sin(rotation) + dy * cos(rotation) + position.y;
    }

    // Draw the four sides of the rectangle
    for (int i = 0; i < 4; i++) {
        DrawLineV(corners[i], corners[(i + 1) % 4], color);
    }
}

void displayShipsOutlines(){
    for(int i = 0; i < shipCount; i++){
        DrawRotatedRectangleLines(ships[i]->GetPosition(), ships[i]->GetDimensions(), ships[i]->GetRotation() * DEG2RAD, BLACK);
    }
}