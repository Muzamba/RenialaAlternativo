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
#include "FadeOut.h"
#include "Wisp.h"
#include "Resources.h"
#include "TransState.h"
#include "Gravidade.h"

Fase2::Fase2() : State() {
    fadeIn = new GameObject();
    fadeIn->AddComponent(new FadeIn(*fadeIn, 0.25f));
    fadeIn->AddComponent(new CameraFollower(*fadeIn));

    fadeOut = new GameObject();
    fadeOut->AddComponent(new FadeOut(*fadeOut, 0.25f));
    fadeOut->AddComponent(new CameraFollower(*fadeOut));

    Camera::SetFase(Camera::CAVERNA);
    Camera::pos = {0,0};
    ((Wisp*)Game::GetInstance().playerStatus.wisp->GetComponent("Wisp"))->fase2 = true;
	musica = new Music("assets/sound/Reniala-fase-2-_120bpm_.ogg");
	musica->Play();

	static bool first = true;
	if (first) {
		((Dialogo*)Game::GetInstance().playerStatus.dialogo->GetComponent("Dialogo"))->Begin("Nossa que escuro!!! Posso te ajudar a iluminar o seu caminho use as setinhas", "wisp");
        first = false;
	}
}

Fase2::~Fase2() {
    delete fadeIn;
    delete fadeOut;
    ((Wisp*)Game::GetInstance().playerStatus.wisp->GetComponent("Wisp"))->fase2 = false;
	delete musica;
} 

void Fase2::LoadAssets() {
    GameObject* gobg = new GameObject();
	Sprite* sprite = new Sprite(*gobg, "assets/img/cenario2/fundo caverna.png");
    sprite->SetCamMulti({0.0f,0.0f});
	sprite->SetScale(3.742690f,3.75f);
	gobg->AddComponent(sprite);
    gobg->box.pos = {0.0f,0.0f};
	AddObject(gobg);
    Game::GetInstance().playerStatus.player->box.mudaCentro({100, -7000});

    LoadPlataformas();

	
    

}

