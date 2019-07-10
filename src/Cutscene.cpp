#include "Cutscene.h"
#include "FadeIn.h"
#include "TestState.h"
#include "Game.h"
#include "string.h"

Cutscene::Cutscene() : State() {
    renderNewScene = true;
    scene = 1;
}

void Cutscene::Update(float dt) {
    this->UpdateArray(dt);
    timer.Update(dt);
    static bool first = true;
    if(timer.Get() > 3.0 && first) {
        fadeOut->Begin();
        first = false;
    }

    if(timer.Get() > 4.0) {
        renderNewScene = true;
        scene++;
        first = true;
        timer.Restart();
    
    } else {
        renderNewScene = false;
    }

    if(renderNewScene) {
        std::cout << "Render new scene" << std::endl;
        fadeIn->Begin();
    }
}

void Cutscene::Render() {
    //this->RenderArray();
    switch (scene)
    {
    case 1:
        cena1obj->Render();
        break;
    case 2:
        cena2obj->Render();
        break;
    case 3:
        cena3obj->Render();
        break;
    case 4:
        cena4obj->Render();
        break;
    case 5:
        cena5obj->Render();
        break;
    case 6:
    default:
        Game::GetInstance().Push(new TestState());
        break;
    }
    fadeIn->Render();
    fadeOut->Render();
}

void Cutscene::Pause() {}

void Cutscene::Resume() {
    popRequested = false;
}

void Cutscene::Start() {
    LoadAssets();
	this->StartArray();
}

void Cutscene::LoadAssets() {
    cena1obj = new GameObject();
    Sprite *scene1 = new Sprite(*cena1obj, "assets/img/cutscenes/cena_1.png");
    scene1->SetScale(1.25, 0.9375);
    cena1obj->box.pos = {0, 0};
    cena1obj->AddComponent(scene1);

    cena2obj = new GameObject();
    Sprite *scene2 = new Sprite(*cena2obj, "assets/img/cutscenes/cena_2.png");
    scene2->SetScale(1.25, 0.9375);
    cena2obj->box.pos = {0, 0};
    cena2obj->AddComponent(scene2);

    cena3obj = new GameObject();
    Sprite *scene3 = new Sprite(*cena3obj, "assets/img/cutscenes/cena_3.png");
    scene3->SetScale(1.25, 0.9375);
    cena3obj->box.pos = {0, 0};
    cena3obj->AddComponent(scene3);

    cena4obj = new GameObject();
    Sprite *scene4 = new Sprite(*cena4obj, "assets/img/cutscenes/cena_4.png");
    scene4->SetScale(1.25, 0.9375);
    cena4obj->box.pos = {0, 0};
    cena4obj->AddComponent(scene4);

    cena5obj = new GameObject();
    Sprite *scene5 = new Sprite(*cena5obj, "assets/img/cutscenes/cena_5.png");
    scene5->SetScale(1.25, 0.9375);
    cena5obj->box.pos = {0, 0};
    cena5obj->AddComponent(scene5);
    
    GameObject *fadeInObj = new GameObject();
    fadeIn = new FadeIn(*fadeInObj, 1.0f);
    fadeInObj->AddComponent(fadeIn);
    AddObject(fadeInObj);

    GameObject *fadeOutObj = new GameObject();
    fadeOut = new FadeOut(*fadeOutObj, 1.0f);
    fadeOutObj->AddComponent(fadeOut);
    AddObject(fadeOutObj);
}