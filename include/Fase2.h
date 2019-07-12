#ifndef FASE2_H
#define FASE2_H

#include "State.h"
#include "Music.h"



class Fase2 : public State {
public:
    Fase2();
    virtual ~Fase2(); 

    void LoadAssets() override;
    void LoadPlataformas();
    void Update(float dt) override;
    void Render() override;

    void Start() override;
    void Pause() override;
    void Resume() override;
private:
    GameObject* fadeIn;
    GameObject* fadeOut;
    Music* musica;
};


#endif //FASE2_H
