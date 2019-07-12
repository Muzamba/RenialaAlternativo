#include "Wisp.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Collider.h"
#include "Game.h"
#include "Dialogo.h"

Wisp::Wisp(GameObject& associated, std::weak_ptr<GameObject> player, bool fase2) : Component(associated) {
    associated.AddComponent(this);
    auto sprite = new Sprite(associated, "assets/img/brilho_amigo.png");//.png", 0, 0, 0.1f, 6);
    ////sprite->SetAlphaChannel(100);
    sprite->SetScale(1.1f, 1.1f);
    associated.AddComponent(sprite);
    luz = new GameObject();
    auto sp2 = new Sprite(*luz, "assets/img/BlackWithHole.png");
    sp2->SetScale(1.5,1.5);
    luz->AddComponent(sp2);
//
    associated.box.pos = {player.lock()->box.centro().x - associated.box.size.x/2, - associated.box.size.y};
    this->player = player;
    posRel = {-20.0f,-20.0f};
    this->fase2 = fase2;
    animacao = true;
}

void Wisp::Update(float dt) {
    auto goP = player.lock();
    if(animacao) {
        auto posDest = ((Collider*)goP->GetComponent("Collider"))->box.pos - Vec2(20,20);
        Vec2 dir = {posDest.x - associated.box.centro().x, posDest.y - associated.box.centro().y};
        static bool first = true;
        static float velo = 0;
        if(first) {
            velo = dir.magnitude()/2.0f;
            first = false;
        }  
        dir = dir.normalizado();
        auto opa = dir * velo * dt;
        if( sqrt(pow(abs(associated.box.centro().x - posDest.x),2) + pow(abs(associated.box.centro().y - posDest.y),2)) > opa.magnitude()) {
             associated.box.mudaCentro(associated.box.centro() + opa);
        } else {
            associated.box.mudaCentro(posDest);
            animacao = false;
            ((Dialogo*)Game::GetInstance().playerStatus.dialogo->GetComponent("Dialogo"))->Begin("Ei espera ai!!! Vou te ajudar a encontrar os talismas", "wisp");
        }
        
    } else {
        auto& im = InputManager::GetInstance();
        float velo = 100;
        float range = 100;
        float aux;

        if(im.IsKeyDown(LEFT_ARROW_KEY)) {
            aux = posRel.x - velo * dt;
            if(sqrt(pow(aux,2)+pow(posRel.y,2)) < range) {
                posRel.x = aux;
            }
        }

        if(im.IsKeyDown(RIGHT_ARROW_KEY)) {
            aux = posRel.x + velo * dt;
            if(sqrt(pow(aux,2)+pow(posRel.y,2)) < range) {
                posRel.x = aux;
            }
        }

        if(im.IsKeyDown(UP_ARROW_KEY)) {
            aux = posRel.y - velo * dt;
            if(sqrt(pow(posRel.x,2)+pow(aux,2)) < range) {
                posRel.y = aux;
            }
        }

        if(im.IsKeyDown(DOWN_ARROW_KEY)) {
            aux = posRel.y + velo * dt;
            if(sqrt(pow(posRel.x,2)+pow(aux,2)) < range) {
                posRel.y = aux;
            }
        }
        if(fase2) {
            auto sprite = (Sprite*)luz->GetComponent("Sprite");
            static int alpha = 0;
            static float radius;
            float val = ((abs(goP->box.pos.y) - 3008) / 4000);//6496);

            if(val < 0) {
                alpha = 255;
                radius = 1.5;
            }else if(val > 1) {
                alpha = 0;
                radius = 10;// * (1-val);
                
            } else {
                radius = 10 * val;
                val = 1 - val;
                alpha = val * 255;
                if(radius < 1.5f){
                    radius = 1.5f;
                }
                
            }
            sprite->SetAlphaChannel(alpha);
            sprite->SetScale(radius, radius);
        }

        if(goP) {
            associated.box.mudaCentro(goP->box.centro() + posRel);
        }

        luz->box.mudaCentro(associated.box.centro());
    }
}

void Wisp::Render() {
    if(fase2)
        luz->Render();
}

bool Wisp::Is(std::string type) {
    return type == "Wisp";
}


