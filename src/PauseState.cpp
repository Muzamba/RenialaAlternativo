#include "PauseState.h"
#include <iostream>
#include <fstream>
#include "Camera.h"
#include "GameData.h"
#include "InputManager.h"
#include "Text.h"

PauseState::PauseState() : State() {
	LoadAssets();
}

void PauseState::LoadAssets() {
	GameObject* goText1 = new GameObject();
	goText1->AddComponent(new Text(*goText1, "assets/font/herculanum.ttf", 30, Text::BLENDED, "Jogo Pausado", { 0,0,0,255 }));
	goText1->box.mudaCentro({ (1280 / 2) + Camera::pos.x, (720 / 2) - 100 + Camera::pos.y});
	GameObject* goText2 = new GameObject();
	goText2->AddComponent(new Text(*goText2, "assets/font/herculanum.ttf", 30, Text::BLENDED, "Aperte ESC para sair do jogo, Enter para continuar ou S para salvar", { 0,0,0,255 }));
	goText2->box.mudaCentro({ 1280 / 2 + Camera::pos.x, (720 / 2) + 100 + Camera::pos.y });
	AddObject(goText1);
	AddObject(goText2);
}

void PauseState::Update(float dt) {
	UpdateArray(dt);
	if (InputManager::GetInstance().KeyPress(ESCAPE_KEY)) {
		quitRequested = true;
	}
	else if (InputManager::GetInstance().KeyPress(S_KEY)) {
		std::ofstream fout;
		fout.open("assets/save/save.txt");
		auto player = GameData::player.lock();
		fout << player->box.centro().x << " " << player->box.centro().y << std::endl;
		fout << GameData::state->nameState;
		GameObject* goSave = new GameObject();
		goSave->AddComponent(new Text(*goSave, "assets/font/herculanum.ttf", 20, Text::BLENDED, "Jogo Salvo", { 0,0,0,255 }));
		goSave->box.mudaCentro({ 1280 / 2 + Camera::pos.x, (720 / 2) + 200 + Camera::pos.y });
		AddObject(goSave);
	}
	else if (InputManager::GetInstance().KeyPress(ENTER_KEY)) {
		popRequested = true;
	}
}

void PauseState::Render() {
	std::cout << "Rendering" << std::endl;
	RenderArray();
}

void PauseState::Start(){}

void PauseState::Pause(){}

void PauseState::Resume(){}