void Fase2::LoadPlataformas() {
    auto chao2 = Resources::GetTileSet("assets/img/chao3.png");
	auto plat_hor_2 = Resources::GetTileSet("assets/img/plat_hor_3.png");
	auto plat_ver_2 = Resources::GetTileSet("assets/img/plat_ver_3.png");

    //GameObject* andaime = new GameObject();
    //andaime->box.size = {10000,32};
    //andaime->box.pos = {0,-7008 + 32 * 0};
    //andaime->AddComponent(new Collider(*andaime));
    //andaime->AddComponent(new Physic(*andaime,Physic::CHAO));
    //AddObject(andaime);


	GameObject *platObj = new GameObject();
	new PlataformaFixa(*platObj, chao2.get(), "assets/map/fase2/plat1.txt");
	platObj->box.pos = {0,-7008};
	AddObject(platObj);

    platObj = new GameObject();
	platObj->box.pos = {1280 * 2 - 32* 2,-7008};
	new PlataformaFixa(*platObj, chao2.get(), "assets/map/fase2/plat2.txt");
	AddObject(platObj);

    platObj = new GameObject();
	platObj->box.pos = {32,-7008 + 32 * 6};
	new PlataformaFixa(*platObj, chao2.get(), "assets/map/fase2/plat3.txt");
	AddObject(platObj);

    platObj = new GameObject();
	platObj->box.pos = {32*10,-7008 - 32 * 2};
	new PlataformaFixa(*platObj, chao2.get(), "assets/map/fase2/plat4.txt");
	AddObject(platObj);

    platObj = new GameObject();
	platObj->box.pos = {32 * 67 ,-7008 + 32 * 6};
	new PlataformaFixa(*platObj, chao2.get(), "assets/map/fase2/plat5.txt");
	AddObject(platObj);

    platObj = new GameObject();
	platObj->box.pos = {32 * 38 ,-7008};
	new PlataformaFixa(*platObj, chao2.get(), "assets/map/fase2/plat6.txt");
	AddObject(platObj);

    platObj = new GameObject();
	platObj->box.pos = {32 * 57 ,-7008 + 32 * 7};
	new PlataformaMovel(*platObj, plat_hor_2.get(), "assets/map/fase2/plat7.txt",PlataformaMovel::VERTICAL, 32 * 6/2, 0.1f);
	AddObject(platObj);

    platObj = new GameObject();
	platObj->box.pos = {32 * 60 ,-7008 + 32 * 16};
	new PlataformaMovel(*platObj, plat_hor_2.get(), "assets/map/fase2/plat8.txt",PlataformaMovel::HORIZONTAL, 32 * 3, 0.15f);
	AddObject(platObj);

    platObj = new GameObject();
	platObj->box.pos = {32 * 57 ,-7008 + 32 * 18};
	new PlataformaMovel(*platObj, plat_hor_2.get(), "assets/map/fase2/plat9.txt",PlataformaMovel::VERTICAL, 32 * 6/2, 0.075f);
	AddObject(platObj);

    platObj = new GameObject();
	platObj->box.pos = {32 * 60 ,-7008 + 32 * 27};
	new PlataformaMovel(*platObj, plat_hor_2.get(), "assets/map/fase2/plat10.txt",PlataformaMovel::HORIZONTAL, 32 * 6, 0.1f);
	AddObject(platObj);

    platObj = new GameObject();
	platObj->box.pos = {32 * 57 ,-7008 + 32 * 29};
	new PlataformaMovel(*platObj, plat_hor_2.get(), "assets/map/fase2/plat11.txt",PlataformaMovel::VERTICAL, 32 * 8 /2, 0.075f);
	AddObject(platObj);

    platObj = new GameObject();
	platObj->box.pos = {32,-7008 + 32 * 25};
	new PlataformaFixa(*platObj, chao2.get(), "assets/map/fase2/plat12.txt");
	AddObject(platObj);

    platObj = new GameObject();
	platObj->box.pos = {32 * 45 ,-7008 + 32 * 39};
	new PlataformaMovel(*platObj, plat_hor_2.get(), "assets/map/fase2/plat13.txt",PlataformaMovel::HORIZONTAL, 32 * 12, 0.09f);
	AddObject(platObj);

    platObj = new GameObject();
	platObj->box.pos = {32 * 66 ,-7008 + 32 * 42};
	new PlataformaMovel(*platObj, plat_hor_2.get(), "assets/map/fase2/plat14.txt",PlataformaMovel::VERTICAL, 32 * 4 /2, 0.25f);
	AddObject(platObj);

    platObj = new GameObject();
	platObj->box.pos = {32 * 64 ,-7008 + 32 * 49};
	new PlataformaFixa(*platObj, chao2.get(), "assets/map/fase2/plat15.txt");
	AddObject(platObj);

    platObj = new GameObject();
	platObj->box.pos = {32 * 20 ,-7008 + 32 * 51};
	new PlataformaMovel(*platObj, plat_hor_2.get(), "assets/map/fase2/plat16.txt",PlataformaMovel::HORIZONTAL, 32 * 18, 0.05f);
	AddObject(platObj);

    platObj = new GameObject();
	platObj->box.pos = {32 * 30 ,-7008 + 32 * 55};
	new PlataformaFixa(*platObj, plat_hor_2.get(), "assets/map/fase2/plat17.txt");
	AddObject(platObj);


    platObj = new GameObject();
	platObj->box.pos = {32 * 20 ,-7008 + 32 * 60};
	new PlataformaFixa(*platObj, chao2.get(), "assets/map/fase2/plat18.txt");
	AddObject(platObj);

    platObj = new GameObject();
	platObj->box.pos = {32 * 42 ,-7008 + 32 * 63};
	new PlataformaMovel(*platObj, plat_hor_2.get(), "assets/map/fase2/plat19.txt",PlataformaMovel::HORIZONTAL, 32 * 10, 0.085f);
	AddObject(platObj);

    platObj = new GameObject();
	platObj->box.pos = {32 * 66 ,-7008 + 32 * 66};
	new PlataformaMovel(*platObj, plat_hor_2.get(), "assets/map/fase2/plat20.txt",PlataformaMovel::VERTICAL, 32 * 8 /2, 0.12f);
	AddObject(platObj);

    platObj = new GameObject();
	platObj->box.pos = {32 * 40 ,-7008 + 32 * 76};
	new PlataformaFixa(*platObj, chao2.get(), "assets/map/fase2/plat21.txt");
	AddObject(platObj);
    
    platObj = new GameObject();
	platObj->box.pos = {32 * 47 ,-7008 + 32 * 80};
	new PlataformaFixa(*platObj, chao2.get(), "assets/map/fase2/plat22.txt");
	AddObject(platObj);

    platObj = new GameObject();
	platObj->box.pos = {32 * 28 ,-7008 + 32 * 82};
	new PlataformaFixa(*platObj, chao2.get(), "assets/map/fase2/plat23.txt");
	AddObject(platObj);

    platObj = new GameObject();
	platObj->box.pos = {32 * 20 ,-7008 + 32 * 83};
	new PlataformaMovel(*platObj, plat_hor_2.get(), "assets/map/fase2/plat24.txt",PlataformaMovel::VERTICAL, 32 * 30 /2, 0.03f);
	AddObject(platObj);

    platObj = new GameObject();
	platObj->box.pos = {32 * 25 ,-7008 + 32 * 114};
	new PlataformaFixa(*platObj, chao2.get(), "assets/map/fase2/plat25.txt");
	AddObject(platObj);

    platObj = new GameObject();
	platObj->box.pos = {32 * 47 ,-7008 + 32 * 119};
	new PlataformaMovel(*platObj, plat_hor_2.get(), "assets/map/fase2/plat26.txt",PlataformaMovel::HORIZONTAL, 32 * 12, 0.045f);
	AddObject(platObj);

    platObj = new GameObject();
	platObj->box.pos = {32 * 61 ,-7008 + 32 * 122};
	new PlataformaMovel(*platObj, plat_hor_2.get(), "assets/map/fase2/plat27.txt",PlataformaMovel::VERTICAL, 32 * 30 /2, 0.03f);
	AddObject(platObj);

     platObj = new GameObject();
	platObj->box.pos = {32 * 4 ,-7008 + 32 * 154};
	new PlataformaMovel(*platObj, plat_hor_2.get(), "assets/map/fase2/plat28.txt",PlataformaMovel::HORIZONTAL, 32 * 28, 0.08f);
	AddObject(platObj);

    platObj = new GameObject();
	platObj->box.pos = {32 * 71 ,-7008 + 32 * 155};
	new PlataformaFixa(*platObj, chao2.get(), "assets/map/fase2/plat29.txt");
	AddObject(platObj);

    platObj = new GameObject();
	platObj->box.pos = {32 * 56 ,-7008 + 32 * 157};
	new PlataformaFixa(*platObj, chao2.get(), "assets/map/fase2/plat30.txt");
	AddObject(platObj);

    platObj = new GameObject();
	platObj->box.pos = {32 * 64 ,-7008 + 32 * 165};
	new PlataformaFixa(*platObj, chao2.get(), "assets/map/fase2/plat31.txt");
	AddObject(platObj);

    platObj = new GameObject();
	platObj->box.pos = {32 * 10 ,-7008 + 32 * 158};
	new PlataformaFixa(*platObj, chao2.get(), "assets/map/fase2/plat32.txt");
	AddObject(platObj);

    platObj = new GameObject();
	platObj->box.pos = {32 * 13 ,-7008 + 32 * 168};
	new PlataformaFixa(*platObj, chao2.get(), "assets/map/fase2/plat33.txt");
	AddObject(platObj);

    platObj = new GameObject();
	platObj->box.pos = {32 * 18 ,-7008 + 32 * 163};
	new PlataformaFixa(*platObj, plat_hor_2.get(), "assets/map/fase2/plat34.txt");
	AddObject(platObj);


    platObj = new GameObject();
	platObj->box.pos = {32 * 36 ,-7008 + 32 * 173};
	new PlataformaMovel(*platObj, plat_hor_2.get(), "assets/map/fase2/plat35.txt",PlataformaMovel::VERTICAL, 32 * 43 /2, 0.03f);
	AddObject(platObj);

    platObj = new GameObject();
	platObj->box.pos = {32 *  30,-7008 + 32 * 220};
	new PlataformaFixa(*platObj, chao2.get(), "assets/map/fase2/plat36.txt");
	AddObject(platObj);

    platObj = new GameObject();
	platObj->box.pos = {32 * 15 ,-7008 + 32 * 221};
	new PlataformaFixa(*platObj, chao2.get(), "assets/map/fase2/plat37.txt");
	AddObject(platObj);








}

