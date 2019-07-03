#include "BoxState.h"
#include "InputManager.h"
#include "Game.h"
#include "Camera.h"
#include "Sprite.h"

BoxState::BoxState(std::string talismaFile, std::string descricao) : State() {
    this->descricao = descricao;
    this->talismaFile = talismaFile;
}

BoxState::~BoxState() {
    objectArray.clear();
}

void BoxState::LoadAssets() {
    GameObject *bg = new GameObject();
    Sprite* sprite = new Sprite(*bg, "assets/img/cenario_arvore.jpg");
    bg->box.pos.x = Camera::pos.x;
    bg->box.pos.y = Camera::pos.y;
	bg->AddComponent(sprite);
    AddObject(bg);

    GameObject *talismaObj = new GameObject();
    Sprite *talisma = new Sprite(*talismaObj, talismaFile);
    talismaObj->AddComponent(talisma);
    talismaObj->box.pos.y = 150 + Camera::pos.y;
    talismaObj->box.pos.x = ((1024/2) - talisma->GetWidth()/2) + Camera::pos.x;
    AddObject(talismaObj);

    GameObject *caixaObj = new GameObject();
    Sprite *caixaDialogo = new Sprite(*caixaObj, "assets/img/description.png");
    caixaDialogo->SetScale(1, 0.5);
    float meio = (1024/2) - caixaDialogo->GetWidth()/2;
    caixaObj->box.pos.x = meio + Camera::pos.x;
    caixaObj->box.pos.y = 300 + Camera::pos.y;
    caixaObj->AddComponent(caixaDialogo);
    AddObject(caixaObj);
    
    /*Mostrar texto depois que aparecer a caixa*/
    GameObject *textObj = new GameObject();
    SDL_Color black = {0, 0, 0, 0};
    Text *text = new Text(*textObj, "assets/font/herculanum.ttf", 20, Text::BLENDED, descricao, black);
    textObj->box.pos.x = meio + 50 + Camera::pos.x;
    textObj->box.pos.y = 320 + Camera::pos.y;
    textObj->AddComponent(text);
    AddObject(textObj);
}

void BoxState::Update(float dt) {
    this->UpdateArray(dt);
    if (InputManager::GetInstance().KeyPress(SDLK_x)) {
        popRequested = true;
    }
}

void BoxState::Render() {
	this->RenderArray();
}

void BoxState::Pause() {}

void BoxState::Resume() {}

void BoxState::Start(){
    LoadAssets();
    StartArray();
}