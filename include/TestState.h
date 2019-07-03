#pragma once
#include "State.h"
class TestState : public State {
public:
	TestState();
	void LoadAssets() override;
	void LoadPlataformas();

	void Update(float dt) override;
	void Render() override;
	
	void Start() override;
	void Pause() override;
	void Resume() override;
private:

};

