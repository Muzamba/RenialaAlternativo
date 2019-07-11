#pragma once
#include "State.h"
#include "Timer.h"
#include "FadeIn.h"
#include "FadeOut.h"
#include "Music.h"
class Cutscene : public State {
public:
	Cutscene(bool inicial=true);
	
	void Update(float dt) override;
	void Render() override;
	
	void Start() override;
	void Pause() override;
	void Resume() override;
	
	void LoadAssets();
private:
	bool inicial;

	Timer timer;

	GameObject *cena1obj;
	GameObject *cena2obj;
	GameObject *cena3obj;
	GameObject *cena4obj;
	GameObject *cena5obj;

	bool renderNewScene;
	int scene;

	FadeIn* fadeIn;
	FadeOut* fadeOut;

	Music* musica;
};
