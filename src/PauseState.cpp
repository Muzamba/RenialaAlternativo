#include "PauseState.h"
#include "InputManager.h"
#include "Text.h"

PauseState::PauseState() : State() {

}

void PauseState::LoadAssets() {
	GameObject* goText1 = new GameObject();
	goText1->AddComponent(new Text(*goText1, "assets/font/herculanum.ttf", 30, Text::BLENDED, "Jogo Pausado", { 0,0,0,255 }));
	goText1->box.pos = { 1280 / 2, (720 / 2) - 20};
	GameObject* goText2 = new GameObject();
	goText2->AddComponent(new Text(*goText1, "assets/font/herculanum.ttf", 30, Text::BLENDED, "Aperte ESC para sair do jogo, Enter para continuar ou S para salvar", { 0,0,0,255 }));
	goText2->box.pos = { 1280 / 2, (720 / 2) + 20 };
	objectArray.emplace_back(goText1);
	objectArray.emplace_back(goText2);
}

void PauseState::Update(float dt) {
	if (InputManager::GetInstance().KeyPress(ESCAPE_KEY)) {
		quitRequested = true;
	}
	else if (InputManager::GetInstance().KeyPress(S_KEY)) {

	}
	else if (InputManager::GetInstance().KeyPress(ENTER_KEY)) {
		popRequested = true;
	}
}

void PauseState::Render() {
	RenderArray();
}

void PauseState::Start(){}

void PauseState::Pause(){}

void PauseState::Resume(){}