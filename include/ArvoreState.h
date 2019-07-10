#ifndef ARVORESTATE_H
#define ARVORESTATE_H

#include "State.h"


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

};


#endif //ARVORESTATE_H
