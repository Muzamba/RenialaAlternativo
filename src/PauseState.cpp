#include "PauseState.h"
#include <iostream>
#include <fstream>
#include "Camera.h"
#include "Game.h"
#include "GameData.h"
#include "InputManager.h"
#include "Text.h"

PauseState::PauseState() : State() {
	LoadAssets();
}

void PauseState::LoadAssets() {
	GameObject* goText1 = new GameObject();
	Sprite* sprite = new Sprite(*goText1, "assets/img/PAUSE.png");
	sprite->SetScale(4, 4);
	goText1->AddComponent(sprite);
	goText1->box.mudaCentro({ (1280 / 2) + Camera::pos.x, (720 / 2) - 100 + Camera::pos.y});
	GameObject* goText2 = new GameObject();
	goText2->AddComponent(new Text(*goText2, "assets/font/PixelFont.otf", 30, Text::BLENDED, "Aperte ESC para sair do jogo, Enter para continuar ou S para salvar", { 255,255,255,255 }));
	goText2->box.mudaCentro({ 1280 / 2 + Camera::pos.x, (720 / 2) + 100 + Camera::pos.y });
	GameObject * bgPause = new GameObject();
		Sprite* sprite2 = new Sprite(*bgPause, "assets/img/Black.png");
		sprite2->SetAlphaChannel(1);
		//	sprite2->SetScale(3.742690f,3.75f);
		bgPause->AddComponent(sprite2);
		bgPause->box.mudaCentro({1280/2 + Camera::pos.x, 720/2 + Camera::pos.y});
		//bgPause->Update(0);
		//bgPause->Render();
	AddObject(bgPause);
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
		auto player = Game::GetInstance().playerStatus.player;
		fout << player->box.centro().x << " " << player->box.centro().y << std::endl;
		//fout << Game::;
		GameObject* goSave = new GameObject();
		goSave->AddComponent(new Text(*goSave, "assets/font/herculanum.ttf", 20, Text::BLENDED, "Jogo Salvo", { 0,0,0,255 }));
		goSave->box.mudaCentro({ 1280 / 2 + Camera::pos.x, (720 / 2) + 200 + Camera::pos.y });
		AddObject(goSave);
	}
	else if (InputManager::GetInstance().KeyPress(SDLK_RETURN)) {
		popRequested = true;
	}
}

void PauseState::Render() {
	RenderArray();
}

void PauseState::Start(){}

void PauseState::Pause(){}

void PauseState::Resume(){}