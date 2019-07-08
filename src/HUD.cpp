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
    for(auto& talisma : talismas) {
        talisma->Update(dt);
    }
}



void HUD::Render() {
    for(auto& talisma : talismas) {
        talisma->Render();
    }
}



bool HUD::Is(std::string type) {
    return type == "HUD";
}

void HUD::AddTalisma(GameObject* talisma) {
    talismas.emplace_back(talisma);
}



