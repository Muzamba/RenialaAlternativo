#include "CreditState.h"
#include "Sprite.h"
#include "MenuState.h"
#include "TestState.h"
#include "Game.h"
#include "Text.h"

CreditState::CreditState() : State() {

}

void CreditState::Update(float dt) {
    this->UpdateArray(dt);
    timer.Update(dt);
    if(timer.Get() > 10.0) {
        Game::GetInstance().Push(new MenuState());
    }
}

void CreditState::Render() {
    this->RenderArray();
}

void CreditState::Start() {
    LoadAssets();
	this->StartArray();
}

void CreditState::Pause() {}

void CreditState::Resume() {
    //popRequested = false;
}

void CreditState::LoadAssets() {
    GameObject *blackGo = new GameObject();
    Sprite *sprite = new Sprite(*blackGo, "assets/img/Black.png");
    blackGo->AddComponent(sprite);
    AddObject(blackGo);

    /*Devs*/
    GameObject *devGo = new GameObject();
    Text * devText = new Text(*devGo,"assets/font/herculanum.ttf", 25, Text::BLENDED, "Desenvolvedores", {255,255,255,255});
    devGo->AddComponent(devText);
    devGo->box.pos = {540, 100};
    AddObject(devGo); 

    GameObject *dObj = new GameObject();
    Text * dText = new Text(*dObj,"assets/font/herculanum.ttf", 20, Text::BLENDED, "Ariel Batista    Cristiane Naves    Divino Junior", {255,255,255,255});
    dObj->AddComponent(dText);
    dObj->box.pos = {400, 200};
    AddObject(dObj); 

    /*Artistas*/
    GameObject *artistaGo = new GameObject();
    Text * artistaText = new Text(*artistaGo,"assets/font/herculanum.ttf", 25, Text::BLENDED, "Artistas", {255,255,255,255});
    artistaGo->AddComponent(artistaText);
    artistaGo->box.pos = {590, 300};
    AddObject(artistaGo);

    GameObject *aObj = new GameObject();
    Text * aText = new Text(*aObj,"assets/font/herculanum.ttf", 20, Text::BLENDED, "Fernanda Dourado    Marcello Brito    Tayna Oliveira", {255,255,255,255});
    aObj->AddComponent(aText);
    aObj->box.pos = {360, 400};
    AddObject(aObj);

    /*Musicos*/
    GameObject *musicoGo = new GameObject();
    Text * musicoText = new Text(*musicoGo,"assets/font/PixelFont.otf", 25, Text::BLENDED, "Musicos", {255,255,255,255});
    musicoGo->AddComponent(musicoText);
    musicoGo->box.pos = {600, 500};
    AddObject(musicoGo); 

    GameObject *mObj = new GameObject();
    Text * mText = new Text(*mObj,"assets/font/PixelFont.otf", 20, Text::BLENDED, "Heliel Sena    Pedro Ribeiro    Daniel", {255,255,255,255});
    mObj->AddComponent(mText);
    mObj->box.pos = {510-5, 600};
    AddObject(mObj);
}