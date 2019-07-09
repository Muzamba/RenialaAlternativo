#include "CameraFollower.h"
#include "Camera.h"

CameraFollower::CameraFollower(GameObject& go, int x, int y) : Component(go) {
    xTela = x;
    yTela = y;
}

void CameraFollower::Update(float dt) {
    associated.box.pos =  Camera::pos + Vec2(xTela, yTela);
}

void CameraFollower::Render() {
}

bool CameraFollower::Is(std::string type) {
    return type == "CameraFollower";
}

void CameraFollower::SetXY(int x, int y) {
    xTela = x;
    yTela = y;
}
