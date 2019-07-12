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
	arvore1->SetScale(1.8f, 1.5f);
	arvore1Obj->AddComponent(arvore1);
	arvore1Obj->box.pos = {200, 457};
	AddObject(arvore1Obj);

	GameObject *arvore2Obj = new GameObject();
	Sprite *arvore2 = new Sprite(*arvore2Obj, "assets/img/cenario1/arvore9.png");
	arvore2->SetScale(2.25f, 1.75f);
	arvore2Obj->AddComponent(arvore2);
	arvore2Obj->box.pos = {400, 377};
	AddObject(arvore2Obj);

	GameObject *grama1Obj = new GameObject();
	Sprite *grama1 = new Sprite(*grama1Obj, "assets/img/cenario1/arbustro1.png");
	grama1->SetScale(2.25f, 1.75f);
	grama1Obj->AddComponent(grama1);
	grama1Obj->box.pos = {400, 579};
	AddObject(grama1Obj);

	GameObject *grama2Obj = new GameObject();
	Sprite *grama2 = new Sprite(*grama2Obj, "assets/img/cenario1/arbustro1.png");
	grama2Obj->AddComponent(grama2);
	grama2Obj->box.pos = {600, 589};
	AddObject(grama2Obj);

	/*2 plataforma*/
	GameObject *arvore3Obj = new GameObject();
	Sprite *arvore3 = new Sprite(*arvore3Obj, "assets/img/cenario1/arvore10.png");
	arvore3->SetScale(1.7f, 1.25f);
	arvore3Obj->AddComponent(arvore3);
	arvore3Obj->box.pos = {1240, 442};
	AddObject(arvore3Obj);

	GameObject *grama3Obj = new GameObject();
	Sprite *grama3 = new Sprite(*grama3Obj, "assets/img/cenario1/arbustro1.png");
	grama3Obj->AddComponent(grama3);
	grama3Obj->box.pos = {1248, 589};
	AddObject(grama3Obj);
	
	/*4 plataforma*/
	GameObject *arvore4Obj = new GameObject();
	Sprite *arvore4 = new Sprite(*arvore4Obj, "assets/img/cenario1/arvore2.png");
	arvore4Obj->AddComponent(arvore4);
	arvore4Obj->box.pos = {2650, 508};
	AddObject(arvore4Obj);

	GameObject *grama5Obj = new GameObject();
	Sprite *grama5 = new Sprite(*grama5Obj, "assets/img/cenario1/arbustro2.png");
	grama5Obj->AddComponent(grama5);
	grama5Obj->box.pos = {2681, 591};
	AddObject(grama5Obj);

	GameObject *arvore5Obj = new GameObject();
	Sprite *arvore5 = new Sprite(*arvore5Obj, "assets/img/cenario1/arvore6.png");
	arvore5->SetScale(1.5f, 1.20f);
	arvore5Obj->AddComponent(arvore5);
	arvore5Obj->box.pos = {2950, 385};
	AddObject(arvore5Obj);

	GameObject *arvore6Obj = new GameObject();
	Sprite *arvore6 = new Sprite(*arvore6Obj, "assets/img/cenario1/arvore9.png");
	arvore6->SetScale(1.5f, 1.20f);
	arvore6Obj->AddComponent(arvore6);
	arvore6Obj->box.pos = {3150, 383};
	AddObject(arvore6Obj);

	GameObject *grama6Obj = new GameObject();
	Sprite *grama6 = new Sprite(*grama6Obj, "assets/img/cenario1/arbustro2.png");
	grama6Obj->AddComponent(grama6);
	grama6Obj->box.pos = {3150, 525};
	AddObject(grama6Obj);

	GameObject *grama7Obj = new GameObject();
	Sprite *grama7 = new Sprite(*grama7Obj, "assets/img/cenario1/arbustro2.png");
	grama7Obj->AddComponent(grama7);
	grama7Obj->box.pos = {3200, 525};
	AddObject(grama7Obj);

	/*5 plataforma*/
	GameObject *arvore7Obj = new GameObject();
	Sprite *arvore7 = new Sprite(*arvore7Obj, "assets/img/cenario1/arvore8.png");
	arvore7->SetScale(1.5f, 1.20f);
	arvore7Obj->AddComponent(arvore7);
	arvore7Obj->box.pos = {4300, 383};
	AddObject(arvore7Obj);
	
	GameObject *arvore8Obj = new GameObject();
	Sprite *arvore8 = new Sprite(*arvore8Obj, "assets/img/cenario1/arvore4.png");
	arvore8->SetScale(0.8f, 0.8f);
	arvore8Obj->AddComponent(arvore8);
	arvore8Obj->box.pos = {4500, 463};
	AddObject(arvore8Obj);

	/*6 plataforma*/
	GameObject *arvore9Obj = new GameObject();
	Sprite *arvore9 = new Sprite(*arvore9Obj, "assets/img/cenario1/arvore1.png");
	arvore9->SetScale(0.8f, 0.8f);
	arvore9Obj->AddComponent(arvore9);
	arvore9Obj->box.pos = {5550, 463};
	AddObject(arvore9Obj);

	GameObject *arvore10Obj = new GameObject();
	Sprite *arvore10 = new Sprite(*arvore10Obj, "assets/img/cenario1/arvore5.png");
	arvore10->SetScale(0.8f, 0.8f);
	arvore10Obj->AddComponent(arvore10);
	arvore10Obj->box.pos = {5650, 463};
	AddObject(arvore10Obj);

	GameObject *arvore11Obj = new GameObject();
	Sprite *arvore11 = new Sprite(*arvore11Obj, "assets/img/cenario1/arvore3.png");
	arvore11->SetScale(0.8f, 0.8f);
	arvore11Obj->AddComponent(arvore11);
	arvore11Obj->box.pos = {5600, 463};
	AddObject(arvore11Obj);

	/*7 plataforma*/
	GameObject *arvore12Obj = new GameObject();
	Sprite *arvore12 = new Sprite(*arvore12Obj, "assets/img/cenario1/arvore10.png");
	arvore12->SetScale(1.5f, 1.20f);
	arvore12Obj->AddComponent(arvore12);
	arvore12Obj->box.pos = {6300, 385};
	AddObject(arvore12Obj);

	GameObject *grama9Obj = new GameObject();
	Sprite *grama9 = new Sprite(*grama9Obj, "assets/img/cenario1/arbustro3.png");
	grama9Obj->AddComponent(grama9);
	grama9Obj->box.pos = {6300, 525};
	AddObject(grama9Obj);

	GameObject *grama10Obj = new GameObject();
	Sprite *grama10 = new Sprite(*grama10Obj, "assets/img/cenario1/arbustro2.png");
	grama10Obj->AddComponent(grama10);
	grama10Obj->box.pos = {6355, 525};
	AddObject(grama10Obj);

	GameObject *grama11Obj = new GameObject();
	Sprite *grama11 = new Sprite(*grama11Obj, "assets/img/cenario1/arbustro1.png");
	grama11Obj->AddComponent(grama11);
	grama11Obj->box.pos = {6385, 527};
	AddObject(grama11Obj);

	/*8 plataforma*/
	GameObject *arvore13Obj = new GameObject();
	Sprite *arvore13 = new Sprite(*arvore13Obj, "assets/img/cenario1/arvore3.png");
	arvore13->SetScale(0.75f, 0.75f);
	arvore13Obj->AddComponent(arvore13);
	arvore13Obj->box.pos = {7800, 466};
	AddObject(arvore13Obj);

	GameObject *arvore14Obj = new GameObject();
	Sprite *arvore14 = new Sprite(*arvore14Obj, "assets/img/cenario1/arvore10.png");
	arvore14->SetScale(1.5f, 1.20f);
	arvore14Obj->AddComponent(arvore14);
	arvore14Obj->box.pos = {7895, 385};
	AddObject(arvore14Obj);

	GameObject *grama12Obj = new GameObject();
	Sprite *grama12 = new Sprite(*grama12Obj, "assets/img/cenario1/arbustro1.png");
	grama12->SetScale(0.90f, 0.90f);
	grama12Obj->AddComponent(grama12);
	grama12Obj->box.pos = {7904, 527};
	AddObject(grama12Obj);

	GameObject *grama13Obj = new GameObject();
	Sprite *grama13 = new Sprite(*grama13Obj, "assets/img/cenario1/arbustro1.png");
	grama13->SetScale(0.90f, 0.90f);
	grama13Obj->AddComponent(grama13);
	grama13Obj->box.pos = {7944, 527};
	AddObject(grama13Obj);

	GameObject *grama14Obj = new GameObject();
	Sprite *grama14 = new Sprite(*grama14Obj, "assets/img/cenario1/arbustro1.png");
	grama14Obj->AddComponent(grama14);
	grama14Obj->box.pos = {7920, 527};
	AddObject(grama14Obj);

	GameObject *grama15Obj = new GameObject();
	Sprite *grama15 = new Sprite(*grama15Obj, "assets/img/cenario1/arbustro1.png");
	grama15->SetScale(0.75f, 0.75f);
	grama15Obj->AddComponent(grama15);
	grama15Obj->box.pos = {7813, 528};
	AddObject(grama15Obj);

	/*9 plataforma*/
	GameObject *arvore15Obj = new GameObject();
	Sprite *arvore15 = new Sprite(*arvore15Obj, "assets/img/cenario1/arvore10.png");
	arvore15->SetScale(1.5f, 1.20f);
	arvore15Obj->AddComponent(arvore15);
	arvore15Obj->box.pos = {8895, 162};
	AddObject(arvore15Obj);

	GameObject *arvore16Obj = new GameObject();
	Sprite *arvore16 = new Sprite(*arvore16Obj, "assets/img/cenario1/arvore7.png");
	arvore16->SetScale(1.1f, 1.0f);
	arvore16Obj->AddComponent(arvore16);
	arvore16Obj->box.pos = {8990, 188};
	AddObject(arvore16Obj);

	GameObject *arvore17Obj = new GameObject();
	Sprite *arvore17 = new Sprite(*arvore17Obj, "assets/img/cenario1/arvore10.png");
	arvore17->SetScale(1.5f, 1.30f);
	arvore17Obj->AddComponent(arvore17);
	arvore17Obj->box.pos = {9040, 150};
	AddObject(arvore17Obj);

	GameObject *arvore18Obj = new GameObject();
	Sprite *arvore18 = new Sprite(*arvore18Obj, "assets/img/cenario1/arvore6.png");
	arvore18Obj->AddComponent(arvore18);
	arvore18Obj->box.pos = {9200, 187};
	AddObject(arvore18Obj);

	GameObject *grama17Obj = new GameObject();
	Sprite *grama17 = new Sprite(*grama17Obj, "assets/img/cenario1/arbustro1.png");
	grama17Obj->AddComponent(grama17);
	grama17Obj->box.pos = {9030, 301};
	AddObject(grama17Obj);

	GameObject *grama16Obj = new GameObject();
	Sprite *grama16 = new Sprite(*grama16Obj, "assets/img/cenario1/arbustro1.png");
	grama16Obj->AddComponent(grama16);
	grama16Obj->box.pos = {9000, 302};
	AddObject(grama16Obj);


	GameObject *grama18Obj = new GameObject();
	Sprite *grama18 = new Sprite(*grama18Obj, "assets/img/cenario1/arbustro1.png");
	grama18Obj->AddComponent(grama18);
	grama18Obj->box.pos = {9062, 304};
	AddObject(grama18Obj);
}

