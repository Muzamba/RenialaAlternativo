#pragma once
#include "State.h"
#include "Text.h"
class InicialState : public State {
public:
	InicialState();
	void Update(float dt);
	void Render();
	void Start();
	void Pause();
	void Resume();
	void LoadAssets();
private:
};
