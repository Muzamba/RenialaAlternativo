#include "TestState.h"
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
#include "Fase2.h"
#include "FadeOut.h"

TestState::TestState() : State() {

}

void TestState::LoadAssets() {
	GameObject* gobg = new GameObject();
	Sprite* sprite = new Sprite(*gobg, "assets/img/cenario arvore inacabado4.png");
	gobg->AddComponent(sprite);
	gobg->AddComponent(new CameraFollower(*gobg));
	gobg->box.pos = {0,0};
	AddObject(gobg);


	GameObject* goHUD = new GameObject();
	HUD* hud = new HUD(*goHUD);
	AddObject(goHUD);


	LoadPlataformas();
	
	
	//GameObject* goPlat = new GameObject();
	//TileSet* tile = new TileSet(32, 32, "assets/img/chao2.png");
	//PlataformaFixa* plat = new PlataformaFixa(*goPlat,tile, "assets/map/test.txt");
	//goPlat->AddComponent(plat);
	//goPlat->AddComponent(new Physic(*goPlat,Physic::CHAO));
	//goPlat->box.pos.y = 400;
	//goPlat->box.pos.x = 100;
	//AddObject(goPlat);
//
	//GameObject* goPlat2 = new GameObject();
	//
	//goPlat2->box.pos.y = 300;
	//goPlat2->box.pos.x = 100;
	//PlataformaMovel* plat2 = new PlataformaMovel(*goPlat2,tile, "assets/map/platTest.txt",PlataformaMovel::VERTICAL, 150.0f, 0.1f);
	//goPlat2->AddComponent(plat2);
	//goPlat2->AddComponent(new Physic(*goPlat2,Physic::CHAO));
	//AddObject(goPlat2);


	//TileSet *chao2 = new TileSet(32, 32, "assets/img/chao2.png");
//
	//GameObject *plat1Obj = new GameObject();
	//PlataformaFixa *plat1 = new PlataformaFixa(*plat1Obj, chao2, "assets/map/plat1.txt");
	//plat1Obj->box.pos = {0, 400};
	//AddObject(plat1Obj);

	GameObject* goplayer = new GameObject();
	Player* player = new Player(*goplayer);
	goplayer->box.pos.x = 11000;//300;
	goplayer->box.pos.y = 300;
	Camera::Fallow(goplayer);
	Game::GetInstance().playerStatus.player = AddObject(goplayer);

	


}

