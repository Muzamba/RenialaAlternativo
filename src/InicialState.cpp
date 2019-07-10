#include "InicialState.h"
#include "CameraFollower.h"
#include "InputManager.h"
#include "Game.h"
#include "Sprite.h"
#include "TestState.h"

InicialState::InicialState() : State () {}

void InicialState::Update(float dt) {
    this->UpdateArray(dt);
    if (InputManager::GetInstance().KeyPress(SDLK_SPACE)) {
        Game::GetInstance().Push(new TestState());
    }
}

void InicialState::Render() {
    this->RenderArray();
}

void InicialState::Start() {

}

void InicialState::Pause() {}

void InicialState::Resume() {
    popRequested = false;
}

void InicialState::LoadAssets() {
    GameObject* gobg = new GameObject();
	Sprite* sprite = new Sprite(*gobg, "assets/img/1.png");
	gobg->AddComponent(sprite);
	gobg->AddComponent(new CameraFollower(*gobg));
	objectArray.emplace_back(gobg);
}