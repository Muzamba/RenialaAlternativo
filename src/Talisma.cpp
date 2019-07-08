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
#include "HUD.h"

Talisma::Talisma(GameObject& associated, std::string textfile, std::string imgfileInGame, std::string imgfileNoAnim, std::string imgfileHUD, int indice) : Component(associated) {
    
    //this->talismaFile = imgfile;
    spriTable["Animated"] = new Sprite(associated, imgfileInGame, 0, 0, 0.1f, 5);
    spriTable["NotAnimated"] = new Sprite(associated, imgfileNoAnim);
    spriTable["HUD"] = new Sprite(associated, imgfileHUD);
    spriTable["Animated"]->SetScale(2,2);
    spriTable["NotAnimated"]->SetScale(2,2);
    spriTable["HUD"]->SetScale(2,2);

    atual = spriTable["NotAnimated"];
    texto = new GameObject();
    texto->AddComponent(new Text(*texto, "assets/font/herculanum.ttf", 15, Text::BLENDED, "precione (x) para coletar", {0,0,0,255}));
    texto->box.pos = associated.box.pos;
    ReadText(textfile); 
    associated.box.size.x = atual->GetWidth();
    associated.box.size.y = atual->GetHeight();
    //associated.AddComponent(talisma);
    associated.AddComponent(this);
    coletado = false;
    talismaAdicionado = false;
    rangeText.pos = associated.box.pos;
    rangeText.size.x = 200;
    rangeText.size.y = 200;
    exibeTexto = false;
    this->indice = indice;
    timer.Restart();
    ligaBrilho = false;
    
}

void Talisma::Update(float dt) {
    timer.Update(dt);
    atual->Update(dt);
    auto& im = InputManager::GetInstance();
    if(!coletado) {
        //timer.Update(dt);
        if(ligaBrilho){
            if(timer.Get() > 0.6f) {
                ligaBrilho = false;
                timer.Restart(); 
                atual = spriTable["NotAnimated"];
            }
        } else {
            if(timer.Get() > 5.0f) {
                ligaBrilho = true;
                timer.Restart();
                atual = spriTable["Animated"];
                atual->SetFrame(0);
            }
        }

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
                    atual = spriTable["HUD"];
                    associated.box.size.x = atual->GetWidth();
                    associated.box.size.y = atual->GetHeight();
                    associated.AddComponent(new CameraFollower(associated, 90 + 44 * indice, 25 ));
                    //Game::GetInstance().Push(new BoxState(talismaFile, text));
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
    atual->Render();
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
    delete spriTable["Animated"];
    delete spriTable["NotAnimated"];
    delete spriTable["HUD"];
    delete texto;
}