#include "Fase2.h"
#include "Collider.h"
#include "Collision.h"
#include "Player.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Camera.h"
#include "PlataformaFixa.h"
#include "Physic.h"
#include "PlataformaMovel.h"
#include "Talisma.h"
#include "Game.h"
#include "CameraFollower.h"
#include "HUD.h"
#include "FadeIn.h"
#include "Wisp.h"

Fase2::Fase2() : State() {

}

Fase2::~Fase2() {

} 

void Fase2::LoadAssets() {
    GameObject* gobg = new GameObject();
	Sprite* sprite = new Sprite(*gobg, "assets/img/cenario2/fundo caverna.png");
    sprite->SetCamMulti({0.0f,0.0f});
	sprite->SetScale(3.742690f,3.75f);
	gobg->AddComponent(sprite);
    gobg->box.pos = {0.0f,0.0f};
	AddObject(gobg);

    LoadPlataformas();

	AddObject(Game::GetInstance().playerStatus.hud.get());


    GameObject* goplayer = new GameObject();
	Player* player = new Player(*goplayer);
	goplayer->box.pos.x = -200;//300;
	goplayer->box.pos.y = (-732);//300;
	Camera::Fallow(goplayer);
    auto p = AddObject(goplayer);
	Game::GetInstance().playerStatus.player = p;

    GameObject* goWisp = new GameObject();
	Wisp* wisp = new Wisp(*goWisp, p, true);
	AddObject(goWisp);

    //GameObject* test = new GameObject();
    //test->AddComponent(new Sprite(*test, "assets/img/BlackWithHole.png"));

    GameObject* fadeInObj = new GameObject();
    FadeIn* fadeIn = new FadeIn(*fadeInObj, 2.0f);
    fadeIn->Begin();
    fadeInObj->AddComponent(fadeIn);
    AddObject(fadeInObj);

}

void Fase2::LoadPlataformas() {
    TileSet *chao2 = new TileSet(32, 32, "assets/img/chao3.png");
	TileSet *plat_hor_2 = new TileSet(32, 32, "assets/img/plat_hor_3.png");
	TileSet *plat_ver_2 = new TileSet(32, 32, "assets/img/plat_ver_3.png");


	GameObject *plat1Obj = new GameObject();
	PlataformaFixa *plat1 = new PlataformaFixa(*plat1Obj, chao2, "assets/map/fase2/plat1.txt");
	plat1Obj->box.pos = {-200, -1280 + 32 * 20};
	AddObject(plat1Obj);

    GameObject *plat2Obj = new GameObject();
	PlataformaFixa *plat2 = new PlataformaFixa(*plat2Obj, chao2, "assets/map/fase2/plat2.txt");
	plat2Obj->box.pos = {plat1Obj->box.pos.x + 32 * 23, plat1Obj->box.pos.y + 32 * 39};
	AddObject(plat2Obj);
}

void Fase2::Update(float dt) {
    Camera::Update(dt);
	UpdateArray(dt);
	if (InputManager::GetInstance().KeyPress(ESCAPE_KEY) || InputManager::GetInstance().QuitRequested()) {
		quitRequested = true;
	}
	for(unsigned int i = 0;i < objectArray.size();++i) {
        auto collider1 = (Collider*)objectArray[i]->GetComponent("Collider");
        if(collider1 != nullptr) {
            for (unsigned int j = i + 1; j < objectArray.size(); ++j) {
                auto collider2 = (Collider*)objectArray[j]->GetComponent("Collider");
                if(collider2 != nullptr) {
                    bool aux = Collision::IsColliding(collider1->box, collider2->box,
                                                      DegreesToRad(objectArray[i]->anlgleDeg),
                                                      DegreesToRad(objectArray[j]->anlgleDeg));
                    if(aux) {
                        objectArray[i]->NotifyCollision(*objectArray[j]);
                        objectArray[j]->NotifyCollision(*objectArray[i]);
                    }

                }
            }
        }
    }
}

void Fase2::Render() {
    RenderArray();
}

void Fase2::Start() {
    LoadAssets();
	StartArray();
}

void Fase2::Pause() {

}

void Fase2::Resume() {

}