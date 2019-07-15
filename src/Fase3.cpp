#include "Fase3.h"
#include "FadeIn.h"
#include "FadeOut.h"
#include "Game.h" 
#include "Collider.h"
#include "Collision.h"
#include "Camera.h"
#include "InputManager.h"
#include "Resources.h"
#include "PlataformaFixa.h"
#include "TransState.h"

Fase3::Fase3() {
    fadeIn = new GameObject();
    auto fade = new FadeIn(*fadeIn, 0.25f);
    fadeIn->AddComponent(fade);

    fadeOut = new GameObject();
    fade = new FadeOut(*fadeOut, 0.25f);
    fadeOut->AddComponent(fade);

    


    musica = new Music("assets/sound/Reniala-fase-3-_67bpm_.ogg");
    musica ->Play();
}

Fase3::~Fase3() {
    delete fadeIn;
    delete fadeOut;
    delete musica;
    frontArray.clear();
}


void Fase3::LoadAssets() {
    LoadBg();
    LoadPlataformas();
     Game::GetInstance().playerStatus.player->box.mudaCentro({0,550});
     Camera::SetFase(Camera::FEIA);

}

void Fase3::LoadPlataformas() {
    auto chao = Resources::GetTileSet("assets/img/chao4.png").get();
    auto plat = Resources::GetTileSet("assets/img/plat_hor_4.png").get();

    GameObject* chao1 = new GameObject();
    new PlataformaFixa(*chao1,chao,"assets/map/fase3/plat1.txt");
    AddObject(chao1);
    chao1->box.pos = {-10,650};

    GameObject* plat1 = new GameObject();
    new PlataformaFixa(*plat1,plat,"assets/map/fase3/plat2.txt");
    plat1->box.pos = {1292, 600};
    AddObject(plat1);
    
}

void Fase3::LoadBg() {
    GameObject* ceu = new GameObject();
	Sprite* sprite = new Sprite(*ceu, "assets/img/cenario3/ceu.png");
	sprite->SetCamMulti({0.0f,0.0f});
	sprite->SetScale(3.742690f,3.75f);
	ceu->AddComponent(sprite);
	
	ceu->box.pos = {0,0}; //154
	AddObject(ceu);

    GameObject* fumaca1;
	for(int i = 0; i < 2; ++i) {
		fumaca1 = new GameObject();
		sprite = new Sprite(*fumaca1, "assets/img/cenario3/nuvem1.png");
		sprite->SetCamMulti({0.14f,0.0f});
		sprite->SetScale(3.742690f,3.75f);
        sprite->SetAlphaChannel(128);
		fumaca1->AddComponent(sprite);
		fumaca1->box.pos = {1280.0f * i,0.0f};
		AddObject(fumaca1);
	}

    GameObject* fumaca2;
	for(int i = 0; i < 2; ++i) {
		fumaca2 = new GameObject();
		sprite = new Sprite(*fumaca2, "assets/img/cenario3/nuvem2.png");
		sprite->SetCamMulti({0.28f,0.0f});
		sprite->SetScale(3.742690f,3.75f);
        sprite->SetAlphaChannel(128);
		fumaca2->AddComponent(sprite);
		fumaca2->box.pos = {1280.0f * i,0.0f};
		AddObject(fumaca2);
	}

	GameObject* montanhas_atras;
	for(int i = 0; i < 2; ++i) {
		montanhas_atras = new GameObject();
		sprite = new Sprite(*montanhas_atras, "assets/img/cenario3/montanhas2.png");
		sprite->SetCamMulti({0.42f,0.0f});
		sprite->SetScale(3.742690f,3.75f);
		montanhas_atras->AddComponent(sprite);
		montanhas_atras->box.pos = {1280.0f * i,0.0f};
		AddObject(montanhas_atras);
	}


	GameObject* montanhas_frente;
	for(int i = 0; i < 2; ++i) {
		montanhas_frente = new GameObject();
		sprite = new Sprite(*montanhas_frente, "assets/img/cenario3/montanhas1.png");
		sprite->SetCamMulti({0.56f,0.0f});
		sprite->SetScale(3.742690f,3.75f);
		montanhas_frente->AddComponent(sprite);
		montanhas_frente->box.pos = {1280.0f * i,0.0f};
		AddObject(montanhas_frente);
	}



	GameObject* grama_baixo;
	for(int i = 0; i < 2; ++i) {
		grama_baixo = new GameObject();
		sprite = new Sprite(*grama_baixo, "assets/img/cenario3/grama morta.png");
		sprite->SetCamMulti({0.7f,0.3f});
		sprite->SetScale(3.742690f,3.75f);
		grama_baixo->AddComponent(sprite);
		grama_baixo->box.pos = {1280.0f * i,0.0f};
		AddObject(grama_baixo);
	}
}

void Fase3::LoadCenarioFrente() {

}

void Fase3::LoadCenarioAtras() {

}


void Fase3::Update(float dt) {
    Camera::Update(dt);
	UpdateArray(dt);
	fadeIn->Update(dt);
	fadeOut->Update(dt);
	auto& playerStatus = Game::GetInstance().playerStatus;
    static bool first = true;
    if(playerStatus.player->box.centro().x < 0 && first){
        ((FadeOut*)fadeOut->GetComponent("FadeOut"))->Begin();
        first = false;
    }
    if(!first && ((FadeOut*)fadeOut->GetComponent("FadeOut"))->timer.Get() > 0.25f) {
        first = true;
        popRequested = true;
        Game::GetInstance().Push(new TransState(2));
    }
	playerStatus.player->Update(dt);
	playerStatus.wisp->Update(dt);
	playerStatus.hud->Update(dt);
	playerStatus.dialogo->Update(dt);

	for(auto& obj : frontArray) {
		obj->Update(dt);
	}

	if (InputManager::GetInstance().KeyPress(ESCAPE_KEY) || InputManager::GetInstance().QuitRequested()) {
		quitRequested = true;
	}

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

void Fase3::Render() {
    RenderArray();
	auto& playerStatus = Game::GetInstance().playerStatus;
	playerStatus.player->Render();
	playerStatus.wisp->Render();
	playerStatus.hud->Render();
	playerStatus.dialogo->Render();
	for(auto& obj : frontArray){
		obj->Render();
	}
	fadeIn->Render();
	fadeOut->Render();
}

	
void Fase3::Start() {
    LoadAssets();
	StartArray();
	((FadeIn*)fadeIn->GetComponent("FadeIn"))->Begin();
}

void Fase3::Pause() {

}

void Fase3::Resume() {

}
