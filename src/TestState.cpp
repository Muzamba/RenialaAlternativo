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
#include "Wisp.h"
#include "Resources.h"
#include "TransState.h"

TestState::TestState() : State() {
	fadeIn= new GameObject();
	fadeIn->AddComponent(new FadeIn(*fadeIn, 0.25f));

	fadeOut= new GameObject();
	fadeOut->AddComponent(new FadeOut(*fadeOut, 0.25f));

	Camera::pos = {0,0};
	Camera::SetFase(Camera::BONITA);
	musica = new Music("assets/sound/Reniala-fase-1-_64bpm_.ogg");
	musica->Play();
}

TestState::~TestState() {
	delete fadeIn;
	delete fadeOut;
	delete musica;
}

void TestState::LoadAssets() {
	
	LoadBg();

	LoadPlataformas();


	//GameObject* goHUD = new GameObject();
	//HUD* hud = new HUD(*goHUD);
	//Game::GetInstance().playerStatus.hud = AddObject(goHUD).lock();

	/*talisma*/
	//static bool first = true;
	//if(first) {
		//GameObject* talismaObject = new GameObject();
		//Talisma *talisma1 = new Talisma(*talismaObject, "assets/text/talisma1.txt", "assets/img/talismans/talisma_folha(1).png","assets/img/talismans/talisma_folha.png","assets/img/talismans/folha.png", Camera::BONITA, 0);
		//talismaObject->box.pos.x = 8850 + 220;//11000; 8900 - 50, 632 
		//talismaObject->box.pos.y = 550 ;//550;
		////GameData::talismaArray.emplace_back(talisma1);
		////talismaObject->AddComponent(talisma1);
		//((HUD*)Game::GetInstance().playerStatus.hud->GetComponent("HUD"))->AddTalisma(talismaObject);
		//first = false;
	//}

	
	
	
	LoadCenarioAtras();

	//GameObject* goplayer = new GameObject();
	//Player* player = new Player(*goplayer);
	//goplayer->box.pos.x = 11000;//300;
	//goplayer->box.pos.y = 300;
	//Camera::Fallow(goplayer);
	//auto p = AddObject(goplayer).lock();
	//Game::GetInstance().playerStatus.player = p;

	//GameObject* goWisp = new GameObject();
	//Wisp* wisp = new Wisp(*goWisp, p, false);
	//AddObject(goWisp);
	Game::GetInstance().playerStatus.player->box.mudaCentro({0,570});


	LoadCenarioFrente();
	


}

void TestState::LoadBg() {
	GameObject* ceu = new GameObject();
	Sprite* sprite = new Sprite(*ceu, "assets/img/cenario1/ceu.png");
	sprite->SetCamMulti({0.0f,0.0f});
	sprite->SetScale(3.742690f,3.75f);
	ceu->AddComponent(sprite);
	
	ceu->box.pos = {0,84}; //154
	AddObject(ceu);

	GameObject* montanhas_atras;
	for(int i = 0; i < 3; ++i) {
		montanhas_atras = new GameObject();
		sprite = new Sprite(*montanhas_atras, "assets/img/cenario1/montanhas-atras.png");
		sprite->SetCamMulti({0.2f,0.1f});
		sprite->SetScale(3.742690f,3.75f);
		montanhas_atras->AddComponent(sprite);
		montanhas_atras->box.pos = {1280.0f * i,0.0f};
		AddObject(montanhas_atras);
	}


	GameObject* montanhas_frente;
	for(int i = 0; i < 5; ++i) {
		montanhas_frente = new GameObject();
		sprite = new Sprite(*montanhas_frente, "assets/img/cenario1/montanhas-frente.png");
		sprite->SetCamMulti({0.4f,0.2f});
		sprite->SetScale(3.742690f,3.75f);
		montanhas_frente->AddComponent(sprite);
		montanhas_frente->box.pos = {1280.0f * i,0.0f};
		AddObject(montanhas_frente);
	}


	GameObject* grama_cima;
	for(int i = 0; i < 6; ++i) {
		grama_cima = new GameObject();
		sprite = new Sprite(*grama_cima, "assets/img/cenario1/grama-cima.png");
		sprite->SetCamMulti({0.6f,0.3f});
		sprite->SetScale(3.742690f,3.75f);
		grama_cima->AddComponent(sprite);
		grama_cima->box.pos = {1280.0f * i,-70.0f};
		AddObject(grama_cima);
	}


	GameObject* grama_baixo;
	for(int i = 0; i < 6; ++i) {
		grama_baixo = new GameObject();
		sprite = new Sprite(*grama_baixo, "assets/img/cenario1/grama-baixo.png");
		sprite->SetCamMulti({0.6f,0.3f});
		sprite->SetScale(3.742690f,3.75f);
		grama_baixo->AddComponent(sprite);
		grama_baixo->box.pos = {1280.0f * i,0.0f};
		AddObject(grama_baixo);
	}

	
}

