#include "Talisma.h"
#include "InputManager.h"
#include "Sprite.h"
#include "Collider.h"
#include "Game.h"
#include "GameData.h"
#include "Camera.h"
#include <fstream>
#include <sstream>
#include "InputManager.h"
#include "CameraFollower.h"
#include "BoxState.h"

Talisma::Talisma(GameObject& associated, std::string imgfile, std::string textfile, int indice) :Component(associated) {
    
    this->talismaFile = imgfile;
    talisma = new Sprite(associated, imgfile);
    talisma->SetScale(2,2);
    texto = new GameObject();
    texto->AddComponent(new Text(*texto, "assets/font/herculanum.ttf", 15, Text::BLENDED, "precione (x) para coletar", {0,0,0,255}));
    texto->box.pos = associated.box.pos;
    ReadText(textfile); 
    associated.box.size.x = talisma->GetWidth();
    associated.box.size.y = talisma->GetHeight();
    //associated.AddComponent(talisma);
    associated.AddComponent(this);
    coletado = false;
    talismaAdicionado = false;
    rangeText.pos = associated.box.pos;
    rangeText.size.x = 200;
    rangeText.size.y = 200;
    exibeTexto = false;
    this->indice = indice;
    
}

void Talisma::Update(float dt) {
    talisma->Update(dt);
    auto& im = InputManager::GetInstance();
    if(!coletado) {
        texto->box.mudaCentro({associated.box.centro().x, associated.box.centro().y - associated.box.size.y/2 - texto->box.size.y});
        rangeText.pos.x = associated.box.pos.x - 100;
        rangeText.pos.y = associated.box.pos.y - 100;
        
        auto player = Game::GetInstance().playerStatus.player.lock();
        if(player) {
            auto centro = player->box.centro();
            if(rangeText.estaDentro(centro.x, centro.y)) {
                exibeTexto = true;
                if(im.KeyPress(SDLK_x)) {
                    //coleta o item
                    coletado = true;
                    exibeTexto = false;
                    associated.AddComponent(new CameraFollower(associated, 90 + 44 * indice, 25 ));
                    Game::GetInstance().Push(new BoxState(talismaFile, text));
                }
            } else {
                exibeTexto = false;
            }


        }
    } else {
        mouseX = im.GetMouseX();
        mouseY = im.GetMouseY();
        //cliando no item
        if(associated.box.estaDentro(mouseX + Camera::pos.x, mouseY + Camera::pos.y) and im.MouseRelease(SDL_BUTTON_LEFT)) {
             Game::GetInstance().Push(new BoxState(talismaFile, text));
        }
    //    SDL_GetMouseState(&mouseX, &mouseY);
    //    if(associated.box.Contains(mouseX + Camera::pos.x, mouseY + Camera::pos.y) && (InputManager::GetInstance().IsMouseDown(SDL_BUTTON_RIGHT) || InputManager::GetInstance().IsMouseDown(SDL_BUTTON_LEFT) ) ) { 
    //        Game::GetInstance().Push(new BoxState(this->talismaFile, this->text));   
    //    }
    }
}

void Talisma::Render() {
    talisma->Render();
    if(exibeTexto){
        texto->Render();
    }
}

bool Talisma::Is(std::string type) {
    return type == "Talisma";
}

void Talisma::ReadText(std::string textfile) {
    std::ifstream fin;
    fin.open(textfile);
    std::stringstream strStream;

    strStream << fin.rdbuf();
    text = strStream.str();
}

Talisma::~Talisma() {
    delete talisma;
    delete texto;
}