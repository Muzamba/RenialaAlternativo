#include "Dialogo.h"
#include "InputManager.h"
#include "Text.h"
#include "Game.h"
#include "Player.h"


Dialogo::Dialogo(GameObject& associated) : Component(associated) {
    associated.AddComponent(this);
    face = new GameObject();
    faceTable["boneco"] = new Sprite(*face, "assets/img/Dialogo/personagem principal.png");
    faceTable["wisp"] = new Sprite(*face, "assets/img/Dialogo/bolinha de luz.png");
    faceTable["arvore"] = new Sprite(*face, "assets/img/Dialogo/arvore.png");

    faceTable["boneco"]->SetCamMulti({0,0});
    faceTable["wisp"]->SetCamMulti({0,0});
    faceTable["arvore"]->SetCamMulti({0,0});

    faceTable["boneco"]->SetScale(2,2);
    faceTable["wisp"]->SetScale(2,2);
    faceTable["arvore"]->SetScale(2,2);
    face->box.pos = {100,650};

    on = false;

    box = new GameObject();
    auto sprite = new Sprite(*box, "assets/img/Dialogo/caixa_dialogo.png", 0, 0, 0.1666666f, 6);
    sprite->SetCamMulti({0,0});
    sprite->SetScale(2,2);
    box->AddComponent(sprite);
    box->box.pos = {50,600};

    button = new GameObject();
    sprite = new Sprite(*button, "assets/img/Dialogo/setinha_dialogo.png");
    sprite->SetCamMulti({0,0});
    button->AddComponent(sprite);
    button->box.pos = {500,700};

    timer.Restart();

    texto = new GameObject();
    texto->AddComponent(new Text(*texto, "assets/font/herculanum.ttf", 20, Text::BLENDED, "", {0,0,0,255}));
    texto->box.pos = {180, 650};
    
}

Dialogo::~Dialogo() {

}


void Dialogo::Update(float dt) {
    if(on){
        if(timer.Get() < 1.0f){
            box->Update(dt);
            timer.Update(dt);
        } else {
            auto& im = InputManager::GetInstance();
            if(im.KeyPress(SDLK_SPACE)) {
                on = false;
                ((Player*)Game::GetInstance().playerStatus.player->GetComponent("Player"))->dialogo = false;
            }
        }
    }
}

void Dialogo::Render() {
    if(on){
        box->Render();
        if(timer.Get() > 1.0f ){
            faceTable[quem]->Render();
            texto->Render();
            button->Render();
        }
    }
}

bool Dialogo::Is(std::string type) {
    return type == "Dialogo";
}

void Dialogo::Begin(std::string text, std::string quem) {
    timer.Restart();
    this->quem = quem;
    on = true;
    ((Text*)texto->GetComponent("Text"))->SetText(text);
    ((Player*)Game::GetInstance().playerStatus.player->GetComponent("Player"))->dialogo = true;
}
