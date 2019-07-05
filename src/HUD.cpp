#include "HUD.h"
#include "Sprite.h"
#include "CameraFollower.h"

HUD::HUD(GameObject& associated) : Component(associated) {

    auto sprite = new Sprite(associated, "assets/img/hud_coletaveis.png");
    sprite->SetScale(2,2); 
    associated.AddComponent(sprite);
    associated.AddComponent(new CameraFollower(associated, 20, 20));
    associated.AddComponent(this);
}



void HUD::Update(float dt) {

}



void HUD::Render() {

}



bool HUD::Is(std::string type) {
    return type == "HUD";
}




