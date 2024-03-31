extern "C" {
    #include "camera.h"
}

void setupCamera(Camera2D* camera){
    int screenWidth = GetMonitorWidth(0);
    int screenHeight = GetMonitorHeight(0);

    camera->target = (Vector2){ 0.0f, 0.0f };
    camera->offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera->rotation = 0.0f;
    camera->zoom = 1.0f;
}
