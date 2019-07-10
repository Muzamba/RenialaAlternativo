#ifndef FADEIN_H
#define FADEIN_H

#include "Component.h"
#include "Timer.h"
#include "Sprite.h"

class FadeIn : public Component {
public:
    FadeIn(GameObject& associated, float tempo);
    virtual ~FadeIn();

    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;
    Timer timer;
    virtual void Begin();

protected:
    Sprite* telaPreta;
    bool ligaTimer;
    float alpha;
    float tempo;
    float multiplicador;


};

#endif //FADEIN_H