void TestState::LoadCenarioFrente() {
	/*1 plataforma*/
	GameObject *flor1Obj = new GameObject();
	Sprite *flor1 = new Sprite(*flor1Obj, "assets/img/cenario1/flor6.png");
	flor1->SetScale(2.1f, 2.5f);
	flor1Obj->AddComponent(flor1);
	flor1Obj->box.pos = {50, 645};
	AddObject(flor1Obj); //colocar paralax

	GameObject *flor2Obj = new GameObject();
	Sprite *flor2 = new Sprite(*flor2Obj, "assets/img/cenario1/flor7.png");
	flor2->SetScale(2.1f, 2.5f);
	flor2Obj->AddComponent(flor2);
	flor2Obj->box.pos = {30, 690};
	AddObject(flor2Obj); //colocar paralax

	GameObject *flor3Obj = new GameObject();
	Sprite *flor3 = new Sprite(*flor3Obj, "assets/img/cenario1/flor7.png");
	flor3->SetScale(2.1f, 2.5f);
	flor3Obj->AddComponent(flor3);
	flor3Obj->box.pos = {80, 690};
	AddObject(flor3Obj); //colocar paralax

	GameObject *flor4Obj = new GameObject();
	Sprite *flor4 = new Sprite(*flor4Obj, "assets/img/cenario1/flor6.png");
	flor4->SetScale(2.1f, 2.5f);
	flor4Obj->AddComponent(flor4);
	flor4Obj->box.pos = {100, 670};
	AddObject(flor4Obj); //colocar paralax

	/*2 plataforma*/
	GameObject *flor5Obj = new GameObject();
	Sprite *flor5 = new Sprite(*flor5Obj, "assets/img/cenario1/flor8.png");
	//flor5->SetScale(2.1f, 2.5f);
	flor5Obj->AddComponent(flor5);
	flor5Obj->box.pos = {930, 595};
	AddObject(flor5Obj); //colocar paralax


	GameObject *grama4Obj = new GameObject();
	Sprite *grama4 = new Sprite(*grama4Obj, "assets/img/cenario1/arbustro2.png");
	grama4->SetScale(1.2f, 1.2f);
	grama4Obj->AddComponent(grama4);
	grama4Obj->box.pos = {1288, 589};
	AddObject(grama4Obj);

	GameObject *flor6Obj = new GameObject();
	Sprite *flor6 = new Sprite(*flor6Obj, "assets/img/cenario1/flor4.png");
	//flor5->SetScale(2.1f, 2.5f);
	flor6Obj->AddComponent(flor6);
	flor6Obj->box.pos = {1350, 605};
	AddObject(flor6Obj); //colocar paralax

	GameObject *grama8Obj = new GameObject();
	Sprite *grama8 = new Sprite(*grama8Obj, "assets/img/cenario1/arbustro2.png");
	grama8Obj->AddComponent(grama8);
	grama8Obj->box.pos = {3170, 528};
	AddObject(grama8Obj);
}


