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
#include "Player.h"
#include "Sound.h"

Talisma::Talisma(GameObject& associated, std::string textfile, std::string imgfileInGame, std::string imgfileNoAnim, std::string imgfileHUD, Camera::FASE fase, int indice) : Component(associated) {
    this->fase = fase;
    //this->talismaFile = imgfile;
    spriTable["Animated"] = new Sprite(associated, imgfileInGame, 0, 0, 0.1f, 5);
    spriTable["NotAnimated"] = new Sprite(associated, imgfileNoAnim);
    spriTable["HUD"] = new Sprite(associated, imgfileHUD);
    spriTable["Animated"]->SetScale(2,2);
    spriTable["NotAnimated"]->SetScale(2,2);
    spriTable["HUD"]->SetScale(2,2);

    atual = spriTable["NotAnimated"];
    texto = new GameObject();
    texto->AddComponent(new Text(*texto, "assets/font/PixelFont.otf", 15, Text::BLENDED, "precione (x) para coletar", {0,0,0,255}));
    texto->box.pos = {associated.box.pos.x,associated.box.pos.y};
    ReadText(textfile); 
    associated.box.size.x = atual->GetWidth();
    associated.box.size.y = atual->GetHeight();
    //associated.AddComponent(talisma);
    associated.AddComponent(this);
    coletado = false;
    talismaAdicionado = false;
    rangeText.pos = associated.box.pos;
    rangeText.size.x = 125;
    rangeText.size.y = 125;
    exibeTexto = false;
    this->indice = indice;
    timer.Restart();
    ligaBrilho = false;
    animacao = false;

    //sound = new Sound(associated, "assets/sound/TRILHA SONORA.ogg");
    
    //associated.AddComponent(sound);
}

void Talisma::Update(float dt) {
    if(!coletado && Camera::fase != fase){
    } else {
        atual->Update(dt);
    }
    

    auto& im = InputManager::GetInstance();
    static Vec2 dir = {0,0};
    static int velo = 0;
    if(Camera::fase == fase){
    if(!coletado) {
        timer.Update(dt);
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

        texto->box.mudaCentro({associated.box.centro().x + 20, associated.box.centro().y - associated.box.size.y/2 - texto->box.size.y/2});
        //rangeText.pos.x = associated.box.pos.x - 75;
        //rangeText.pos.y = associated.box.pos.y - 75;
        rangeText.mudaCentro({associated.box.centro().x + 10, associated.box.centro().y + 25});
        
        auto player = Game::GetInstance().playerStatus.player;
        if(player) {
            auto centro = player->box.centro();
            //auto cameraFo = (CameraFollower*)associated.GetComponent("CameraFollower");
            if(rangeText.estaDentro(centro.x, centro.y) and !animacao) {
                exibeTexto = true;
                if(im.KeyPress(SDLK_x)) {
                    //coleta o item
                    //coletado = true;
                    exibeTexto = false;
                    animacao = true;
                    //animação
                    //atual = spriTable["HUD"];
                    //associated.box.size.x = atual->GetWidth();
                    //associated.box.size.y = atual->GetHeight();
                    //cameraFo = new CameraFollower(associated, associated.box.pos.x - Camera::pos.x, associated.box.pos.y - Camera::pos.y);
                    //associated.AddComponent(cameraFo);// tirar essa pos
                    dir = {(90 + 44 * indice) + Camera::pos.x - associated.box.pos.x, 25 + Camera::pos.y - associated.box.pos.y};
                    velo = dir.magnitude() / 2.0f;
                    dir = dir.normalizado();
                    ((Player*)player->GetComponent("Player"))->pegarItem = true;
                    //sound->Play();
                    
                    
                    //Game::GetInstance().Push(new BoxState(talismaFile, text));
                }
            } else if(animacao) {
                if(associated.box.pos.x - (90 + 44 * indice) > 10 and associated.box.pos.y - 25 > 10) {
                    
                    associated.box.pos = associated.box.pos + dir * velo * dt; 
                } else {
                    spriTable["HUD"]->SetCamMulti({0,0});
                    associated.box.pos = {90 + 44 * indice, 25};
                    atual = spriTable["HUD"];
                    associated.box.size.x = atual->GetWidth();
                    associated.box.size.y = atual->GetHeight();
                    animacao = false;
                    coletado = true;
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
             //Game::GetInstance().Push(new BoxState(talismaFile, text));
        }
    //    SDL_GetMouseState(&mouseX, &mouseY);
    //    if(associated.box.Contains(mouseX + Camera::pos.x, mouseY + Camera::pos.y) && (InputManager::GetInstance().IsMouseDown(SDL_BUTTON_RIGHT) || InputManager::GetInstance().IsMouseDown(SDL_BUTTON_LEFT) ) ) { 
    //        Game::GetInstance().Push(new BoxState(this->talismaFile, this->text));   
    //    }
    }
    }
}

void Talisma::Render() {
    if(!coletado && Camera::fase != fase){
    } else {
        atual->Render();
        if(exibeTexto){
            texto->Render();
        }
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