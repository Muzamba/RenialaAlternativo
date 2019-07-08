#include "Wisp.h"
#include "Sprite.h"
#include "InputManager.h"


Wisp::Wisp(GameObject& associated, std::weak_ptr<GameObject> player) : Component(associated) {
    associated.AddComponent(this);
    auto sprite = new Sprite(associated, "assets/img/penguin.png");
    sprite->SetAlphaChannel(100);
    associated.AddComponent(sprite);
    luz = new GameObject();
    luz->AddComponent(new Sprite(*luz, "assets/img/BlackWithHole.png"));

    this->player = player;
    posRel = {0.0f,0.0f};
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



    if(goP) {
        associated.box.mudaCentro(goP->box.centro() + posRel);
    }

    luz->box.mudaCentro(associated.box.centro());
}

void Wisp::Render() {
    //luz->Render();
}

bool Wisp::Is(std::string type) {
    return type == "Wisp";
}