void Fase2::Update(float dt) {
    auto& playerStatus = Game::GetInstance().playerStatus;
	if(InputManager::GetInstance().KeyPress(SDLK_h)){
		playerStatus.player->box.mudaCentro({32* 74, -32 * 210});
	}
    Camera::Update(dt);
	UpdateArray(dt);
    playerStatus.player->Update(dt);
	playerStatus.wisp->Update(dt);
	playerStatus.hud->Update(dt);
	playerStatus.dialogo->Update(dt);

    fadeIn->Update(dt);
    fadeOut->Update(dt);

	if (InputManager::GetInstance().KeyPress(ESCAPE_KEY) || InputManager::GetInstance().QuitRequested()) {
		quitRequested = true;
	}

	
    static bool first = true;

    if(Game::GetInstance().playerStatus.player->box.centro().y < - 7008 && first ){
        first = false;
        ((FadeOut*)fadeOut->GetComponent("FadeOut"))->Begin();
		musica->Stop(250);
    }

    if(((FadeOut*)fadeOut->GetComponent("FadeOut"))->timer.Get() > 0.25f) {
        popRequested = true;
        first = true;
        Game::GetInstance().Push(new TransState(3));
        ((Gravidade*)Game::GetInstance().playerStatus.player->GetComponent("Gravidade"))->SetVelocidade(-500);
        return;
    }
	//for(uint i = 0;i < objectArray.size();++i) {
    //    auto collider1 = (Collider*)objectArray[i]->GetComponent("Collider");
    //    if(collider1 != nullptr) {
    //        for (uint j = i + 1; j < objectArray.size(); ++j) {
    //            auto collider2 = (Collider*)objectArray[j]->GetComponent("Collider");
    //            if(collider2 != nullptr) {
    //                bool aux = Collision::IsColliding(collider1->box, collider2->box,
    //                                                  DegreesToRad(objectArray[i]->anlgleDeg),
    //                                                  DegreesToRad(objectArray[j]->anlgleDeg));
    //                if(aux) {
    //                    objectArray[i]->NotifyCollision(*objectArray[j]);
    //                    objectArray[j]->NotifyCollision(*objectArray[i]);
    //                }
//
    //            }
    //        }
    //    }
    //}
    auto collider1 = (Collider*)Game::GetInstance().playerStatus.player->GetComponent("Collider");
    for(unsigned int i = 0;i < objectArray.size();++i) {
        auto collider2 = (Collider*)objectArray[i]->GetComponent("Collider");
        if(collider2 != nullptr) {
            bool aux = Collision::IsColliding(collider1->box, collider2->box,
                                              DegreesToRad(Game::GetInstance().playerStatus.player->anlgleDeg),
                                              DegreesToRad(objectArray[i]->anlgleDeg));
            if(aux) {
                objectArray[i]->NotifyCollision(*Game::GetInstance().playerStatus.player);
                Game::GetInstance().playerStatus.player->NotifyCollision(*objectArray[i]);
            }
        }

    }
}

void Fase2::Render() {
    RenderArray();
    auto& playerStatus = Game::GetInstance().playerStatus;
    //playerStatus.player->Render();
	//playerStatus.wisp->Render();
	playerStatus.hud->Render();
	playerStatus.dialogo->Render();
	fadeIn->Render();
	fadeOut->Render();
}

void Fase2::Start() {
    LoadAssets();
	StartArray();
    ((FadeIn*)fadeIn->GetComponent("FadeIn"))->Begin();
}

void Fase2::Pause() {

}

void Fase2::Resume() {

}