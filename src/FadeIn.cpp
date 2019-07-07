#include "FadeIn.h"
#include "Sprite.h"
#include "CameraFollower.h"


FadeIn::FadeIn(GameObject& associated, float tempo) : Component(associated) {
    ligaTimer = false;
    timer.Restart();
    associated.AddComponent(new CameraFollower(associated));
    telaPreta = new Sprite(associated, "assets/img/Black.png");
    alpha = 255;
    this->tempo = tempo;
    multiplicador = 255 / tempo;
}
FadeIn::~FadeIn() {
    delete telaPreta;
}

void FadeIn::Update(float dt) {
    if(ligaTimer){
        timer.Update(dt);
        if(timer.Get() > tempo) {
            ligaTimer = false;
            //timer.Restart();
            
        } else {
            alpha -=  multiplicador * dt;
            if(alpha < 0) {
                alpha = 0;
            }
            telaPreta->SetAlphaChannel(alpha);
        }

    }

}

void FadeIn::Render() {
    if(ligaTimer) {
        telaPreta->Render();
    }
}

bool FadeIn::Is(std::string type) {
    return type == "FadeIn";
}


void FadeIn::Begin() {
    ligaTimer = true;
    timer.Restart();
    alpha = 255;
}
