#include "Camera.h"
#include "InputManager.h"
#include "Geometric.h"
Vec2 Camera::pos = Vec2();
Vec2 Camera::speed = Vec2();
GameObject* Camera::focus = nullptr;
Camera::FASE Camera::fase = Camera::ARVORE;


void Camera::Fallow(GameObject* newFocus) {
    focus = newFocus;
}

void Camera::Unfollow() {
    focus = nullptr;
}

void Camera::Update(float dt) {
    float xMax,xMin;
    float yMax, yMin;
    if(focus != nullptr) {
        float auxX = focus->box.centro().x - 1280 / 2.0f;
        float auxY = focus->box.centro().y - 720 / 2.0f;
        switch (fase){
            case ARVORE:
                xMax = 128;
                xMin = 0;
                yMax = 0;
                yMin = 0;
                break;

            case TRANSICAO:
                xMax = 0;
                xMin = 0;
                yMax = 0;
                yMin = 0;
                break;

            case BONITA:
                xMax = 10000;
                xMin = 0;
                yMax = 0;
                yMin = -1000;
                break;

            case FEIA:
                xMax = 640;
                xMin = 0;
                yMax = 0;
                yMin = 0;
                break;

            case CAVERNA:
                xMax = 1280;
                xMin = 0;
                yMax = -32 * 16;
                yMin = -7008;

                break;

        }
        if(auxX < xMin) {
            auxX = xMin;
        } else if( auxX > xMax) {
            auxX = xMax;
        }
        if(auxY < yMin) {
            auxY = yMin;
        } else if(auxY > yMax){
            auxY = yMax;
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

void Camera::SetFase(FASE fase) {
    Camera::fase = fase;
}