void TestState::LoadPlataformas() {
	TileSet *chao2 = new TileSet(32, 32, "assets/img/chao2.png");
	TileSet *plat_hor_2 = new TileSet(32, 32, "assets/img/plat_hor_2.png");
	TileSet *plat_ver_2 = new TileSet(32, 32, "assets/img/plat_ver_2.png");


	GameObject *plat1Obj = new GameObject();
	PlataformaFixa *plat1 = new PlataformaFixa(*plat1Obj, chao2, "assets/map/plat1.txt");
	plat1Obj->box.pos = {-50, 500};
	AddObject(plat1Obj);	

	GameObject *plat2Obj = new GameObject();
	PlataformaFixa *plat2 = new PlataformaFixa(*plat2Obj, chao2, "assets/map/plat1.txt");
	plat2Obj->box.pos = {814, 500};
	AddObject(plat2Obj);

	GameObject *plat3Obj = new GameObject();
	PlataformaFixa *plat3 = new PlataformaFixa(*plat3Obj, chao2, "assets/map/plat2.txt");
	plat3Obj->box.pos = {1728 - 50, 500};
	AddObject(plat3Obj);

	GameObject *plat4Obj = new GameObject();
	PlataformaFixa *plat4 = new PlataformaFixa(*plat4Obj, plat_hor_2, "assets/map/plat3.txt");
	plat4Obj->box.pos = {2300 - 50, 530 - 100};
	AddObject(plat4Obj);

	GameObject *plat5Obj = new GameObject();
	PlataformaFixa *plat5 = new PlataformaFixa(*plat5Obj, chao2, "assets/map/plat4.txt");
	plat5Obj->box.pos = {2620 - 50, 600 - 100};
	AddObject(plat5Obj);

	GameObject *plat6Obj = new GameObject();
	PlataformaFixa *plat6 = new PlataformaFixa(*plat6Obj, chao2, "assets/map/plat5.txt");
	plat6Obj->box.pos = {2844 -  50, 536 - 100};
	AddObject(plat6Obj);

	GameObject *plat7Obj = new GameObject();
	PlataformaFixa *plat7 = new PlataformaFixa(*plat7Obj, plat_hor_2, "assets/map/plat3.txt");
	plat7Obj->box.pos = {3484 - 50, 480 - 100};
	AddObject(plat7Obj);

	GameObject *plat8Obj = new GameObject();
	plat8Obj->box.pos = {3740 - 50, 440 - 100};
	PlataformaMovel *plat8 = new PlataformaMovel(*plat8Obj, plat_hor_2, "assets/map/plat3.txt", PlataformaMovel::HORIZONTAL, 100.0f, 0.2f);
	AddObject(plat8Obj);

	GameObject *plat9Obj = new GameObject();
	PlataformaFixa *plat9 = new PlataformaFixa(*plat9Obj, chao2, "assets/map/plat2.txt");
	plat9Obj->box.pos = {4200 - 50, 536 - 100};
	AddObject(plat9Obj);

	GameObject *plat10Obj = new GameObject();
	plat10Obj->box.pos = {4800 - 50, 480 - 100};
	PlataformaMovel *plat10 = new PlataformaMovel(*plat10Obj, plat_hor_2, "assets/map/plat3.txt", PlataformaMovel::HORIZONTAL, 100.0f, 0.2f);
	AddObject(plat10Obj);

	GameObject *plat11Obj = new GameObject();
	plat11Obj->box.pos = {5200 - 50, 550 - 100};
	PlataformaMovel *plat11 = new PlataformaMovel(*plat11Obj, plat_hor_2, "assets/map/plat3.txt", PlataformaMovel::VERTICAL, 100.0f, 0.2f);
	AddObject(plat11Obj);
	
	GameObject *plat12Obj = new GameObject();
	PlataformaFixa *plat12 = new PlataformaFixa(*plat12Obj, chao2, "assets/map/plat2.txt");
	plat12Obj->box.pos = {5500, 536 - 100};
	AddObject(plat12Obj);

	GameObject *plat13Obj = new GameObject();
	PlataformaFixa *plat13 = new PlataformaFixa(*plat13Obj, chao2, "assets/map/plat2.txt");
	plat13Obj->box.pos = {6150 - 50, 536 - 100};
	AddObject(plat13Obj);

	GameObject *plat14Obj = new GameObject();
	plat14Obj->box.pos = {6800 - 50, 480 - 100};
	PlataformaMovel *plat14 = new PlataformaMovel(*plat14Obj, plat_hor_2, "assets/map/plat3.txt", PlataformaMovel::HORIZONTAL, 100.0f, 0.2f);
	AddObject(plat14Obj);

	GameObject *plat15Obj = new GameObject();
	plat15Obj->box.pos = {7100 - 50, 450 - 100};
	PlataformaMovel *plat15 = new PlataformaMovel(*plat15Obj, plat_hor_2, "assets/map/plat3.txt", PlataformaMovel::VERTICAL, 100.0f, 0.1f);
	AddObject(plat15Obj);

	GameObject *plat16Obj = new GameObject();
	plat16Obj->box.pos = { 7400 - 50, 480 - 100};
	PlataformaMovel *plat16 = new PlataformaMovel(*plat16Obj, plat_hor_2, "assets/map/plat3.txt", PlataformaMovel::HORIZONTAL, 100.0f, 0.2f);
	AddObject(plat16Obj);

	//GameObject *plat17Obj = new GameObject();
	//PlataformaFixa *plat17 = new PlataformaFixa(*plat17Obj, chao2, "assets/map/plat6.txt");
	//plat17Obj->box.pos = {7800 - 50, 536 - 100};
	//AddObject(plat17Obj);

	GameObject *plat18Obj = new GameObject();
	PlataformaFixa *plat18 = new PlataformaFixa(*plat18Obj, chao2, "assets/map/plat6.txt");
	plat18Obj->box.pos = {7800 - 50, 536 - 100};
	AddObject(plat18Obj);

	GameObject *plat19Obj = new GameObject();
	PlataformaFixa *plat19 = new PlataformaFixa(*plat19Obj, chao2, "assets/map/plat7.txt");
	plat19Obj->box.pos = {8216 - 50, 440 - 100};
	AddObject(plat19Obj);

	GameObject *plat20Obj = new GameObject();
	PlataformaFixa *plat20 = new PlataformaFixa(*plat20Obj, chao2, "assets/map/plat8.txt");
	plat20Obj->box.pos = {8900 - 50, 312 - 100};
	AddObject(plat20Obj);

	GameObject *plat21Obj = new GameObject();
	PlataformaFixa *plat21 = new PlataformaFixa(*plat21Obj, chao2, "assets/map/plat9.txt");
	plat21Obj->box.pos = {9284 - 50, 472 - 100};
	AddObject(plat21Obj);

	GameObject *plat22Obj = new GameObject();
	PlataformaFixa *plat22 = new PlataformaFixa(*plat22Obj, chao2, "assets/map/plat1.txt");
	plat22Obj->box.pos = {8900 - 50, 632 - 100};
	AddObject(plat22Obj);

	/*talisma*/
	GameObject* talismaObject = new GameObject();
	Talisma *talisma1 = new Talisma(*talismaObject, "assets/img/planta.png", "assets/text/talisma1.txt",2);
	talismaObject->box.pos.x = 200;//plat22Obj->box.pos.x + 220;
	talismaObject->box.pos.y = 400;//plat22Obj->box.pos.y - 60;
	//GameData::talismaArray.emplace_back(talisma1);
	//talismaObject->AddComponent(talisma1);
	AddObject(talismaObject);

	GameObject *plat23Obj = new GameObject();
	plat23Obj->box.pos = {9732 - 50, 550 - 100};
	PlataformaMovel *plat23 = new PlataformaMovel(*plat23Obj, plat_ver_2, "assets/map/plat10.txt", PlataformaMovel::VERTICAL, 100.0f, 0.1f);
	AddObject(plat23Obj);

	GameObject *plat24Obj = new GameObject();
	PlataformaFixa *plat24 = new PlataformaFixa(*plat24Obj, plat_hor_2, "assets/map/plat3.txt");
	plat24Obj->box.pos = {9892 - 50, 530 - 100};
	AddObject(plat24Obj);

	GameObject *plat25Obj = new GameObject();
	plat25Obj->box.pos = {10244 - 150, 550 - 100};
	PlataformaMovel *plat25 = new PlataformaMovel(*plat25Obj, plat_ver_2, "assets/map/plat10.txt", PlataformaMovel::HORIZONTAL, 100.0f, 0.1f);
	AddObject(plat25Obj);

	GameObject *plat26Obj = new GameObject();
	PlataformaFixa *plat26 = new PlataformaFixa(*plat26Obj, plat_hor_2, "assets/map/plat3.txt");
	plat26Obj->box.pos = {10436 - 50, 530 - 100};
	AddObject(plat26Obj);

	GameObject *plat27Obj = new GameObject();
	PlataformaFixa *plat27 = new PlataformaFixa(*plat27Obj, chao2, "assets/map/plat27.txt");
	plat27Obj->box.pos = {10628 - 50, 600 - 100};
	AddObject(plat27Obj);

	GameObject *platTransObj = new GameObject();
	TileSet* tileCaverna = new TileSet(32, 32, "assets/img/chao3.png");
	PlataformaFixa *platTras = new PlataformaFixa(*platTransObj,tileCaverna,"assets/map/platTras1.txt");
	platTransObj->box.pos = {11058, 500};
	AddObject(platTransObj);


}

