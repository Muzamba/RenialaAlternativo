#ifndef TRANSSTATE_H
#define TRANSSTATE_H

#include "State.h"


class TransState : public State {
public:
    TransState(int pos);
    virtual ~TransState();

    void LoadAssets() override;
    void Update(float dt) override;
    void Render() override;

    void Start() override;
    void Pause() override;
    void Resume() override;
private:
    bool mudaState;
    State* destino;
    GameObject* fadeOut;
    GameObject*fadeIn;

};

#endif // TRANSSTATE_H

