#pragma once
#include "State.h"
class TestState : public State {
public:
	TestState();
	virtual ~TestState();

	void LoadAssets() override;
	void LoadPlataformas();
	void LoadBg();
	void LoadCenarioFrente();
	void LoadCenarioAtras();

	void Update(float dt) override;
	void Render() override;
	
	void Start() override;
	void Pause() override;
	void Resume() override;
private:
	GameObject* fadeIn;
	GameObject* fadeOut;

};

