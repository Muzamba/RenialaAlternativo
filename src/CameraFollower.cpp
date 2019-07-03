#include "CameraFollower.h"
#include "Camera.h"

CameraFollower::CameraFollower(GameObject& go) : Component(go) {
}

void CameraFollower::Update(float dt) {
    associated.box.pos =  Camera::pos;
}

void CameraFollower::Render() {
}

bool CameraFollower::Is(std::string type) {
    return type == "CameraFollower";
}