void TestState::LoadPlataformas() {
	auto chao2 = Resources::GetTileSet("assets/img/chao2.png");
	auto plat_hor_2 = Resources::GetTileSet("assets/img/plat_hor_2.png");
	auto plat_ver_2 = Resources::GetTileSet("assets/img/plat_ver_2.png");


	GameObject *plat1Obj = new GameObject();
	PlataformaFixa *plat1 = new PlataformaFixa(*plat1Obj, chao2.get(), "assets/map/plat1.txt");
	plat1Obj->box.pos = {-50, 600};
	AddObject(plat1Obj);	

	GameObject *plat2Obj = new GameObject();
	PlataformaFixa *plat2 = new PlataformaFixa(*plat2Obj, chao2.get(), "assets/map/plat1.txt");
	plat2Obj->box.pos = {814, 600};
	AddObject(plat2Obj);

	GameObject *plat3Obj = new GameObject();
	PlataformaFixa *plat3 = new PlataformaFixa(*plat3Obj, chao2.get(), "assets/map/plat2.txt");
	plat3Obj->box.pos = {1728 - 50, 600};
	AddObject(plat3Obj);

	GameObject *plat4Obj = new GameObject();
	PlataformaFixa *plat4 = new PlataformaFixa(*plat4Obj, plat_hor_2.get(), "assets/map/plat3.txt");
	plat4Obj->box.pos = {2300 - 50, 530 };
	AddObject(plat4Obj);

	GameObject *plat5Obj = new GameObject();
	PlataformaFixa *plat5 = new PlataformaFixa(*plat5Obj, chao2.get(), "assets/map/plat4.txt");
	plat5Obj->box.pos = {2620 - 50, 600 };
	AddObject(plat5Obj);

	GameObject *plat6Obj = new GameObject();
	PlataformaFixa *plat6 = new PlataformaFixa(*plat6Obj, chao2.get(), "assets/map/plat5.txt");
	plat6Obj->box.pos = {2844 -  50, 536 };
	AddObject(plat6Obj);

	GameObject *plat7Obj = new GameObject();
	PlataformaFixa *plat7 = new PlataformaFixa(*plat7Obj, plat_hor_2.get(), "assets/map/plat3.txt");
	plat7Obj->box.pos = {3484 - 50, 480 };
	AddObject(plat7Obj);

	GameObject *plat8Obj = new GameObject();
	plat8Obj->box.pos = {3740 - 50, 440 };
	PlataformaMovel *plat8 = new PlataformaMovel(*plat8Obj, plat_hor_2.get(), "assets/map/plat3.txt", PlataformaMovel::HORIZONTAL, 100.0f, 0.2f);
	AddObject(plat8Obj);

	GameObject *plat9Obj = new GameObject();
	PlataformaFixa *plat9 = new PlataformaFixa(*plat9Obj, chao2.get(), "assets/map/plat2.txt");
	plat9Obj->box.pos = {4200 - 50, 536 };
	AddObject(plat9Obj);

	GameObject *plat10Obj = new GameObject();
	plat10Obj->box.pos = {4800 - 50, 480 };
	PlataformaMovel *plat10 = new PlataformaMovel(*plat10Obj, plat_hor_2.get(), "assets/map/plat3.txt", PlataformaMovel::HORIZONTAL, 100.0f, 0.2f);
	AddObject(plat10Obj);

	GameObject *plat11Obj = new GameObject();
	plat11Obj->box.pos = {5200 - 50, 550 };
	PlataformaMovel *plat11 = new PlataformaMovel(*plat11Obj, plat_hor_2.get(), "assets/map/plat3.txt", PlataformaMovel::VERTICAL, 100.0f, 0.2f);
	AddObject(plat11Obj);
	
	GameObject *plat12Obj = new GameObject();
	PlataformaFixa *plat12 = new PlataformaFixa(*plat12Obj, chao2.get(), "assets/map/plat2.txt");
	plat12Obj->box.pos = {5500, 536 };
	AddObject(plat12Obj);

	GameObject *plat13Obj = new GameObject();
	PlataformaFixa *plat13 = new PlataformaFixa(*plat13Obj, chao2.get(), "assets/map/plat2.txt");
	plat13Obj->box.pos = {6150 - 50, 536 };
	AddObject(plat13Obj);

	GameObject *plat14Obj = new GameObject();
	plat14Obj->box.pos = {6800 - 50, 480 };
	PlataformaMovel *plat14 = new PlataformaMovel(*plat14Obj, plat_hor_2.get(), "assets/map/plat3.txt", PlataformaMovel::HORIZONTAL, 100.0f, 0.2f);
	AddObject(plat14Obj);

	GameObject *plat15Obj = new GameObject();
	plat15Obj->box.pos = {7100 - 50, 450 };
	PlataformaMovel *plat15 = new PlataformaMovel(*plat15Obj, plat_hor_2.get(), "assets/map/plat3.txt", PlataformaMovel::VERTICAL, 100.0f, 0.1f);
	AddObject(plat15Obj);

	GameObject *plat16Obj = new GameObject();
	plat16Obj->box.pos = { 7400 - 50, 480 };
	PlataformaMovel *plat16 = new PlataformaMovel(*plat16Obj, plat_hor_2.get(), "assets/map/plat3.txt", PlataformaMovel::HORIZONTAL, 100.0f, 0.2f);
	AddObject(plat16Obj);

	//GameObject *plat17Obj = new GameObject();
	//PlataformaFixa *plat17 = new PlataformaFixa(*plat17Obj, chao2.get(), "assets/map/plat6.txt");
	//plat17Obj->box.pos = {7800 - 50, 536 };
	//AddObject(plat17Obj);

	GameObject *plat18Obj = new GameObject();
	PlataformaFixa *plat18 = new PlataformaFixa(*plat18Obj, chao2.get(), "assets/map/plat6.txt");
	plat18Obj->box.pos = {7800 - 50, 536 };
	AddObject(plat18Obj);

	GameObject *plat19Obj = new GameObject();
	PlataformaFixa *plat19 = new PlataformaFixa(*plat19Obj, chao2.get(), "assets/map/plat7.txt");
	plat19Obj->box.pos = {8216 - 50, 440 };
	AddObject(plat19Obj);

	GameObject *plat20Obj = new GameObject();
	PlataformaFixa *plat20 = new PlataformaFixa(*plat20Obj, chao2.get(), "assets/map/plat8.txt");
	plat20Obj->box.pos = {8900 - 50, 312 };
	AddObject(plat20Obj);

	GameObject *plat21Obj = new GameObject();
	PlataformaFixa *plat21 = new PlataformaFixa(*plat21Obj, chao2.get(), "assets/map/plat9.txt");
	plat21Obj->box.pos = {9284 - 50, 472 };
	AddObject(plat21Obj);

	GameObject *plat22Obj = new GameObject();
	PlataformaFixa *plat22 = new PlataformaFixa(*plat22Obj, chao2.get(), "assets/map/plat1.txt");
	plat22Obj->box.pos = {8900 - 50, 632 };
	AddObject(plat22Obj);

	

	GameObject *plat23Obj = new GameObject();
	plat23Obj->box.pos = {9732 - 50, 550 };
	PlataformaMovel *plat23 = new PlataformaMovel(*plat23Obj, plat_ver_2.get(), "assets/map/plat10.txt", PlataformaMovel::VERTICAL, 100.0f, 0.1f);
	AddObject(plat23Obj);

	GameObject *plat24Obj = new GameObject();
	PlataformaFixa *plat24 = new PlataformaFixa(*plat24Obj, plat_hor_2.get(), "assets/map/plat3.txt");
	plat24Obj->box.pos = {9892 - 50, 530 };
	AddObject(plat24Obj);

	GameObject *plat25Obj = new GameObject();
	plat25Obj->box.pos = {10244 - 150, 550 };
	PlataformaMovel *plat25 = new PlataformaMovel(*plat25Obj, plat_ver_2.get(), "assets/map/plat10.txt", PlataformaMovel::HORIZONTAL, 100.0f, 0.1f);
	AddObject(plat25Obj);

	GameObject *plat26Obj = new GameObject();
	PlataformaFixa *plat26 = new PlataformaFixa(*plat26Obj, plat_hor_2.get(), "assets/map/plat3.txt");
	plat26Obj->box.pos = {10436 - 50, 530 };
	AddObject(plat26Obj);

	GameObject *plat27Obj = new GameObject();
	PlataformaFixa *plat27 = new PlataformaFixa(*plat27Obj, chao2.get(), "assets/map/plat27.txt");
	plat27Obj->box.pos = {10628 - 50, 600 };
	AddObject(plat27Obj);


	

	//GameObject *platTransObj = new GameObject();
	//TileSet* tileCaverna = new TileSet(32, 32, "assets/img/chao3.png");
	//PlataformaFixa *platTras = new PlataformaFixa(*platTransObj,tileCaverna,"assets/map/platTras1.txt");
	//platTransObj->box.pos = {11058, 600};
	//AddObject(platTransObj);


}

