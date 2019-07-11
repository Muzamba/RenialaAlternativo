#ifndef ARVORESTATE_H
#define ARVORESTATE_H

#include "State.h"
#include "Timer.h"


class ArvoreState : public State {
public:
    ArvoreState();
    virtual ~ArvoreState();
    
    void LoadAssets();
    void Update(float dt);
    void Render();

    void Start();
    void Pause();
    void Resume();

private:
    GameObject* arvore;
    GameObject* fadeOut;
    GameObject* fadeIn;
    Timer timerFade;

};


#endif //ARVORESTATE_H
