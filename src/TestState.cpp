#include "TestState.h"
#include "Collider.h"
#include "Collision.h"
#include "Player.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Camera.h"
#include "PauseState.h"
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
	frontArray.clear();
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
	static auto chao2 = Resources::GetTileSet("assets/img/chao2.png");
	static auto plat_hor_2 = Resources::GetTileSet("assets/img/plat_hor_2.png");
	static auto plat_ver_2 = Resources::GetTileSet("assets/img/plat_ver_2.png");


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
	plat4Obj->box.pos = {2325 - 50, 530 };
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
	plat14Obj->box.pos = {6700 - 50, 480 };
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

	for(auto& obj : frontArray) {
		obj->Update(dt);
	}

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
			musica->Stop(250);
		}
		
	} else if(Game::GetInstance().playerStatus.player->box.centro().x < -20){
		if(first){
			((FadeOut*)fadeOut->GetComponent("FadeOut"))->Begin();
			first = false;
			musica->Stop(250);
		}
	}
	if(Game::GetInstance().playerStatus.player->box.pos.y > 720) {
		Game::GetInstance().playerStatus.player->box.pos = {300,300};
	}
	if(InputManager::GetInstance().KeyPress(ESCAPE_KEY) ){
		Game::GetInstance().Push(new PauseState());
	}
	if (InputManager::GetInstance().QuitRequested()) {
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
	{
	static bool first = true;
    if (first){
        ((Dialogo*)Game::GetInstance().playerStatus.dialogo->GetComponent("Dialogo"))->Begin("Uau que lugar bonito >.<", "boneco");
        first = false;
    }
	}
}

