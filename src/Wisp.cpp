#include "Wisp.h"
#include "Sprite.h"
#include "InputManager.h"


Wisp::Wisp(GameObject& associated, std::weak_ptr<GameObject> player, bool fase2) : Component(associated) {
    associated.AddComponent(this);
    auto sprite = new Sprite(associated, "assets/img/brilho_amigo.png");//.png", 0, 0, 0.1f, 6);
    //sprite->SetAlphaChannel(100);
    sprite->SetScale(1.1f, 1.1f);
    associated.AddComponent(sprite);
    luz = new GameObject();
    luz->AddComponent(new Sprite(*luz, "assets/img/BlackWithHole.png"));

    this->player = player;
    posRel = {0.0f,0.0f};
    this->fase2 = fase2;
}

void Wisp::Update(float dt) {
    auto goP = player.lock();
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
        float val = abs((goP->box.pos.y - 548) / 1280);

        if(val < 1) {
            val = 1 - val;
            alpha = val * 255;
        }
        sprite->SetAlphaChannel(alpha);
    }

    if(goP) {
        associated.box.mudaCentro(goP->box.centro() + posRel);
    }

    luz->box.mudaCentro(associated.box.centro());
}

void Wisp::Render() {
    if(fase2)
        luz->Render();
}

bool Wisp::Is(std::string type) {
    return type == "Wisp";
}