void TestState::Update(float dt) {
	Camera::Update(dt);
	UpdateArray(dt);
	fadeIn->Update(dt);
	fadeOut->Update(dt);
	auto& playerStatus = Game::GetInstance().playerStatus;
	playerStatus.player->Update(dt);
	playerStatus.wisp->Update(dt);
	playerStatus.hud->Update(dt);
	playerStatus.dialogo->Update(dt);

	static bool first = true;
	if(((FadeOut*)fadeOut->GetComponent("FadeOut"))->timer.Get() > 0.25) {
		popRequested = true;
		Game::GetInstance().Push(new TransState(1));
		first = true;
		return;
	}

	
	if(Game::GetInstance().playerStatus.player->box.pos.x > 11100) {
		if(first){
			((FadeOut*)fadeOut->GetComponent("FadeOut"))->Begin();
			first = false;
			musica->Stop(0.25f);
		}
		
	} else if(Game::GetInstance().playerStatus.player->box.centro().x < -20){
		if(first){
			((FadeOut*)fadeOut->GetComponent("FadeOut"))->Begin();
			first = false;
			musica->Stop(0.25f);
		}
	}
	if(Game::GetInstance().playerStatus.player->box.pos.y > 720) {
		Game::GetInstance().playerStatus.player->box.pos = {300,300};
	}
	if (InputManager::GetInstance().KeyPress(ESCAPE_KEY) || InputManager::GetInstance().QuitRequested()) {
		quitRequested = true;
	}
	//for(unsigned int i = 0;i < objectArray.size();++i) {
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

void TestState::Render() {
	RenderArray();
	auto& playerStatus = Game::GetInstance().playerStatus;
	playerStatus.player->Render();
	playerStatus.wisp->Render();
	playerStatus.hud->Render();
	playerStatus.dialogo->Render();
	fadeIn->Render();
	fadeOut->Render();
}

void TestState::Pause() {}

void TestState::Resume() {}

void TestState::Start() {
	LoadAssets();
	StartArray();
	((FadeIn*)fadeIn->GetComponent("FadeIn"))->Begin();
}

void TestState::LoadCenarioAtras() {

}

void TestState::LoadCenarioFrente() {

}


