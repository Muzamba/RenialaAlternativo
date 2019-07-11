#pragma once
#include "State.h"
#include "Timer.h"
class CreditState : public State {
public:
    CreditState();

    void Update(float dt) override;
    void Render() override;

    void Start() override;
    void Pause() override;
    void Resume() override;

    void LoadAssets();
private:
    Timer timer;
};