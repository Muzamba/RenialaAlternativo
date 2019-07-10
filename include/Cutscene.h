#pragma once
#include "State.h"
#include "Timer.h"
#include "Sprite.h"
#include "FadeIn.h"
#include "FadeOut.h"
class Cutscene : public State {
public:
	Cutscene();
	
	void Update(float dt) override;
	void Render() override;
	
	void Start() override;
	void Pause() override;
	void Resume() override;
	
	void LoadAssets();
private:
	Timer timer;

	GameObject *cena1obj;
	GameObject *cena2obj;
	GameObject *cena3obj;
	GameObject *cena4obj;
	GameObject *cena5obj;

	//GameObject *fadeInObj;

	bool renderNewScene;
	bool showFadeOut;
	int scene;

	FadeIn* fadeIn;
	FadeOut* fadeOut;

};
