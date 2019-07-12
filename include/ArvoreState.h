#ifndef ARVORESTATE_H
#define ARVORESTATE_H

#include "State.h"
#include "Timer.h"
#include "Music.h"


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
    Music* musica;

};


#endif //ARVORESTATE_H
