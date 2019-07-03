#ifndef TRAB5_7_GRAVIDADE_H
#define TRAB5_7_GRAVIDADE_H

#include "Component.h"
#include "Timer.h"
#include "Physic.h"


class Gravidade : public Component {
public:
friend class Physic;
    Gravidade(GameObject& associated, float Acel);
    ~Gravidade();

    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;
    void NotifyCollision(GameObject& other) override;

    void SetAceleration(float newAcel);
    void SetVelocidade(float newVelo);
    void Jump();
    bool GetGrounded();
    float GetVelocidade();



private:
    float acelY;
    float velocidade;
    bool toggle;
    Timer timer;
};


#endif //TRAB5_7_GRAVIDADE_H
