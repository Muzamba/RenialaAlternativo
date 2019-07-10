#include "MenuState.h"
#include "InputManager.h"
#include "Game.h"
#include "TestState.h"
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
    if (InputManager::GetInstance().KeyPress(SDLK_SPACE)) {
        //popRequested = true;
        //Game::GetInstance().Push(new TestState());
        ((FadeOut*)fadeOut->GetComponent("FadeOut"))->Begin();
        musica->Stop();
    }
    if (textCounter.Get() > 1.2) {
        mostrarTexto = !mostrarTexto;
        textCounter.Restart();
    }
    if(((FadeOut*)fadeOut->GetComponent("FadeOut"))->timer.Get() > 1.5f) {
        popRequested = true;
        Game::GetInstance().Push(new ArvoreState());
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
	Sprite* sprite = new Sprite(*gobg, "assets/img/Background.jpg");
	sprite->SetScale(0.937042f, 0.9375f);
    gobg->AddComponent(sprite);
	gobg->AddComponent(new CameraFollower(*gobg));
	gobg->box.pos = {0,0};
	AddObject(gobg);

    goTextbg = new GameObject();
    Sprite *spriteBg = new Sprite(*goTextbg, "assets/img/barra_de_texto.png");
    goTextbg->AddComponent(spriteBg);
    Vec2 centro = {(1280/2.0f) - spriteBg->GetWidth()/2, (720/2.0f) + 100};
    goTextbg->box.pos = centro;

    texto = new GameObject();
    Text *textoFonte = new Text(*texto, "assets/font/PixelFont.otf", 20, Text::BLENDED, "APERTE SPACE PARA JOGAR", {255,255,255,255});
    texto->AddComponent(textoFonte);
    texto->box.pos = {centro.x + (350/2), centro.y + 10};

    musica = new Music("assets/sound/TRILHA SONORA.ogg");
    musica->Play();

    fadeOut = new GameObject();
    fadeOut->AddComponent(new FadeOut(*fadeOut, 1.5f));
}