void TestState::Update(float dt) {
	Camera::Update(dt);
	UpdateArray(dt);
	if(Game::GetInstance().playerStatus.player.lock()->box.pos.x > 11100) {
		static GameObject* fadeOutObj = new GameObject();
		static FadeOut* fadeOut = new FadeOut(*fadeOutObj, 1.0f);
		static bool firstRun = true;
		if(firstRun){
			fadeOutObj->AddComponent(fadeOut);
			fadeOut->Begin();
			AddObject(fadeOutObj);
			firstRun = false;
		}
		if(fadeOut->timer.Get() > 1.0f) {
			popRequested = true;
			Game::GetInstance().Push(new Fase2());
		}
	}
	if (InputManager::GetInstance().KeyPress(ESCAPE_KEY) || InputManager::GetInstance().QuitRequested()) {
		quitRequested = true;
	}
	for(uint i = 0;i < objectArray.size();++i) {
        auto collider1 = (Collider*)objectArray[i]->GetComponent("Collider");
        if(collider1 != nullptr) {
            for (uint j = i + 1; j < objectArray.size(); ++j) {
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

void TestState::Render() {
	RenderArray();
}

void TestState::Pause() {}

void TestState::Resume() {}

void TestState::Start() {
	//LoadPlataformas();
	LoadAssets();
	StartArray();
}