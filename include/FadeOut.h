#ifndef FADEOUT_H
#define FADEOUT_H

#include "FadeIn.h"

class FadeOut : public FadeIn {
public:
    FadeOut(GameObject& associated, float tempo);

    void Begin() override;
    void Update(float dt) override;

    bool Is(std::string type) override;
};




#endif //FADEOUT_H
