#ifndef ARVORECOMPONENT_H
#define ARVORECOMPONENT_H

#include "Component.h"
#include "Sprite.h"
#include "Timer.h"

class ArvoreComponent : public Component {
public:
    ArvoreComponent(GameObject& associated);
    virtual ~ArvoreComponent();

    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;
    void Start() override;

private:
    Sprite* ascendendo;
    Sprite* idle;
    Sprite* atual;
    GameObject* brilhoChao;
    GameObject* wisp;
    bool ligaRender;
    Timer timer;
    Timer timer2;

};


#endif //ARVORECOMPONENT_H
