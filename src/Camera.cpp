#include "Camera.h"
#include "InputManager.h"
#include "Geometric.h"
Vec2 Camera::pos = Vec2();
Vec2 Camera::speed = Vec2();
GameObject* Camera::focus = nullptr;


void Camera::Fallow(GameObject* newFocus) {
    focus = newFocus;
}

void Camera::Unfollow() {
    focus = nullptr;
}

void Camera::Update(float dt) {

    if(focus != nullptr) {
        float auxX = focus->box.centro().x - 1280 / 2.0f;
        float auxY = focus->box.centro().y - 720 / 2.0f;

        if(auxX < 0) {
            auxX = 0;
        } else if( auxX > 10000) {
            auxX = 10000;
        }
        if(auxY > 0) {
            auxY = 0;
        }
        
        pos.x = auxX;
        pos.y = auxY;

    } else {
        float speedLocal = 100;
        auto& im = InputManager::GetInstance();
        if (im.IsKeyDown(LEFT_ARROW_KEY)) {
            speed.x -= speedLocal;
        }
        if(im.IsKeyDown(RIGHT_ARROW_KEY)) {
            speed.x += speedLocal;
        }
        if (im.IsKeyDown(UP_ARROW_KEY)) {
            speed.y -= speedLocal;
        }
        if (im.IsKeyDown(DOWN_ARROW_KEY)) {
            speed.y += speedLocal;
        }
        pos = pos + (speed * dt);
        speed = speed * 0;
    }
}
