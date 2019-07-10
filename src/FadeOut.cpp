#include "FadeOut.h"

FadeOut::FadeOut(GameObject& associated, float tempo) : FadeIn(associated, tempo) {

}


void FadeOut::Begin() {
    ligaTimer = true;
    timer.Restart();
    alpha = 0;
    telaPreta->SetAlphaChannel(alpha);
}

void FadeOut::Update(float dt) {
    if(ligaTimer){
        timer.Update(dt);
        if(timer.Get() > tempo) {
            //ligaTimer = false;
            //timer.Restart();
            
        } else {
            alpha +=  multiplicador * dt;
            if(alpha > 255) {
                alpha = 255;
            }
            telaPreta->SetAlphaChannel(alpha);
        }

    }
}

bool FadeOut::Is(std::string type) {
    return type == "FadeOut";
}

