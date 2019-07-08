#include "MenuState.h"
#include "InputManager.h"
#include "Game.h"
#include "TestState.h"
#include "CameraFollower.h"
#include "Sprite.h"

MenuState::MenuState() : State () {
    mostrarTexto = true;

    texto = new GameObject();
    Sprite *textoSprite = new Sprite(*texto, "assets/img/penguin.png");
    texto->AddComponent(textoSprite);
    texto->box.pos = {(1280/2.0f) - textoSprite->GetWidth()/2, (720/2.0f) + 100};
}

void MenuState::Update(float dt) {
    textCounter.Update(dt);
    this->UpdateArray(dt);
    if (InputManager::GetInstance().KeyPress(SDLK_SPACE)) {
        Game::GetInstance().Push(new TestState());
    }
    if (textCounter.Get() > 0.8) {
        mostrarTexto = !mostrarTexto;
        textCounter.Restart();
    }
}

void MenuState::Render() {
    this->RenderArray();
    if(mostrarTexto) {
        texto->Render();
    }
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
}