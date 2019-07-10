#pragma once
#include "State.h"
class PauseState : public State {
public:
	PauseState();
	void LoadAssets();

	void Update(float dt) override;
	void Render() override;

	void Start() override;
	void Pause() override;
	void Resume() override;
};

