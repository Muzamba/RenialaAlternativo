#include "HUD.h"
#include "Sprite.h"
#include "CameraFollower.h"
#include "Game.h"
#include "Wisp.h"
#include "Talisma.h"

HUD::HUD(GameObject& associated) : Component(associated) {

    hud = new GameObject();
    auto sprite = new Sprite(*hud, "assets/img/hud_coletaveis.png");
    sprite->SetScale(2,2);
    sprite->SetCamMulti({0,0});
    hud->AddComponent(sprite);
    hud->box.pos = {20,20};
    //hud->AddComponent(new CameraFollower(associated, 20, 20));
    associated.AddComponent(this);
}

HUD::~HUD(){
    delete hud;
}


void HUD::Update(float dt) {
    hud->Update(dt);
    for(auto& talisma : talismas) {
        talisma->Update(dt);
    }
}



void HUD::Render() {
    if(!Game::GetInstance().playerStatus.criarVariaveis) {
        if(((Wisp*)Game::GetInstance().playerStatus.wisp->GetComponent("Wisp"))->fase2){
            for(auto& talisma : talismas) {
                if(!((Talisma*)talisma->GetComponent("Talisma"))->coletado && !((Talisma*)talisma->GetComponent("Talisma"))->animacao) {
                    talisma->Render();
                }
            }
            Game::GetInstance().playerStatus.player->Render();
            Game::GetInstance().playerStatus.wisp->Render();
            hud->Render();
            for(auto& talisma : talismas) {
                if(((Talisma*)talisma->GetComponent("Talisma"))->coletado || ((Talisma*)talisma->GetComponent("Talisma"))->animacao) {
                    talisma->Render();
                }
            }
        } else {
            hud->Render();
            for(auto& talisma : talismas) {
                talisma->Render();
            }
        }
    } else {
        hud->Render();
        for(auto& talisma : talismas) {
            talisma->Render();
        }
    }
}



bool HUD::Is(std::string type) {
    return type == "HUD";
}

void HUD::AddTalisma(GameObject* talisma) {
    talismas.emplace_back(talisma);
}

int HUD::faltaQuantos() {
    int contador = 0;
    for(auto& obj : talismas){
        if(((Talisma*)obj->GetComponent("Talisma"))->coletado) {
            contador++;
        }


    }
    return contador;
}



