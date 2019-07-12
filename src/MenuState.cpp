#include "MenuState.h"
#include "InputManager.h"
#include "Game.h"
#include "TestState.h"
#include "Cutscene.h"
#include "CameraFollower.h"
#include "Sprite.h"
#include "Music.h"
#include "FadeOut.h"
#include "ArvoreState.h"

MenuState::MenuState() : State () {
    mostrarTexto = true;
}

void MenuState::Update(float dt) {
    textCounter.Update(dt);
    this->UpdateArray(dt);
    fadeOut->Update(dt);
    static bool first = true;
    if (InputManager::GetInstance().KeyPress(SDLK_SPACE) && first) {
        ((FadeOut*)fadeOut->GetComponent("FadeOut"))->Begin();
        musica->Stop();
        first = false;
    }
    if (textCounter.Get() > 1.2) {
        mostrarTexto = !mostrarTexto;
        textCounter.Restart();
    }
    if(((FadeOut*)fadeOut->GetComponent("FadeOut"))->timer.Get() > 1.5f) {
        popRequested = true;
        Game::GetInstance().Push(new  Cutscene());
        first = true;
    }
}

void MenuState::Render() {
    this->RenderArray();
    if(mostrarTexto) {
        goTextbg->Render();
        texto->Render();
    }
    fadeOut->Render();
}

void MenuState::Pause() {}

void MenuState::Resume() {
    popRequested = false;
}

void MenuState::Start() {
    LoadAssets();
	StartArray();
}

void MenuState::LoadAssets() {
    GameObject* gobg = new GameObject();
	Sprite* sprite = new Sprite(*gobg, "assets/img/menu/bg_menuinicial.png");
	sprite->SetScale(3.742690f,3.75f);//sprite->SetScale(0.937042f, 0.9375f);
    gobg->AddComponent(sprite);
	gobg->AddComponent(new CameraFollower(*gobg));
	gobg->box.pos = {0,0};
	AddObject(gobg);

    GameObject* logo = new GameObject();
    auto sprite2 = new Sprite(*logo, "assets/img/menu/reniala_logo.png", 0,0,0.1f,9);
    logo->AddComponent(sprite2);
    sprite2->SetScale(3.5,3.5);
    logo->box.mudaCentro({1280 / 2.0f, 720 / 2 - logo->box.size.y/2});
    AddObject(logo);

    goTextbg = new GameObject();
    Sprite *spriteBg = new Sprite(*goTextbg, "assets/img/barra_de_texto.png");
    goTextbg->AddComponent(spriteBg);
    Vec2 centro = {(1280/2.0f) - spriteBg->GetWidth()/2, (720/2.0f) + 100};
    goTextbg->box.pos = centro;

    texto = new GameObject();
    Text *textoFonte = new Text(*texto, "assets/font/PixelFont.otf", 20, Text::BLENDED, "APERTE SPACE PARA JOGAR", {255,255,255,255});
    texto->box.pos = {centro.x + (350/2), centro.y + 10};
    texto->AddComponent(textoFonte);

    musica = new Music("assets/sound/Menu.ogg");
    musica->Play();

    fadeOut = new GameObject();
    fadeOut->AddComponent(new FadeOut(*fadeOut, 1.5f));
}