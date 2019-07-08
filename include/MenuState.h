#pragma once
#include "State.h"
#include "Text.h"
#include "GameObject.h"
#include "Timer.h"
class MenuState : public State {
public:
	MenuState();
	
	void Update(float dt) override;
	void Render() override;
	
	void Start() override;
	void Pause() override;
	void Resume() override;
	
	void LoadAssets();
private:
	GameObject *texto;
	GameObject *goTextbg;
	bool mostrarTexto;
	Timer textCounter;
};