void TestState::Render() {
	RenderArray();
	auto& playerStatus = Game::GetInstance().playerStatus;
	playerStatus.player->Render();
	playerStatus.wisp->Render();
	playerStatus.hud->Render();
	for(auto& obj : frontArray){
		obj->Render();
	}

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
	/*1 plataforma*/
	GameObject *arvore1Obj = new GameObject();
	Sprite *arvore1 = new Sprite(*arvore1Obj, "assets/img/cenario1/arvore3.png");
	arvore1->SetScale(4.0f, 4.0f);
	arvore1Obj->AddComponent(arvore1);
	arvore1Obj->box.pos = {200, 220};
	AddObject(arvore1Obj);

	GameObject *arvore2Obj = new GameObject();
	Sprite *arvore2 = new Sprite(*arvore2Obj, "assets/img/cenario1/arvore9.png");
	arvore2->SetScale(4.0f, 4.0f);
	arvore2Obj->AddComponent(arvore2);
	arvore2Obj->box.pos = {400, 92};
	AddObject(arvore2Obj);

	GameObject *grama1Obj = new GameObject();
	Sprite *grama1 = new Sprite(*grama1Obj, "assets/img/cenario1/arbustro1.png");
	grama1->SetScale(4.0f, 4.0f);
	grama1Obj->AddComponent(grama1);
	grama1Obj->box.pos = {300, 552};
	AddObject(grama1Obj);

	GameObject *grama2Obj = new GameObject();
	Sprite *grama2 = new Sprite(*grama2Obj, "assets/img/cenario1/arbustro1.png");
	grama2->SetScale(4.0f, 4.0f);
	grama2Obj->AddComponent(grama2);
	grama2Obj->box.pos = {520, 552};
	AddObject(grama2Obj);

	/*2 plataforma*/
	GameObject *arvore3Obj = new GameObject();
	Sprite *arvore3 = new Sprite(*arvore3Obj, "assets/img/cenario1/arvore10.png");
	arvore3->SetScale(4.0f, 4.0f);
	arvore3Obj->AddComponent(arvore3);
	arvore3Obj->box.pos = {1240, 92};
	AddObject(arvore3Obj);

	GameObject *grama3Obj = new GameObject();
	Sprite *grama3 = new Sprite(*grama3Obj, "assets/img/cenario1/arbustro1.png");
	grama3->SetScale(4.0f, 4.0f);
	grama3Obj->AddComponent(grama3);
	grama3Obj->box.pos = {1248, 552};
	AddObject(grama3Obj);
	
	/*3 plataforma*/
	GameObject *arvore3_1Obj = new GameObject();
	Sprite *arvore3_1 = new Sprite(*arvore3_1Obj, "assets/img/cenario1/arvore2.png");
	arvore3_1->SetScale(4.0f, 4.0f);
	arvore3_1Obj->AddComponent(arvore3_1);
	arvore3_1Obj->box.pos = {1800, 220};
	AddObject(arvore3_1Obj);
	/*4 plataforma*/
	GameObject *arvore4Obj = new GameObject();
	Sprite *arvore4 = new Sprite(*arvore4Obj, "assets/img/cenario1/arvore2.png");
	arvore4->SetScale(4.0f, 4.0f);
	arvore4Obj->AddComponent(arvore4);
	arvore4Obj->box.pos = {2550, 220};
	AddObject(arvore4Obj);

	GameObject *grama5Obj = new GameObject();
	Sprite *grama5 = new Sprite(*grama5Obj, "assets/img/cenario1/arbustro2.png");
	grama5->SetScale(4.0f, 4.0f);
	grama5Obj->AddComponent(grama5);
	grama5Obj->box.pos = {2581, 554};
	AddObject(grama5Obj);

	GameObject *arvore5Obj = new GameObject();
	Sprite *arvore5 = new Sprite(*arvore5Obj, "assets/img/cenario1/arvore6.png");
	arvore5->SetScale(4.0f, 4.0f);
	arvore5Obj->AddComponent(arvore5);
	arvore5Obj->box.pos = {2850, 28};
	AddObject(arvore5Obj);

	GameObject *arvore6Obj = new GameObject();
	Sprite *arvore6 = new Sprite(*arvore6Obj, "assets/img/cenario1/arvore9.png");
	arvore6->SetScale(4.0f, 4.0f);
	arvore6Obj->AddComponent(arvore6);
	arvore6Obj->box.pos = {3100, 28};
	AddObject(arvore6Obj);

	/*5 plataforma*/
	GameObject *arvore7Obj = new GameObject();
	Sprite *arvore7 = new Sprite(*arvore7Obj, "assets/img/cenario1/arvore8.png");
	arvore7->SetScale(4.0f, 4.0f);
	arvore7Obj->AddComponent(arvore7);
	arvore7Obj->box.pos = {4150, 28};
	AddObject(arvore7Obj);
	
	GameObject *arvore8Obj = new GameObject();
	Sprite *arvore8 = new Sprite(*arvore8Obj, "assets/img/cenario1/arvore4.png");
	arvore8->SetScale(4.0f, 4.0f);
	arvore8Obj->AddComponent(arvore8);
	arvore8Obj->box.pos = {4450, 156};
	AddObject(arvore8Obj);

	/*6 plataforma*/

	GameObject *arvore10Obj = new GameObject();
	Sprite *arvore10 = new Sprite(*arvore10Obj, "assets/img/cenario1/arvore5.png");
	arvore10->SetScale(4.0f, 4.0f);
	arvore10Obj->AddComponent(arvore10);
	arvore10Obj->box.pos = {5475, 156};
	AddObject(arvore10Obj);

	GameObject *arvore9Obj = new GameObject();
	Sprite *arvore9 = new Sprite(*arvore9Obj, "assets/img/cenario1/arvore1.png");
	arvore9->SetScale(4.0f, 4.0f);
	arvore9Obj->AddComponent(arvore9);
	arvore9Obj->box.pos = {5750, 156};
	AddObject(arvore9Obj);
	
	/*7 plataforma*/
	GameObject *arvore12Obj = new GameObject();
	Sprite *arvore12 = new Sprite(*arvore12Obj, "assets/img/cenario1/arvore10.png");
	arvore12->SetScale(4.0f, 4.0f);
	arvore12Obj->AddComponent(arvore12);
	arvore12Obj->box.pos = {6300, 28};
	AddObject(arvore12Obj);

	GameObject *grama9Obj = new GameObject();
	Sprite *grama9 = new Sprite(*grama9Obj, "assets/img/cenario1/arbustro3.png");
	grama9->SetScale(4.0f, 4.0f);
	grama9Obj->AddComponent(grama9);
	grama9Obj->box.pos = {6300, 490};
	AddObject(grama9Obj);

	GameObject *grama10Obj = new GameObject();
	Sprite *grama10 = new Sprite(*grama10Obj, "assets/img/cenario1/arbustro2.png");
	grama10->SetScale(4.0f, 4.0f);
	grama10Obj->AddComponent(grama10);
	grama10Obj->box.pos = {6355, 490};
	AddObject(grama10Obj);

	GameObject *grama11Obj = new GameObject();
	Sprite *grama11 = new Sprite(*grama11Obj, "assets/img/cenario1/arbustro1.png");
	grama11->SetScale(4.0f, 4.0f);
	grama11Obj->AddComponent(grama11);
	grama11Obj->box.pos = {6385, 490};
	AddObject(grama11Obj);

	/*8 plataforma*/
	GameObject *arvore13Obj = new GameObject();
	Sprite *arvore13 = new Sprite(*arvore13Obj, "assets/img/cenario1/arvore3.png");
	arvore13->SetScale(4.0f, 4.0f);
	arvore13Obj->AddComponent(arvore13);
	arvore13Obj->box.pos = {7800, 156};
	AddObject(arvore13Obj);

	GameObject *arvore14Obj = new GameObject();
	Sprite *arvore14 = new Sprite(*arvore14Obj, "assets/img/cenario1/arvore10.png");
	arvore14->SetScale(4.0f, 4.0f);
	arvore14Obj->AddComponent(arvore14);
	arvore14Obj->box.pos = {7895, 28};
	AddObject(arvore14Obj);

	GameObject *grama12Obj = new GameObject();
	Sprite *grama12 = new Sprite(*grama12Obj, "assets/img/cenario1/arbustro1.png");
	grama12->SetScale(4.0f, 4.0f);
	grama12Obj->AddComponent(grama12);
	grama12Obj->box.pos = {7800, 490};
	AddObject(grama12Obj);

	GameObject *grama13Obj = new GameObject();
	Sprite *grama13 = new Sprite(*grama13Obj, "assets/img/cenario1/arbustro1.png");
	grama13->SetScale(4.0f, 4.0f);
	grama13Obj->AddComponent(grama13);
	grama13Obj->box.pos = {7944, 490};
	AddObject(grama13Obj);

	GameObject *grama14Obj = new GameObject();
	Sprite *grama14 = new Sprite(*grama14Obj, "assets/img/cenario1/arbustro1.png");
	grama14->SetScale(4.0f, 4.0f);
	grama14Obj->AddComponent(grama14);
	grama14Obj->box.pos = {7920, 490};
	AddObject(grama14Obj);


	/*9 plataforma*/
	GameObject *grama17Obj = new GameObject();
	Sprite *grama17 = new Sprite(*grama17Obj, "assets/img/cenario1/arbustro1.png");
	grama17->SetScale(4.0f, 4.0f);
	grama17Obj->AddComponent(grama17);
	grama17Obj->box.pos = {9030, 263};
	AddObject(grama17Obj);

	GameObject *grama16Obj = new GameObject();
	Sprite *grama16 = new Sprite(*grama16Obj, "assets/img/cenario1/arbustro1.png");
	grama16->SetScale(4.0f, 4.0f);
	grama16Obj->AddComponent(grama16);
	grama16Obj->box.pos = {9000, 263};
	AddObject(grama16Obj);

	GameObject *grama18Obj = new GameObject();
	Sprite *grama18 = new Sprite(*grama18Obj, "assets/img/cenario1/arbustro1.png");
	grama18->SetScale(4.0f, 4.0f);
	grama18Obj->AddComponent(grama18);
	grama18Obj->box.pos = {9062, 263};
	AddObject(grama18Obj);

	/*Ultima plataforma*/
	GameObject *arvore19Obj = new GameObject();
	Sprite *arvore19 = new Sprite(*arvore19Obj, "assets/img/cenario1/arvore9.png");
	arvore19->SetScale(4.0f, 4.0f);
	arvore19Obj->AddComponent(arvore19);
	arvore19Obj->box.pos = {10700, 92};
	AddObject(arvore19Obj);

	GameObject *arvore20Obj = new GameObject();
	Sprite *arvore20 = new Sprite(*arvore20Obj, "assets/img/cenario1/arvore3.png");
	arvore20->SetScale(4.0f, 4.0f);
	arvore20Obj->AddComponent(arvore20);
	arvore20Obj->box.pos = {10900, 220};
	AddObject(arvore20Obj);
}

void TestState::LoadCenarioFrente() {
	/*1 plataforma*/
	GameObject *flor1_2Obj = new GameObject();
	Sprite *flor1_2 = new Sprite(*flor1_2Obj, "assets/img/cenario1/flor8.png");
	flor1_2->SetScale(4.0f, 4.0f);
	flor1_2Obj->AddComponent(flor1_2);
	flor1_2Obj->box.pos = {0, 640};

	frontArray.emplace_back(flor1_2Obj); //colocar paralax


	GameObject *flor1Obj = new GameObject();
	Sprite *flor1 = new Sprite(*flor1Obj, "assets/img/cenario1/flor6.png");
	flor1->SetScale(4.0f, 4.0f);
	flor1Obj->AddComponent(flor1);
	flor1Obj->box.pos = {100, 610};

	frontArray.emplace_back(flor1Obj); //colocar paralax

	//flor1Obj->box.pos = {50, 645};
	//frontArray.emplace_back(flor1Obj); //colocar paralax

	GameObject *flor2Obj = new GameObject();
	Sprite *flor2 = new Sprite(*flor2Obj, "assets/img/cenario1/flor8.png");
	flor2->SetScale(4.0f, 4.0f);
	flor2Obj->AddComponent(flor2);
	flor2Obj->box.pos = {200, 640};

	frontArray.emplace_back(flor2Obj); //colocar paralax


	/*
	flor2Obj->box.pos = {30, 690};
	frontArray.emplace_back(flor2Obj); //colocar paralax

	GameObject *flor3Obj = new GameObject();
	Sprite *flor3 = new Sprite(*flor3Obj, "assets/img/cenario1/flor7.png");
	flor3->SetScale(2.1f, 2.5f);
	flor3Obj->AddComponent(flor3);
	flor3Obj->box.pos = {80, 690};
	frontArray.emplace_back(flor3Obj); //colocar paralax

	GameObject *flor4Obj = new GameObject();
	Sprite *flor4 = new Sprite(*flor4Obj, "assets/img/cenario1/flor6.png");
	flor4->SetScale(4.0f, 4.0f);
	flor4Obj->AddComponent(flor4);
	flor4Obj->box.pos = {240, 610};

	frontArray.emplace_back(flor4Obj); //colocar paralax

	//flor4Obj->box.pos = {100, 670};
	//frontArray.emplace_back(flor4Obj); //colocar paralax

	GameObject *flor3Obj = new GameObject();
	Sprite *flor3 = new Sprite(*flor3Obj, "assets/img/cenario1/flor7.png");
	flor3->SetScale(4.0f, 4.0f);
	flor3Obj->AddComponent(flor3);
	flor3Obj->box.pos = {260, 665};

	frontArray.emplace_back(flor3Obj); //colocar paralax


	/*2 plataforma*/
	/*GameObject *flor5Obj = new GameObject();
	Sprite *flor5 = new Sprite(*flor5Obj, "assets/img/cenario1/flor8.png");
	flor5->SetScale(2.1f, 2.5f);
	flor5Obj->AddComponent(flor5);
	flor5Obj->box.pos = {930, 665};

	frontArray.emplace_back(flor5Obj); //colocar paralax

	*/
	GameObject *flor5_2Obj = new GameObject();
	Sprite *flor5_2 = new Sprite(*flor5_2Obj, "assets/img/cenario1/flor8.png");
	flor5_2->SetScale(4.0f, 4.0f);
	flor5_2Obj->AddComponent(flor5_2);
	flor5_2Obj->box.pos = {930, 635};

	frontArray.emplace_back(flor5_2Obj); //colocar paralax

	//flor5Obj->box.pos = {930, 595};
	//frontArray.emplace_back(flor5Obj); //colocar paralax


	GameObject *grama4Obj = new GameObject();
	Sprite *grama4 = new Sprite(*grama4Obj, "assets/img/cenario1/arbustro2.png");
	grama4->SetScale(4.0f, 4.0f);
	grama4Obj->AddComponent(grama4);
	grama4Obj->box.pos = {1688, 558};

	frontArray.emplace_back(grama4Obj);

	//grama4Obj->box.pos = {1288, 589};
	//frontArray.emplace_back(grama4Obj);

	GameObject *flor6Obj = new GameObject();
	Sprite *flor6 = new Sprite(*flor6Obj, "assets/img/cenario1/flor4.png");
	flor6->SetScale(4.0f, 4.0f);
	flor6Obj->AddComponent(flor6);
	flor6Obj->box.pos = {1350, 605};
	//frontArray.emplace_back(flor6Obj); //colocar paralax

	GameObject *grama8Obj = new GameObject();
	Sprite *grama8 = new Sprite(*grama8Obj, "assets/img/cenario1/arbustro2.png");
	grama8->SetScale(4.0f, 4.0f);
	grama8Obj->AddComponent(grama8);
	grama8Obj->box.pos = {3170, 500};

	frontArray.emplace_back(grama8Obj);

	//grama8Obj->box.pos = {3170, 528};
	//frontArray.emplace_back(grama8Obj);
}


